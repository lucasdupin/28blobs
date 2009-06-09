#ifndef _CANVAS
#define _CANVAS

#include "ofMain.h"
#include "CameraView.h"
#include "settings.h"
#include "ofxCvBlobTracker.h"

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
	
	//Blob Tracking
	void blobOn( int x, int y, int id, int order );
    void blobMoved( int x, int y, int id, int order );
    void blobOff( int x, int y, int id, int order );
	ofxCvBlobTracker tracker;
	
	//Transformation
	int width;
	int height;
	ofPoint position;
	
	//Attributes
	ofColor color;
	
	CameraView * cameras;
	int camNumber;

};

#endif