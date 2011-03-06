/*
 * PoseParser.h
 *
 *  Created on: 2011-02-21
 *      Author: pierre-luc
 */

#ifndef POSEPARSER_H_
#define POSEPARSER_H_

#include <string>
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

	typedef std::vector<Pose3D>::const_iterator const_iterator;
	typedef std::vector<Pose3D>::size_type size_type;

	const_iterator begin() const {
	    return poses.begin();
	}

	const_iterator end() const {
	    return poses.end();
	}

	size_type size() const {
		return poses.size();
	}

private:
	std::vector<Pose3D> poses;
};

#endif /* POSEPARSER_H_ */