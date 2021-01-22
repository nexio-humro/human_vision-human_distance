// include ros
#include "ros/ros.h"
#include "ros/package.h"

#include <RosTopics.hpp>

int main(int argc, char **argv) 
{
	ros::init(argc, argv, "human_detection");
	ros::NodeHandle node("/human_detection/");
	
	ros::Subscriber objectsGetter = node.subscribe("/zed2/zed_node/obj_det/objects", 1000, RT::grab_objects);
	MD::setClientPresentPublisher(node, "isClientPresent");
	
	ros::spin();
	
	return 0;
}

