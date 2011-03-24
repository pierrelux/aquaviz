/*
 * QuaternionToEuler.h
 *
 *  Created on: 2011-03-23
 *      Author: Pierre-Luc Bacon <pbacon@cim.mcgill.ca>
 */

#ifndef QUATERNIONTOEULER_H__
#define QUATERNIONTOEULER_H__

#include "QuaternionToRotationMatrix.h"
#include "RotationMatrix3x3ToEuler.h"

#include <functional>

namespace ublas = boost::numeric::ublas;

struct QuaternionToEuler : std::unary_function <boost::numeric::ublas::vector<double>, boost::numeric::ublas::vector<double> > {
	boost::numeric::ublas::vector<double> operator() (const double& x, const double& y, const double& z, const double& w) const
	{
		boost::numeric::ublas::vector<double> q(4);
		q(0) = x;
		q(1) = y;
		q(2) = z;
		q(3) = w;

		QuaternionToRotationMatrix quatToMat;
		boost::numeric::ublas::matrix<double> rotationMatrix = quatToMat(q);

		RotationMatrix3x3ToEuler matToEuler;
		return matToEuler(rotationMatrix);
	}

	boost::numeric::ublas::vector<double> operator() (const boost::numeric::ublas::vector<double>& q) const
    {
	  QuaternionToRotationMatrix quatToMat;

	  boost::numeric::ublas::matrix<double> rotationMatrix = quatToMat(q);

	  RotationMatrix3x3ToEuler matToEuler;
	  return matToEuler(rotationMatrix);
    }
};

#endif /* QUATERNIONTOEULER_H__ */
