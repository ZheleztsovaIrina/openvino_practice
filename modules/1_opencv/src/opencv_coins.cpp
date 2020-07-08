#include "opencv_coins.hpp"
#include <opencv2/imgproc.hpp>
#include <vector>
#include <math.h>

using namespace cv;

unsigned countCoins(const Mat& img) {
    Mat gray, thresh;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    threshold(gray, thresh, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);
    morphologyEx(thresh, thresh, MORPH_CLOSE, Mat::ones(3, 3, CV_8U), Point(-1, -1), 3);
    distanceTransform(thresh, thresh, DIST_L2, 5);
    double dist_transform=0.0;
    minMaxLoc(thresh,0, &dist_transform);
    threshold(thresh,thresh, 0.7*dist_transform,255, THRESH_BINARY);
    thresh.convertTo(thresh, CV_8U);
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    int ncomp = contours.size();
    int sum = 0;
    double radius;
    for (int i = 0; i < ncomp; ++i) {
        radius = sqrt(contourArea(contours[i]) /CV_PI);
        if (radius > 11) {
            sum += 2;
        }
        else {
            sum += 1;
        }
    }
    return sum;
}
