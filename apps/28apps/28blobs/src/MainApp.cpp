#include "MainApp.h"

//--------------------------------------------------------------
void MainApp::setup(){
	ofBackground(0,0,0);
	
	//Loading settings
	if(!settings.loadFile("config.xml"))
		cout << "failed to load config.xml";
	
	//Setup
	canvas.setup();
	
	windowResized(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void MainApp::update(){
	canvas.update();
}

//--------------------------------------------------------------
void MainApp::draw(){
	canvas.draw();
}

//--------------------------------------------------------------
void MainApp::keyPressed(int key){
}

//--------------------------------------------------------------
void MainApp::keyReleased(int key){
	//Set to fullscreen?
	if(key == 'f'){
		ofSetFullscreen(!ofGetWindowMode());
	}
}

//--------------------------------------------------------------
void MainApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void MainApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void MainApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void MainApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void MainApp::windowResized(int w, int h){

	//Canvas align
	canvas.position.x = (w - canvas.width)/2;
	canvas.position.y = (h - canvas.height)/2;
}

