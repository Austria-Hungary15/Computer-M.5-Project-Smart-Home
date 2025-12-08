a#include <IROVER.h>
#include <Adafruit_NeoPixel.h>

#define PixelRing 12
#define PixelPin 32

Adafruit_NeoPixel pixels(PixelRing, PixelPin, NEO_GRB + NEO_KHZ800);

const int MaindoorButton = 0;


const int BedroomButton = 34;
const int SoundSensor = 35;
const int GarageButton = 33;


const int LDR = i0;
const int IR1 = i1;

const int Ultra = i3;
const int SoilMoister = i5;
const int TempSensor = i6;

const int LED1 = 5;
const int LED2 = 23;
//const int 

const int Buzzer = 25;

int BedroomN = 1;
bool GarageState = false;

void setup() {
  Serial.begin(9600);
  oled.clearDisplay();
  oled.textSize(2);
  init(0x48);
  pixels.begin();
  pixels.setBrightness(50);
  pinMode(BedroomButton, INPUT_PULLUP);
  pinMode(MaindoorButton, INPUT_PULLUP);
  pinMode(GarageButton, INPUT_PULLUP);
  pinMode(Buzzer,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
}

int BedroomControl() {
  Serial.println(analogRead(SoundSensor));
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

/*bool daynightcheck(){
  if(analogRead(LDR) <= 1000){
    return true;
  }else{
    return false;
  }
}

void ExteriorLight(int a){
  if(a){
    digitalWrite(LED2,HIGH);
  }else{
    digitalWrite(LED2,LOW);
  }
}

void ProximityLight(int a){
  if(a){
    if(analogRead(Ultra) <= 500){
      digitalWrite(LED1,HIGH);
    }else{
      digitalWrite(LED1,LOW);
    }
  }
}*/

void Garage(){
  if(digitalRead(GarageButton) == 0){
    if(!(GarageState)){
      GarageState = true;
      //digitalWrite( ,HIGH);
        tone(Buzzer,200);
        servo(11,720);
        delay(100);
        noTone(Buzzer);
        delay(100);
    }else{
      GarageState = false;
      //digitalWrite( ,LOW);
        tone(Buzzer,20);
        servo(11,0);
        delay(100);
        noTone(Buzzer);
        delay(100);
    }
    delay(200);
  }
}

void GateControl(){
  int IR1Value = analog(IR1);
  if(IR1Value >= 500){
    
      servo(10,180);
      
      delay(1800);
  }else{
      servo(10,90);
    }
    delay(200);
  
}

void MaindoorControl(){
  //Serial.println(digitalRead(MaindoorButton));
  if(digitalRead(MaindoorButton) == 0){
    servo(12,75);
    tone(Buzzer,500);
    delay(100);
    noTone(Buzzer);
    delay(1700);
  }else{
    servo(12,0);
  }
  delay(200);
}

void SmartGarden(){
  int rawMoist = analog(SoilMoister);
  int percentMoist = (rawMoist * 100) / 4095;
  int rawTemp = analog(TempSensor);
  int percentTemp = (rawTemp * 100) / 4095;
  oled.text(0,0,"Soil Moister Percent : %d",percentMoist);
  oled.text(1,0,"Temperature Percent : %d",percentTemp);
}

void loop() {
  /*ExteriorLight(daynightcheck());
  ProximityLight(daynightcheck());*/
  Bedroom(BedroomControl());
  Garage();
  GateControl();
  MaindoorControl();
  SmartGarden();
}
