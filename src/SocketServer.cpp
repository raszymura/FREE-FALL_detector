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
    try {
        // Deserialization
        //std::istream inputStream(&receiveBuffer);
        //inputStream.read(reinterpret_cast<char*>(&receivedData), sizeof(IMUData));
        int messageType;
        asio::read(socket, asio::buffer(&messageType, sizeof(messageType)));

        switch (messageType) {
            case 1: {
                asio::read(socket, asio::buffer(&receivedRegisters, sizeof(receivedRegisters)));
                break;
            }
            case 2: {   
                asio::read(socket, asio::buffer(&receivedData, sizeof(receivedData)));
                break;
            }
            case 3: {   
                endData = 1;
                break;
            }
            default: std::cerr << "Unknown message type" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error receiving data: " << e.what() << std::endl;
    }
}

IMUData SocketServer::getReceivedData() const {
    return receivedData;
}

IMURegisters SocketServer::getReceivedRegisters() const {
    return receivedRegisters;
}
