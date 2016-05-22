#ifndef SETTINGS_H
#define SETTINGS_H

#define NUM_LEDS      240
#define LED_TYPE      NEOPIXEL
#define LED_PIN       17

#define BRIGHTNESS    255
#define VOLTS         5
#define MAX_AMPS      5
#define MAX_RAYS      16

#include <FastLED.h>
#include "Ray.h"

CRGB leds[NUM_LEDS];
Ray rays[MAX_RAYS];
CRGB black = CRGB::Black;

#endif /* SETTINGS_H */
