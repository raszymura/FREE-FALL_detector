# Free Fall Detector

## Overview

This project implements a Free Fall Detector module in C++ that processes measurement data from a simulator to detect the free fall of a device.

## Features
- Free Fall detection: The module identifies the free fall state of the device based on accelerometer data. Free fall is defined as the condition where accelerations from all 3 axes are within a certain range of values around 0 g (FREE-FALL Zone) for a specified duration (FF duration).
- Notifying the user about Free Fall detection.
- Configurability: The algorithm's sensitivity and time constant can be configured without the need for software recompilation.

## Compiler
GCC

## Build system:
Cmake

## Clone the repository
`git clone https://github.com/raszymura/FREE-FALL_detector`

## Navigate to the project directory
`cd FREE-FALL_detector`
`cd build`

## Compile the code
`make`

## Run program
`cd FREE-FALL_detector`
`cd build`
`.\FREE-FALL_detector`