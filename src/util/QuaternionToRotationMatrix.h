/*
 * QuaternionToRotationMatrix.h
 *
 *  Created on: 2011-03-23
 *      Author: Pierre-Luc Bacon <pbacon@cim.mcgill.ca>
 */

#ifndef QUATERNIONTOROTATIONMATRIX_H_
#define QUATERNIONTOROTATIONMATRIX_H_

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>

#include <functional>

#include "Quaternion.h"

namespace ublas = boost::numeric::ublas;

struct QuaternionToRotationMatrix : std::unary_function <boost::numeric::ublas::matrix<double>, boost::numeric::ublas::vector<double> > {
	boost::numeric::ublas::matrix<double> operator() (const boost::numeric::ublas::vector<double>& q) const
    {
	  using namespace ublas;

	  /**
	   * q_axis = q(1:3);
	   * Q = q_axis * q_axis';
	   */
	  vector<double> qAxis = project(q, range(0, 3));
	  matrix<double> Q = outer_prod(qAxis, qAxis);

	  /*
	  qx = [  0    -q(3)   q(2);
       q(3)    0    -q(1);
      -q(2)   q(1)    0];
	   */
	  matrix<double> qx(3,3);
	  qx(0,0) = 0;
	  qx(0,1) = -qAxis(2);
	  qx(0,2) = qAxis(1);

	  qx(1,0) = qAxis(2);
	  qx(1,1) = 0;
	  qx(1,2) = -qAxis(0);

	  qx(2,0) = -qAxis(1);
	  qx(2,1) = qAxis(0);
	  qx(2,2) = 0;

	  /**
	   * Cq = (2*q(4)^2-1)*eye(3) - 2*q(4)*qx + 2*Q;
	   */
	  identity_matrix<double> I(3);

	  return (2*q(3)*q(3)-1)*I - 2*q(3)*qx + 2*Q;
    }

	boost::numeric::ublas::matrix<double> operator() (const Quaternion &q) const
	{
		return this->operator()(q.getX(),q.getY(),q.getZ(),q.getW());
	}

	boost::numeric::ublas::matrix<double> operator() (double x, double y, double z, double w) const
    {
		boost::numeric::ublas::vector<double> q(4);
		q(0) = x; q(1) = y; q(2) = z; q(3) = w;

		return this->operator()(q);
    }
};

#endif /* QUATERNIONTOROTATIONMATRIX_H_ */
