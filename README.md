# OpenCV Face Detection (C++)

A modular face detection project built with **C++ and OpenCV**.

This project demonstrates real-time computer vision techniques including:

- Static image face detection
- Live camera face detection
- Privacy-focused face blurring
- Timed automatic image capture
- Class-based modular architecture

---

## 🚀 Features

- Haar Cascade based face detection
- Real-time video processing
- Gaussian blur for privacy protection
- Automatic timestamped image saving
- Clean modular C++ structure
- CMake build system support

---

## 🏗 Project Architecture

This project is designed using a reusable class-based structure.

- `FaceDetection.h` → Class declaration
- `FaceDetection.cpp` → Implementation
- `main.cpp` → User interface & mode selection

The face detection logic is encapsulated in a reusable module,
allowing easy integration into future computer vision projects.

---

## 📁 Project Structure
opencv-face-detection-cpp/
│
├── src/
│ ├── main.cpp
│ └── FaceDetection.cpp
│
├── include/
│ └── FaceDetection.h
│
├── models/
│ └── haarcascade_frontalface_default.xml
│
├── assets/
│ └── human_image1.jpg
│
├── CMakeLists.txt
├── .gitignore
└── README.md

---

## 📦 Dependencies

This project requires:

- **C++17**
- **OpenCV 4.x**

Required OpenCV modules:

- core
- imgproc
- highgui
- objdetect
- videoio

Make sure OpenCV is properly installed and accessible by CMake.

If OpenCV is not automatically detected, configure it manually:
cmake -DOpenCV_DIR="C:\path\to\opencv\build" ..


---

## 🛠 Build Instructions (CMake)
mkdir build
cd build
cmake ..
cmake --build 


After building, run the executable and choose one of the available modes.

---

## 🎯 Available Modes

1. Static image detection  
2. Live camera face detection  
3. Face blur (privacy mode)  
4. Timed capture (auto-save every 10 seconds)

---

## 🔐 Privacy Note

The blur mode demonstrates a simple privacy-preserving
approach by applying Gaussian blur to detected faces in real-time.

---

## 📚 Credits

This project was inspired by the idea presented in:

https://github.com/Chando0185/face_detection_c-

Note:  
This implementation was written independently and extended with:

- Additional operating modes  
- Modular class-based architecture  
- CMake support  
- Improved project structure  

---

## 📌 Future Improvements

- DNN-based face detection
- Face recognition module
- Cross-platform camera handling
- Performance benchmarking
- Unit testing integration

---

## 👩‍💻 Author

Developed as part of a structured OpenCV learning path
focused on building reusable computer vision components in C++.
