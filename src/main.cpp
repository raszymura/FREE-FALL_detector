/**
 * This project was written as a recruitment task for Embevity.
 * @author Rafal Szymura
 * Date: December 2023
 */

#include <iostream>
#include "IMU.h"
#include "SocketServer.h"

int main()
{
    std::cout << "\n************** Welcome to FF detector! **************\n";

    std::cout << "Server on port: 1234" << '\n';
    SocketServer server("12345");

    server.startListening();

    std::cout << "Receiving IMU Data..." << std::endl;

    //bool endData;  // Flag for end control
    //IMUData receivedData = server.getReceivedData();
while(1){
    server.startListening();
    IMUData imuData = server.getReceivedData();
    std::cout << "Accelerometer: (" << imuData.ax << ", " << imuData.ay << ", " << imuData.az << ")\n";
    std::cout << "Gyroscope:     (" << imuData.gx << ", " << imuData.gy << ", " << imuData.gz << ")\n";
    std::cout << "---------------------------------------------------------------------------------\n";

    //if (receivedData.samplingRate == -1) {
    // IMURegisters receivedData = server.getReceivedData();

    //  endData = true;
    //  std::cout << "Sampling Rate: "          << receivedData.samplingRate        << " Hz" << std::endl;
    //  std::cout << "Accelerometer Range: "    << receivedData.accelerometerRange  << " g"  << std::endl;
    //  std::cout << "Gyroscope Range: "        << receivedData.gyroscopeRange      << " dps" << std::endl;
}
//}
    std::cout << "Done"  << std::endl;

    return 0;
}