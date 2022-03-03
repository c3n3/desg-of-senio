

cmake_minimum_required(VERSION 3.9)

project(Common VERSION 1.0.1 DESCRIPTION "mylib description")

add_library(Common SHARED
    src/EncoderMessage.cpp
    src/ButtonMessage.cpp
    src/Capabilities.cpp
    src/HexStringSerializer.cpp
    src/Message.cpp
    src/MessageId.cpp
    src/PwmMessage.cpp
    src/StepperMotorMessage.cpp
    src/Subscriber.cpp
    src/Timer.cpp
)

target_include_directories(Common PRIVATE ./include/)
