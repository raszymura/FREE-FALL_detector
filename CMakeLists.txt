cmake_minimum_required(VERSION 3.10)
project(FREE-FALL_detector)

set(ASIO_PATH lib/asio-1.28.0/include)

# Our Project
set(SOURCE_FILES
    src/main.cpp
    src/IMU.cpp
    src/SocketServer.cpp
    src/FFdetector.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${ASIO_PATH})
target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)