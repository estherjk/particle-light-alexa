#include "neopixel.h" // use for local build

// IMPORTANT: Set pixel PIN, COUNT, and TYPE
// Supported pixel types: WS2812, WS2812B, WS2812B2, WS2811, TM1803, TM1829, SK6812RGBW
#define PIXEL_PIN D2
#define PIXEL_COUNT 16
#define PIXEL_TYPE SK6812RGBW

#define BRIGHTNESS 50 // 0 - 255

Adafruit_NeoPixel ring = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {
  ring.setBrightness(BRIGHTNESS);
  ring.begin();
  ring.show(); // Initialize all pixels to 'off'

  Particle.function("state", setLightState);
  Particle.function("color", setLightColor);
  Particle.function("brightness", setLightBrightness);
}

int setLightState(String state) {
  if(state == "on") {
    changeColor(ring.Color(0, 0, 0, 255)); // GRB+W
  }
  else if(state == "off") {
    ring.setBrightness(0);
    ring.show();
  }
}

int setLightColor(String color) {
  if(color == "red") {
    changeColor(ring.Color(0, 255, 0)); // GRB
  }
  else if(color == "green") {
    changeColor(ring.Color(255, 0, 0)); // GRB
  }
  else if(color == "blue") {
    changeColor(ring.Color(0, 0, 255));
  }
  else if(color == "white") {
    changeColor(ring.Color(0, 0, 0, 255)); // GRB+W
  }
}

int setLightBrightness(String brightness) {
  ring.setBrightness(brightness.toInt());
  ring.show();
}

void changeColor(uint32_t color) {
  for(uint16_t i=0; i < ring.numPixels(); i++) {
    ring.setPixelColor(i, color);
    ring.show();
  }
}
