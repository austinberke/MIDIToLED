



#include "config.h"
//  ==============
//     FUNCTIONS
//  ==============
#define seg_args(OFFS, WID) \ 
  leds + ((NUM_LEDS / WID) * (note - OFFS)), NUM_LEDS / WID , color

void fillSegment(byte note, CRGB color) {
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

void formRay(byte note, CRGB& color, bool dir) {
  rays.unshift(new Ray(dir, color, note, NUM_LEDS/2));
}

void showAllRays() {

  for (int i = 0; i != rays.size(); i++) {
    uint8_t rayPos = rays.get(i)->position();
    uint8_t rayWid = min(rays.get(i)->width(), NUM_LEDS - rayPos); // Less/equal to ray width to not overflow
    CRGB rayCol = rays.get(i)->color(); 
    
    if (rayPos > 0 && rays.get(i)->direction() == 0)
      leds[rayPos-1] = black;
    else if (rayPos > 1 && rays.get(i)->direction() == 1)
      leds[NUM_LEDS-(rayPos-1)] = black;
      
    for (int j = 0; j != rayWid; j++) {
      if (rays.get(i)->direction() == 0)
        leds[constrain(rayPos+j, 0, NUM_LEDS-1)] = rayCol;
      else
        leds[constrain(NUM_LEDS-(rayPos+j), 0, NUM_LEDS-1)] = rayCol;
    }
    
  
  }
}

void advanceAllRays() {
  int i = 0;
  while (i != rays.size()) {
    if (rays.get(i)->advance() == NUM_LEDS) {
      delete rays.get(i);
      rays.remove(i);
      continue;
    }
    i++;
  }
}

void clearRays() {
  FastLED.clear();
  for (int i = 0; i != rays.size(); i++)
    delete rays.get(i);
  rays.clear();
}

void OnNoteOn(byte channel, byte note, byte velocity) {
  velocity = map(velocity, 0, 127, 255, 0);
  CRGB color = ColorFromPalette(RainbowColors_p, velocity);

  switch (channel) {
    case 1: // CHANNEL 1 -> Static Colored Segment
      fillSegment(note, color);
      break;
    case 2: // CHANNEL 2: -> Static White Segment
      fillSegment(note, CRGB(CRGB::White));
      break;
    case 3: // CHANNEL 3 -> Forward Ray
      if (note == 127) { clearRays(); break; }
      formRay(note, color, 0);
      break;
    case 4: // CHANNEL 4 -> Backward Ray
      if (note == 127) { clearRays(); break; }
      formRay(note, color, 1);
      break;
    case 5: // CHANNEL 5 -> Full Rainbow
      fill_rainbow(leds, NUM_LEDS, note, 5);
      break;
    case 16: // CHANNEL 16 -> Brightness
      FastLED.setBrightness(map(note, 0, 127, 0, 255));
      break;
      

  }

}

void OnNoteOff(byte channel, byte note, byte velocity) {


  switch (channel) {
    case 1:
    case 2:
      fillSegment(note, black);
      break;
    case 5:
      fillSegment(0, black);
      break;

  }
}


//  ==============
//      SETUP
//  ==============

void setup() {
  //delay(3000); // power-up safety delay


  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  set_max_power_in_volts_and_milliamps(VOLTS, MAX_AMPS * 1000);
  FastLED.setBrightness(BRIGHTNESS);

  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);

  fill_solid(leds, NUM_LEDS, CRGB::Black);

}

//  ==============
//       LOOP
//  ==============

void loop() {  
  usbMIDI.read(); 
  advanceAllRays();
  showAllRays();
  
  FastLED.show();

  
}


