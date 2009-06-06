#ifndef _CANVAS
#define _CANVAS

#include "ofMain.h";
#include "settings.h";

class Canvas{
	
public:
	void virtual setup();
	void virtual update();
	void virtual draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	//Transformation
	int width;
	int height;
	ofPoint position;
	
	//Attributes
	ofColor color;
	
};

#endif