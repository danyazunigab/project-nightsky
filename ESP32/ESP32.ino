#include <Adafruit_NeoPixel.h>

#define LEDPIN 32
#define NUM_LEDS 6

Adafruit_NeoPixel LEDStrip = Adafruit_NeoPixel(NUM_LEDS, LEDPIN, NEO_GRB + NEO_KHZ800);

int SpeedDelay = 1000;
byte currentRed = 0x43;
byte currentGreen = 0x00;
byte currentBlue = 0x6f;
void setup(){
  Serial.begin(115200);
  LEDStrip.begin();
  LEDStrip.show();
}

void loop(){
  /*rainbowCycle();
  delay(5000);*/
  FadeInOut();
  //delay(5000);
}

void FadeInOut(){
  float r, g, b;
      
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*currentRed;
    g = (k/256.0)*currentGreen;
    b = (k/256.0)*currentBlue;
    setAll(r,g,b);
    LEDStrip.show();
    delay(SpeedDelay/256);
  }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*currentRed;
    g = (k/256.0)*currentGreen;
    b = (k/256.0)*currentBlue;
    setAll(r,g,b);
    LEDStrip.show();
    delay(SpeedDelay/256);
  }
}

void rainbowCycle() {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    LEDStrip.show();                                                                                                                           
    delay(SpeedDelay/256);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }
  return c;
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
  LEDStrip.setPixelColor(Pixel, LEDStrip.Color(red, green, blue));
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  LEDStrip.show();
}