#ifndef FACEDETECTION_H
#define FACEDETECTION_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

using namespace cv;
using namespace std;

class FaceDetection {

private:
    CascadeClassifier facedetect;   // Haar cascade face detector object
    string modelPath;               // Path to the XML model file
    string imagePath;               // Relative path to the static image
    string desktopPath;             // Desktop path for saving photos
    int cameraIndex;                // 0 = internal camera, 1 = external camera

    void loadModel();                         // Loads the cascade model (called in constructor)
    void drawUI(Mat& img, int faceCount);     // Draws background box and face count text on frame
    void detectAndDraw(Mat& img, vector<Rect>& faces); // Detects faces and draws rectangles

public:
    // Constructor: loads model, sets paths, takes camera index as parameter
    FaceDetection(int camIndex = 1);

    void showImage();       // Option 1: Detect faces on a static image file
    void liveCamera();      // Option 2: Live camera feed with face detection
    void blurFaces();       // Option 3: Blur detected faces on live feed
    void safeEntrance();    // Option 4: Auto-save photo to Desktop when face detected
};

#endif
