#include <font.h>
#include <LEDMatrix.h>

LEDMatrix mymatriz('C');

char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void setup(){
    Serial.begin(9600);
    mymatriz.begin(8, 9, 10, 11, 12, 14, 15, 16, 0, 1, 2, 3, 4, 5, 6, 7);
}

void loop(){    
    
    for(int i = 0; i < 10; i++) {    
      for(int j = 0; j < 10; j++) {
        mymatriz.printChar( numbers[j], 1, false, 0);
        mymatriz.printChar( numbers[i], 1, false, 4);
        delay(50);
      }
    }
    
}

