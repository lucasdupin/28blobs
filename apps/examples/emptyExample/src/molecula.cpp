/*
 *  molecula.cpp
 *  openFrameworks
 *
 *  Created by Marcelo Arteiro on 04/06/09.
 *  Copyright 2009 Casa. All rights reserved.
 *
 */

#include "molecula.h"
molecula::molecula(){
	tamanho=ofRandom(2,15);
	posicao.x=ofRandom(50,ofGetWidth()-50);
	posicao.y=ofRandom(50,ofGetWidth()-50);
	
	velocidade.x=ofRandom(-2, 2);
	velocidade.y=ofRandom(-2, 2);
	
	cor.r=int(ofRandom(0,255));
	cor.g=int(ofRandom(0,255));
	cor.b=int(ofRandom(0,255));
	
}

void molecula::update(){
	
}

void molecula::draw(){
	if(posicao.x+(tamanho/2)>ofGetWidth() || posicao.x-(tamanho/2)<0)
	   velocidade.x*=-1;
	posicao.x+=velocidade.x;
	
	if(posicao.y+(tamanho/2)>ofGetHeight() || posicao.y-(tamanho/2)<0)
	   velocidade.y*=-1;
	posicao.y+=velocidade.y;
		
	ofSetColor(cor.r, cor.g, cor.b);
	ofCircle(posicao.x,posicao.y,tamanho);
}
