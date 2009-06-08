#include "Canvas.h"

void Canvas::setup(){
	//My size
	width = settings.getValue("teBlobs:canvas:width", 400);
	height = settings.getValue("teBlobs:canvas:height", 300);
	
	//My color
	color.r = settings.getValue("teBlobs:application:canvasColor:r",30);
	color.g = settings.getValue("teBlobs:application:canvasColor:g",30);
	color.b = settings.getValue("teBlobs:application:canvasColor:b",30);
	
	//Camera color
	ofColor camBorderColor;
	camBorderColor.r = settings.getValue("teBlobs:application:camera:borderColor:r",30);
	camBorderColor.g = settings.getValue("teBlobs:application:camera:borderColor:g",30);
	camBorderColor.b = settings.getValue("teBlobs:application:camera:borderColor:b",30);
	
	//My cameras
	settings.pushTag("teBlobs");
	settings.pushTag("cameras");
	
	camNumber = settings.getNumTags("camera");
	cameras = new CameraView[camNumber];
	
	//Setting up the cameras
	for(int i=0; i < camNumber; ++i){
		settings.pushTag("camera", i);
		
		cameras[i].setup(settings.getValue("width",320), settings.getValue("height",240), settings.getValue("device",i));
		cameras[i].position.x = settings.getValue("x", 0);
		cameras[i].position.y = settings.getValue("y", 0);
		cameras[i].borderColor = camBorderColor;
		
		settings.popTag();
	}
	
	//Going back to the root of the xml
	settings.popTag();
	settings.popTag();
}

void Canvas::draw(){
	glPushMatrix();
	glTranslated(position.x, position.y, 0);
	
	//drawing the cameras
	for(int i=0; i < camNumber; ++i){
		cameras[i].draw();
	}
	
	//Drawing the canvas limit
	ofSetColor(color.r, color.g, color.b);
	ofNoFill();
	ofRect(0,0, width, height);

	glPopMatrix();
}
void Canvas::update(){
	//Updating cameras
	for(int i=0; i < camNumber; ++i){
		cameras[i].update();
	}
}

//--------------------------------------------------------------
void Canvas::keyPressed(int key){
}

//--------------------------------------------------------------
void Canvas::keyReleased(int key){
}

//--------------------------------------------------------------
void Canvas::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void Canvas::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void Canvas::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void Canvas::mouseReleased(int x, int y, int button){
}