#include <font.h>
#include <LEDMatrix.h>
#include <Thermistor.h>

Thermistor temp(17);

LEDMatrix mymatriz('C');

char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void setup(){
    Serial.begin(9600);
    mymatriz.begin(10, 11, 12, 13, 14, 15, 4, 6, 7, 8, 9);
}

void loop(){    
  
        String temperatura = Termistor();
        printValue(temperatura);
}

//Printing the values in matrix
void printValue(String valor){
  
    char arrayCharNumbers[valor.length() + 1]; //determine size of the array
    int countString = sizeof(arrayCharNumbers) - 1;
    valor.toCharArray(arrayCharNumbers, sizeof(arrayCharNumbers)); //put readStringinto an array
          
    if( countString < 3 )
    {
       if( countString > 1) {          
           mymatriz.printChar(valor[0], 1, false, 0);
           mymatriz.printChar(valor[1], 1, false, 3);
       }else{
           mymatriz.printChar('0', 1, false, 0);
           mymatriz.printChar(valor[0], 1, false, 3);
       }
    }else{
       mymatriz.printChar('X', 1, false, 0);
    }
}

//  funcao usada para o sensor de temperatura
String Termistor ()
{
  int valor = temp.getTemp();
  String temperature = String(valor);
  Serial.print("Temperatura no Sensor eh: ");
  Serial.print(temperature);
  Serial.println("*C");
  
  return temperature;
}
