#pragma once

struct IMUData {  
    double ax, ay, az;  // Accelerometer data
    double gx, gy, gz;  // Gyroscope data
};

struct IMURegisters {
    int samplingRate;        // Sampling rate in [Hz]
    int accelerometerRange;  // Accelerometer measurement range in [g]
    int gyroscopeRange;      // Gyroscope measurement range in [dps]
};