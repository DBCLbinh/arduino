#include <SoftwareSerial.h>
SoftwareSerial mySerial(3,1);  // RX và TX của mạch
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
