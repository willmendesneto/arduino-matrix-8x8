#include <math.h> 

 void setup()
 {
   Serial.begin(9600); //Troque pela sua porta serial
 }
 
 void loop()
 { 
   Termistor(0);
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
