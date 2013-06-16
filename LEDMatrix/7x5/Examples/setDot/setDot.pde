#include <font.h>
#include <LEDMatrix.h>

LEDMatrix mymatriz('C');

void setup(){
mymatriz.begin(7,6,5,4,3,8,9,10,11,12,13,2);
}
void loop(){
mymatriz.setDot(1, 4, 1);
}
}