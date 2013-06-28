/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 5;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    String stringOne =  String(results.value, HEX);   
    if( stringOne == "910"){
      Serial.println('0');
    }else if ( stringOne == "10"){
      Serial.println('1');
    }else if ( stringOne == "810"){
      Serial.println('2');
    }else if ( stringOne == "410"){
      Serial.println('3');
    }else if ( stringOne == "c10"){
      Serial.println('4');
    }else if ( stringOne == "210"){
      Serial.println('5');
    }else if ( stringOne == "a10"){
      Serial.println('6');
    }else if ( stringOne == "610"){
      Serial.println('7');
    }else if ( stringOne == "e10"){
      Serial.println('8');
    }else if ( stringOne == "110"){
      Serial.println('9');
    }
    
    irrecv.resume(); // Receive the next value
  }
}
