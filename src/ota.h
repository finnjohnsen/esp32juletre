#ifndef ota_h
#define ota_h
#include "secrets.h"
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// Over-The-Air update
namespace OTA {

    void handle() {
      ArduinoOTA.handle();
    }

    void setup()
    {
        Serial.println("Booting");
        WiFi.setHostname(MY_ID);
        WiFi.mode(WIFI_STA);
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        while (WiFi.waitForConnectResult() != WL_CONNECTED)
        {
            Serial.println("Connection Failed! Rebooting...");
            delay(5000);
            ESP.restart();
        }
        IPAddress ip = WiFi.localIP();
        Serial.println(ip);

        ArduinoOTA.setHostname(MY_ID);
        ArduinoOTA.setPassword(OTA_PASSWORD);

        ArduinoOTA.setPort(8266);

        ArduinoOTA.onStart([](){
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type); })
            .onEnd([]() { 
              Serial.println("\nEnd"); 
              })
            .onProgress([](unsigned int progress, unsigned int total){ 
              Serial.printf("Progress: %u%%\r", (progress / (total / 100))); 
            })
            .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed"); 
      });

        ArduinoOTA.begin();

        Serial.println("Ready");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }
}
#endif