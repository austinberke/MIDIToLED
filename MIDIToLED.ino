#include "config.h"

//  ==============
//      SETUP
//  ==============
void OnNoteOn(byte channel, byte note, byte velocity);
void OnNoteOff(byte channel, byte note, byte velocity);
void advanceAllRays();
void showAllRays();

void setup() {
  //delay(3000); // power-up safety delay


  FastLED.addLeds<LED_TYPE, LED_PIN_1>(leds,0, NUM_LEDS_1).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN_2>(leds, NUM_LEDS_1, NUM_LEDS_2).setCorrection(TypicalLEDStrip);
  //set_max_power_in_volts_and_milliamps(VOLTS, MAX_AMPS * 1000);
  FastLED.setBrightness(BRIGHTNESS);

  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);


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

//  ==============
//     FUNCTIONS
//  ==============



void setSegment(byte segNum, CRGB color, byte fade=0) {
  segNum %= NUM_SEGMENTS + 1; // Account for segment number overflow,
                              // add one for universal segment
  color = color.nscale8(fade);
   
  switch (segNum) {
     
    case 0: fill_solid(leds + seg1o, seg1w, color); break;
    case 1: fill_solid(leds + seg2o, seg2w, color); break;
    case 2: fill_solid(leds + seg3o, seg3w, color); break;
    case 3: fill_solid(leds + seg4o, seg4w, color); break;
    case 4: fill_solid(leds + seg5o, seg5w, color); break;
    case 5: fill_solid(leds + seg6o, seg6w, color); break;
    case 6: fill_solid(leds + seg7o, seg7w, color); break;
    case 7: fill_solid(leds + seg8o, seg8w, color); break;

    case 8: fill_solid(leds, NUM_LEDS_1+NUM_LEDS_2, color); break; // Set all LEDs
  }
}

void clearSegment(byte segNum) {
  setSegment(segNum, black);
}

 void formRay(byte octave, CRGB& color, bool dir) {
   uint16_t pos;
   byte life;
   switch (octave) {
    default:
    case 0:
    case 1:
      pos = seg1o;
      life = seg1w;
      break;
    case 2:
      pos = seg2o;
      life = seg2w;
      break;
    case 3:
      pos = seg3o;
      life = seg3w;
      break;
    case 4:
      pos = seg4o;
      life = seg4w/2;
      break;
    case 5:
      pos = seg4o+seg4w/2;
      life = seg4w/2;
      break;
    case 6:
      pos = seg5o;
      life = seg4w/2;
      break;    
    case 7:
      pos = seg5o+seg5w/2;
      life = seg5w/2;
   }
   rays.unshift(new Ray(dir, color, pos, life));
 }

void showAllRays() {

   for (int i = 0; i != rays.size(); i++) {
     uint16_t rayPos = rays.get(i)->position();
     uint8_t rayWid = min(rays.get(i)->width(), NUM_LEDS - rayPos); // Less/equal to ray width to not overflow
     CRGB rayCol = rays.get(i)->color(); 


     // Delete trail behind ray
     if (rayPos > 0 && rays.get(i)->direction() == 0)
       leds[rayPos-1] = black;
     else if (rayPos > 1 && rays.get(i)->direction() == 1)
       leds[NUM_LEDS-(rayPos-1)] = black;


      // Show ray
     for (int j = 0; j != rayWid; j++) {
       if (rays.get(i)->life() > rayWid) {
       
         if (rays.get(i)->direction() == 0)
           leds[constrain(rayPos+j, 0, NUM_LEDS-1)] = rayCol;
         else
           leds[constrain(NUM_LEDS-(rayPos+j), 0, NUM_LEDS-1)] = rayCol;
       
     }
    
  
   }
 }
}

 void advanceAllRays() {
   int i = 0;
   while (i != rays.size()) {
     if (rays.get(i)->advance() == 0) {
       delete rays.get(i);
       rays.remove(i);
       continue;
     }
     i++;
   }
 }

 void clearRays() {
   FastLED.clear(true);
   for (int i = 0; i != rays.size(); i++)
     delete rays.get(i);
   rays.clear();
 }

void OnNoteOn(byte channel, byte note, byte velocity) {
  byte brightness = map(velocity, 0, 127, 0, 255);
  byte octave = note / 12;
  CRGB color = noteColors[note%12];

  switch (channel) {
    case 1: // CHANNEL 1 -> All LEDS
      setSegment(8, color, brightness);
    case 2: // CHANNEL 2 -> Static Segment
      setSegment(octave, color, brightness);
      break;
    case 3: // CHANNEL 3 -> Forward Ray
      if (note == 127) { clearRays(); break; }
        formRay(octave, color, 0);
      break;

  }

}

void OnNoteOff(byte channel, byte note, byte velocity) {
  byte octave = note / 12;

  switch (channel) {
    case 1: // CHANNEL 1 -> All LEDS
      FastLED.clear();
    case 2: // CHANNEL 2 -> Static Segment
      clearSegment(octave);
      break;

  }
}


