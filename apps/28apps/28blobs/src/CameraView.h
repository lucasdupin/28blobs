#ifndef _CAMERA_VIEW
#define _CAMERA_VIEW

#include "ofMain.h";
#include "settings.h";
#include "ofTextureAdv.h";

class CameraView{
	
public:
	void virtual setup(int w, int h, int cameraID);
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
	ofPoint position;
	int width;
	int height;
	
	//Image
	ofTextureAdv theImage;
	ofVideoGrabber camera;
	
	//Distortion
	ofPoint outputPositions[4];
	ofPoint inputPositions[4];
	
	//Appearence
	ofColor borderColor;
	ofImage fourPointHandle;
	ofImage cropHandle;
	ofImage moveHandle;
};

#endif