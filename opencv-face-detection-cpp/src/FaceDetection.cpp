#include "FaceDetection.h"

// ===================== CONSTRUCTOR =====================
FaceDetection::FaceDetection(int camIndex){

    cameraIndex = camIndex; // Store the selected camera index (0 = internal, 1 = external)

    // Relative paths - files must be in the correct folders (assets/ and models/)
    modelPath = "models/haarcascade_frontalface_default.xml";
    imagePath = "assets/human_image1.jpg";

    // Automatically get Desktop path from Windows system environment variable
    char* userProfile = getenv("USERPROFILE");
    if(userProfile){
        desktopPath = string(userProfile) + "\\Desktop\\";
    } else {
        desktopPath = ""; // Fallback: saves to the current working directory
        cout << "WARNING: Could not find USERPROFILE. Photos will be saved to the current directory." << endl;
    }

    loadModel(); // Load the face detection model on startup
}

// ===================== PRIVATE METHODS =====================

// Loads the pre-trained Haar cascade face detection model
void FaceDetection::loadModel(){
    if(!facedetect.load(modelPath)){
        cout << "ERROR: Could not load model file: " << modelPath << endl;
        cout << "Make sure the .xml file is in the same folder as the executable." << endl;
        exit(1); // Terminate the program if model is missing
    }
    cout << "Model loaded successfully: " << modelPath << endl;
}

// Draws a filled background box and face count text on the top-left corner of the frame
void FaceDetection::drawUI(Mat& img, int faceCount){
    rectangle(img, Point(0,0), Point(250,70), Scalar(50,50,255), FILLED); // Background box for the text
    putText(img, to_string(faceCount) + " FACE FOUND", Point(10,40),
            FONT_HERSHEY_DUPLEX, 1, Scalar(255,255,255), 1); // Displays face count on the screen
}

// Detects faces in the frame and draws red rectangles around them
void FaceDetection::detectAndDraw(Mat& img, vector<Rect>& faces){
    facedetect.detectMultiScale(img, faces, 1.3, 5);
    // 1.3 = scales the image down by 30% at each step
    // 5   = requires at least 5 neighboring detections to count as a face (reduces false positives)

    for(int i = 0; i < faces.size(); i++){
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(50,50,255), 3); // tl = top left, br = bottom right
    }
}

// ===================== OPTION 1 =====================
// Loads a static image from the relative path and runs face detection on it
void FaceDetection::showImage(){
    Mat img = imread(imagePath); // Loads image from the same folder as the executable

    if(img.empty()){
        cout << "ERROR: Could not load image: " << imagePath << endl;
        cout << "Make sure the image file is in the same folder as the executable." << endl;
        return;
    }

    vector<Rect> faces; // List to store detected face coordinates
    detectAndDraw(img, faces);
    drawUI(img, faces.size());

    cout << "Faces detected: " << faces.size() << endl;
    imshow("Frame - Image", img);
    waitKey(0); // Waits until a key is pressed before closing
}

// ===================== OPTION 2 =====================
// Opens the selected camera and detects faces in real time
void FaceDetection::liveCamera(){
    VideoCapture video(cameraIndex); // Opens internal (0) or external (1) camera

    if(!video.isOpened()){
        cout << "ERROR: Could not open camera at index " << cameraIndex << endl;
        return;
    }

    cout << "Live camera started." << endl;

    Mat img; // Empty image matrix to hold each video frame
    while(true){

        if(!video.read(img)){ // If frame cannot be read, exit the loop
            cout << "WARNING: Could not read frame. Exiting..." << endl;
            break;
        }

        vector<Rect> faces; // List to store detected face coordinates
        detectAndDraw(img, faces);
        drawUI(img, faces.size());

        cout << "Faces detected: " << faces.size() << endl;

        imshow("Frame - Live Camera", img);
        waitKey(1);
    }
    video.release();     // Releases the camera resource
    destroyAllWindows(); // Closes all OpenCV windows
    cout << "Camera closed." << endl;
}

// ===================== OPTION 3 =====================
// Opens the selected camera and blurs detected faces in real time
void FaceDetection::blurFaces(){
    VideoCapture video(cameraIndex); // Opens internal (0) or external (1) camera

    if(!video.isOpened()){
        cout << "ERROR: Could not open camera at index " << cameraIndex << endl;
        return;
    }

    cout << "Blur mode started." << endl;

    Mat img; // Empty image matrix to hold each video frame
    while(true){

        if(!video.read(img)){ // If frame cannot be read, exit the loop
            cout << "WARNING: Could not read frame. Exiting..." << endl;
            break;
        }

        vector<Rect> faces; // List to store detected face coordinates
        facedetect.detectMultiScale(img, faces, 1.3, 5);
        // 1.3 = scales the image down by 30% at each step
        // 5   = requires at least 5 neighboring detections to count as a face (reduces false positives)

        for(int i = 0; i < faces.size(); i++){
            // Apply blur BEFORE drawing the rectangle, otherwise the rectangle gets blurred too
            Mat faceROI = img(faces[i]);                      // Crops the face region from the frame
            GaussianBlur(faceROI, faceROI, Size(99,99), 30); // Applies Gaussian blur to the face region
            rectangle(img, faces[i].tl(), faces[i].br(), Scalar(50,50,255), 3); // Draws rectangle around face
        }

        drawUI(img, faces.size());

        cout << "Faces detected: " << faces.size() << endl;

        imshow("Frame - Blur Mode", img);
        waitKey(1);
    }
    video.release();     // Releases the camera resource
    destroyAllWindows(); // Closes all OpenCV windows
    cout << "Camera closed." << endl;
}

// ===================== OPTION 4 =====================
// Opens the selected camera and auto-saves a photo to the Desktop every 10 seconds when a face is detected
void FaceDetection::safeEntrance(){
    VideoCapture video(cameraIndex); // Opens internal (0) or external (1) camera

    if(!video.isOpened()){
        cout << "ERROR: Could not open camera at index " << cameraIndex << endl;
        return;
    }

    cout << "Safe entrance mode started. Photos will be saved to: " << desktopPath << endl;

    Mat img; // Empty image matrix to hold each video frame
    auto lastCapture = chrono::steady_clock::now(); // Used to track time between captures

    while(true){

        if(!video.read(img)){ // If frame cannot be read, exit the loop
            cout << "WARNING: Could not read frame. Exiting..." << endl;
            break;
        }

        vector<Rect> faces; // List to store detected face coordinates
        detectAndDraw(img, faces);
        drawUI(img, faces.size());

        cout << "Faces detected: " << faces.size() << endl;

        // Save a photo to the Desktop every 10 seconds when a face is detected
        auto now_time = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(now_time - lastCapture).count();

        if(faces.size() > 0 && elapsed >= 10){
            time_t now = time(0);
            tm* ltm = localtime(&now);

            // Create a unique filename using the current date and time
            string filename = desktopPath + "face_" +
                to_string(1900 + ltm->tm_year) + "-" +
                to_string(1 + ltm->tm_mon)     + "-" +
                to_string(ltm->tm_mday)        + "_" +
                to_string(ltm->tm_hour)        + "-" +
                to_string(ltm->tm_min)         + "-" +
                to_string(ltm->tm_sec)         + ".jpg";

            imwrite(filename, img); // Saves the current frame as a JPEG image
            cout << "Photo saved: " << filename << endl;
            lastCapture = now_time; // Reset the timer
        }

        imshow("Frame - Safe Entrance", img);
        waitKey(1);
    }
    video.release();     // Releases the camera resource
    destroyAllWindows(); // Closes all OpenCV windows
    cout << "Camera closed." << endl;
}
