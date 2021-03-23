#include <catch.hpp>

#include <limits>
#include <RosTopics.hpp>

#define testOneObject(objectData, description, result)	{ 																		\
													SECTION( (description) ) 											\
													{ 																	\
														human_vision_exchange::Objects objects;											\
														std::vector<human_vision_exchange::ObjectStamped> objectsVector;						\
														objectsVector.push_back( (objectData) );						\
														objects.objects = objectsVector;							\										
														REQUIRE(RT::checkIfObjectAreCloseToCamera(objects) == (result));	\
													}																	\
												}

TEST_CASE("checkIfObjectAreCloseToCamera()", "[RosTopic]")
{	
	human_vision_exchange::ObjectStamped closestObject;
	closestObject.position.z = 0.0;
	
	human_vision_exchange::ObjectStamped farestObject;
	farestObject.position.z = std::numeric_limits<float>::max();
	
	human_vision_exchange::ObjectStamped closerThanDistanceLimitObject;
	closerThanDistanceLimitObject.position.z = MD::getDistanceParameter() - 0.5;
	
	human_vision_exchange::ObjectStamped minimallyCloserThanDistanceLimitObject;
	minimallyCloserThanDistanceLimitObject.position.z = MD::getDistanceParameter() - 0.000000000000000000001;
	
	human_vision_exchange::ObjectStamped fartherThanDistanceLimitObject;
	fartherThanDistanceLimitObject.position.z = MD::getDistanceParameter() + 0.5;
	
	human_vision_exchange::ObjectStamped atDistanceLimitObject;
	atDistanceLimitObject.position.z = MD::getDistanceParameter();
	
	testOneObject(closestObject, "send closest object", true)
	testOneObject(farestObject, "send farest object", false)
	testOneObject(closerThanDistanceLimitObject, "send object which is closer than distance limit", true)
	testOneObject(minimallyCloserThanDistanceLimitObject, "send object which is minimally closer than distance limit", true)
	testOneObject(fartherThanDistanceLimitObject, "send object which is farther than distance limit", false)
	testOneObject(atDistanceLimitObject, "send object which is at distance limit", true)
	
	SECTION( "send two object which are closer than maximum distance" ) 											
	{ 																				
		human_vision_exchange::Objects objects;										
		std::vector<human_vision_exchange::ObjectStamped> objectsVector;						
		objectsVector.push_back( closestObject );									
		objectsVector.push_back( closerThanDistanceLimitObject );						
		objects.objects = objectsVector;															
		REQUIRE(RT::checkIfObjectAreCloseToCamera(objects) == true);	
	}	
	
	SECTION( "send two object which are farther than maximum distance" ) 											
	{ 																			
		human_vision_exchange::Objects objects;										
		std::vector<human_vision_exchange::ObjectStamped> objectsVector;						
		objectsVector.push_back( farestObject );									
		objectsVector.push_back( fartherThanDistanceLimitObject );						
		objects.objects = objectsVector;															
		REQUIRE(RT::checkIfObjectAreCloseToCamera(objects) == false);	
	}	
	
	SECTION( "send more objects where at least one is closer than maximum distance" ) 											
	{ 																			
		human_vision_exchange::Objects objects;										
		std::vector<human_vision_exchange::ObjectStamped> objectsVector;						
		objectsVector.push_back( farestObject );									
		objectsVector.push_back( fartherThanDistanceLimitObject );				
		objectsVector.push_back( closerThanDistanceLimitObject );						
		objects.objects = objectsVector;															
		REQUIRE(RT::checkIfObjectAreCloseToCamera(objects) == true);	
	}	
}
