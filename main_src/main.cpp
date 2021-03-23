// include ros
#include "ros/ros.h"
#include "ros/package.h"

#include <RosTopics.hpp>

int main(int argc, char **argv) 
{
	ros::init(argc, argv, "human_distance");
	ros::NodeHandle node("/human_distance/");
	
	ros::Subscriber objectsGetter = node.subscribe("/human_zed_talker/objects", 1000, RT::grab_objects);
	MD::setClientPresentPublisher(node, "isClientPresent");
	
	ros::spin();
	
	return 0;
}

