#include <SoftwareSerial.h>
SoftwareSerial mySerial(11,12);
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); 
}

void loop() {
  if(mySerial.available()){
    String RxBuffer = "";
    while(mySerial.available()){
      RxBuffer = mySerial.readString();
      }
    Serial.println(RxBuffer);
    
    }
}
