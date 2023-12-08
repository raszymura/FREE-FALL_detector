#pragma once

#include <iostream>
#include <asio.hpp>
#include "IMU.h"

class SocketServer {
private:
    asio::io_context ioContext;
    asio::ip::tcp::acceptor acceptor;
    asio::ip::tcp::socket socket;
    IMUData receivedData;
    IMURegisters receivedRegisters;

public:
    SocketServer(const std::string& serverPort);
    ~SocketServer();

    void startListening();
    IMUData getReceivedData() const;
    IMURegisters getReceivedRegisters() const;

    bool endData;  // Flag for end control
};
