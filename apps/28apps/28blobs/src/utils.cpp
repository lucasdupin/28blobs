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

#include "utils.h";
bool hitRect(ofPoint point, ofRectangle rect){
	//cout << "point " << point.x << "," << point.y << " rect " << rect.x << "," << rect.y << "," << rect.width << "," << rect.height << endl;
	return hitRect(point.x, point.y, rect.x, rect.y, rect.width, rect.height);
}

bool hitRect(int x, int y, int rX, int rY, int rW, int rH){
	
	return (x > rX && x < rX + rW &&
			y > rY && y < rY + rH);
	
	
}

ofxOscSender oscSender;
void setupOSC(std::string ip, int port){
	cout << "OSC set up at: " << ip << ":" << port << endl;
	oscSender.setup(ip, port);
}
void sendOSC(const char * mensagem, int id, float x, float y){
	ofxOscMessage msg;
	msg.setAddress(mensagem);
	msg.addIntArg(id);
	msg.addFloatArg(x);
	msg.addFloatArg(y);
	
	oscSender.sendMessage(msg);
}