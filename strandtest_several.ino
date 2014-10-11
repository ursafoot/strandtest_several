#include <Adafruit_NeoPixel.h>

// based directly from strandtest.ino, the example file supplied with Adafruit Neopixel libraries.

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(12, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(12, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(12, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(12, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(12, 7, NEO_GRB + NEO_KHZ800);

void setup() {
  strip1.begin();
  strip1.show(); // Initialize all pixels to 'off'
  strip2.begin();
  strip2.show(); // Initialize all pixels to 'off'
  strip3.begin();
  strip3.show(); // Initialize all pixels to 'off'
  strip4.begin();
  strip4.show(); // Initialize all pixels to 'off'
  strip5.begin();
  strip5.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip1,strip1.Color(255, 105, 0), 5); // Orange
  colorWipe(strip2,strip2.Color(255, 255, 0), 5); // Yellow
  colorWipe(strip3,strip3.Color(0, 255, 0), 5); // Green
  colorWipe(strip4,strip4.Color(0, 0, 255), 5); // Blue
  colorWipe(strip5,strip5.Color(80, 0, 80), 5); // Violet
}

// Fill the dots one after the other with a color
void colorWipe(Adafruit_NeoPixel strip, uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(Adafruit_NeoPixel strip, uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(strip,(i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(Adafruit_NeoPixel strip, uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(strip,((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel strip, byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

