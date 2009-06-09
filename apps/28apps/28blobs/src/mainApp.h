#ifndef _MAIN_APP
#define _MAIN_APP

#include "ofMain.h"
#include "settings.h"
#include "utils.h"
#include "Canvas.h"

//#include "renderManager.h";

class MainApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		Canvas canvas;

		ofColor textColor;
};

#endif
