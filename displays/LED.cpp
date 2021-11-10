//
// Created by antoo on 10/11/2021.
//

#include <wiringPi.h>
#include <iostream>
#include <chrono>
#include "LED.h"

#define LED_R 25
#define LED_G 21
#define LED_B 28

using namespace std;

LED::LED() {
    pinMode(LED_G, OUTPUT);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_B, OUTPUT);
}

void LED::waiting() {
    turnOff();
    digitalWrite(LED_B, HIGH);
}

void LED::reading() {
    turnOff();
    blink(LED_R, 1, 200);
}

void LED::success() {
    turnOff();
    blink(LED_G, 1, 50);
}


void LED::error() {
    turnOff();
    blink(LED_R, 1, 50);
}

void LED::turnOff() {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
}

void LED::blink(int led, int duration, int frequency) {
    turnOff();

    bool on = false;
    for(auto runUntil = std::chrono::system_clock::now() + std::chrono::seconds(duration);
        std::chrono::system_clock::now() < runUntil;)
    {
        if (on)
            digitalWrite(led, LOW);
        else
            digitalWrite(led, HIGH);

        on = !on;

        delay(frequency);
    }
}