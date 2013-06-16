/*
 *  LEDMatrix.cpp
 *  Biblioteca para exibi��o de caracter em uma Mtriz de leds.
 *  Criado por Tiago H. Melo em 06/03/13.
 *  Licensed under LGPL (free to modify and use as you wish)
 */

#include "LEDMatrix.h"
#include "font.h"
#include "Arduino.h"

LEDMatrix::LEDMatrix(bool mode){
if(mode){
Mode = 1;
}else{
Mode = 0;
}
}

void LEDMatrix::begin(short int C1,short int C2,short int C3,short int C4,short int C5,short int L1,short int L2,short int L3,short int L4,short int L5,short int L6,short int L7){
colunas[0] = C1;
colunas[1] = C2;
colunas[2] = C3;
colunas[3] = C4;
colunas[4] = C5;
linhas[0] = L1;
linhas[1] = L2;
linhas[2] = L3;
linhas[3] = L4;
linhas[4] = L5;
linhas[5] = L6;
linhas[6] = L7;

for(short i=0; i<5;i++){
  pinMode(colunas[i], OUTPUT);
}

for(short i=0; i<7;i++){
  pinMode(linhas[i], OUTPUT);
}
}

void LEDMatrix::setDot(short col, short row, short onOff){
if(Mode){
for(int i=1;i<=5;i++){
    if(i==col) digitalWrite(colunas[i-1], !onOff);
    else digitalWrite(colunas[i-1], HIGH);
  }
  
  for(int i=1; i<=7;i++){
   if(i==row) digitalWrite(linhas[i-1], HIGH);
  else digitalWrite(linhas[i-1], LOW); 
  }
}else{
for(int i=1;i<=5;i++){
    if(i==col) digitalWrite(colunas[i-1], onOff);
    else digitalWrite(colunas[i-1], LOW);
  }
  
  for(int i=1; i<=7;i++){
   if(i==row) digitalWrite(linhas[i-1], LOW);
  else digitalWrite(linhas[i-1], HIGH); 
  }
}
}

void LEDMatrix::printChar(short int caracter, short int duration, bool invert, short int shift){
int cnt = 0;
short num_col;	
  while(cnt < duration){
  for(int i=0; i<7; i++){
   for(int j=0; j<5; j++){
    
	num_col = (j+1) + shift;
	if(num_col>5) num_col = num_col - 5;
	
	if(!invert) setDot(num_col, i+1, (Font[caracter][6 - i]>>(4 - j))&0x01);
    else	setDot(num_col, i+1, !((Font[caracter][6 - i]>>(4 - j))&0x01));
	
	delay(1);
   } 
  }
  cnt++;
  }
}

void LEDMatrix::printCustomChar(unsigned char *caracter, short int duration, bool invert,short int shift){
int cnt = 0;
short num_col;
  while(cnt < duration){
  for(int i=0; i<7; i++){
   for(int j=0; j<5; j++){
    
	num_col = (j+1) + shift;
	if(num_col>5) num_col = num_col - 5;
	
	if(!invert) setDot(j+1, i+1, (caracter[6-i]>>(4-j))&0x01);
	else setDot(j+1, i+1, !((caracter[6-i]>>(4-j))&0x01));
	
	delay(1);
   } 
  }
  cnt++;
  }
}