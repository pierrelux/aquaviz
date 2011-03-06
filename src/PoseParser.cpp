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
#include <iterator>
#include <algorithm>

template<class T>
    T from_string(const std::string& s)
{
     std::istringstream stream(s);
     T t;
     stream >> t;
     return t;
}

PoseParser::PoseParser(const std::string& filename) {
	std::ifstream file(filename.c_str(), std::ifstream::in);

	std::string line;
	while(std::getline(file, line)) {
		// Split the line into columns, contained in a vector
		std::vector<std::string> tokens;
	    std::istringstream iss(line);
		std::copy(std::istream_iterator<std::string>(iss),
				  std::istream_iterator<std::string>(),
				  std::back_inserter<std::vector<std::string> >(tokens));

		Pose3D pose;
		pose.quaternion.x = from_string<double>(tokens.at(0));
		pose.quaternion.y = from_string<double>(tokens.at(1));
		pose.quaternion.z = from_string<double>(tokens.at(2));
		pose.quaternion.w = from_string<double>(tokens.at(3));

		pose.position.x = from_string<double>(tokens.at(13));
		pose.position.y = from_string<double>(tokens.at(14));
		pose.position.z = from_string<double>(tokens.at(15));

		unsigned timestamp = from_string<unsigned>(tokens.at(31));

		std::map<unsigned, Poses >::iterator it = posesTimestamped.find(timestamp);
		if (it == posesTimestamped.end()) {
			Poses poses;
			poses.push_back(pose);

			posesTimestamped.insert(std::pair<unsigned, Poses >(timestamp, poses));
		} else {
			(it->second).push_back(pose);
		}
	}
}

PoseParser::~PoseParser() {
	// TODO Auto-generated destructor stub
}
