#include <RosTopics.hpp>

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
	
	void grab_objects(const zed_interfaces::Objects& objects)
	{
		bool result = RT::checkIfObjectAreCloseToCamera(objects);
		
		std_msgs::Bool msg;
        msg.data = result;
        MD::getClientPresentPublisher()->publish(msg);
	}
}
