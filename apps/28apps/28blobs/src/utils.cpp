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