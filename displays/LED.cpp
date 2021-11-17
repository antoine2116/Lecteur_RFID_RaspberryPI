//
// Created by antoo on 10/11/2021.
//

#include <wiringPi.h>
#include <iostream>
#include <chrono>
#include "LED.h"

#define LED_R       26
#define LED_G        5
#define LED_B       20

LED::LED() {
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
}

void LED::waiting() {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
}

void LED::success() {
    blink(LED_G, 1000, 800);
    digitalWrite(LED_G, HIGH);
    delay(750);
    waiting();
}

void LED::error() {
    blink(LED_R, 500, 250);
    digitalWrite(LED_R, HIGH);
    delay(750);
    waiting();
}

void LED::turnOff() {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
}

void LED::blink(int led, int duration, int frequency) {
    turnOff();

    bool on = false;
    for(auto runUntil = std::chrono::system_clock::now() + std::chrono::milliseconds (duration);
        std::chrono::system_clock::now() < runUntil;)
    {
        if (on)
            digitalWrite(led, LOW);
        else
            digitalWrite(led, HIGH);

        on = !on;

        delay(frequency);
    }

    turnOff();
}