//
// Created by antoo on 11/15/2021.
//

#include <wiringPi.h>
#include "Buzzer.h"

#define BUZZER     4

Buzzer::Buzzer() {
    pinMode(BUZZER, OUTPUT);
}

void Buzzer::waiting() {

}

void Buzzer::success() {
    for (int i = 0; i < 2; i++) {
        digitalWrite(BUZZER, HIGH);
        delay(200);
        digitalWrite(BUZZER, LOW);
        delay(200);
    }
}

void Buzzer::error() {
    digitalWrite(BUZZER, HIGH);
    delay(750);
    digitalWrite(BUZZER, LOW);
}

void Buzzer::turnOff() {
    digitalWrite(BUZZER, LOW);
}