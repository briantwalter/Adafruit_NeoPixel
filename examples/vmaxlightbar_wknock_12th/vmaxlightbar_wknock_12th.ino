#include <Adafruit_NeoPixel.h>

//
// vmaxlightbar_wknock         VMAX Light Bar with Knock Sensor
// version                     0.0.2
// author                      Brian Walter @briantwalter
// description                 Modification of EMC VMAX cabinet light feature
//                             to use NeoPixel RGB LEDs powered by Arduino

// configuration constants
const int knocksensor = A0;        // piezo sensor on analog 0
const int knockthres = 10;         // sensitivity of piezo
const int noofpixels = 34;         // number of NeoPixels in the light bar
const int endofpixels = 0;         // this to where you want it to start/end 
const boolean usingbar = true;     // true for the 8x1 Neopixel Bar or false for 3 leds
const int knockgap = 4000;         // milisecond interval to listen for knocks
//configuration variables
int knockreading = 0;

// Adafruit define based on header
#define PIN 6

// Adafruit light strip hardware options
// Parameter 1 = number of pixels in strip
// Parameter 2 asds= Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(noofpixels, PIN, NEO_GRB + NEO_KHZ800);

// runs once
void setup() {
  strip.begin(); // Start function from header
  strip.show();  // Initialize all pixels to 'off'
}

// runs constant
void loop() {
  cylon(30);
  
  // Seahawks Colors
  colorWipeLR(strip.Color(6, 25, 46), 50);  // Seahawks Blue 
  colorWipeRL(strip.Color(78, 174, 71), 50); //Seahawks Green
  for(uint16_t i=0; i<knockgap; i++) {
    knockreading = analogRead(knocksensor);
    if (knockreading >= knockthres) {
      rainbow(20);
      delay(1);
  }
 }
}
// end main loop

// functions below

// Fill the dots one after the other with a color left to right
void colorWipeLR(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Fill the dots one after the other with a color right to left
void colorWipeRL(uint32_t c, uint8_t wait) {
  for(uint16_t i=strip.numPixels(); i>0; i--) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Smooth rainbow blend
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
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

// simple roll up of the multi-color cylon effect
void cylonmc(uint8_t wait) {
  for(int l=0; l<2; l++) {
    //Example: CylonEyeUp(Center_Dot_Color, Second_Dot_color, Third_Dot_color, wait, noofpixels, endofpixels);
    CylonEyeUp(strip.Color(175,0,0), strip.Color(25,0,0), strip.Color(10,0,0), wait, noofpixels, endofpixels);
    delay(wait);
    CylonEyeDown(strip.Color(175,0,0), strip.Color(25,0,0), strip.Color(10,0,0), wait, noofpixels, endofpixels);
    delay(wait);
  }
  for(int l=0; l<2; l++) {
    CylonEyeUp(strip.Color(0,175,0), strip.Color(0,25,0), strip.Color(0,10,0), wait, noofpixels, endofpixels);
    delay(wait);
    CylonEyeDown(strip.Color(0,175,0), strip.Color(0,25,0), strip.Color(0,10,0), wait, noofpixels, endofpixels);
    delay(wait);
  }
  for(int l=0; l<2; l++) {
    CylonEyeUp(strip.Color(0,0,175), strip.Color(0,0,25), strip.Color(0,0,10), wait, noofpixels, endofpixels);
    delay(wait);
    CylonEyeDown(strip.Color(0,0,175), strip.Color(0,0,25), strip.Color(0,0,10), wait, noofpixels, endofpixels);
    delay(wait);
  }
  for(int l=0; l<2; l++) {
    CylonEyeUp(strip.Color(175,0,0), strip.Color(0,25,0), strip.Color(0,0,10), wait, noofpixels, endofpixels);
    delay(wait);
    CylonEyeDown(strip.Color(175,0,0), strip.Color(0,25,0), strip.Color(0,0,10), wait, noofpixels, endofpixels);
    delay(wait);
  }
  for(int l=0; l<2; l++) {
    CylonEyeUp(strip.Color(175,175,175), strip.Color(25,25,25), strip.Color(10,10,10), wait, noofpixels, endofpixels);
    delay(wait);
    CylonEyeDown(strip.Color(175,175,175), strip.Color(25,25,25), strip.Color(10,10,10), wait, noofpixels, endofpixels);
    delay(wait);
  }
}
// simple roll up of the single color cylon
void cylon(uint8_t wait) {
  CylonEyeUp(strip.Color(175,0,0), strip.Color(25,0,0), strip.Color(10,0,0), wait, noofpixels, endofpixels);
  delay(wait);
  CylonEyeDown(strip.Color(175,0,0), strip.Color(25,0,0), strip.Color(10,0,0), wait, noofpixels, endofpixels);
  delay(wait);
}
void CylonEyeUp(uint32_t Co, uint32_t Ct, uint32_t Ctt, uint8_t Delay, int TotalPixels, int pStart) {
  for(int i=pStart; i<TotalPixels; i++) {
       if(!usingbar) { strip.setPixelColor(i+2, Ctt); } //Third Dot Color
    strip.setPixelColor(i+1, Ct);   //Second Dot Color
    strip.setPixelColor(i, Co);     //Center Dot Color
    strip.setPixelColor(i-1, Ct);   //Second Dot Color
    if(!usingbar) { strip.setPixelColor(i-2, Ctt); } //Third Dot Color

    if(!usingbar) {
      strip.setPixelColor(i-3, strip.Color(0,0,0)); //Clears the dots after the 3rd color
    } else {
      strip.setPixelColor(i-2, strip.Color(0,0,0)); //Clears the dots after the 2rd color
    }
    strip.show();
    //Serial.println(i); //Used For pixel Count Debugging
    delay(Delay);

  }
}
void CylonEyeDown(uint32_t Co, uint32_t Ct, uint32_t Ctt, uint8_t Delay, int TotalPixels, int pEnd) {
  for(int i=TotalPixels-1; i>pEnd; i--) {
    if(!usingbar) { strip.setPixelColor(i-2, Ctt); } //Third Dot Color
    strip.setPixelColor(i-1, Ct);   //Second Dot Color
    strip.setPixelColor(i, Co);    //Center Dot Color
    strip.setPixelColor(i+1, Ct);  //Second Dot Color
    if(!usingbar) { strip.setPixelColor(i+2, Ctt); } //Third Dot Color

    if(!usingbar) { 
      strip.setPixelColor(i+3, strip.Color(0,0,0)); //Clears the dots after the 3rd color
    } else {
      strip.setPixelColor(i+2, strip.Color(0,0,0)); //Clears the dots after the 2rd color
    }
    strip.show();
    //Serial.println(i); //Used For pixel Count Debugging
    delay(Delay);
  }
}
