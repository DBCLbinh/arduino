// khai báo thư viện
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"
#include <WiFiClientSecure.h>
#include <Wire.h>

// khai báo wifi và hosting
const char* ssid = "BINH";
const char* password = "Binh123456@";
const char* host = "script.google.com";
// enpoint của api
const char *enpoint = "/macros/s/AKfycbyg6Mc0J13As_WiF0iqbgG2Uk-yup0dA4pDACn6M1Rbu5kLc6Otn7_G5cEMet-7_hkH/exec"; // Receiving data from google script address

// truyền dữ liệu vào
String payload =  "{\"name\": \"binh\",\"email\": \"phamvanbinh97hup@gmail.com\"}";

// khai báo cổng https
const int httpsPort = 443;
HTTPSRedirect* client = nullptr;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi conneted");
}

void loop() {
  // phần connet http
  static int error_count = 0;
  static int connect_count = 0;
  const unsigned int MAX_CONNECT = 20;
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
    error_count = 5;
  }
  if (connect_count > MAX_CONNECT){
    connect_count = 0;
    flag = false;
    delete client;
    Serial.println("connect_count = 0");
    return;
  }
  ++connect_count;
  ++connect_count;
    
  if (error_count > 3){
    Serial.println("Halting processor..."); 
    delete client;
    client = nullptr;
    Serial.flush();
    ESP.deepSleep(0);
  }
 // Add some delay in between checks
  delay(2000);
  // gọi API tại đây
  sendData(); //--> Calls the sendData Subroutine
}

// Subroutine for sending data to Google Sheets
void sendData() {
// Publish data to Google Sheets
  if(client->POST(enpoint, host, payload)){ 
    // do stuff here if publish was successful
  }
  else{
    Serial.println("Error while connecting");
  }

  // a delay of several seconds is required before publishing again    
//  delay(2000);
  //----------------------------------------Processing data and sending data
  
} 
