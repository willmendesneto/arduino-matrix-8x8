#include <font.h>
#include <LEDMatrix.h>
#include <Thermistor.h>
#include <IRremote.h>

// usado para definir pino para o sensor infravermelho
int RECV_PIN = 19;
IRrecv irrecv(RECV_PIN);
decode_results results;


//  usado para definir os pinos usados no sensor ultrasonico
// # Connection:
// #       SENSOR ULTRA-SONICO  -> ARDUINO
// #       Pin 1 VCC (URM V3.2) -> VCC (Arduino)
// #       Pin 2 GND (URM V3.2) -> GND (Arduino)
// #       Pin 4 PWM (URM V3.2) -> Pin 3 (Arduino)
// #       Pin 6 COMP/TRIG (URM V3.2) -> Pin 5 (Arduino)
// #
int URPWM = 3; // PWM Output 0－25000US，Every 50US represent 1cm
int URTRIG = 5; // PWM trigger pin

// usado para definir pino para o sensor de temperatura
Thermistor temp(17);

uint8_t EnPwmCmd[4] = {0x44, 0x02, 0xbb, 0x01};    // distance measure command
//  funcao para passar valor inicial para o sensor ultrasonico
unsigned int distance = 0;

// usado para imprimir na matriz
LEDMatrix mymatriz('C');

void setup(){
    Serial.begin(9600);
    
    //  Chamando funcao usada para o sensor infravermelho
    pinMode(2, OUTPUT); // 5v do InfraRed.
    digitalWrite(2, HIGH);  // 5v do InfraRed.
    analogWrite(18, 0); // GND do InfraRed.
    
    irrecv.enableIRIn(); // Start the receiver
    
    //  Chamando funcao usada para o sensor ultrasonico
    PWM_Mode_Setup();
     
    
    //  Inicializa a matriz de led
    mymatriz.begin(10, 11, 12, 13, 14, 15, 4, 6, 7, 8, 9);
}

void loop(){ 
  
  /**
   * Ao apertar o controle, o programa vai responder da seguinte forma:
   *   Se clicar "1", vai ser habilitado o sensor ultrasonico
   *   Se clicar "2", vai ser habilitado o sensor de temperatura
   *   Se clicar "3", vai ser habilitado o sensor de luminosidade
   *   
   *   Senao sera impresso o numero que foi clicado 
   */
  if (irrecv.decode(&results)) {
    String stringOne =  String(results.value, HEX);   
    if( stringOne == "910"){
      Serial.println('0');
      printValue("0");
    }else if ( stringOne == "10"){
      Serial.println('1');
      
      //  SENSOR ULTRASONICO
      //String distance = PWM_Mode();
      //printValue(distance);    
        
    }else if ( stringOne == "e13dda28"){
      Serial.println('2');
      
      //  SENSOR ULTRASONICO
      String distance = PWM_Mode();
      printValue(distance); 
      
      //  SENSOR TEMPERATURA
      //String temperatura = Termistor();
      //printValue(temperatura);
      
    }else if ( stringOne == "410"){
      Serial.println('3');
      
      //  SENSOR LUMINOSIDADE
      String luminosidade = getValueSensorLDR(16);
      printValue(luminosidade);
      
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
     
  delay(50);
  
  
        //  SENSOR ULTRASONICO
        //String distance = PWM_Mode();
        //printValue(distance);    
        
        //  SENSOR TEMPERATURA
        //String temperatura = Termistor();
        //printValue(temperatura);
        
        //  SENSOR LUMINOSIDADE
        //String luminosidade = getValueSensorLDR(16);
        //printValue(luminosidade);
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

//  funcao usada para o sensor de luminosidade
String getValueSensorLDR(int numeroPino)
{
  String value = String(analogRead(numeroPino));
  Serial.print(value); 
  Serial.println (" luminosidade");
  return value;
}

//  funcao usada para o sensor ultrasonico
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

//  funcao usada para o sensor ultrasonico
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
  Serial.print(numberPrintable);
  Serial.println("(cm)");
    
  return numberPrintable;
}
