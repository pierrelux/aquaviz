/*
 * PoseParser.h
 *
 *  Created on: 2011-02-21
 *      Author: pierre-luc
 */

#ifndef POSEPARSER_H_
#define POSEPARSER_H_

#include <string>
#include <map>
#include <vector>

class PoseParser {
public:
	PoseParser(const std::string& filename);
	virtual ~PoseParser();

	/**
	 * Partial representation of the input file.
	 */
	struct Pose3D {
		/**
		 * 1-4 is the x,y,z,w of the quaternion that represents
		 * the rotation from the global frame to the IMU frame
		 * on the robot.
		 */
		struct {
			double x;
			double y;
			double z;
			double w;
		} quaternion;

		/**
		 * 14-16 is the position of the IMU frame in
		 * global coordinates (in meters)
		 */
		struct {
			double x;
			double y;
			double z;
		} position;
	};

	typedef std::vector<Pose3D> Poses;
	typedef std::map<unsigned, Poses >::const_iterator const_iterator;

	const_iterator begin() const {
	    return posesTimestamped.begin();
	}

	const_iterator end() const {
	    return posesTimestamped.end();
	}

	const_iterator find (const unsigned& timestamp) const {
		return posesTimestamped.find(timestamp);
	}

private:
	std::map<unsigned, Poses > posesTimestamped;
};

#endif /* POSEPARSER_H_ */
