#include "utils.h";
bool hitRect(ofPoint * point, ofRectangle * rect){
	
	return hitRect(point->x, point->y, rect->x, rect->y, rect->width, rect->height);
	
	
}

bool hitRect(int x, int y, int rX, int rY, int rW, int rH){
	
	return (x > rX && x < rX + rW &&
			y > rY && y < rY + rH);
	
	
}