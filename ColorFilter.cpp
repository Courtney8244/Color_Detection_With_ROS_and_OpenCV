#include "ColorFilter.h"

using namespace std;
using namespace cv;

Mat blueMat;
Mat blueThresh;
Mat blueContourImage;
Mat blueContourMask;
Mat blueCupColor;
vector<Mat> blueContours;
vector<Vec4i> blueHierarchy;

Mat greenMat;
Mat greenThresh;
Mat greenContourImage;
Mat greenContourMask;
Mat greenCupColor;
vector<Mat> greenContours;
vector<Vec4i> greenHierarchy;

Mat redMat;
Mat redThresh;
Mat redContourImage;
Mat redContourMask;
Mat redCupColor;
vector<Mat> redContours;
vector<Vec4i> redHierarchy;

Mat blueGreenShowCup;
Mat greenRedShowCup;
Mat allThreeCup;

void ColorFilter::processImage(cv::Mat img) {
    _frame = img;
    split();
    findBlue();
    findGreen();
    findRed();
    findBGR();
    // showResult();
}

void ColorFilter::split() {
    cv:: split(_frame, _chans);
}

void ColorFilter::showResult() {
    // VideoCapture cap("./three_cups.avi");
   
    
    //Problem 1

    // namedWindow("bluecup");
    // imshow("bluecup", _frame);

    //Problem 2

    // namedWindow("blue2cup");
    // namedWindow("redcup");
    // namedWindow("greencup");
    // imshow("blue2cup", _chans[0]);
    // imshow("greenCup", _chans[1]);
    // imshow("redCup", _chans[2]);

    // Problem 3 Blue Subtraction
    // namedWindow("blueMat");
    // imshow("blueMat", blueMat);

    // Problem 3 Blue Threshold
    // namedWindow("blueThresh");
    // imshow("blueThresh", blueThresh);

    // Problem 3 Largest Blue Blob
    // namedWindow("blueMask");
    // imshow("blueMask", blueContourImage);
    // imshow("blueMask", blueCupColor);

    // Problem 4 Green Subtraction
    // namedWindow("greenMat");
    // imshow("greenMat", greenMat);

    // Problem 4 Green Threshold
    // namedWindow("greenThresh");
    // imshow("greenThresh", greenThresh);

    // Problem 4 Largest Green Blob
    // namedWindow("greenMask");
    // imshow("greenMask", greenContourImage);
    // imshow("greenMask", greenCupColor);

    // Problem 5 Red subtraction
    // namedWindow("redMat");
    // imshow("redMat", redMat);

    // Problem 5 Red Threshhold
    // namedWindow("redThreshold");
    // imshow("redThreshold", redThresh);

    // Problem 5 Largest Red Blob
    // namedWindow("redMask");
    // imshow("redMask", redContourImage);
    // imshow("redMask", redCupColor);

    // Problem 6 All Three
    // namedWindow("AllThree");
    // imshow("AllThree", allThreeCup);


    // waitKey(100);
}

void ColorFilter::findBlue() {
    cv::subtract (_chans[0], _chans[2], blueMat);
    cv::threshold(blueMat, blueThresh, 50, 255, cv::THRESH_BINARY);
    cv::findContours(blueThresh, blueContours, blueHierarchy, cv:: RETR_CCOMP, cv:: CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for(int i = 0; i < blueContours.size(); i++){
        int contourSize = cv::contourArea(blueContours[i]);
        if(contourSize > maxContourSize){
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }

    blueContourImage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(blueContourImage, blueContours, maxSizeContour, cv::Scalar(255, 255, 255), 
                    cv::LineTypes::FILLED, 8, blueHierarchy);

    blueContourMask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours( blueContourMask, blueContours, maxSizeContour, cv::Scalar(255), 
                    cv::LineTypes::FILLED, 8, blueHierarchy);

    blueCupColor = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    _frame.copyTo(blueCupColor, blueContourMask);
        
}

void ColorFilter::findGreen() {
    cv::subtract (_chans[1], _chans[0], greenMat);
    cv::threshold(greenMat, greenThresh, 50, 255, cv::THRESH_BINARY);
    cv::findContours(greenThresh, greenContours, greenHierarchy, cv:: RETR_CCOMP, cv:: CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for(int i = 0; i < greenContours.size(); i++){
        int contourSize = cv::contourArea(greenContours[i]);
        if(contourSize > maxContourSize){
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }

    greenContourImage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(greenContourImage, greenContours, maxSizeContour, cv::Scalar(255, 255, 255), 
                    cv::LineTypes::FILLED, 8, greenHierarchy);

    greenContourMask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours( greenContourMask, greenContours, maxSizeContour, cv::Scalar(255), 
                    cv::LineTypes::FILLED, 8, greenHierarchy);

    greenCupColor = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    _frame.copyTo(greenCupColor, greenContourMask);
}

void ColorFilter::findRed() {
     cv::subtract (_chans[2], _chans[1], redMat);
     cv::threshold(redMat, redThresh, 50, 255, cv::THRESH_BINARY);
     cv::findContours(redThresh, redContours, redHierarchy, cv:: RETR_CCOMP, cv:: CHAIN_APPROX_SIMPLE);

     int maxSizeContour = 0;
     int maxContourSize = 0;
     for(int i = 0; i < redContours.size(); i++){
         int contourSize = cv::contourArea(redContours[i]);
         if(contourSize > maxContourSize){
             maxSizeContour = i;
             maxContourSize = contourSize;
         }
     }

     redContourImage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
     drawContours(redContourImage, redContours, maxSizeContour, cv::Scalar(255, 255, 255),
                    cv::LineTypes::FILLED, 8, redHierarchy);

    redContourMask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(redContourMask, redContours, maxSizeContour, cv::Scalar(255),
                    cv::LineTypes::FILLED, 8, redHierarchy);

    redCupColor = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    _frame.copyTo(redCupColor, redContourMask);
}

void ColorFilter::findBGR() {
    cv::bitwise_or(blueCupColor, greenCupColor, blueGreenShowCup);
    cv::bitwise_or(greenCupColor, redCupColor, greenRedShowCup);
    cv::bitwise_or(blueGreenShowCup, greenRedShowCup, allThreeCup);

}

cv::Mat ColorFilter::getBlueImage(){
    return blueCupColor;
}

cv::Mat ColorFilter::getGreenImage(){
    return greenCupColor;
}

cv::Mat ColorFilter::getRedImage(){
    return redCupColor;
}

cv::Mat ColorFilter::getBGRImage(){
    return allThreeCup;
}