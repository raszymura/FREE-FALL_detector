#include "FFdetector.h"

#include <limits>

int FFdetector::staticFallNumber = 0;

void FFdetector::setThresholds() {
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

        if ((threshold_plus < 1 && threshold_plus > -1) && (threshold_plus >= threshold_minus) ) {
            break;
        }
        else if (threshold_plus < threshold_minus) {
            std::cout << "Incorrect data. The upper threshold must be greater or equal than the lower threshold.\n";
        }
        else {
            std::cout << "Incorrect data. Try again.\n";
        }
    }
    while (1) {
        std::cout << "Enter your minimum detectable Free-Fall Duration, in the range (0, 10s): ";
        std::cin >> minDuration;

        if (minDuration > 0 && minDuration < 10) {
            break;
        }
        else {
            std::cout << "Incorrect data. Try again.\n";
        }
    }
    std::cout << "---------------------------------------------------------------------------------\n";
    std::cout << "Detected zone is from " << threshold_minus << "g to " << threshold_plus << "g\n";
    std::cout << "Minimum triggering Free-Fall Duration is " << minDuration << "s\n";
    std::cout << "---------------------------------------------------------------------------------\n";

    // For testing purposes
    /*
    minDuration = 0.6;
    threshold_plus = 0.1;
    threshold_minus = -0.1;
    */
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

    // Minimum duration in trigger range,
    // when reached - start measuring the duration of the free fall (trigger time is added)
    interrupt = isFreeFallDetected(inRange);

    if (interrupt) {
        DetectedFF freeFall;
        freeFall.imuData = imuData;
        freeFall.fallDuration = duration;
        
        freeFall.fallStart = simDuration - duration;
        if ( (interrupt == 1) && (previousInterrupt == 0) ) {
            FFdetector::staticFallNumber++;
        }
        freeFall.fallNumber = FFdetector::staticFallNumber;

        detectedFreeFalls.push_back(freeFall);
    }
    previousInterrupt = interrupt;
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

void FFdetector::printFreeFall() const {
    if (FFdetector::staticFallNumber == 0) {
        std::cout << "No Values.\n";
    } else {
        for (int i = 0, j = 1; i < detectedFreeFalls.size(); i++) {
            const auto& freeFall = detectedFreeFalls[i];

            if (freeFall.fallNumber == j) {
                    std::cout << "\n";
                    j++;
            }

            std::cout << "Free-Fall number: " << freeFall.fallNumber << " Accelerometer: (" << std::setprecision(15) 
            << freeFall.imuData.ax << ", " << freeFall.imuData.ay << ", " << freeFall.imuData.az
            << ") for: " << std::setprecision(2) << freeFall.fallDuration << "s, started in: " << freeFall.fallStart << "s \n";
        }
    }
}

void FFdetector::printFreeFallResults() const {
    std::cout << "\n======================= Detected " << FFdetector::staticFallNumber << " Free-Falls: =======================\n";
    
    if (FFdetector::staticFallNumber == 0) {
        std::cout << "No Free-Fall.\n";
    }
    
    for (int j = 1; j <= FFdetector::staticFallNumber; j++) {
        for (int i = 0; i < detectedFreeFalls.size(); i++) {
            const auto& freeFall = detectedFreeFalls[i];
            if (freeFall.fallNumber == j) {
                std::cout << freeFall.fallNumber << " Free-Fall started in: " << freeFall.fallStart << "s \n";
                break;
            }    
        }
    }
}