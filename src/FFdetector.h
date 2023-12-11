#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

#include "IMU.h"


class FFdetector {
private:
    bool interrupt;             // Flag true when minDuration is reached
    bool previousInterrupt;     // Previosus interrupt value, to detect changes

    double minDuration; // Minimum duration in trigger range (minimum time during which all 3-axes of 
    // the accelerometer are between Threshold_minus and Threshold_plus and which causes Interrupt to be triggered))
    double duration;    // Full free-fall duration
    double simDuration; // Full simulation duration

    double threshold_plus;      // Upper (positive) limit of the free-fall zone
    double threshold_minus;     // Lower (negative) limit of the free-fall zone
    double samplingPeriod;

    static int staticFallNumber;

    bool isInRange(const double& value, const double& threshold_minus, const double& threshold_plus);

    struct DetectedFF {
        IMUData imuData;
        double fallDuration;
        double fallStart;
        int fallNumber;
    };
    std::vector<DetectedFF> detectedFreeFalls;

public:
    //FFdetector();

    void setThresholds();
    void setPeriod(IMURegisters& imuRegisters);
    void processReceivedData(const IMUData& imuData);
    bool isFreeFallDetected(bool inRange);
    void printFreeFall() const;
    void printFreeFallResults() const;
};

