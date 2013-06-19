/**
 *  IFBA - Instituto Federal de EducaÃ§Ã£o, CiÃªncia e Tecnologia da Bahia - IFBA
 *  
 *  A example using ultra sonic sensor for print numeric informations in matrix LED 8x8
 */

#include <font.h>
#include <LEDMatrix.h>


//  Instance the constructor
LEDMatrix mymatriz('C');

void setup(){
    Serial.begin(9600);
    mymatriz.begin(8, 9, 10, 11, 12, 14, 15, 16, 0, 1, 2, 19, 4, 18, 6, 7);
}

void loop(){    
   
  String temperatura = Termistor(17);
  Serial.println(temperatura);
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

String Termistor (int RawADC)
{
  int Temp;
  Temp = log(((10240000/RawADC) - 10000)); // Considerando resistÃªncia de 10K
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp ); 
  // EquaÃ§Ã£o de Steinhart-Hart para o termistor - temperatura em Kelvin
  
  Temp = Temp - 273.15; // Converte Kelvin para Celsius 
  
  //  Initial message in serial
  Serial.print(Temp); // Exibe temperatura em Celsius 
  Serial.println (" graus Celsius");
   
  //  Printing the values in matrix
  String numberPrintable = String(Temp);
  
  return numberPrintable;
}
