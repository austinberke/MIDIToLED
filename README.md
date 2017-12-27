# Introduction
MIDIToLED is a program that allows MIDI data to be used to control one or more LED strips in real-time. Its primary purpose is for use in conjunction with a DAW such as Ableton Live to synchronize lights with music. It is currently designed to be used on a Teensy 3.2 with an OctoWS2811 adapter connected to two sets of NeoPixel (WS2812B) strips.

A basic demo video is available [here](https://www.youtube.com/watch?v=8L4q8ZUSSMk).

# Setup
First, adjust the settings in "config.h" to pertain to the specific length and pins of the LED strips (note that for OctoWS2811, pins 2 and 6 correspond to the orange wires of each Cat6 cable). Then, adjust each desired segment's offset and width depending on the physical layout of the strips. Within the Arduino IDE, set the Teensy to act as a MIDI divice by selecting "Tools > USB Type > MIDI."

#Usage
In a DAW, set the output of a MIDI track to the Teensy, and send data to channels according to the table below.

|Channel   |Description   |
|---|---|
|1   | Set all LEDs in system to a single color (refer to Colors below) regardless of octave. Brightness is proportional to velocity. |
|2  | Set a segment of LEDs as defined in "config.h" to a single color. Each octave corresponds to a particular segment, with octaves 0-7 --> segments 1-8. Brightness is proportional to velocity.    |
|3   | Send a ray of width 8 and a single color and across a segment. Rays terminate at the beginning of the next segment. Sending MIDI note 127 will clear all rays from the system. |

## Colors
Below is the current assignment of colors within any given octave.
~~~~
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
~~~~

# License

MIDIToLED is licensed under the MIT license:

The MIT License (MIT)

Copyright (c) 2016 Austin Berke

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
