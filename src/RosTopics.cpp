#include <RosTopics.hpp>

namespace
{
	bool distanceVerificationActivated = false;
	ros::Duration maximumDifferenceTimeBetweenIterations(0, 200000000); // in nanosec
	ros::Duration minimumDistanceVerificationTime(3, 0); // in nanosec
	ros::Time verificationStartingTime;
	ros::Time previousIterationTime;
}

namespace RT
{
	bool checkIfObjectAreCloseToCamera(const zed_interfaces::Objects& objects)
	{
		bool result = false;
		
		for(size_t i = 0; i < objects.objects.size(); i++)
		{
			if(objects.objects[i].position.z <= MD::getDistanceParameter())
			{
				result = true;
			}
		}
		
		return result;
	}
	
	bool checkIfDifferenceBetweenIteretionsIsOk(ros::Time presentIterationTime)
	{
		bool result = false;
		
		ros::Duration timeDifference;
		timeDifference = presentIterationTime - previousIterationTime;
		
		if(timeDifference < maximumDifferenceTimeBetweenIterations)
		{
			result = true;
		}
		
		return result;
	}
	
	bool checkIfObjectIsPresentLongEnough(ros::Time presentIterationTime)
	{
		bool result = false;
		
		ros::Duration timeDifference;
		timeDifference = presentIterationTime - verificationStartingTime;
		
		if(timeDifference > minimumDistanceVerificationTime)
		{
			result = true;
		}
		
		return result;
	}
	
	void grab_objects(const zed_interfaces::Objects& objects)
	{
		bool isPresent = false;
		
		bool objectIsClose = RT::checkIfObjectAreCloseToCamera(objects);
		
		if(objectIsClose == true)
		{
			bool differenceBetweenIterationsOk = checkIfDifferenceBetweenIteretionsIsOk(objects.objects[0].header.stamp);
			
			if(differenceBetweenIterationsOk == true)
			{
				if(distanceVerificationActivated == true)
				{
					bool isObjectPresentLongEnough = checkIfObjectIsPresentLongEnough(objects.objects[0].header.stamp);
					
					if(isObjectPresentLongEnough == true)
					{
						isPresent = true;
					}
				}
				else
				{
					verificationStartingTime = objects.objects[0].header.stamp;
					distanceVerificationActivated = true;
				}
			}
			else
			{
				distanceVerificationActivated = false;
			}
		}
		else
		{
			distanceVerificationActivated = false;
		}
		
		if(objects.objects.size() > 0)
		{
			previousIterationTime = objects.objects[0].header.stamp;
		}
		
//		std::cout<<"grab_objects():isPresent = "<<isPresent<<", distanceVerificationActivated = "<<distanceVerificationActivated<<", objectIsClose = "<<objectIsClose<<std::endl;
		
		std_msgs::Bool msg;
        msg.data = isPresent;
        MD::getClientPresentPublisher()->publish(msg);
	}
}
