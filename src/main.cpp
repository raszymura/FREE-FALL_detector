/**
 * This project was written as a recruitment task for Embevity.
 * @author Rafal Szymura
 * Date: December 2023
 */

#include <iostream>
#include <iomanip>

#include "IMU.h"
#include "SocketServer.h"
#include "FFdetector.h"


int main() {
    std::cout << "\n************** Welcome to FREE-FALL detector! **************\n";
    
    FFdetector detector;
    detector.setThresholds();
    
    std::cout << "Open IMU_simulator.exe and upload the simulation values.\nWaiting for connection...\n";

    SocketServer server("12345");
    std::cout << "Port: 1234" << '\n';

    server.startListening();

    IMURegisters imuRegisters = server.getReceivedRegisters();

    std::cout << "-------------------------Received values:---------------------------------------\n";
    std::cout << "Sampling rate:                   " << imuRegisters.samplingRate        << " Hz"   << "\n";
    std::cout << "Accelerometer measurement range: " << imuRegisters.accelerometerRange  << " g"    << "\n";
    std::cout << "Gyroscope measurement range:     " << imuRegisters.gyroscopeRange      << " dps"  << "\n";
    std::cout << "---------------------------------------------------------------------------------\n";

    detector.setPeriod(imuRegisters);

    std::cout << std::fixed << std::setprecision(15);

    int dataCount = 0;
    while (1) {
        server.startListening();

        if (server.endData == 1) {
            break;
        }

        IMUData imuData = server.getReceivedData();

        detector.processReceivedData(imuData); // FF detector

        // std::cout << "Accelerometer: (" << imuData.ax << ", " << imuData.ay << ", " << imuData.az << ")\n";
        // std::cout << "Gyroscope:     (" << imuData.gx << ", " << imuData.gy << ", " << imuData.gz << ")\n";
        // std::cout << "---------------------------------------------------------------------------------\n";
        dataCount++;
    }
    std::cout << "Number of received values: " << dataCount << " in "
    << std::setprecision(2) << dataCount * (1.0 / imuRegisters.samplingRate) << "s\n";

    int showFFvalues;
    std::cout << "Do you want to display detected FF values? Type 1\n";
    std::cin >> showFFvalues;

    if (showFFvalues == 1) {
        detector.printFreeFall();
    }
    std::cout << "Results"  << std::endl;
    double ffDuration = detector.getFreeFallDuration();

    return 0;
}