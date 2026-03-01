#include "FaceDetection.h"

// Asks user to choose between internal and external camera
int selectCamera(){
    int cam;
    cout << endl;
    cout << "===== SELECT CAMERA =====" << endl;
    cout << "Type 0 - Internal camera" << endl;
    cout << "Type 1 - External camera" << endl;
    cout << "=========================" << endl;
    cout << "Your choice: ";
    cin  >> cam;

    if(cam != 0 && cam != 1){
        cout << "Invalid choice! Using external camera (1) by default." << endl;
        return 1;
    }
    return cam;
}

int main(){
    int choice;
    cout << "===== FACE DETECTION SYSTEM ===============" << endl;
    cout << "Type 1 - Show image from file"               << endl;
    cout << "Type 2 - Live camera feed"                   << endl;
    cout << "Type 3 - Blur faces on camera"               << endl;
    cout << "Type 4 - Safe entrance (auto save to Desktop)" << endl;
    cout << "===========================================" << endl;
    cout << "Your choice: ";
    cin  >> choice;

    if(choice < 1 || choice > 4){
        cout << "Invalid choice! Please restart and enter a number between 1-4." << endl;
        return 1;
    }

    // Option 1 uses a static image, no camera needed
    // Options 2, 3, 4 require camera selection
    int camIndex = 1; // Default: external camera
    if(choice != 1){
        camIndex = selectCamera();
    }

    FaceDetection fd(camIndex); // Constructor: loads model, sets paths, sets camera

    if      (choice == 1) fd.showImage();
    else if (choice == 2) fd.liveCamera();
    else if (choice == 3) fd.blurFaces();
    else if (choice == 4) fd.safeEntrance();

    return 0;
}
