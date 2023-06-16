#include <Arduino.h>

#define LED 14

int c;

void invertLED();

void setup() {
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
    digitalWrite(LED, LOW);
}

void loop() {
    delay(15);
    if(Serial.available()){
        c = Serial.read();
        switch(c){
            case ' ':
                invertLED();
                break;
        }
    }
}

void invertLED(){
    if(digitalRead(LED)){
        digitalWrite(LED, LOW);
    }else{
        digitalWrite(LED, HIGH);
    }
}