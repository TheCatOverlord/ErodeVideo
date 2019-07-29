#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv){
    VideoCapture cap(0);\
    int sizeOfKernel = 3;
    if (cap.isOpened() == false){
        cout << "[Failure] Failed to open video feed." << endl;
        return 1;
    }
    String windowNameOriginal = "Original video feed";
    String windowNameErode = "Eroded video feed";
    namedWindow(windowNameOriginal, WINDOW_NORMAL);
    namedWindow(windowNameErode, WINDOW_NORMAL);
    cout << "The current kernel size is " << sizeOfKernel << endl;

    while (true){
        Mat frame;
        Mat frameEroded;
        bool bSuccess = cap.read(frame);
        if(bSuccess == false){
            cout << "[Failure] Failed to grab frame. (Disconnected?)" << endl;
            break;
        }
        erode(frame, frameEroded, getStructuringElement(MORPH_ERODE, Size(sizeOfKernel,sizeOfKernel)));
        imshow(windowNameOriginal, frame);
        imshow(windowNameErode, frameEroded);
        char key = waitKey(10);
        if (key == 27){
            cout << "[Note] ESC key was pressed by the user. Stopping video feed." << endl;
            break;
        }
        if (key == 119) {
            sizeOfKernel = sizeOfKernel + 2;
            if (sizeOfKernel > 100) {
                cout << "[Error] Kernel size would be too large." << endl;
                sizeOfKernel = sizeOfKernel - 2;
            }
            else {
                cout << "[Note] The new kernel size is " << sizeOfKernel << endl;
            }
        }
        if (key == 115) {
            sizeOfKernel = sizeOfKernel - 2;
            if (sizeOfKernel < 3) {
                cout << "[Error] Kernel size would be too small." << endl;
                sizeOfKernel = sizeOfKernel + 2;
            }
            else {
                cout << "[Note] The new kernel size is " << sizeOfKernel << endl;
            }
        }
    }
    destroyAllWindows();
    return 0;
}