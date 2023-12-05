#include "SocketServer.h"

SocketServer::SocketServer(const std::string& serverPort)
    : acceptor(ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), std::stoi(serverPort))),
      socket(ioContext) {

    acceptor.accept(socket);
}

SocketServer::~SocketServer() {
    if (socket.is_open()) {
        socket.close();
    }
}

void SocketServer::startListening() {
    /*try {
        std::cout << "Listening..";
        acceptor.accept(socket);
        asio::streambuf receiveBuffer;
        asio::read(socket, receiveBuffer);
      
        std::istream inputStream(&receiveBuffer);
        inputStream.read(reinterpret_cast<char*>(&receivedData), sizeof(IMUData));

        std::cout << "Accelerometer: (" << receivedData.ax << ", " << receivedData.ay << ", " << receivedData.az << ")\n";
        std::cout << "Gyroscope:     (" << receivedData.gx << ", " << receivedData.gy << ", " << receivedData.gz << ")\n";
        std::cout << "---------------------------------------------------------------------------------\n";

    } catch (const std::exception& e) {
        std::cerr << "Error receiving data: " << e.what() << std::endl;
    }*/
    asio::read(socket, asio::buffer(&receivedData, sizeof(receivedData)));
}

IMUData SocketServer::getReceivedData() const {
    return receivedData;
}

IMURegisters SocketServer::getReceivedRegisters() const {
    return receivedRegisters;
}
