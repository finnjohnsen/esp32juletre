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
    //FastLED.setMaxPowerInVoltsAndMilliamps(5, 2500);
    FastLED.setBrightness(200);
    FastLED.setCorrection(TypicalPixelString);
    //FastLED.setCorrection(UncorrectedColor);

    OTA::setup();
    
}

int cycle = 0;

void fillEvent() {
    CRGB newColor = CRGB::White;
    switch(cycle) {
        case 1: newColor = CRGB::White; break;
        case 2: newColor = CRGB::Pink; break;
        case 3: newColor = CRGB::DeepPink; break;
        case 4: newColor = CRGB::DarkGreen; break;
        case 5: newColor = CRGB::DarkSlateBlue; break;
        default: cycle = 0; break;
    }
    for(int i = 0; i < NUM_LEDS; i++) { leds[i] = newColor; }
    cycle = (++cycle % 6);
    FastLED.show();
}

boolean firstRun = true;
void loop() {

    if (firstRun) { 
        firstRun = false;
        fillEvent(); 
    }

    EVERY_N_MILLISECONDS (10000) {
        fillEvent();
    }

    EVERY_N_MILLIS(150) {
        fadeToBlackBy(leds, NUM_LEDS, 10);
        FastLED.show();
    }

    EVERY_N_MILLIS(100) {
        OTA::handle();
    }
}