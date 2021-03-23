#ifndef ROS_TOPIC_HPP
#define ROS_TOPIC_HPP

#include <iostream>

#include "ros/ros.h"

#include "human_vision_exchange/Objects.h"
#include <MainData.hpp>

namespace RT
{
	bool checkIfObjectAreCloseToCamera(const human_vision_exchange::Objects& objects);
	bool checkIfDifferenceBetweenIterationsIsOk(ros::Time presentIterationTime);
	bool checkIfObjectIsPresentLongEnough(ros::Time presentIterationTime);
	void grab_objects(const human_vision_exchange::Objects& objects);
}

#endif
