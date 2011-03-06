/*
 * LandMarkParser.cpp
 *
 *  Created on: 2011-02-20
 *      Author: pierre-luc
 */

#include "LandmarkParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

LandmarkParser::LandmarkParser(const std::string& filename) {
	std::ifstream file(filename.c_str(), std::ifstream::in);

	std::string line;
	while(std::getline(file, line)) {
		std::istringstream buffer(line);

		double x,y,z;
		buffer >> x;
		buffer >> y;
		buffer >> z;

		unsigned key;
		buffer >> key;

		std::map<unsigned, std::vector<Point3D> >::iterator it = landmarks.find(key);
		if (it == landmarks.end()) {
			std::vector<Point3D> points;
			points.push_back(Point3D(x,y,z));

			landmarks.insert(std::pair<unsigned, std::vector<Point3D> >(key, points));
		} else {
			(it->second).push_back(Point3D(x, y, z));
		}

	}
}

LandmarkParser::~LandmarkParser() {
	// TODO Auto-generated destructor stub
}


