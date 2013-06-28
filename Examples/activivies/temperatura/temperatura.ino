/**
 *  IFBA - Instituto Federal de Educação, Ciência e Tecnologia da Bahia - IFBA
 *
 *  A example using ultra sonic sensor for print numeric informations in matrix LED 8x8
 */

#include <font.h>
#include <LEDMatrix.h>
#include <Thermistor.h>


/**
 *  GLOBAL PARAMETERS TEMPERATURE
 */
Thermistor temp(19);

//  Instance the constructor
LEDMatrix mymatriz('C');

void setup(){
    Serial.begin(9600);

  mymatriz.begin(8, 9, 10, 11, 12, 14, 15, 16, 17, 13, 2, 3, 4, 18, 6, 7);
}

void loop(){

  int temperature = temp.getTemp();
  //Serial.println("Temperatura no Sensor eh: ");
  Serial.println(temperature);

   String temperatura = Termistor();
   printValue(temperatura);

   delay(1);
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

String Termistor ()
{
  int valor = temp.getTemp();
  String temperature = String(valor);
  Serial.print(temperature);
  Serial.println("*C");

  return temperature;
}

