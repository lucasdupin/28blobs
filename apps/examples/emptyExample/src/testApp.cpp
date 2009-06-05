#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	for(int i=0; i<NUM_MOLECULAS; i++){
		molecula m;
		m.posicao.x;
		bolas[i]= m;
	}
	
	ofBackground(255,255,255);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_SRC_COLOR);
	
	for(int i=0; i<NUM_MOLECULAS; i++){
		bolas[i].draw();
	}
	glDisable(GL_BLEND);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

