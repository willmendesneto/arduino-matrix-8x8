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
// #       Pin 4 PWM (URM V3.2) -> Pin 3 (Arduino)
// #       Pin 6 COMP/TRIG (URM V3.2) -> Pin 5 (Arduino)
// #
int URPWM = 7; // PWM Output 0－25000US，Every 50US represent 1cm
int URTRIG = 11; // PWM trigger pin

unsigned int distance = 0;
// distance measure command
                        // D,   2,    ?,   1
uint8_t EnPwmCmd[4] = {0x44, 0x02, 0xbb, 0x01};   
//uint8_t EnPwmCmd[4] = {0x46, 0x02, 0xbb, 0x01};  
//  Instance the constructor
LEDMatrix mymatriz('C');

void setup(){
    Serial.begin(9600);
    PWM_Mode_Setup();
    mymatriz.begin(8, 9, 10, 11, 12, 14, 15, 16, 0, 1, 2, 19, 4, 18, 6, 7);
    //mymatriz.begin(8, 9, 10, 11, 12, 14, 15, 16, 0, 1, 2, 3, 4, 5, 6, 7);
}

void loop(){    
   
   //Printing the values in matrix
   //mymatriz.printChar(numberPrintable.substring(0, 1), 1, false, 0);
   
   //String distancia = PWM_Mode();
   String distancia = "10";
   //String temperatura = Termistor(0);
      
   printValue(distancia);
   //printValue(temperatura);
   
   delay(10);
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
      Serial.println("Up!");
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

  if(DistanceMeasured >= 50000){              // the reading is invalid.
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
    
    Serial.println('Valores retornados: ');
    Serial.print('Valor total: ');
    Serial.println(valor);  //so you can see the captured string 
    Serial.print('Valor caracter 1: ');
    Serial.println(valor[0]);
    Serial.print('Valor caracter 2: ');
    Serial.println(valor[1]);
    Serial.println('------------------------------');
  
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
  int Temp;
  Temp = log(((10240000/RawADC) - 10000)); // Considerando resistência de 10K
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp ); 
  // Equação de Steinhart-Hart para o termistor - temperatura em Kelvin
  
  Temp = Temp - 273.15; // Converte Kelvin para Celsius 
  
  //  Initial message in serial
  Serial.print(Temp); // Exibe temperatura em Celsius 
  Serial.println (" graus Celsius");
   
  //  Printing the values in matrix
  String numberPrintable = String(Temp);
  
  return numberPrintable;
}


