//
// Created by antoo on 11/15/2021.
//

#include <wiringPi.h>
#include "Buzzer.h"

#define BUZZER 7

Buzzer::Buzzer() = default;

void Buzzer::waiting() {
    digitalWrite(BUZZER, LOW);
}

void Buzzer::reading() {
}

void Buzzer::success() {
    digitalWrite(BUZZER, LOW);
    delay(50);
    digitalWrite(BUZZER, HIGH);
    delay(50);
}

void Buzzer::turnOff() {
    digitalWrite(BUZZER, LOW);
}
