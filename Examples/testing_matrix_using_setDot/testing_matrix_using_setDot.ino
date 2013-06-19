#include <font.h>
#include <LEDMatrix.h>

LEDMatrix mymatriz('C');

void setup(){
    Serial.begin(9600);
    //  LINHAS ->>   0, 1, 2, 19, 4, 18, 6, 7
    //  COLUNAS ->>  8, 9, 10, 11, 12, 14, 15, 16
    //  3 e 5 ->> RESERVADOS PARA O SENSOR ULTRA SONICO
    mymatriz.begin(8, 9, 10, 11, 12, 14, 15, 16, 0, 1, 2, 19, 4, 18, 6, 7);
}

void loop(){    
  /**
   * 
   *
   */
    for(int i = 1; i < 9; i++) {    
      for(int j = 1; j < 9; j++) {
        mymatriz.setDot(i, j, 1);  
        delay(1000);
      }
    }
}

