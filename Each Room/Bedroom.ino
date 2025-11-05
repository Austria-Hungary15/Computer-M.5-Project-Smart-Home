#include <IROVER.h>
#include <Adafruit_NeoPixel.h>

const int PixelRing = 12;
const int PixelPin = 19;

Adafruit_NeoPixel pixels(PixelRing, PixelPin, NEO_GRB + NEO_KHZ800);

const int BedroomButton = 34;
const int SoundSensor = 35;

int BedroomN = 1;

void setup() {
  pixels.begin();
  pixels.setBrightness(50);
  pinMode(BedroomButton, INPUT_PULLUP);
}

int BedroomControl() {
  if (digitalRead(BedroomButton) == 0 || analogRead(SoundSensor) >= 2500) {
    delay(500);
    BedroomN++;
    if (BedroomN > 3) {
      BedroomN = 1 ;
    }
  }
  return BedroomN;
}

void Bedroom(int a) {
  pixels.clear();
  if (a == 1) {
    for (int i = 0; i < PixelRing; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 230, 255));
    }
  } else if (a == 2) {
    for (int i = 0; i < PixelRing; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    }
  } else if (a == 3) {
    for (int i = 0; i < PixelRing; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
  }
  pixels.show();
}

void loop() {
  Bedroom(BedroomControl());
}
