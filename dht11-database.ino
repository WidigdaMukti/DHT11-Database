#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE); 
WiFiClient wifiClient; 

// Variables
const char* ssid = "iPhone"; 
const char* password = "1234567890"; 

void setup() { 
  dht.begin(); 
  Serial.begin(115200); // Initialize serial communication
  Serial.print("Connecting to "); 
  Serial.println(ssid); 
  WiFi.begin(ssid, password); 

  for(uint8_t t = 4; t > 0; t--) { 
    Serial.printf("[SETUP] WAIT %d...\n", t); 
    Serial.flush(); 
    delay(1000); 
  } 

  Serial.println(""); 
  Serial.println("WiFi connected"); 
  Serial.println(WiFi.localIP()); 
} 

void loop() { 
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 

  if(WiFi.status() == WL_CONNECTED){ 
    HTTPClient http; 
    Serial.print("[HTTP] begin...\n"); 
    String link; 
    link = F("http://172.20.10.13/esp/sensordata.php?humidity="); 
    link += String(h, 6); 
    link +="&suhu="; 
    link += String(t, 6);
    Serial.printf("Link : %s\n", link); 
    http.begin(wifiClient,link); 

    Serial.print("[HTTP] GET...\n"); 
    int httpCode = http.GET(); 

    if(httpCode > 0){ 
      Serial.printf("[HTTP] GET... code: %d\n", httpCode); 

      if(httpCode == HTTP_CODE_OK) { 
        Serial.print(F("Berhasil mengirimkan data ke Server \n")); 
        Serial.print(F("Humidity: ")); 
        Serial.print(h); 
        Serial.print("\n"); 
        Serial.print(F(" Temperature: ")); 
        Serial.print(t); 
        Serial.print(F("°C ")); 
      }
      else{ 
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str()); 
      } 
      delay(50); 
    } 
    http.end(); 
  }
  else { 
    Serial.println("Delay..."); 
  } 
  delay(5000); 
}