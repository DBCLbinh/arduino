// khai báo thư viện
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"
#include <WiFiClientSecure.h>
#include <Wire.h>
#include "DHT.h"
#include <string>

using namespace std;

// khai báo DHT
#define DHTTYPE DHT11
const int DHTPin = 4;
DHT dht(DHTPin, DHTTYPE);
static char celsiusTemp[7];
static char fahrenheitTem[7];
static char humidityTemp[7];


// khai báo wifi và hosting
const char* ssid = "BINH";
const char* password = "Binh123456@";
const char* host = "script.google.com";
// enpoint của api
const char *enpoint = "/macros/s/AKfycbxGBrhcpImHohuwnG2JHIor6wsoVeYMwvcr6K89-LwIIYlu2_q6-YstXnIecySLW5Vw/exec"; // Receiving data from google script address
//https://script.google.com/macros/s/AKfycbxGBrhcpImHohuwnG2JHIor6wsoVeYMwvcr6K89-LwIIYlu2_q6-YstXnIecySLW5Vw/exec


// khai báo cổng https
const int httpsPort = 443;
HTTPSRedirect* client = nullptr;

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi conneted");
}



void loop() {
float h = dht.readHumidity();
float t = dht.readTemperature();

  // phần connet http
  static bool flag = false;
  if (!flag){
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();
    flag = true;
    client->setPrintResponseBody(false);
    client->setContentTypeHeader("application/json");
  }
  if (client != nullptr){
    if (!client->connected()){
      client->connect(host, httpsPort);
    }
  }
  else{
    Serial.println("Error creating client object!");
  }
    
 // Add some delay in between checks
  delay(2000);
 // Kiểm tra dữ liệu vào
if(!isnan(t)){
    // truyền dữ liệu vào
String payload =  "{\"temperature\": \""  + String(t,2) + "\",\"humidity\": \"" + String(h,2) +  "\"}";
Serial.print(payload);

  // gọi API tại đây
  sendData(payload); //--> Calls the sendData Subroutine
  
  }
 

}




void sendData(String payload) {

  if(client->POST(enpoint, host, payload)){ 
    Serial.println("sended data");
  }
  else{
    Serial.println("Error while connecting");
  }

 delay(120000);
  
} 
