/*
 * LandMarkParser.h
 *
 *  Created on: 2011-02-20
 *      Author: pierre-luc
 */

#ifndef LANDMARKPARSER_H_
#define LANDMARKPARSER_H_

#include <string>
#include <vector>

class LandmarkParser {
public:
	LandmarkParser(const std::string& file);
	virtual ~LandmarkParser();

	struct Point3D {
		explicit Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
		double x;
		double y;
		double z;
	};

	typedef std::vector<Point3D>::const_iterator const_iterator ;
	typedef std::vector<Point3D>::size_type size_type;

	const_iterator begin() const {
	    return landmarks.begin();
	}

	const_iterator end() const {
	    return landmarks.end();
	}

	size_type size() const {
		return landmarks.size();
	}
private:
	std::vector<Point3D> landmarks;
};

#endif /* LANDMARKPARSER_H_ */
