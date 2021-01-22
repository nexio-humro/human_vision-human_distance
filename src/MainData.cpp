#include <MainData.hpp>

namespace
{
	ros::Publisher clientPresentPublisher;
	float minimalDistance = 1.2;
}

namespace MD
{
	const ros::Publisher* getClientPresentPublisher()
	{
		return &clientPresentPublisher;
	}
	
	void setClientPresentPublisher(ros::NodeHandle& node, std::string topicName)
	{		
		clientPresentPublisher = node.advertise<std_msgs::Bool>(topicName.c_str(), 10);
	}
	
	float getDistanceParameter()
	{
		return minimalDistance;
	}
	
	void setDistanceParameter(float distance)
	{
		minimalDistance = distance;
	}
}
