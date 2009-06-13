#include "Canvas.h"

void Canvas::setup(){
	//My size
	width = settings.getValue("teBlobs:canvas:width", 400);
	height = settings.getValue("teBlobs:canvas:height", 300);
	
	drawThreshold = settings.getValue("teBlobs:canvas:drawThreshold", true);
	
	//My color
	color.r = settings.getValue("teBlobs:application:canvasColor:r",30);
	color.g = settings.getValue("teBlobs:application:canvasColor:g",30);
	color.b = settings.getValue("teBlobs:application:canvasColor:b",30);
	
	//Camera color
	ofColor camBorderColor;
	camBorderColor.r = settings.getValue("teBlobs:application:camera:borderColor:r",30);
	camBorderColor.g = settings.getValue("teBlobs:application:camera:borderColor:g",30);
	camBorderColor.b = settings.getValue("teBlobs:application:camera:borderColor:b",30);
	
	//The blob tracker
	tracker.setListener(this);
	
	//Allocating space for detection images
	background.allocate(width, height);
	canvasColorOutput.allocate(width, height);
	canvasGrayOutput.allocate(width, height);
	diffImage.allocate(width,height);
	pixelGrabber.allocate(width, height, OF_IMAGE_COLOR);
	
	//My cameras
	settings.pushTag("teBlobs");
	settings.pushTag("cameras");
	
	camNumber = settings.getNumTags("camera");
	cameras = new CameraView[camNumber];
	
	cout << "The canvas has " << camNumber << " cameras\n";
	
	//Setting up the cameras
	for(int i=0; i < camNumber; ++i){
		settings.pushTag("camera", i);
		
		cameras[i].setup(settings.getValue("width",320), settings.getValue("height",240), settings.getValue("device",i));
		cameras[i].borderColor = camBorderColor;
		
		settings.popTag();
	}
	
	//Going back to the root of the xml
	settings.popTag();
	settings.popTag();
	
	//Threshold & blur
	threshold = 80;
	blur = settings.getValue("teBlobs:canvas:blur",-1);
	
	//Detection parameters
	minBlobSize = 0;
	maxBlobSize = 1000;
	maxBlobs = 10;
	gui	= ofxGui::Instance(this);
	if(!gui->buildFromXml(OFXGUI_XML))
	{	
		ofxGuiPanel* panel1 = gui->addPanel(kPanel_gui, "Detection Properties", 10, 10, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
		
		panel1->addSlider(kThreshold_slider, "threshold", 110, OFXGUI_SLIDER_HEIGHT, 0, 200, threshold, kofxGui_Display_Int, 0);
		//panel1->addSlider(kBlur_slider, "blur", 110, OFXGUI_SLIDER_HEIGHT, 0, 10, blur, kofxGui_Display_Int, 0);
		panel1->addSlider(kMinBlob_slider, "min blob size", 110, OFXGUI_SLIDER_HEIGHT, 0, 150, minBlobSize, kofxGui_Display_Int, 0);
		panel1->addSlider(kMaxBlob_slider, "max blob size", 110, OFXGUI_SLIDER_HEIGHT, 0, 10000, maxBlobSize, kofxGui_Display_Int, 0);
		panel1->addSlider(kMaxBlobs_slider, "max blobs number", 110, OFXGUI_SLIDER_HEIGHT, 0, 40, maxBlobs, kofxGui_Display_Int, 0);
		
		//	do update while inactive
		gui->forceUpdate(true);
		
		cout << "gui was not loaded by XML, creating it with default values\n";
	}
}

void Canvas::draw(){
	
	glPushMatrix();
	glTranslated(position.x, position.y, 0);
	
	//Black background
	ofFill();
	ofSetColor(0,0,0);
	ofRect(0,0, width, height);
	
	//Drawing the analysis image
	for(int i=camNumber-1; i >= 0; --i){
		cameras[i].drawOutput();
	}
	
	//grabbing screen for detection
	pixelGrabber.grabScreen(position.x,position.y,width,height);
	
	//drawing the cameras
	for(int i=camNumber-1; i >= 0; --i){
		cameras[i].draw();
	}
	
	//Drawing blobs
	ofEnableAlphaBlending();
	ofFill();
	ofSetColor(255,255,255);
	finder.draw(0,0);
	for (vector<ofxCvTrackedBlob>::iterator b = tracker.blobs.begin(); b != tracker.blobs.end(); b++) {

		ofSetColor(color.r,color.g,color.b,100);
		ofCircle(b->centroid.x, b->centroid.y, 10);
		
		ofSetColor(255,255,255,255);
		ofDrawBitmapString(ofToString(b->id), b->centroid.x-5, b->centroid.y-5);
	}
	
	//Draw detection image
	if(drawThreshold){
		glBlendFunc(GL_ONE, GL_ONE);
		diffImage.draw(0,0);
		ofEnableAlphaBlending();
	}
	
	ofDisableAlphaBlending();
	
	//Drawing the canvas limit
	ofSetColor(color.r, color.g, color.b, 255);
	ofNoFill();
	ofRect(0,0, width, height);
	
	//Drawing the GUI
	gui->draw();
	
	glPopMatrix();
}
void Canvas::update(){
	//Updating cameras
	for(int i=0; i < camNumber; ++i){
		cameras[i].update();
	}
	
	//Analysing the image
	canvasColorOutput.setFromPixels(pixelGrabber.getPixels(), width, height);
	canvasGrayOutput = canvasColorOutput;
	diffImage.absDiff(background, canvasGrayOutput);
	if(blur>0)
		diffImage.blurGaussian(blur);
	
	diffImage.threshold(threshold);
	
	finder.findContours(diffImage, minBlobSize, maxBlobSize, maxBlobs, false); //Do not search fo holes
	tracker.trackBlobs(finder.blobs);
}

//--------------------------------------------------------------
void Canvas::keyPressed(int key){
	if(key == 'b' || key == 'B'){
		background = canvasGrayOutput;
		cout << "remebering background\n";
	} else if(key == 'g' || key == 'G'){
		gui->activate(!gui->mIsActive);
	} else if(key == 's' || key == 'S'){
		gui->saveToXml(OFXGUI_XML);
		settings.setValue("teBlobs:canvas:drawThreshold",drawThreshold);
		settings.saveFile("config.xml");
	} else if (key == 't' || key == 'T') {
		drawThreshold = !drawThreshold;
	}
	
	for(int i=0; i < camNumber; ++i){
		cameras[i].keyPressed(key);
	}
}

//--------------------------------------------------------------
void Canvas::keyReleased(int key){
}

//--------------------------------------------------------------
void Canvas::mouseMoved(int x, int y ){
	x-= position.x;
	y-= position.y;
	
	//Did we hit a camera?
	for(int i=0; i < camNumber; ++i){
			cameras[i].mouseMoved(x,y);

	}
}

//--------------------------------------------------------------
void Canvas::mouseDragged(int x, int y, int button){
	x-= position.x;
	y-= position.y;
	
	//Did we hit a camera?
	for(int i=0; i < camNumber; ++i){
			cameras[i].mouseDragged(x,y,button);
	}
	
	gui->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void Canvas::mousePressed(int x, int y, int button){
	x-= position.x;
	y-= position.y;
	
	//Did we hit a camera?
	for(int i=0; i < camNumber; ++i){
			if (cameras[i].mousePressed(x,y,button))
				break; //Only one camera by click
	}
	
	gui->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void Canvas::mouseReleased(int x, int y, int button){
	x-= position.x;
	y-= position.y;
	
	//Did we hit a camera?
	for(int i=0; i < camNumber; ++i){
			cameras[i].mouseReleased(x,y,button);
	}
	
	gui->mouseReleased(x, y, button);
}

void Canvas::handleGui(int parameterId, int task, void* data, int length)
{
	switch(parameterId)
	{
		case kPanel_gui:
			break;
		case kThreshold_slider:
			threshold = *(float*)data;
			break;
		case kBlur_slider:
			blur = *(float*)data;
			break;
		case kMinBlob_slider:
			minBlobSize = *(float*)data;
			break;
		case kMaxBlob_slider:
			maxBlobSize = *(float*)data;
			break;
		case kMaxBlobs_slider:
			maxBlobs = *(float*)data;
			break;
			
	}
	
	cout << "gui data " << *(int*)data << endl;
}

void Canvas::blobOn( int x, int y, int id, int order ) {
    sendOSC("/create", id, x/width, y/height);
}
void Canvas::blobMoved( int x, int y, int id, int order) {
    sendOSC("/update", id, x/width, y/height);	
}
void Canvas::blobOff( int x, int y, int id, int order ) {
    sendOSC("/destroy", id, x/width, y/height);
}