#include <font.h>
#include <LEDMatrix.h>

LEDMatrix mymatriz('C');

unsigned char Coracao[7] = {0B00000,
                            0B01010,
                            0B11111,
                            0B11111,
                            0B01110,
                            0B00100,
                            0B00000,
                            };

void setup(){
mymatriz.begin(7,6,5,4,3,8,9,10,11,12,13,2)
}

short shift=0;

void loop(){
mymatriz.printCustomChar(Coracao, 10, 0, shift);
shift++;
if(shift>=5) shift = 0;
}