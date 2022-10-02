

// import opencv library
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

// import c++ library
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <vector>


// namespaces
using namespace std;
using namespace cv;


// video warping into required size
int main()
{
    Mat frame, frame2;
    VideoCapture vid(0);
    namedWindow("Normal_webcam", WINDOW_AUTOSIZE);
    namedWindow("Warped_webcam");

    if (!vid.isOpened())
    {
        cout << "Error no camera stream" << endl;
        return -1;
    }
    while (vid.read(frame))
    {

        Mat im_src = imread("C:/Users/sagar/Downloads/10455130.jpg"); // image from webcam capture to define source and destination points
        // Four corners of the book in source image
        vector<Point2f> pts_src;
        pts_src.push_back(Point2f(445, 385));
        pts_src.push_back(Point2f(610, 385));
        pts_src.push_back(Point2f(270, 683));
        pts_src.push_back(Point2f(815, 683));

        // Read destination image.
        Mat Blankdisplay = Mat::zeros(Size(1024, 683), CV_8UC1);
        // Four corners of the book in destination image.
        vector<Point2f> pts_dst;
        pts_dst.push_back(Point2f(445, 385));
        pts_dst.push_back(Point2f(610, 385));
        pts_dst.push_back(Point2f(435, 683));
        pts_dst.push_back(Point2f(650, 683));

        // Calculate Homography
        Mat Matrix = findHomography(pts_src, pts_dst, INTER_LINEAR | WARP_INVERSE_MAP);

        //Mat Matrix = getPerspectiveTransform(srcPoints, dscPoints);
        warpPerspective(frame, frame2, Matrix, Size());

        imshow("Normal_webcam", frame);
        imshow("Warped_webcam", frame2);

        int fps = 40;
        if (waitKey(1000 / fps) >= 0)
            break;
    }
    return 1;

    vid.release();
    destroyAllWindows();

}


