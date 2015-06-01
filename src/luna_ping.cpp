#include "ros/ros.h"
#include "std_msgs/String.h"
#include "stdlib.h"
#include <ctime>

void pingRecieved(const std_msgs::String::ConstPtr& msg);

int counter = 0;

int main(int argc, char **argv) {
	//Init ros
	ros::init(argc, argv, "luna_ping");
	ros::NodeHandle nh;
	ros::Rate rate(5); //5Hz
	
	//Publishers
	ros::Publisher serverPing = nh.advertise<std_msgs::String>("serverPing", 1);
	ros::Publisher driveCommands = nh.advertise<std_msgs::String>("driveCommands",1);

	//Subscribers
	ros::Subscriber clientPing = nh.subscribe("clientPing", 1, pingRecieved);
	ros::spin();	

	//Main Loop LOOP NOT EXECUTING
	while(ros::ok()) {
		if(++counter>=5) {
			std_msgs::String msg;
			msg.data = '0';
			driveCommands.publish(msg);
			counter = 0;
		}
			
		//Send PING to client
		std_msgs::String msg;
		msg.data = "PING";
		serverPing.publish(msg);

		rate.sleep();
	}
}

void pingRecieved(const std_msgs::String::ConstPtr& msg) {
	//Reset counter
	counter = 0;
}

