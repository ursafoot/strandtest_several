#include <Adafruit_NeoPixel.h>

// based directly from strandtest.ino, the example file supplied with Adafruit Neopixel libraries.

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(14, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(14, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(14, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(14, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(14, 7, NEO_GRB + NEO_KHZ800);
uint32_t secondColor; // the color used for the second 7 lights

void setup() {
  Serial.begin(57600);
  Serial.println(__FILE__);
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
  secondColor = strip1.Color(150, 150, 150); // color for all second strips
  for( int cd=5; cd; cd-- ) {
    Serial.print(cd);
    delay(1000);
  }
  Serial.println("\nDone with setup");
}

#define VOLTCOEFF 13.179  // larger number interprets as lower voltage
#define AMPCOEFF 8.0682 // 583 - 512 = 71; 71 / 8.8 amps = 8.0682
#define AMPOFFSET 512.0 // when current sensor is at 0 amps this is the ADC value

void loop() {
  Serial.println("Top of loop");
  // Some example procedures showing how to display to the pixels:
  float voltage = analogRead(A0) / VOLTCOEFF;
  int volts = (int)(voltage / 25);
  int amps = (int)((analogRead(A1) - AMPOFFSET) / AMPCOEFF);
  colorBars(strip1,strip1.Color(255, 105, 0), amps, volts); // Orange
  amps = (int)((analogRead(A2) - AMPOFFSET) / AMPCOEFF);
  colorBars(strip2,strip2.Color(255, 255, 0), amps, volts); // Yellow
  amps = (int)((analogRead(A3) - AMPOFFSET) / AMPCOEFF);
  colorBars(strip3,strip3.Color(0, 255, 0), amps, volts); // Green
  amps = (int)((analogRead(A4) - AMPOFFSET) / AMPCOEFF);
  colorBars(strip4,strip4.Color(0, 0, 255), amps, volts); // Blue
  amps = (int)((analogRead(A5) - AMPOFFSET) / AMPCOEFF);
  colorBars(strip5,strip5.Color(80, 0, 80), amps, volts); // Violet
  Serial.println("Bottom of loop");
}

// fourteen LEDs arranged as two bars of 7.
// give this function a color, and two numbers from 0 to 7 (how many to light up)
void colorBars(Adafruit_NeoPixel& strip, uint32_t color, uint8_t first, uint8_t second) {
  for(uint16_t i=0; i<7; i++) if (i < first) { // if the pixel should be "lit up"
    strip.setPixelColor(i, color); // light up the pixel with "color"
  } else {
    strip.setPixelColor(i, strip.Color(10, 10, 10)); // otherwise, a dull white
  }

  for(uint16_t i=7; i<14; i++) if (i < second + 7) { // if the pixel should be "lit up"
    strip.setPixelColor(i, secondColor); // light up the pixel with "secondColor"
  } else {
    strip.setPixelColor(i, strip.Color(10, 10, 10)); // otherwise, a dull white
  }
  strip.show(); // make it happen
}
