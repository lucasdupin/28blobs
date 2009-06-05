#ifndef MALECULA
#define MALECULA
#include "ofMain.h"

class molecula{
	
public:
	molecula();
	void update();
	void draw();
	
	float tamanho;
	ofPoint posicao;
	ofPoint velocidade;
	
	ofColor cor;
};

#endif