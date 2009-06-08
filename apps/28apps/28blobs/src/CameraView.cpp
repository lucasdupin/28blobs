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
	outputPositions[1].set(0, height, 0);//bottom left
	outputPositions[2].set(width, 0, 0);//top right
	outputPositions[3].set(width, height, 0);
	
	inputPositions[0].set(0, 0);
	inputPositions[1].set(1, 0);
	inputPositions[2].set(0, 1);
	inputPositions[3].set(1, 1);
	
	//Setting up the interface
	fourPointHandle.loadImage("4point.png");
	cropHandle.loadImage("crop.png");
	moveHandle.loadImage("move.png");
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
	ofEndShape();
	ofRect(0,0,width,height);
	
	/*
	 Drawing handlers
	 */
	ofEnableAlphaBlending();
	ofSetColor(255,255,255);
	
	//4 ponit
	ofPushMatrix();
	fourPointHandle.draw(0, 0);
	ofTranslate(width, 0, 0); ofRotateZ(90);
	fourPointHandle.draw(0, 0);
	ofTranslate(height, 0, 0); ofRotateZ(90);
	fourPointHandle.draw(0, 0);
	ofTranslate(width, 0, 0); ofRotateZ(90);
	fourPointHandle.draw(0, 0);
	ofPopMatrix();
	
	
	//crop
	int crX = -cropHandle.width/2; int crY = -cropHandle.height/2;
	ofPushMatrix();
	cropHandle.draw(crX, crY);
	ofTranslate(width, 0, 0); ofRotateZ(90);
	cropHandle.draw(crX, crY);
	ofTranslate(height, 0, 0); ofRotateZ(90);
	cropHandle.draw(crX, crY);
	ofTranslate(width, 0, 0); ofRotateZ(90);
	cropHandle.draw(crX, crY);
	ofPopMatrix();
	
	//Move
	moveHandle.draw(width/2 - moveHandle.width/2, height/2 - moveHandle.height/2);
	
	ofDisableAlphaBlending();
}