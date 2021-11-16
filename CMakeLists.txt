cmake_minimum_required(VERSION 3.0)
project(rat)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(guigui main.cpp displays/LCD.cpp displays/LCD.h displays/IDisplay.cpp displays/IDisplay.h displays/LED.cpp displays/LED.h reader/RFID.cpp reader/RFID.h displays/Buzzer.cpp displays/Buzzer.h addons/GestionPinGPIO.cpp addons/GestionPinGPIO.h addons/GestionPin.cpp addons/GestionPin.h)

find_library(wiringPi_LIB wiringPi)

ADD_LIBRARY(RFID reader/MFRC522.cpp displays/LCD.cpp displays/LCD.h displays/IDisplay.cpp displays/IDisplay.h displays/LED.cpp displays/LED.h reader/RFID.cpp reader/RFID.h)
target_link_libraries(guigui wiringPi wiringPiDev RFID bcm2835)
