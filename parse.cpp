#include "LandmarkParser.h"
#include "PoseParser.h"

#include <iostream>

int main(void)
{
    LandmarkParser parser("landmarks.txt");

    for (LandmarkParser::const_iterator it = parser.begin(); it != parser.end(); it++) {
    	std::cout << "Landmark x " << it->x << " y " << it->y << " z " << it->z << std::endl;
    }

    PoseParser poseParser("pose.txt");
    for (PoseParser::const_iterator it = poseParser.begin(); it != poseParser.end(); it++) {
    	std::cout << "IMU Quaternion x " << it->quaternion.x << " y " << it->quaternion.y << " z " << it->quaternion.z << std::endl;
    	std::cout << "IMU Position x " << it->position.x << " y " << it->position.y << " z " << it->position.z << std::endl;
    }

    std::cout << parser.size() << " landmarks " << poseParser.size() << " poses " << std::endl;
}
