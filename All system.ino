#include <IROVER.h>
#include <Adafruit_NeoPixel.h>


const int PixelRing = 12;
const int PixelPin = 19;

Adafruit_NeoPixel pixels(PixelRing, PixelPin, NEO_GRB + NEO_KHZ800);

const int BedroomButton = 34;
const int SoundSensor = 35;
const int LDR = 33;
const int Ultra = 32;

const int GateButton = i0;
const int IR = i1;

const int LED1 = 5;
const int LED2 = 23;

int BedroomN = 1;
int Gate = 0;

void setup() {
  init(0x48);
  pixels.begin();
  pixels.setBrightness(50);
  pinMode(BedroomButton, INPUT_PULLUP);
  pinMode(GateButton, INPUT_PULLUP);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
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

int daynightcheck(){
  if(analogRead(LDR) >= 1000){
    return 0;
  }else{
    return 1;
  }
}

void ExteriorLight(int a){
  if(a == 0){
    digitalWrite(LED2,HIGH);
  }else{
    digitalWrite(LED2,LOW);
  }
}

void ProximityLight(int a){
  if(a == 0){
    if(analogRead(Ultra) <= 500){
      digitalWrite(LED1,HIGH);
    }else{
      digitalWrite(LED1,LOW);
    }
  }
}

/*void Garage(){
  if(digitalRead() == 0){
    if(!(GarageState)){
      GarageState = true;
      digitalWrite( ,HIGH);
      for(int i = 1;i<= ;i++){
        tone(Buzzer,);
        motor(1,30);
        delay(100);
        noTone(Buzzer);
        delay(100);
      }
      motor(1,0);
    }else{
      GarageState = false;
      digitalWrite( ,LOW);
      for(int i = 1;i<= ;i++){
        tone(Buzzer,);
        motor(1,-30);
        delay(100);
        noTone(Buzzer);
        delay(100);
      }
      motor(1,0);
    }
  }
}*/

void GateControl(){
  if(digitalRead(GateButton) == 0 || analogRead(IR) >= 1500){
    if(Gate == 0){
      servo(10,0);
      Gate = 1;
    }else{
      servo(10,45);
      Gate = 0;
    }
    delay(200);
  }
}

void loop() {
  ExteriorLight(daynightcheck());
  ProximityLight(daynightcheck());
  Bedroom(BedroomControl());
  //Garage()
  GateControl();
}
