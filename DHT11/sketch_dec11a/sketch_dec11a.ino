#include "DHT.h"
// khai báo DHT
#define DHTTYPE DHT11
const int DHTPin = 4;

DHT dht(DHTPin, DHTTYPE);
static char celsiusTemp[7];
static char fahrenheitTem[7];
static char humidityTemp[7];

void setup() {
  // put your setup code here, to run once:
  pinMode(D4,OUTPUT);
  
// kết nối DHT11 
Serial.begin(9600);
delay(10);
dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
delay(2000);
float h = dht.readHumidity();
float t = dht.readTemperature();
if(isnan(h)|| isnan(t)){
  delay(500);
  }
  else{
    digitalWrite(D4,LOW);
    delay(2000);
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t temperature: ");
    Serial.print(t);
    Serial.print(" *C\n");
    digitalWrite(D4,HIGH);
    delay(2000);
    }
}
