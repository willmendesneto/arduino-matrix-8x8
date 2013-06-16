/*
 *  LEDMatrix.h
 *  Biblioteca para exibição de caracter em uma Mtriz de leds.
 *  Criado por Tiago H. Melo em 06/03/13.
 *  Licensed under LGPL (free to modify and use as you wish)
 */

#ifndef LEDMatrix_h
#define LEDMatrix_h

#include <inttypes.h>

#define C 0
#define L 1


class LEDMatrix{
  public:
    LEDMatrix(bool mode);
	void begin(short int C1,short int C2,short int C3,short int C4,short int C5,short int C6,short int C7,short int C8,short int L1,short int L2,short int L3,short int L4,short int L5,short int L6,short int L7,short int L8);
    void setDot(short col, short row, short onOff);
    void printChar(short int caracter, short int duration, bool invert, short int shift);
    void printCustomChar(unsigned char *caracter, short int duration, bool invert, short int shift);
    
  private: 
    short colunas[8];
	short linhas[8];
	bool Mode;
};

#endif


