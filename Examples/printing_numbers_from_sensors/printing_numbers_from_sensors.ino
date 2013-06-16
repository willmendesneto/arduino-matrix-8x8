/**
 *  IFBA - Instituto Federal de Educação, Ciência e Tecnologia da Bahia - IFBA
 *  
 *  A example using ultra sonic sensor for print numeric informations in matrix LED 8x8
 */

#include <font.h>
#include <LEDMatrix.h>
#include <Thermistor.h>

Thermistor temp(17);

// # Connection:
// #       SENSOR ULTRA-SONICO  -> ARDUINO
// #       Pin 1 VCC (URM V3.2) -> VCC (Arduino)
// #       Pin 2 GND (URM V3.2) -> GND (Arduino)
// #       Pin 4 PWM (URM V3.2) -> Pin 3 (Arduino)
// #       Pin 6 COMP/TRIG (URM V3.2) -> Pin 5 (Arduino)
// #
int URPWM = 3; // PWM Output 0－25000US，Every 50US represent 1cm
int URTRIG = 5; // PWM trigger pin

/**
 *  INTEGER USED FOR SENSOR VERIFICATION
 *  Options:
 *
 *   1 => ULTRA_SONIC
 *   2 => TEMPERATURE
 *   3 => LUMINOSITY
 *   4 => INFRA_RED
 *   default => "99"
 */
const int sensor = 1;

uint8_t EnPwmCmd[4] = {0x44, 0x02, 0xbb, 0x01};    // distance measure command

unsigned int distance = 0;

//  Instance the constructor
LEDMatrix mymatriz('C');

void setup(){
    Serial.begin(9600);
    PWM_Mode_Setup();
    mymatriz.begin(8, 9, 10, 11, 12, 14, 15, 16, 0, 1, 2, 19, 4, 18, 6, 7);
}

void loop(){
    if (sensor == 1) {          //  1 => ULTRA_SONIC
        String distancia = PWM_Mode();
        printValue(distancia);    
    } else if( sensor ==  2 ) { //  2 => TEMPERATURE
        String temperatura = Termistor(17);
        printValue(temperatura);
    } else if(sensor ==  3 ) {  //  3 => LUMINOSITY
        String luminosidade = getValueSensorLDR(17);
        printValue(luminosidade);
    } else if(sensor ==  4 ) {  //  4 => INFRA_RED
        /*   INSERT THE CODE HERE...   */
    } else {                    //  DEFAULT VALUE
        mymatriz.printChar('4', 1, false, 4);
        mymatriz.printChar('4', 1, false, 0);
    }
     
   delay(1);
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

String PWM_Mode(){              

  // a low pull on pin COMP/TRIG  triggering a sensor reading
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);               // reading Pin PWM will output pulses

  unsigned long DistanceMeasured = pulseIn(URPWM, LOW);

  if(DistanceMeasured == 50000){              // the reading is invalid.
    Serial.print("Distancia invalida!");
    distance = 0;
  } else {
    distance = DistanceMeasured / 50;           // every 50us low level stands for 1cm
  }
    
  String numberPrintable = String(distance);
    
  //  Printing values in serial
  Serial.print("Distance Measured: ");
  Serial.println(DistanceMeasured);
  Serial.print("Distance (cm): ");
  Serial.println(distance);
  Serial.print("Number returned: ");
  Serial.println(numberPrintable);
    
  return numberPrintable;
}

//Printing the values in matrix
void printValue(String valor){
  
    char arrayCharNumbers[valor.length() + 1]; //determine size of the array
    int countString = sizeof(arrayCharNumbers) - 1;
    valor.toCharArray(arrayCharNumbers, sizeof(arrayCharNumbers)); //put readStringinto an array
          
    if( countString < 3 )
    {
       if( countString > 1) {          
           mymatriz.printChar(valor[0], 1, false, 4);
           mymatriz.printChar(valor[1], 1, false, 0);
       }else{
           mymatriz.printChar(valor[0], 1, false, 0);
           mymatriz.printChar('0', 1, false, 4);
       }
    }else{
       mymatriz.printChar('X', 1, false, 0);
    }
}

String Termistor (int RawADC)
{
  int valor = temp.getTemp();
  String temperature = String(valor);
  Serial.print("Temperatura no Sensor eh: ");
  Serial.print(temperature);
  Serial.println("*C");
  
  return temperature;
}

String getValueSensorLDR(int numeroPino)
{
  String value = String(analogRead(numeroPino));
  Serial.print(value); 
  Serial.println (" luminosidade");
  return value;
}
