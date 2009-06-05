#ifndef _TEST_APP
#define _TEST_APP

#define NUM_MOLECULAS 5000


#include "ofMain.h";
#include "molecula.h";


class testApp : public ofBaseApp{

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
		
		molecula bolas[NUM_MOLECULAS];
};

#endif
