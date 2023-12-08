#pragma once

#include "IMU.h"
#include <iostream>

class FFdetector {
private:
    bool interrupt;     // Flag true when minDuration is reached

    double minDuration; // Minimum duration in trigger range
    double duration;    // Full free-fall duration
    double simDuration; // Full simulation duration

    double threshold_plus;
    double threshold_minus;
    double samplingPeriod;

    bool isInRange(double value, double threshold_minus, double threshold_plus);
public:
    FFdetector();

    void setThresholds();
    void setPeriod(IMURegisters& imuRegisters);
    void processReceivedData(const IMUData& imuData);
    bool isFreeFallDetected(bool inRange);
    double getFreeFallDuration() const;
};

/*
Description of variables, for more information go to the documentation.
• Interrupt - flag, true when the IMU reaches the free fall state
• minDuration - minimum time during which all 3-axes of the accelerometer are between 
• Threshold_minus and Threshold_plus and which causes Interrupt to be triggered
• Threshold_plus - upper (positive) limit of the free-fall zone
• Threshold_minus - lower (negative) limit of the free-fall zone
• Duration - duration of free fall
*/

