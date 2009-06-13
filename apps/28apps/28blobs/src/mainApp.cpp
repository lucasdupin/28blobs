/*
 Copyright (c) 2009 sala28 - Lucas Dupin
 
 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MainApp.h"

//--------------------------------------------------------------
void MainApp::setup(){
	
	//Loading settings
	if(!settings.loadFile("config.xml"))
		cout << "failed to load config.xml";
	
	//Text color
	//My color
	textColor.r = settings.getValue("teBlobs:application:textColor:r",30);
	textColor.g = settings.getValue("teBlobs:application:textColor:g",30);
	textColor.b = settings.getValue("teBlobs:application:textColor:b",30);
	
	//OSC
	setupOSC(settings.getValue("teBlobs:osc:ip","localhost"), settings.getValue("teBlobs:osc:port",8888));
	
	//Background
	background.loadImage("assets/background.png");
	
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
	ofSetColor(255,255,255);
	background.draw(0,0,ofGetWidth(), ofGetHeight());
	
	ofSetColor(textColor.r, textColor.g, textColor.b);
	ofDrawBitmapString(ofToString(ofGetFrameRate(), 0) + "FPS, F to toggle fullscreen, B for background or G for gui, S to save, V to show hidden cameras, T for threshold", 10, ofGetHeight()-15);
	
	canvas.draw();
}

//--------------------------------------------------------------
void MainApp::keyPressed(int key){
	canvas.keyPressed(key);
}

//--------------------------------------------------------------
void MainApp::keyReleased(int key){
	//Set to fullscreen?
	if(key == 'f' || key == 'F'){
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

