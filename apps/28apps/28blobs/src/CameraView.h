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

#ifndef _CAMERA_VIEW
#define _CAMERA_VIEW

#include "ofMain.h"
#include "settings.h"
#include "ofTextureAdv.h"
#include "ofxXmlSettings.h"
#include "utils.h"

class CameraView{
	
public:
	void virtual setup(int w, int h, int cameraID);
	void virtual update();
	void virtual draw();
	
	void virtual drawOutput();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	bool mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	int cameraID;
	ofxXmlSettings cameraSettings;
	
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
	ofImage closeButton;
	
	int static CLOSE_BUTTON_MARGIN;
	bool visible;

	//Objects wich control the interaction
	void* hitObject;
	int outputId;
	int inputId;
	ofPoint moveOffset;
};

#endif