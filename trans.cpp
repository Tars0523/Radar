#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <pcl_ros/transforms.h>
#include <iostream>
#include <pcl/conversions.h>
#include "nav_msgs/Odometry.h"
#include "pcl_ros/point_cloud.h"
#include <sensor_msgs/point_cloud_conversion.h>
#include <tf/tf.h>
#include <math.h>

sensor_msgs::PointCloud2 cloud_msg;
sensor_msgs::PointCloud out_cloud;
nav_msgs::Odometry odom_ekf;


class PubAndSub
{
private:
    ros::NodeHandle n_;
    ros::Publisher pub_;
    ros::Subscriber sub_1;
    ros::Subscriber sub_2;

public:

    PubAndSub()
    {
        pub_ = n_.advertise<sensor_msgs::PointCloud>("out_cloud", 10);
        sub_1 = n_.subscribe<sensor_msgs::PointCloud2> ("radar/target_list_cartesian",10,&PubAndSub::cloud_callback,this);
        sub_2 = n_.subscribe<nav_msgs::Odometry>("/odom",10,&PubAndSub::odom_callback,this);
        callback();
       
    }

    void cloud_callback (const sensor_msgs::PointCloud2ConstPtr& msg_c){
	cloud_msg=*msg_c;
	std::cout<<"cloud Ok"<<std::endl;
	sensor_msgs::convertPointCloud2ToPointCloud(cloud_msg, out_cloud);
	geometry_msgs::Point32 point;
	
	for(int i = 0 ; i < out_cloud.points.size();i++){
	std::cout<<"TRANS OK"<<std::endl;
    /* Quternion to Euler*/
    tf::Quaternion q(
        odom_ekf.pose.pose.orientation.x,
        odom_ekf.pose.pose.orientation.y,
        odom_ekf.pose.pose.orientation.z,
        odom_ekf.pose.pose.orientation.w
    );
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    std::cout<<"Roll:" <<roll*180/3.141592<<std::endl;
    std::cout<<"Pitch:" <<pitch*180/3.141592<<std::endl;
    std::cout<<"Yaw: "<<yaw*180/3.141592<<std::endl;

    /*X,Y,Z in Radar Frame*/
    double X_r, Y_r, Z_r;
    X_r = out_cloud.points[i].x;   
    Y_r = out_cloud.points[i].y; 
    Z_r = out_cloud.points[i].z;

    /*X,Y,Z in Inertia Frame*/
    double X_i, Y_i, Z_i;
    X_i = cos(yaw)*cos(pitch)*X_r + (-sin(yaw)*cos(roll)+cos(yaw)*sin(pitch)*sin(roll))*Y_r + (sin(yaw)*sin(roll)+cos(yaw)*sin(pitch)*cos(roll))*Z_r;
    Y_i = sin(yaw)*cos(pitch)*X_r + (cos(yaw)*cos(roll)+sin(yaw)*sin(pitch)*sin(roll))*Y_r + (-cos(yaw)*sin(roll)+sin(yaw)*sin(pitch)*cos(roll))*Y_r ;
    Z_i = -sin(pitch)*X_r + cos(pitch)*sin(roll)*Y_r + cos(pitch)*cos(roll)*Z_r ;

    /* Euler compensation */
	out_cloud.points[i].x = X_i + odom_ekf.pose.pose.position.x*1;
	out_cloud.points[i].y = Y_i + odom_ekf.pose.pose.position.y*1;
	out_cloud.points[i].z = Z_i + odom_ekf.pose.pose.position.z*1;
	}
	
	pub_.publish(out_cloud);
	}
	
    void odom_callback(const nav_msgs::Odometry::ConstPtr& msg_o){
	odom_ekf = *msg_o;
	std::cout<<"odom ok"<<std::endl;
	}
    
    void callback(){
       std::cout<<"trans ok"<<std::endl;
       }  
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "multi_node");
    PubAndSub PAS;
    ros::spin();
    return 0;
}
