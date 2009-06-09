#include "MainApp.h"

//--------------------------------------------------------------
void MainApp::setup(){
	ofBackground(0,0,0);
	
	//Loading settings
	if(!settings.loadFile("config.xml"))
		cout << "failed to load config.xml";
	
	//OSC
	setupOSC(settings.getValue("teBlobs:osc:ip","localhost"), settings.getValue("teBlobs:osc:port",8888));
	
	//Setup
	canvas.setup();
	
	windowResized(ofGetWidth(), ofGetHeight());
	
//	rmTest.allocateForNScreens(1, 700, 500);
}

//--------------------------------------------------------------
void MainApp::update(){
	canvas.update();
}

//--------------------------------------------------------------
void MainApp::draw(){
	ofSetColor(255,255,255);
	ofDrawBitmapString(ofToString(ofGetFrameRate(), 0), 10, 20);
	
	canvas.draw();
}

//--------------------------------------------------------------
void MainApp::keyPressed(int key){
	canvas.keyPressed(key);
}

//--------------------------------------------------------------
void MainApp::keyReleased(int key){
	//Set to fullscreen?
	if(key == 'f'){
		ofSetFullscreen(!ofGetWindowMode());
	}
	
	canvas.keyReleased(key);
}

//--------------------------------------------------------------
void MainApp::mouseMoved(int x, int y ){
	canvas.mouseMoved(x, y);
}

//--------------------------------------------------------------
void MainApp::mouseDragged(int x, int y, int button){
	canvas.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void MainApp::mousePressed(int x, int y, int button){
	canvas.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void MainApp::mouseReleased(int x, int y, int button){
	canvas.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void MainApp::windowResized(int w, int h){

	//Canvas align
	canvas.position.x = (w - canvas.width)/2;
	canvas.position.y = (h - canvas.height)/2;
}

