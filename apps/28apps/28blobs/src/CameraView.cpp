#include "cameraView.h"

int CameraView::CLOSE_BUTTON_MARGIN = 20;

void CameraView::setup(int w, int h, int camID){
	
	//Initializing the videoGrabber
	camera.setVerbose(true);
	camera.setDeviceID(camID);
	camera.initGrabber(w,h);
	
	//width and height variables
	width = camera.getWidth();
	height = camera.getHeight();
	cameraID = camID;
	
	//The distortion texture
	theImage.allocate(width, height, false);
	
	cameraSettings.loadFile("camera" + ofToString(cameraID) + ".xml");
	
	//setting the input and output points (distorion)
	//of the texture
	outputPositions[0].set(cameraSettings.getValue("camera:out:x0",0), cameraSettings.getValue("camera:out:y0",0), 0);//top left
	outputPositions[1].set(cameraSettings.getValue("camera:out:x1",width), cameraSettings.getValue("camera:out:y1",0), 0);//bottom left
	outputPositions[2].set(cameraSettings.getValue("camera:out:x2",width), cameraSettings.getValue("camera:out:y2",height), 0);//top right
	outputPositions[3].set(cameraSettings.getValue("camera:out:x3",0), cameraSettings.getValue("camera:out:y3",height), 0);
	
	inputPositions[0].set(cameraSettings.getValue("camera:in:x0",.0), cameraSettings.getValue("camera:in:y0",.0), 0);
	inputPositions[1].set(cameraSettings.getValue("camera:in:x1",1.0), cameraSettings.getValue("camera:in:y1",0.0), 0);
	inputPositions[2].set(cameraSettings.getValue("camera:in:x2",1.0), cameraSettings.getValue("camera:in:y2",1.0), 0);
	inputPositions[3].set(cameraSettings.getValue("camera:in:x3",.0), cameraSettings.getValue("camera:in:y3",1.0), 0);
	
	cout << "point 1 position:" << inputPositions[1].x << "," << inputPositions[1].y << endl;
	
	position.set(cameraSettings.getValue("camera:position:x",10), cameraSettings.getValue("camera:position:y",10), 0);
	
	//Setting up the interface
	fourPointHandle.loadImage("assets/4point.png");
	cropHandle.loadImage("assets/crop.png");
	moveHandle.loadImage("assets/move.png");
	
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
		ofRotateZ(90*i);
		fourPointHandle.draw(0, 0);
		ofRotateZ(-90*i);
		cropHandle.draw(0, 0);
		ofPopMatrix();
	}

	//Move
	moveHandle.draw(width/2 - moveHandle.width/2, height/2 - moveHandle.height/2);
	
	ofDisableAlphaBlending();
	
	ofPopMatrix();
}

void CameraView::drawOutput(){
	ofPushMatrix();
	ofTranslate(position.x, position.y, position.z);
	
	//Drawing the image
	ofSetColor(255,255,255);
	theImage.setPoints(inputPositions, outputPositions);
	theImage.draw();
	
	ofPopMatrix();
}

void CameraView::keyPressed(int key){
	//Salvar
	if(key == 's' || key == 'S'){
		cameraSettings.setValue("camera:out:x0",outputPositions[0].x);cameraSettings.setValue("camera:out:y0",outputPositions[0].y);
		cameraSettings.setValue("camera:out:x1",outputPositions[1].x);cameraSettings.setValue("camera:out:y1",outputPositions[1].y);
		cameraSettings.setValue("camera:out:x2",outputPositions[2].x);cameraSettings.setValue("camera:out:y2",outputPositions[2].y);
		cameraSettings.setValue("camera:out:x3",outputPositions[3].x);cameraSettings.setValue("camera:out:y3",outputPositions[3].y);
		
		cameraSettings.setValue("camera:in:x0",inputPositions[0].x);cameraSettings.setValue("camera:in:y0",inputPositions[0].y);
		cameraSettings.setValue("camera:in:x1",inputPositions[1].x);cameraSettings.setValue("camera:in:y1",inputPositions[1].y);
		cameraSettings.setValue("camera:in:x2",inputPositions[2].x);cameraSettings.setValue("camera:in:y2",inputPositions[2].y);
		cameraSettings.setValue("camera:in:x3",inputPositions[3].x);cameraSettings.setValue("camera:in:y3",inputPositions[3].y);
		
		cameraSettings.setValue("camera:position:x",position.x);cameraSettings.setValue("camera:position:y",position.y);
		
		cameraSettings.saveFile("camera" + ofToString(cameraID) + ".xml");
		
		cout << "config saved for camera: " << cameraID << endl;
	}
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
bool CameraView::mousePressed(int x, int y, int button){
	x-=position.x;
	y-=position.y;
	
	//hit the move handle
	if(hitRect(ofPoint(x, y), ofRectangle(width/2 - moveHandle.width/2, height/2 - moveHandle.height/2, moveHandle.width, moveHandle.height))){
		hitObject = &moveHandle;
		
	//Close button?
	} else if (hitRect(ofPoint(x,x), ofRectangle(width - closeButton.width - CLOSE_BUTTON_MARGIN, CLOSE_BUTTON_MARGIN, closeButton.width, closeButton.height))){
		
	//any of the 4point handlers?
	} else {
		for(int i=0; i<4; i++){
			if(hitRect(ofPoint(x, y), ofRectangle(outputPositions[i].x-cropHandle.width/2, outputPositions[i].y-cropHandle.height/2, cropHandle.width, cropHandle.height))){
				inputId = i;
			}
		}		
		
		if(inputId<0) //Only check output if input was not hitten
		for(int i=0; i<4; i++){
			if(hitRect(ofPoint(x, y), ofRectangle(outputPositions[i].x-fourPointHandle.width/2, outputPositions[i].y-fourPointHandle.height/2, fourPointHandle.width, fourPointHandle.height))){
				outputId = i;
			}
		}
	}
	
	moveOffset.x = x;
	moveOffset.y = y;
	
	//Did we hit something?
	if(hitObject != nil || inputId >= 0 || outputId >= 0)
		return true;
	else
		return false;
}

//--------------------------------------------------------------
void CameraView::mouseReleased(int x, int y, int button){
	//Not dragging anything
	hitObject = nil;
	outputId = -1;
	inputId = -1;
}