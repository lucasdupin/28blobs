#include "cameraView.h"

void CameraView::setup(int w, int h, ofVideoGrabber * camera){
	width = w;
	height = h;
	
	theImage.allocate(width, height, false);
	cameraReference = camera;
}

void CameraView::update(){
	//Updating the texture with the image from the camera
	if(cameraReference->isFrameNew()){
		theImage.swapIn();
		cameraReference->draw(0, 0, width, height);
		theImage.swapOut();
	}
}

void CameraView::draw(){
	theImage.draw();
}