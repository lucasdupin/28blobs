#ifndef _TE_UTILS
#define _TE_UTILS

#include "ofMain.h"
bool hitRect(ofPoint * point, ofRectangle * rect);
bool hitRect(int x, int y, int rX, int rY, int rW, int rH);

#endif