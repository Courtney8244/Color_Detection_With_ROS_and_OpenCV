#include <ros/ros.h>
#include "ROSInterface.h"
#include "ColorFilter.h"



ROSInterface::ROSInterface(ColorFilter &cf):
    cf(cf), it(nh) {
    printColor = it.subscribe("/kinect2/hd/image_color", 1, &ROSInterface::imageCallBack, this);
    pubBlueImage = it.advertise("blue2", 1);
    pubGreenImage = it.advertise("green2", 1);
    pubRedImage = it.advertise("red2", 1);
    pubBGRImage = it.advertise("bgr2", 1);

    }



void ROSInterface::imageCallBack(const sensor_msgs::ImageConstPtr& msg){
    cv_bridge::CvImagePtr cv_ptr;

    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    cv::Mat cv_image = cv_ptr->image;
    cf.processImage(cv_image);

    cv::Mat finalBlue = cf.getBlueImage();
    cv::Mat finalGreen = cf.getGreenImage();
    cv::Mat finalRed = cf.getRedImage();
    cv::Mat finalBGR = cf.getBGRImage();


    sensor_msgs::ImagePtr printBlue = cv_bridge::CvImage(std_msgs::Header(), "bgr8", finalBlue).toImageMsg();
    sensor_msgs::ImagePtr printGreen = cv_bridge::CvImage(std_msgs::Header(), "bgr8", finalGreen).toImageMsg();
    sensor_msgs::ImagePtr printRed = cv_bridge::CvImage(std_msgs::Header(), "bgr8", finalRed).toImageMsg();
    sensor_msgs::ImagePtr printBGR = cv_bridge::CvImage(std_msgs::Header(), "bgr8", finalBGR).toImageMsg();

    pubBlueImage.publish(printBlue);
    pubGreenImage.publish(printGreen);
    pubRedImage.publish(printRed);
    pubBGRImage.publish(printBGR);

}

