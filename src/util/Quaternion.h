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
		w = -w;
	}

	double inline getX() const { return x; }
	double inline getY() const { return y; }
	double inline getZ() const { return z; }
	double inline getW() const { return w; }

	Quaternion leftMultiply(double x, double y, double z, double w) {
		return leftMultiply(Quaternion(x,y,z,w));
	}

	Quaternion leftMultiply(const Quaternion& q2) {
		/*(Q1 * Q2).w = (w1w2 - x1x2 - y1y2 - z1z2)
		(Q1 * Q2).x = (w1x2 + x1w2 + y1z2 - z1y2)
		(Q1 * Q2).y = (w1y2 - x1z2 + y1w2 + z1x2)
		(Q1 * Q2).z = (w1z2 + x1y2 - y1x2 + z1w2*/

		double mw = w*q2.getW() - x*q2.getX() - y*q2.getY() - z*q2.getZ();
		double mx = w*q2.getX() + x*q2.getW() + y*q2.getZ() - z*q2.getY();
		double my = w*q2.getY() - x*q2.getZ() + y*q2.getW() + z*q2.getX();
		double mz = w*q2.getZ() + x*q2.getY() - y*q2.getX() + z*q2.getW();


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
