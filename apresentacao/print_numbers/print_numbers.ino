#include <font.h>
#include <LEDMatrix.h>

LEDMatrix mymatriz('C');

char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void setup(){
    Serial.begin(9600);
    mymatriz.begin(10, 11, 12, 13, 14, 15, 4, 6, 7, 8, 9);
}

void loop(){    
    
    for(int i = 0; i < 10; i++) {    
      for(int j = 0; j < 10; j++) {
        mymatriz.printChar( numbers[i], 3, false, 0);
        mymatriz.printChar( numbers[j], 3, false, 3);
        delay(100);
      }
    }
    
    
    //mymatriz.printChar('1', 1, false, 0);
    //mymatriz.printChar( '0', 1, false, 3);
    
    /*
    for(int i = 1; i < 7; i++) {    
      for(int j = 1; j < 7; j++) {
        mymatriz.setDot(i, j, 1);  
        delay(1000);
      }
    }
   */
}

