/*
 * PoseParser.cpp
 *
 *  Created on: 2011-02-21
 *      Author: pierre-luc
 */

#include "PoseParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

PoseParser::PoseParser(const std::string& filename) {
	std::ifstream file(filename.c_str(), std::ifstream::in);

	std::string line;
	while(std::getline(file, line)) {
		std::istringstream buffer(line);

		Pose3D pose;
		buffer >> pose.quaternion.x;
		buffer >> pose.quaternion.y;
		buffer >> pose.quaternion.z;
		buffer >> pose.quaternion.w;

		// Skip to the IMU position (col 14)
		double v;
		for (int i = 0; i < 9; i++) {
			buffer >> v;
		}

		buffer >> pose.position.x;
		buffer >> pose.position.y;
		buffer >> pose.position.z;

		poses.push_back(pose);
	}
}

PoseParser::~PoseParser() {
	// TODO Auto-generated destructor stub
}
