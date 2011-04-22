/*
 * Quaternion.h
 *
 *  Created on: 2011-03-23
 *      Author: Pierre-Luc Bacon <pbacon@cim.mcgill.ca>
 */

#ifndef QUATERNION_H__
#define QUATERNION_H__

struct Quaternion {
	explicit Quaternion(double x, double y, double z, double w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	void invert() {
		x = -x;
		y = -y;
		z = -z;
	}

	double inline getX() const { return x; }
	double inline getY() const { return y; }
	double inline getZ() const { return z; }
	double inline getW() const { return w; }

	Quaternion leftMultiply(double x, double y, double z, double w) {
		return leftMultiply(Quaternion(x,y,z,w));
	}

	Quaternion leftMultiply(const Quaternion& q2) {
		/**
		 * Note: this is the version used in "Indirect Kalman Filter for 3D
	     * Attitude estimation"
         * qMult = [ q(4)*p(1) + q(3)*p(2) - q(2)*p(3) + q(1)*p(4);
         * -q(3)*p(1) + q(4)*p(2) + q(1)*p(3) + q(2)*p(4);
         *  q(2)*p(1) - q(1)*p(2) + q(4)*p(3) + q(3)*p(4);
         * -q(1)*p(1) - q(2)*p(2) - q(3)*p(3) + q(4)*p(4);
        ];

		 *
		 */
		double mw = x*q2.getW() + y*q2.getZ() - z*q2.getY() + w*q2.getX();
		double mx = x*q2.getZ() + y*q2.getW() + z*q2.getX() + w*q2.getY();
		double my = x*q2.getY() - y*q2.getX() + z*q2.getW() + w*q2.getZ();
		double mz = x*q2.getX() - y*q2.getY() - z*q2.getZ() + w*q2.getW();


		return Quaternion(mx, my, mz, mw);
	}

	Quaternion operator*(const Quaternion& q2) {
		return leftMultiply(q2);
	}

private:
	double x;
	double y;
	double z;
	double w;
};

#endif
