set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake) 

cmake_minimum_required(VERSION 2.8)

project(rgb-led C CXX)

print_board_list()
print_programmer_list()

generate_arduino_firmware(rgb
    SRCS rgb.cc Adafruit_TLC5947.cpp
    BOARD micro
    PORT /dev/ttyACM0)
