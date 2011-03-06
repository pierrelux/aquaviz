#include "LandmarkParser.h"
#include "PoseParser.h"

#include <iostream>

int main(void)
{
//    LandmarkParser landmarkParser("landmarks.txt");
//    LandmarkParser::const_iterator it;
//    for (it = landmarkParser.begin(); it != landmarkParser.end(); it++) {
//    	std::cout << "Timestamp " << it->first << std::endl;
//
//    	LandmarkParser::Points points = it->second;
//    	LandmarkParser::Points::iterator pointsIt;
//    	for (pointsIt = points.begin(); pointsIt != points.end(); pointsIt++) {
//    		std::cout << "		" << " x " << pointsIt->x << " y " << pointsIt->y << " z " << pointsIt->z << std::endl;
//    	}
//    }

    PoseParser poseParser("pose.txt");
    PoseParser::const_iterator itPose;

    for (itPose = poseParser.begin(); itPose != poseParser.end(); itPose++) {
    	std::cout << "Timestamp " << itPose->first << std::endl;

    	PoseParser::Poses poses = itPose->second;
    	PoseParser::Poses::iterator posesIt;
    	for (posesIt = poses.begin(); posesIt != poses.end(); posesIt++) {
    		std::cout << "		" << " x " << posesIt->position.x << " y " << posesIt->position.y << " z " << posesIt->position.z << std::endl
    				  << "		" << " x " << posesIt->quaternion.x << " y " << posesIt->quaternion.y << " z " << posesIt->quaternion.z << " w " << posesIt->quaternion.w << std::endl;
    	}
    }
}
