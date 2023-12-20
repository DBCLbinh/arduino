#include <SoftwareSerial.h>
void setup() {
  Serial.begin(9600); 
}

void loop() {
  if(Serial.available()){
    String RxBuffer = "";
    while(Serial.available()){
      RxBuffer = Serial.readString();
      }
    Serial.println(RxBuffer);
    
    }
}
