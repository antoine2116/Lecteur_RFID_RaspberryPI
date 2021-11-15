//
// Created by antoo on 10/11/2021.
//

#include <iostream>
#include <cstring>
#include "RFID.h"

RFID::RFID() {
    this->mfrc = new MFRC522();
    this->mfrc->PCD_Init();
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
