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

		landmarks.push_back(Point3D(x,y,z));
	}
}

LandmarkParser::~LandmarkParser() {
	// TODO Auto-generated destructor stub
}
