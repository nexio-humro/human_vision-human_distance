#ifndef ROS_TOPIC_HPP
#define ROS_TOPIC_HPP

#include <iostream>

#include "ros/ros.h"

#include "zed_interfaces/Objects.h"
#include <MainData.hpp>

namespace RT
{
	bool checkIfObjectAreCloseToCamera(const zed_interfaces::Objects& objects);
	void grab_objects(const zed_interfaces::Objects& objects);
}

#endif
