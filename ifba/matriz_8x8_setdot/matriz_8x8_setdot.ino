#include <font.h>
#include <LEDMatrix.h>

LEDMatrix mymatriz('C');

void setup(){
 mymatriz.begin(8, 9, 10, 11, 12, 14, 15, 16, 0, 1, 2, 3, 4, 5, 6, 7);
}
void loop(){
  mymatriz.printChar('C', 10, false, 0);
}

