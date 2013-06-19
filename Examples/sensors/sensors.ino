/**
 *  IFBA - Instituto Federal de Educação, Ciência e Tecnologia da Bahia - IFBA
 *  
 *  A example using ultra sonic sensor for print numeric informations in matrix LED 8x8
 *
 *  INFRA RED EXAMPLE
 */

#include <font.h>
#include <LEDMatrix.h>
#include <IRremote.h>

/**
 *  GLOBAL PARAMETERS INFRA RED
 */
int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;

//  Instance the constructor
LEDMatrix mymatriz('C');

void setup(){
    Serial.begin(9600);
    
    mymatriz.begin(8, 9, 10, 11, 12, 14, 15, 16, 0, 1, 2, 19, 4, 18, 6, 7);
    irrecv.enableIRIn(); // Start the receiver
}


void loop(){
  //printValue(getValueSensorInfraRed());
  
  if (irrecv.decode(&results)) {
    String stringOne =  String(results.value, HEX);   
    if( stringOne == "910"){
      Serial.println('0');
      printValue("0");
    }else if ( stringOne == "10"){
      Serial.println('1');
      printValue("1");
    }else if ( stringOne == "810"){
      Serial.println('2');
      printValue("2");
    }else if ( stringOne == "410"){
      Serial.println('3');
      printValue("3");
    }else if ( stringOne == "c10"){
      Serial.println('4');
      printValue("4");
    }else if ( stringOne == "210"){
      Serial.println('5');
      printValue("5");
    }else if ( stringOne == "a10"){
      Serial.println('6');
      printValue("6");
    }else if ( stringOne == "610"){
      Serial.println('7');
      printValue("7");
    }else if ( stringOne == "e10"){
      Serial.println('8');
      printValue("8");
    }else if ( stringOne == "110"){
      Serial.println('9');
      printValue("9");
    }
    
    irrecv.resume(); // Receive the next value
  }  
     
  delay(100);
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
