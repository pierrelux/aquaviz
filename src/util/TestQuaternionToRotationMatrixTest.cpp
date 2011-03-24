#include "QuaternionToRotationMatrix.h"
#include "RotationMatrix3x3ToEuler.h"
#include "QuaternionToEuler.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <iostream>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

int main(void)
{
	boost::numeric::ublas::vector<double> q(4);
	q(0) = 1;
	q(1) = 2;
	q(2) = 3;
	q(3) = 4;

	QuaternionToRotationMatrix quatToMat;
	matrix<double> rotMat = quatToMat(q);

	/**
	    33    28   -10
       -20    39    20
        22     4    49
	 */
	std::cout << rotMat << std::endl;

	RotationMatrix3x3ToEuler matToEuler;
	vector<double> euler = matToEuler(rotMat);

	std::cout << euler << std::endl;
	euler = matToEuler.naive(rotMat);
	std::cout << euler << std::endl;

	QuaternionToEuler quatToEuler;
	euler = quatToEuler(q);
	std::cout << euler << std::endl;

	return 0;
}
