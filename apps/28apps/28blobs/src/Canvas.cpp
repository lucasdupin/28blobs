#include "Canvas.h"

void Canvas::setup(){
	color.r = settings.getValue("teBlobs:application:canvasColor:r",30);
	color.g = settings.getValue("teBlobs:application:canvasColor:g",30);
	color.b = settings.getValue("teBlobs:application:canvasColor:b",30);
	
	width = settings.getValue("teBlobs:canvas:width", 400);
	height = settings.getValue("teBlobs:canvas:height", 300);
}

void Canvas::draw(){
	glPushMatrix();
	glTranslated(position.x, position.y, 0);
	
	//Drawing the canvas limit
	ofSetColor(color.r, color.g, color.b);
	ofNoFill();
	ofRect(0,0, width, height);
	
	glPopMatrix();
}
void Canvas::update(){
	
}