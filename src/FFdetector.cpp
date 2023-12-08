#include "FFdetector.h"

FFdetector::FFdetector() 
    : interrupt(false), duration(0.0) {}

void FFdetector::setThresholds() {
    /*
    std::cout << "Set detector FF_Threshold values, in the range (-1, 1):\n";
    while (1) {
        std::cout << "-FF_Threshold: ";
        std::cin >> threshold_minus;

        if (threshold_minus < 1 && threshold_minus > -1) {
            break;
        }
        else {
            std::cout << "Incorrect data. Try again.\n";
        }
    }
    while (1) {
        std::cout << "+FF_Threshold: ";
        std::cin >> threshold_plus;

        if (threshold_plus > -1 && threshold_plus < 1) {
            std::cout << "Incorrect data. Try again.\n";
        }
        else if (threshold_plus <= threshold_minus) {
            std::cout << "Incorrect data. The upper threshold must be greater than the lower threshold.\n";
        }
        else {
            break;
        }
    }
    while (1) {
        std::cout << "Enter your minimum detectable free fall duration, in the range (0, 10s), after which detection occurs: ";
        std::cin >> minDuration;

        if (minDuration > 0 && minDuration < 10) {
            std::cout << "Incorrect data. Try again.\n";
        }
        else {
            break;
        }
    }
    std::cout << "---------------------------------------------------------------------------------\n";
    std::cout << "Detected zone is from " << threshold_minus << "g to " << threshold_plus << "g\n";
    std::cout << "Minimum triggering Free-Fall Duration is " << minDuration << "s\n";
    */

   // For testing purposes
    minDuration = 0.6;
    threshold_plus = 0.1;
    threshold_minus = -0.1;
}

void FFdetector::setPeriod(IMURegisters& imuRegisters) {
    samplingPeriod = 1.0 / imuRegisters.samplingRate;
}

void FFdetector::processReceivedData(const IMUData& imuData) {
    simDuration += samplingPeriod;

    // Entering the trigger range
    bool inRange = isInRange(imuData.ax, threshold_minus, threshold_plus) &&
                    isInRange(imuData.ay, threshold_minus, threshold_plus) &&
                    isInRange(imuData.az, threshold_minus, threshold_plus);
    //std::cout << inRange; // For debugging purposes

    // Minimum duration in trigger range, when reached start measuring the duration of the free fall (trigger time is added)
    interrupt = isFreeFallDetected(inRange);

    if (interrupt) {
        DetectedFF freeFall;
        freeFall.imuData = imuData;
        freeFall.fallDuration = duration;
        detectedFreeFalls.push_back(freeFall);
    } //else {}
}

bool FFdetector::isFreeFallDetected(bool inRange) {
    if (inRange) {
        duration += samplingPeriod;
    } else {
        duration = 0;
    }
    
    if (inRange && (duration >= minDuration) ) {
        interrupt = 1;
    } else {
        interrupt = 0;
    }

    return interrupt;
}

bool FFdetector::isInRange(const double& value, const double& threshold_minus, const double& threshold_plus) {
    return  ( (value >= threshold_minus) && (value <= threshold_plus) );
}

double FFdetector::getFreeFallDuration() const {
    return duration;
}

void FFdetector::printFreeFall() const {
    for (int i = 0; i < detectedFreeFalls.size(); i++) {
        const auto& freeFall = detectedFreeFalls[i];
        std::cout << "Detected Fall: (" << std::setprecision(15) << freeFall.imuData.ax << ", " << freeFall.imuData.ay << ", " << freeFall.imuData.az
                << ") for: " << std::setprecision(2) << freeFall.fallDuration << "s\n";
    }
}