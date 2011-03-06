/*
 * LandMarkParser.h
 *
 *  Created on: 2011-02-20
 *      Author: pierre-luc
 */

#ifndef LANDMARKPARSER_H_
#define LANDMARKPARSER_H_

#include <map>
#include <vector>
#include <string>

class LandmarkParser {
public:
	LandmarkParser(const std::string& file);
	virtual ~LandmarkParser();

	/**
	 * Describes an landmark in the 3D world
	 * with respect to the global frame of reference,
	 * which is the starting pose of the robot.
	 */
	struct Point3D {
		explicit Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
		double x;
		double y;
		double z;
	};

	typedef std::vector<Point3D> Points;
	typedef std::map<unsigned, Points >::const_iterator const_iterator;

	const_iterator begin() {
		return landmarks.begin();
	}

	const_iterator end() {
		return landmarks.end();
	}

private:
	/** timestamp : Point3D */
	std::map<unsigned, Points > landmarks;
};

#endif /* LANDMARKPARSER_H_ */
