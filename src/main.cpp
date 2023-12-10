#include "Arduino.h"
#include <FastLED.h>
#include <sstream>
#include "ota.h"

#define NUM_LEDS 60 
#define LED_STRIP1_PIN GPIO_NUM_16
CRGB leds[NUM_LEDS];


void setup()
{
    Serial.begin(9600);
    Serial.println("Starter");
    FastLED.addLeds<WS2812B, LED_STRIP1_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 200);
    //FastLED.setCorrection(UncorrectedColor);

    OTA::setup();
    
}

int cycle = 0;
void loop()
{

    EVERY_N_MILLISECONDS (30000) {
        cycle = ++cycle % 4;
        CRGB newColor = CRGB::Green;
        switch(cycle) {
            case 1: newColor = CRGB::Red; break;
            case 2: newColor = CRGB::Blue; break;
            case 3: newColor = CRGB::Yellow; break;
            case 4: newColor = CRGB::Purple; break;
            case 5: newColor = CRGB::CornflowerBlue; break;
            default: newColor = CRGB::White; break;
            }
        for(int i = 0; i < NUM_LEDS; i++) { leds[i] = newColor; }
            FastLED.show();

    }

    EVERY_N_MILLIS(100) {
        OTA::handle();
    }
}