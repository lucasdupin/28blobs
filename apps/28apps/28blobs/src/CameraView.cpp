#include "cameraView.h"

void CameraView::setup(int w, int h, int cameraID){
	
	//Initializing the videoGrabber
	camera.setVerbose(true);
	camera.setDeviceID(cameraID);
	camera.initGrabber(w,h);
	
	//width and height variables
	width = camera.getWidth();
	height = camera.getHeight();
	
	//The distortion texture
	theImage.allocate(width, height, false);
	
	//setting the input and output points (distorion)
	//of the texture
	outputPositions[0].set(0, 0, 0);//top left
	outputPositions[1].set(width, 0, 0);//bottom left
	outputPositions[2].set(width, height, 0);//top right
	outputPositions[3].set(0, height, 0);
	
	inputPositions[0].set(0, 0);
	inputPositions[1].set(1, 0);
	inputPositions[2].set(1, 1);
	inputPositions[3].set(0, 1);
	
	//Setting up the interface
	fourPointHandle.loadImage("4point.png");
	cropHandle.loadImage("crop.png");
	moveHandle.loadImage("move.png");
	
	cropHandle.setAnchorPercent(.5, .5);
	fourPointHandle.setAnchorPercent(.5, .5);
	
	//No point selected
	inputId = outputId = -1;
}

void CameraView::update(){
	
	//Updating the texture with the image from the camera
	camera.grabFrame();
	//Do we have a new frame? (performance)
	if(camera.isFrameNew()){
		//Goingo to the FBO
		theImage.swapIn();
		theImage.setupScreenForMe();
		
		//Writing the image
		ofSetColor(255,255,255);
		camera.draw(0, 0, width, height);
		
		//Exiting the FBO
		theImage.swapOut();
		theImage.setupScreenForThem();
	}
}

void CameraView::draw(){
	ofPushMatrix();
	ofTranslate(position.x, position.y, position.z);
	
	//Drawing the image
	ofSetColor(255,255,255);
	theImage.setPoints(inputPositions, outputPositions);
	theImage.draw();
	//theImage.draw(0,0,width,height);
	
	//Drawing the border
	ofSetColor(borderColor.r, borderColor.g, borderColor.b);
	ofNoFill();
	ofBeginShape();
	for(int i=0; i<4; i++)
		ofVertex(outputPositions[i].x, outputPositions[i].y);
	ofEndShape(true);
	
	/*
	 Drawing handlers
	 */
	ofEnableAlphaBlending();
	ofSetColor(255,255,255);
	
	//4 ponit, crop
	for(int i=0; i<4; i++){
		ofPushMatrix();
		ofTranslate(outputPositions[i].x, outputPositions[i].y, 0);
		ofRotateZ(-90*i);
		fourPointHandle.draw(0, 0);
		ofRotateZ(90*i);
		cropHandle.draw(0, 0);
		ofPopMatrix();
	}

	//Move
	moveHandle.draw(width/2 - moveHandle.width/2, height/2 - moveHandle.height/2);
	
	ofDisableAlphaBlending();
	
	ofPopMatrix();
}

//--------------------------------------------------------------
void CameraView::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void CameraView::mouseDragged(int x, int y, int button){
	x-= position.x;
	y-= position.y;
	
	//Are we dragging an object?
	if(hitObject == &moveHandle){
		cout << "updating position\n";
		position.x = x - moveOffset.x + position.x;
		position.y = y - moveOffset.y + position.y;
		
	//Or a handle?
	} else if (outputId >= 0) {
		outputPositions[outputId].x = x;
		outputPositions[outputId].y = y;
	} else if (inputId >= 0) {
		inputPositions[inputId].x = (x - inputPositions[inputId].x) / width;
		inputPositions[inputId].y = (y - inputPositions[inputId].y) / height;
	}
}

//--------------------------------------------------------------
void CameraView::mousePressed(int x, int y, int button){
	x-=position.x;
	y-=position.y;
	
	//hit the move handle
	if(hitRect(x, y, width/2 - moveHandle.width/2, height/2 - moveHandle.height/2, moveHandle.width, moveHandle.height)){
		hitObject = &moveHandle;
	//any of the 4point handlers?
	} else {
		for(int i=0; i<4; i++){
			if(hitRect(x, y, outputPositions[i].x-cropHandle.width/2, outputPositions[i].y-cropHandle.height/2, cropHandle.width, cropHandle.height)){
				inputId = i;
			}
		}		
		
		if(inputId<0) //Only check output if input was not hitten
		for(int i=0; i<4; i++){
			if(hitRect(x, y, outputPositions[i].x-fourPointHandle.width/2, outputPositions[i].y-fourPointHandle.height/2, fourPointHandle.width, fourPointHandle.height)){
				outputId = i;
			}
		}
	}
	
	moveOffset.x = x;
	moveOffset.y = y;
}

//--------------------------------------------------------------
void CameraView::mouseReleased(int x, int y, int button){
	//Not dragging anything
	hitObject = nil;
	outputId = -1;
	inputId = -1;
}