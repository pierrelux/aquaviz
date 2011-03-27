/*
 * RotationMatrix3x3ToEuler.h
 *
 *  Created on: 2011-03-23
 *      Author: Pierre-Luc Bacon <pbacon@cim.mcgill.ca>
 */

#ifndef ROTATIONMATRIX3X3TO4X4_H__
#define ROTATIONMATRIX3X3TO4X4_H__

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>

#include <functional>

namespace ublas = boost::numeric::ublas;

struct RotationMatrix3x3To4x4: std::unary_function<
		boost::numeric::ublas::matrix<double>, boost::numeric::ublas::matrix<
				double> > {

	boost::numeric::ublas::matrix<double> operator()(
			const boost::numeric::ublas::matrix<double>& m) const {
		  using namespace ublas;

		  matrix<double> rotationMatrix4x4(4,4);

		  /**
		   * R4 = |R3 0|
		   *      |0  0|
		   */
		  for (int i = 0; i < 4; i++) {
			  rotationMatrix4x4(3,i) = 0;
			  rotationMatrix4x4(i, 3) = 0;
		  }

		  rotationMatrix4x4(3,3) = 1;

		  // Copy submatrix
		  for (int i = 0; i < 3; i++) {
			  for (int j = 0; j < 3; j++) {
				  rotationMatrix4x4(i,j) = m(i,j);
			  }
		  }

		  return rotationMatrix4x4;
	}

};

#endif /* ROTATIONMATRIX3X3TO4X4_H__ */
