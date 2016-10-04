#ifndef SETTINGS_H
#define SETTINGS_H

#define LED_TYPE      NEOPIXEL

#define NUM_LEDS_1    480
#define LED_PIN_1     2

#define NUM_LEDS_2    240
#define LED_PIN_2     6

#define NUM_LEDS NUM_LEDS_1+NUM_LEDS_2

#define BRIGHTNESS    255
#define VOLTS         5
#define MAX_AMPS      10

#include <FastLED.h>
#include <LinkedList.h>
#include "Ray.h"

CRGB leds[NUM_LEDS_1+NUM_LEDS_2];
LinkedList<Ray*> rays;
CRGB black = CRGB::Black;


// Define segment offsets and width – differs depending on
// physical layout of LEDs

#define NUM_SEGMENTS 8

#define seg1o 0
#define seg1w 83

#define seg2o 83
#define seg2w 67

#define seg3o 150
#define seg3w 90

#define seg4o 240
#define seg4w 120

#define seg5o 360
#define seg5w 120

#define seg6o 480
#define seg6w 120

#define seg7o 600
#define seg7w 50

#define seg8o 650
#define seg8w 70

// Define color assignment for each note within an octave
CRGB noteColors[12] = {
    CRGB::Red,          // C
    CRGB::OrangeRed,    // C#
    CRGB::Orange,       // D
    CRGB::Yellow,       // D#
    CRGB::Green,        // E
    CRGB::SkyBlue,      // F
    CRGB::Blue,         // F#
    CRGB::Cyan,         // G
    CRGB::Indigo,       // G#
    CRGB::Violet,       // A
    CRGB::FairyLight,   // A#   
    CRGB::White         // B
};


#endif /* SETTINGS_H */
