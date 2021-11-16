//
// Created by antoo on 10/11/2021.
//

#include <iostream>
#include <cstring>
#include <wiringPi.h>
#include "RFID.h"

#define IRQ_PIN    5

RFID::RFID() {
    this->mfrc = new MFRC522();
    this->mfrc->PCD_Init();
    this->mfrc->PCD_WriteRegister(MFRC522::ComIrqReg, 0x80); //Clear interrupts
    this->mfrc->PCD_WriteRegister(MFRC522::ComIEnReg, 0x7F); //Enable all interrupts
    this->mfrc->PCD_WriteRegister(MFRC522::DivIEnReg, 0x14);
    pinMode(IRQ_PIN, INPUT);
    digitalWrite(IRQ_PIN, HIGH);
}

bool RFID::isReading() {
    if(!(this->mfrc->PICC_IsNewCardPresent())) {
        return false;
    }

    if(!(this->mfrc->PICC_ReadCardSerial())) {
        return false;
    }
    return true;
}

bool RFID::cardIsValid(byte valid[4]) {
    return memcmp(valid, this->mfrc->uid.uidByte, sizeof(valid)) == 0;
}
