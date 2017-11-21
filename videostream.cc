#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace std;

int main(int, char**) {

    cv::VideoCapture vcap;
    cv::Mat image;

    const std::string videoStreamAddress = "http://10.201.131.67:9090/stream/video.mjpeg";
    /* it may be an address of an mjpeg stream, 
    e.g. "http://user:pass@cam_address:8081/cgi/mjpg/mjpg.cgi?.mjpg" */

    //check if the videostream is open
    if(!vcap.open(videoStreamAddress)) {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    //Create output window for displaying frames. 
    //It's important to create this window outside of the `for` loop
    //Otherwise this window will be created automatically each time you call
    //`imshow(...)`, which is very inefficient. 

    cv::namedWindow("Output Window");
    cv::namedWindow("Left");
    cv::namedWindow("Right");
    cout<<"cap is opened"<<endl;
    for(;;) {
        if(!vcap.read(image)) {
            std::cout << "No frame" << std::endl;
            cv::waitKey();
        }
        //Mat croppedFrame = frame(Rect(0, frame.rows/2, frame.cols, frame.rows/2));
        cv::Mat imgL = image(cv::Range(0, image.rows), cv::Range(0, image.cols / 2));
        cv::Mat imgR = image(cv::Range(0, image.rows), cv::Range(image.cols / 2 + 1, image.cols));
        cv::imshow("Output Window", image);
        cv::imshow("Left",imgL);
        cv::imshow("Right",imgR);
        if(cv::waitKey(1) >= 0) break;
    }
}
