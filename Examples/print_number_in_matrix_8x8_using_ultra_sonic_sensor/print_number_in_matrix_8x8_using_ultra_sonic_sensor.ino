/**
 *  IFBA - Instituto Federal de Educação, Ciência e Tecnologia da Bahia - IFBA
 *  
 *  A example using ultra sonic sensor for print numeric informations in matrix LED 8x8
 */

#include <font.h>
#include <LEDMatrix.h>


// # Connection:
// #       SENSOR ULTRA-SONICO  -> ARDUINO
// #       Pin 1 VCC (URM V3.2) -> VCC (Arduino)
// #       Pin 2 GND (URM V3.2) -> GND (Arduino)
// #       Pin 4 PWM (URM V3.2) -> Pin 0 (Arduino)
// #       Pin 6 COMP/TRIG (URM V3.2) -> Pin 1 (Arduino)
// #
int URPWM = 3; // PWM Output 0－25000US，Every 50US represent 1cm
int URTRIG = 5; // PWM trigger pin

unsigned int distance = 0;
// distance measure command
uint8_t EnPwmCmd[4] = {0x44, 0x02, 0xbb, 0x01};    
//  Instance the constructor
LEDMatrix mymatriz('C');

void setup(){
    Serial.begin(9600);
    PWM_Mode_Setup();
    mymatriz.begin(8, 9, 10, 11, 12, 14, 15, 16, 0, 1, 2, 3, 4, 5, 6, 7);
}

void loop(){    
      
   PWM_Mode();
   delay(20);
}

/**
 *  ULTRA SONIC SENSOR
 *
 *  This code is a example using ultra sonic sensor
 *  for print collected informations in matrix 8x8
 */
void PWM_Mode_Setup(){
  pinMode(URTRIG, OUTPUT);                     // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG, HIGH);                  // Set to HIGH

  pinMode(URPWM, INPUT);                      // Sending Enable PWM mode command

  for(int i=0; i<4; i++){
      Serial.write(EnPwmCmd[i]);
  }
  //  Initial message in serial
  Serial.println("\n\nThen we go!!\n");
}

void PWM_Mode(){                              // a low pull on pin COMP/TRIG  triggering a sensor reading
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);               // reading Pin PWM will output pulses

  unsigned long DistanceMeasured = pulseIn(URPWM, LOW);

  if(DistanceMeasured == 50000){              // the reading is invalid.
    Serial.print("Distancia invalida!");
  } else {
    distance = DistanceMeasured / 50;           // every 50us low level stands for 1cm
  }
  
  numberPrintable = distance;
  
  if( distance < 100){
    
    String numberPrintable = String(distance);
    
    //  Printing values in serial
    Serial.println("Distance (cm)");
    Serial.print("Number returned: ");
    Serial.println(numberPrintable);
    Serial.print("First number: ");
    Serial.println(numberPrintable.substring(0, 1));
    Serial.print("Second number: ");
    Serial.println(numberPrintable.substring(2, 1));
    
    //  Printing the values in matrix
    mymatriz.printChar( numberPrintable.substring(0, 1), 1, false, 0);
    mymatriz.printChar( numberPrintable.substring(2, 1), 1, false, 4);
    delay(50);
    
  } else {
    Serial.println("Distancia maior que 99 cm.");
    mymatriz.printChar( "X", 1, false, 4);
  }
}


