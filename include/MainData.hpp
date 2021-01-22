#ifndef MAIN_DATA_HPP
#define MAIN_DATA_HPP

#include <iostream>

#include "ros/ros.h"
#include "std_msgs/Bool.h"

namespace MD
{
	const ros::Publisher* getClientPresentPublisher();
	void setClientPresentPublisher(ros::NodeHandle& node, std::string topicName);
	
	float getDistanceParameter();
	void setDistanceParameter(float distance);
}

#endif
