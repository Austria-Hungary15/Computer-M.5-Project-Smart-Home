#include <IROVER.h>
#include <Adafruit_NeoPixel.h>

const int Ultra = 32;
const int LDR = 33;
const int LED1 = 5;
const int LED2 = 23;

void setup() {
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
}

int daynightcheck(){
  if(analogRead(LDR) <= 1000){
    return 0;
  }else{
    return 1;
  }
}

void ExteriorLight(int a){
  if(a == 0){
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
  }else{
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
  }
}

void ProximityLight(int a){
  if(a == 0){
    if(analogRead(Ultra) <= 1000){
      digitalWrite(LED2,HIGH);
    }else{
      digitalWrite(LED2,LOW);
    }
  }
}

void loop() {
  ExteriorLight(daynightcheck());
  ProximityLight(daynightcheck());
}
