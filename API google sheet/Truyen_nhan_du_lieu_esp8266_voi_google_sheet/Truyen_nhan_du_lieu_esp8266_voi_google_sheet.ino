#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"
#include <WiFiClientSecure.h>
#include <Wire.h>

// Fill ssid and password with your network credentials
const char* ssid = "BINH";
const char* password = "Binh123456@";
const char* host = "script.google.com";
// Replace with your own script id to make server side changes
const char *GScriptId = "AKfycbyl0uSACrNsg_gLsGvtD2gjJCq31aEEg6uMfuKZGjwxuXjKdIWQui1faqwDCMI4y6NM"; // Receiving data from google script address
const char *cellAddress1 = "A2"; //To set moisture value
const char *cellAddress2 = "B2"; // to set temperature value
String payload_base =  "{\"command\": \"insert_row\", \"sheet_name\": \"Sheet1\", \"values\": ";

const int httpsPort = 443;

String url1 = String("/macros/s/") + GScriptId + "/exec?read=" + cellAddress1;
String url2 = String("/macros/s/") + GScriptId + "/exec?read=" + cellAddress2;

String payload = "";
String payload1 = "";
String payload2 = "";
HTTPSRedirect* client = nullptr;
int msvalue = 0; // moisture sensor value 
int mspercent; // moisture value in percentage
float temp; //to store the temperature value
float hum; // to store the humidity value



void setup() {
  Serial.begin(115200);
  Serial.flush();
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  // flush() is needed to print the above (connecting...) message reliably, 
  // in case the wireless connection doesn't go through
  Serial.flush();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(16,OUTPUT);
  digitalWrite(16,LOW);
}

void loop() {
  
  temp = 12;//dht.readTemperature();
  hum = 23;//dht.readHumidity();
  Serial.print("temperature = ");
  Serial.println(temp);
  Serial.print("humidity = ");
  Serial.println(hum);
  msvalue = analogRead(A0);
  mspercent = map(msvalue,0,1023,100,0); // To display the soil moisture value in percentage

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
    //error_count = 5;
    connect_count = 0;
    flag = false;
    delete client;
    Serial.println("connect_count = 0");
    return;
  }

  Serial.println("GET Data from cell 1 soil moisture: ");
  Serial.print(cellAddress1);Serial.print("=");
  if (client->GET(url1, host)){
    //get the value of the cell
    payload1 = client->getResponseBody();
    payload1.trim(); //soil moisture set value
    Serial.println(payload1);
    ++connect_count;
  }
  Serial.println("GET Data from cell 2: ");
  Serial.print(cellAddress2);Serial.print("=");
  if (client->GET(url2, host)){
    //get the value of the cell
    payload2 = client->getResponseBody();
    payload2.trim(); /// temperature value
    Serial.println(payload2);
    ++connect_count;
  }
  
  if (error_count > 3){
    Serial.println("Halting processor..."); 
    delete client;
    client = nullptr;
    Serial.flush();
    ESP.deepSleep(0);
  }
 // Add some delay in between checks
  delay(1000);
  int moisture = payload1.toInt();
  int ctemp= payload2.toInt();
  if(temp>ctemp){
    digitalWrite(16,HIGH);
  }
  else{
    digitalWrite(16,LOW);
  }

  sendData(temp, hum, mspercent); //--> Calls the sendData Subroutine
}
void getData(){
  
  
}
// Subroutine for sending data to Google Sheets
void sendData(float value0, int value1, int value2) {

String GAS_ID = "AKfycby6__9DF6COPhs2xFPcqyRRwahuyUBFozPKKg-IlMXeTicePcxTGSY2yawFcHgDFmYI"; //sending data to google script address

String url = String("/macros/s/") + GScriptId + "/exec";// neu dung trang tinh khac thì thay GScriptId thành GAS_ID

  payload = payload_base + "\"" + value0 + "," + value1 + "," + value2 + "\"}";

// Publish data to Google Sheets
  Serial.println("Publishing data...");
  Serial.println(payload);
  if(client->POST(url, host, payload)){ 
    // do stuff here if publish was successful
  }
  else{
    // do stuff here if publish was not successful
    Serial.println("Error while connecting");
  }

  // a delay of several seconds is required before publishing again    
  delay(100);
  //----------------------------------------Processing data and sending data
  
} 
