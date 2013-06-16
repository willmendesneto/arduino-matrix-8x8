/*
 *  String substring()
 *
 *  Examples of how to use substring in a String
 *  Based in our task for activity at IFBA
 */

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // send an intro:
  Serial.println("\n\nString  substring():");
  Serial.println();
}

void loop() {
  // Set up a String:
  String stringOne = String(93);
  Serial.print(stringOne);
  Serial.print(", ");
  
  Serial.print(stringOne.substring(0, 1));
  Serial.print(", ");
  Serial.println(stringOne.substring(2, 1));

  // do nothing while true:
  while(true);
}
