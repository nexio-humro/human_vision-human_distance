#include <catch.hpp>

#include <limits>

#include "ros/this_node.h"
#include "ros/ros.h"
#include "ros/package.h"

#include <MainData.hpp>

TEST_CASE("Publisher functions", "[MainData]")
{	
	int argc = 0;
	char **argv = nullptr;
	
	ros::init(argc, argv, "test_node");
	ros::NodeHandle node;
	
	std::vector<std::string> publishers;
	
	// before advertise any topic Publisher should be empty
	ros::this_node::getAdvertisedTopics(publishers);
		
	REQUIRE(publishers.size() == 1);
	REQUIRE(MD::getClientPresentPublisher()->getTopic() == "");
	
	std::cout<<"publishers without:"<<std::endl;
	for(size_t i = 0; i < publishers.size(); i++)
	{
		std::cout<<i<<" = "<<publishers.at(i)<<std::endl;
	}
	
	// set publisher
	std::string publisherName = "isClientNear";
	MD::setClientPresentPublisher(node, publisherName);
	ros::this_node::getAdvertisedTopics(publishers);
	
	REQUIRE(publishers.size() == 2);
	std::string setAnswer = "/" + publisherName;
	REQUIRE(MD::getClientPresentPublisher()->getTopic() == setAnswer);
	
	std::cout<<"once set publishers:"<<std::endl;
	for(size_t i = 0; i < publishers.size(); i++)
	{
		std::cout<<i<<" = "<<publishers.at(i)<<std::endl;
	}
	
	// set publisher twice
	std::string publisherName1 = "isNotFarClient1";
	MD::setClientPresentPublisher(node, publisherName1);
	ros::this_node::getAdvertisedTopics(publishers);
	
	REQUIRE(publishers.size() == 2);
	std::string setTwiceAnswer1 = "/" + publisherName1;
	REQUIRE(MD::getClientPresentPublisher()->getTopic() == setTwiceAnswer1);
	
	std::cout<<"twice set publishers (first):"<<std::endl;
	for(size_t i = 0; i < publishers.size(); i++)
	{
		std::cout<<i<<" = "<<publishers.at(i)<<std::endl;
	}
	
	std::string publisherName2 = "isNotFarClient2";
	MD::setClientPresentPublisher(node, publisherName2);	
	ros::this_node::getAdvertisedTopics(publishers);
	
	REQUIRE(publishers.size() == 2);
	std::string setTwiceAnswer2 = "/" + publisherName2;
	REQUIRE(MD::getClientPresentPublisher()->getTopic() == setTwiceAnswer2);
	
	std::cout<<"twice set publishers (second):"<<std::endl;
	for(size_t i = 0; i < publishers.size(); i++)
	{
		std::cout<<i<<" = "<<publishers.at(i)<<std::endl;
	}
}

TEST_CASE("Distance parameters functions", "[MainData]")
{
//	float getDistanceParameter();
//	void setDistanceParameter(float distance);

	float defaultValue = MD::getDistanceParameter();

	MD::setDistanceParameter(1.0);
	REQUIRE(MD::getDistanceParameter() == 1.0);
	
	float minValue = -std::numeric_limits<float>::max();
	MD::setDistanceParameter(minValue);
	REQUIRE(MD::getDistanceParameter() == minValue);
	
	float maxValue = std::numeric_limits<float>::max();
	MD::setDistanceParameter(maxValue);
	REQUIRE(MD::getDistanceParameter() == maxValue);
	
	MD::setDistanceParameter(defaultValue);
	REQUIRE(MD::getDistanceParameter() == defaultValue);
}
