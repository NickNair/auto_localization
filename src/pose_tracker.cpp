#include <ros/ros.h>
#include <iostream>
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include <ros/package.h>
using std::cerr;
using std::endl;
#include <fstream>
#include <cstdlib> 

class Pose_Tracker {

    private:
    std::ofstream outdata;
    std::ifstream indata; 
    ros::Publisher InitialPose;
    ros::Subscriber  RobotPose;
    std::string path = ros::package::getPath("auto_localization").c_str(); 

    public:
    Pose_Tracker(ros::NodeHandle *nh) {

        InitialPose = nh->advertise<geometry_msgs::PoseWithCovarianceStamped>("/initialpose", 10, true); 
           
        path = path +"/files/pose.txt";

        indata.open(path);

        if(!indata) 
        { 
            cerr << "Error: file could not be opened" << endl;
            exit(1);
        }

        float num[7];

        for(int i = 0; i<=6; i++)
        {
            indata >> num[i];
        }
        indata.close();

        geometry_msgs::PoseWithCovarianceStamped Stored_Pose;
        Stored_Pose.header.frame_id = "map";
        Stored_Pose.header.stamp = ros::Time::now();
        Stored_Pose.pose.pose.position.x = num[0];
        Stored_Pose.pose.pose.position.y = num[1];
        Stored_Pose.pose.pose.position.z = num[2];
        Stored_Pose.pose.pose.orientation.x = num[3];
        Stored_Pose.pose.pose.orientation.y = num[4];
        Stored_Pose.pose.pose.orientation.z = num[5];
        Stored_Pose.pose.pose.orientation.w = num[6];

        InitialPose.publish(Stored_Pose);
        ros::spinOnce();

        RobotPose = nh->subscribe("/robot_pose", 1000, &Pose_Tracker::callback, this);
        
    }

    void callback(const geometry_msgs::Pose::ConstPtr& msg) {

        outdata.open(path); 
        if( !outdata ) 
        { 
            cerr << "Error: file could not be opened" << endl;
            exit(1);
        }

        outdata <<msg->position.x<<" "<<msg->position.y<<" "<< msg->position.z<<" ";
        outdata <<msg->orientation.x<<" "<<msg->orientation.y<<" "<<msg->orientation.z<<" "<<msg->orientation.w<<" ";
        outdata.close();
    }

};
int main (int argc, char **argv)
{
    ros::init(argc, argv, "Pose_Tracker");
    ros::NodeHandle nh;
    Pose_Tracker nc = Pose_Tracker(&nh);
    ros::spin();
}