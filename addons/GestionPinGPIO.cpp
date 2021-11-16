/*
 * GestionPinGPIO.cpp
 *
 *  Created on: 1 ao�t 2016
 *      Author: totof
 */

#include <wiringPi.h>
#include "GestionPinGPIO.h"

// ***********************
// Constructeur
// Constructeur par defaut
// ***********************
GestionPinGPIO::GestionPinGPIO() {
}

// ******************************************************
// M�thode init en cas d'appel au constructeur par d�faut
// @param num�ro de pin
// ******************************************************
void GestionPinGPIO::init(PinGPIO pPinNumber) {
    pinNumber = pPinNumber;
}

// *********************************
// Constructeur
// M�morise le num�ro de pin utilis�
// @param num�ro de pin
// *********************************
GestionPinGPIO::GestionPinGPIO(PinGPIO pPinNumber) {
    pinNumber = pPinNumber;
}

// **********************************
// Applique la direction sur une GPIO
// @param pDirection la direction
// **********************************
void GestionPinGPIO::pinModePI(PinDirection pDirection) {
    pinMode(pinNumber, pDirection);
}

// **************
// GPIO en entr�e
// **************
void GestionPinGPIO::in() {
    PinDirection input = In;
    pinMode(pinNumber, input);
}

// **************
// GPIO en sortie
// **************
void GestionPinGPIO::out() {
    PinDirection output = Out;
    pinMode(pinNumber, output);
}

// ***********************************************
// Active/d�sactive les r�sistance de pull down/up
// @param le type de r�sistance
// ***********************************************
void GestionPinGPIO::pullUpDnControlPI(Pud pNiveau) {
    pullUpDnControl(pinNumber, pNiveau);
}

// *******************************
// Active la r�sistance de pull up
// *******************************
void GestionPinGPIO::pullUp() {
    Pud pudUp = Up;
    pullUpDnControl(pinNumber, pudUp);
}

// *********************************
// Active la r�sistance de pull down
// *********************************
void GestionPinGPIO::pullDn() {
    Pud pudDown = Down;
    pullUpDnControl(pinNumber, pudDown);
}

// ***************************************
// D�sactive la r�sistance de pull up/down
// ***************************************
void GestionPinGPIO::pullOff() {
    Pud pudOff = Off;
    pullUpDnControl(pinNumber, pudOff);
}

// ****************************
// Applique un niveau � la GPIO
// @param le niveau
// ****************************
void GestionPinGPIO::write(Level pValue) {
    switch(pValue) {
        case LOW: off(); break;
        case HIGH: on(); break;
    }
}

// ********************************
// Applique un niveau bas � la GPIO
// ********************************
void GestionPinGPIO::off() {
    Level low = Low;
    digitalWrite(pinNumber, LOW);
}

// *********************************
// Applique un niveau haut � la GPIO
// *********************************
void GestionPinGPIO::on() {
    Level high = High;
    digitalWrite(pinNumber, HIGH);
}

// ****************************
// inverse le niveau de la GPIO
// ****************************
void GestionPinGPIO::invertState() {
    if(isOn()) {
        off();
    } else {
        on();
    }
}

// ****************************
// Lecture du niveau de la GPIO
// @return le niveau
// ****************************
Level GestionPinGPIO::read() {
    if(digitalRead(pinNumber)) {
        Level high = High;
        return high;
    } else {
        Level low = Low;
        return low;
    }
}

// *************************************
// Demande si la GPIO est au niveau haut
// @return true si oui sinon false
// *************************************
bool GestionPinGPIO::isOn() {
    Level high = High;
    if(digitalRead(pinNumber) == high){
        return true;
    }
    return false;
}

// ************************************
// Demande si la GPIO est au niveau bas
// @return true si oui sinon false
// ************************************
bool GestionPinGPIO::isOff() {
    Level low = Low;
    if(digitalRead(pinNumber) == low){
        return true;
    }
    return false;
}

// ***********************************************
// Active une fonction d'interruption sur un front
// @param le front
// @param un pointeur sur la fonction
// @return 0 si OK
// ***********************************************
int GestionPinGPIO::fctInterrupt(FrontIntr pFront, interrupt intr) {
    return wiringPiISR(pinNumber, pFront, *intr);
}

// ******************************************
// Demande si le destructeur sera appliqu�
// return destroyFlag, le flag de destructeur
// ******************************************
bool GestionPinGPIO::isToDesactivate(void) {
    return desactivateFlag;
}

// ****************************************
// Indique que le destructeur sera appliqu�
// ****************************************
void GestionPinGPIO::toDesactivate(void) {
    setToDesactivate(true);
}

// ***********************************************
// Indique que le destructeur ne sera pas appliqu�
// ***********************************************
void GestionPinGPIO::noDesactivate(void) {
    setToDesactivate(false);
}

// ************************************
// Positionne le flag de destructeur
// @param pValue le flag de destructeur
// ************************************
void GestionPinGPIO::setToDesactivate(bool pValue) {
    desactivateFlag = pValue;
}

// **********************************************************
// Destructeur
// Si le flag de destroy est activ�,
// met la GPIO en entr�e et d�sactive la r�sistance de rappel
// sinon, la GPIO reste en �tat m�me � la sortie du programme
// **********************************************************
GestionPinGPIO::~GestionPinGPIO() {
    if(isToDesactivate()) {
        Pud pudOff = Off;
        PinDirection in = In;
        pullUpDnControlPI(pudOff);
        pinModePI(in);
    }
}
