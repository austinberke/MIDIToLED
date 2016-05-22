#include "config.h"

//  ==============
//     FUNCTIONS
//  ==============
#define seg_args(OFFS, WID) \ 
  leds + ((NUM_LEDS / WID) * (note - OFFS)), NUM_LEDS / WID , color
void fillSegment(byte note, CRGB& color) {
  if      (note < 1) // 0 .. 1 -> Full
    fill_solid(seg_args(0,1));
  else if (note < 3) // 1 .. 3 -> 1/2
    fill_solid(seg_args(1,2));
  else if (note < 6) // 3 .. 6 -> 1/3
    fill_solid(seg_args(3,3));
  else if (note < 10) // 6 .. 10 -> 1/4
    fill_solid(seg_args(6,4));
  else if (note < 18) // 10 .. 18 -> 1/8
    fill_solid(seg_args(10,8));
  else if (note < 34) // 18 .. 34 -> 1/16
    fill_solid(seg_args(18, 16));
  else if (note < 94) // 34 .. 94 -> 1/60
    fill_solid(seg_args(34,60));
}

void showRays() {
  
}
 
void OnNoteOn(byte channel, byte note, byte velocity) {
  velocity = map(velocity, 0, 127, 255, 0);
  CRGB color = ColorFromPalette(RainbowColors_p, velocity);
  
  switch (channel) {
    case 1: // CHANNEL 1 -> Static Segment
      fillSegment(note, color);
      break;
    case 2: // CHANNEL 2 -> Ray
      fillSegment(note, color);
      break;
    
  }

}
 
void OnNoteOff(byte channel, byte note, byte velocity) {
  
  
  switch (channel) {
    case 1:
      fillSegment(note, black); 
      break;
    
  }
}


//  ==============
//      SETUP
//  ==============

void setup() {
  delay(3000); // power-up safety delay

  
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  set_max_power_in_volts_and_milliamps(VOLTS, MAX_AMPS*1000);
  FastLED.setBrightness(BRIGHTNESS);
  
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);

  fill_solid(leds, 240, CRGB::Black);
  
}

//  ==============
//       LOOP
//  ==============

void loop() {
  usbMIDI.read();
  showRays();
  FastLED.show();
}


