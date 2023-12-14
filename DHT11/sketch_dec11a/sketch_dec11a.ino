#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// khai báo DHT
#define DHTTYPE DHT11
const int DHTPin = 4;

// Khai báo wifi
const char* ssid = "BINH";
const char* password = "Binh123456@";

DHT dht(DHTPin, DHTTYPE);
static char celsiusTemp[7];
static char fahrenheitTem[7];
static char humidityTemp[7];

void setup() {
  // put your setup code here, to run once:
  pinMode(D4,OUTPUT);

 // kết nối wifi
WiFi.disconnect();
WiFi.mode(WIFI_STA);
WiFi.begin(ssid,password);

// kết nối DHT11 
Serial.begin(9600);
delay(10);
dht.begin();

while(WiFi.status() != WL_CONNECTED){
  delay(2000);
  Serial.print(".");
}
 Serial.println(WiFi.localIP()); 
}

void loop() {
  // put your main code here, to run repeatedly:
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
