#ifndef _TE_UTILS
#define _TE_UTILS

#include "ofMain.h"
//#include "ofxOsc.h"

//Hit test
bool hitRect(ofPoint * point, ofRectangle * rect);
bool hitRect(int x, int y, int rX, int rY, int rW, int rH);

/*
//OSC
void sendOSC(const char * mensagem, int id, float valor);
extern ofxOscSender oscSender;
 */
#endif