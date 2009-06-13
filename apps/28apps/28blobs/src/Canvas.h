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

#ifndef _CANVAS
#define _CANVAS

#include "ofMain.h"
#include "CameraView.h"
#include "settings.h"
#include "ofxCvBlobTracker.h"
#include "ofxCvMain.h"
#include "ofxGui.h"

class Canvas: public ofxCvBlobListener, public ofxGuiListener{
	enum{
		kPanel_gui,
		kThreshold_slider,
		kBlur_slider,
		kMinBlob_slider,
		kMaxBlob_slider,
		kMaxBlobs_slider
	};
	
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
	
	//Tracking objects
	ofxCvBlobTracker tracker;
	ofxCvContourFinder finder;
	ofxCvGrayscaleImage background; //Background for diff
	ofxCvColorImage canvasColorOutput; //Used for image convertion
	ofxCvGrayscaleImage canvasGrayOutput; //Image converted for analysis
	ofxCvGrayscaleImage diffImage; //Image after diff
	ofImage pixelGrabber; //To grab screen pixels
	
	int minBlobSize;
	int maxBlobSize;
	int maxBlobs;
	
	int threshold;
	int blur;
	
	//Transformation
	int width;
	int height;
	ofPoint position;
	
	//Attributes
	ofColor color;
	
	CameraView * cameras;
	int camNumber;
	
	ofxGui *gui;
	void		handleGui(int parameterId, int task, void* data, int length);
	
	bool drawThreshold;

};

#endif