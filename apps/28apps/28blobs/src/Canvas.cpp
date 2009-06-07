#include "Canvas.h"

void Canvas::setup(){
	//My size
	width = settings.getValue("teBlobs:canvas:width", 400);
	height = settings.getValue("teBlobs:canvas:height", 300);
	
	//My color
	color.r = settings.getValue("teBlobs:application:canvasColor:r",30);
	color.g = settings.getValue("teBlobs:application:canvasColor:g",30);
	color.b = settings.getValue("teBlobs:application:canvasColor:b",30);
	
	//My cameras
	settings.pushTag("teBlobs");
	settings.pushTag("cameras");
	
	camNumber = settings.getNumTags("camera");
	cameras = new CameraView[camNumber];
	
	settings.popTag();
	settings.popTag();
	
	//Setting up the cameras
	for(int i=0; i < camNumber; ++i){
		settings.pushTag("camera", i);
		
		cameras[i].position.x = settings.getValue("x", 0);
		cameras[i].position.y = settings.getValue("y", 0);
		
		settings.popTag();
	}
}

void Canvas::draw(){
	glPushMatrix();
	glTranslated(position.x, position.y, 0);
	
	//Drawing the canvas limit
	ofSetColor(color.r, color.g, color.b);
	ofNoFill();
	ofRect(0,0, width, height);
	
	//drawing the cameras
	for(int i=0; i < camNumber; ++i){
		cameras[i].draw();
	}

	glPopMatrix();
}
void Canvas::update(){
	
}