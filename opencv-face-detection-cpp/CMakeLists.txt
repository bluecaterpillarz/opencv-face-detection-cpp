cmake_minimum_required(VERSION 3.10)
project(OpenCVFaceDetectionCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(face_app
    src/main.cpp
    src/FaceDetection.cpp
)

target_include_directories(face_app PRIVATE include)
target_link_libraries(face_app PRIVATE ${OpenCV_LIBS})