#include <ros/ros.h>
#include "ROSInterface.h"
#include "ColorFilter.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "listener");
    ColorFilter cf;
    ROSInterface rosInter(cf);
        ros::spin();
        return 0;
}