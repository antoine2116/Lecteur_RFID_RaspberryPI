cmake_minimum_required(VERSION 3.0)
project(rat)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(guigui main.cpp)

find_library(wiringPi_LIB wiringPi)

ADD_LIBRARY( RFID MFRC522.cpp )
target_link_libraries(guigui wiringPi wiringPiDev RFID bcm2835)
