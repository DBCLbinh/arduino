#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
 
void setup() 
{
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    Serial.begin(115200);
    WiFiManager wm;
    bool res;
    res = wm.autoConnect("AutoConnectAP"); // password protected ap
 
    if(!res) 
        Serial.println("Failed to connect");
    else 
        Serial.println("connected...yeey :)");
}
 
void loop() 
{
    
}
