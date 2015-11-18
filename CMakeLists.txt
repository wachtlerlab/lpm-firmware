set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake) 

cmake_minimum_required(VERSION 2.8)

project(rgb-led C CXX)

print_board_list()
print_programmer_list()

if(DEFINED ENV{DEVICE})
    set(DEVICE $ENV{DEVICE})
else()
    set(DEVICE /dev/ttyACM0)
endif()

generate_arduino_firmware(rgb
        SRCS firmware.cc Adafruit_TLC5947.cpp nikon.cc
        BOARD micro
        PORT ${DEVICE})

if(NOT EXISTS $ENV{DEVICE})
    message(WARNING "Device file ${DEVICE} does not exist!")
endif()

message(STATUS "READY. ")
message(STATUS "=================================")
message(STATUS "Device file:  ${DEVICE}")
message(STATUS "=================================")