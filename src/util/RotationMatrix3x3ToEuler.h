/*
 * RotationMatrix3x3ToEuler.h
 *
 *  Created on: 2011-03-23
 *      Author: Pierre-Luc Bacon <pbacon@cim.mcgill.ca>
 */

#ifndef ROTATIONMATRIX3X3TOEULER_H_
#define ROTATIONMATRIX3X3TOEULER_H_

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>

#include <functional>

#include <float.h>

#define EulSafe	     "\000\001\002\000"
#define EulNext	     "\001\002\000\001"

/* EulGetOrd unpacks all useful information about order simultaneously. */
#define EulGetOrd(ord,i,j,k,h,n,s,f) {unsigned o=ord;f=o&1;o>>=1;s=o&1;o>>=1;\
    n=o&1;o>>=1;i=EulSafe[o&3];j=EulNext[i+n];k=EulNext[i+1-n];h=s?k:i;}

/* EulOrd creates an order value between 0 and 23 from 4-tuple choices. */
#define EulOrd(i,p,r,f)	   (((((((i)<<1)+(p))<<1)+(r))<<1)+(f))
#define EulParEven   0
#define EulParOdd    1
#define EulRepNo     0
#define EulRepYes    1
#define EulFrmS	     0
#define EulFrmR	     1

namespace ublas = boost::numeric::ublas;

struct RotationMatrix3x3ToEuler: std::unary_function<
		boost::numeric::ublas::vector<double>, boost::numeric::ublas::matrix<
				double> > {
	enum QuatPart {X, Y, Z, W};

	enum EulerOrder {
		/* Static axes */
		EulOrdXYZs = EulOrd(X,EulParEven,EulRepNo,EulFrmS),
		EulOrdXYXs = EulOrd(X,EulParEven,EulRepYes,EulFrmS),
		EulOrdXZYs = EulOrd(X,EulParOdd,EulRepNo,EulFrmS),
		EulOrdXZXs = EulOrd(X,EulParOdd,EulRepYes,EulFrmS),
		EulOrdYZXs = EulOrd(Y,EulParEven,EulRepNo,EulFrmS),
		EulOrdYZYs = EulOrd(Y,EulParEven,EulRepYes,EulFrmS),
		EulOrdYXZs = EulOrd(Y,EulParOdd,EulRepNo,EulFrmS),
		EulOrdYXYs = EulOrd(Y,EulParOdd,EulRepYes,EulFrmS),
		EulOrdZXYs = EulOrd(Z,EulParEven,EulRepNo,EulFrmS),
		EulOrdZXZs = EulOrd(Z,EulParEven,EulRepYes,EulFrmS),
		EulOrdZYXs = EulOrd(Z,EulParOdd,EulRepNo,EulFrmS),
		EulOrdZYZs = EulOrd(Z,EulParOdd,EulRepYes,EulFrmS),
		/* Rotating axes */
		EulOrdZYXr = EulOrd(X,EulParEven,EulRepNo,EulFrmR),
		EulOrdXYXr = EulOrd(X,EulParEven,EulRepYes,EulFrmR),
		EulOrdYZXr = EulOrd(X,EulParOdd,EulRepNo,EulFrmR),
		EulOrdXZXr = EulOrd(X,EulParOdd,EulRepYes,EulFrmR),
		EulOrdXZYr = EulOrd(Y,EulParEven,EulRepNo,EulFrmR),
		EulOrdYZYr = EulOrd(Y,EulParEven,EulRepYes,EulFrmR),
		EulOrdZXYr = EulOrd(Y,EulParOdd,EulRepNo,EulFrmR),
		EulOrdYXYr = EulOrd(Y,EulParOdd,EulRepYes,EulFrmR),
		EulOrdYXZr = EulOrd(Z,EulParEven,EulRepNo,EulFrmR),
		EulOrdZXZr = EulOrd(Z,EulParEven,EulRepYes,EulFrmR),
		EulOrdXYZr = EulOrd(Z,EulParOdd,EulRepNo,EulFrmR),
		EulOrdZYZr = EulOrd(Z,EulParOdd,EulRepYes,EulFrmR)
	};

	boost::numeric::ublas::vector<double> operator()(
			const boost::numeric::ublas::matrix<double>& m, EulerOrder order = EulOrdZXYs) const {
		double x, y, z;
		int i, j, k, h, n, s, f;
		EulGetOrd(order, i, j, k, h, n, s, f);

		if (s == EulRepYes) {
			double sy = ::sqrt(m(i, j) * m(i, j) + m(i, k) * m(i, k));

			if (sy > 16 * FLT_EPSILON) {
				x = ::atan2(m(i,j), m(i,k));
				y = ::atan2(sy, m(i,i));
				z = ::atan2(m(j,i), -m(k,i));
			} else {
				x = ::atan2(-m(j,k), m(j,j));
				y = ::atan2(sy, m(i,i));
				z = 0;
			}

		} else {
			double cy = sqrt(m(i,i) * m(i,i) + m(j,i) * m(j,i));

			if (cy > 16 * FLT_EPSILON) {
				x = ::atan2(m(k,j), m(k,k));
				y = ::atan2(-m(k,i), cy);
				z = ::atan2(m(j,i), m(i,i));
			} else {
				x = ::atan2(-m(j,k), m(j,j));
				y = ::atan2(-m(k,i), cy);
				z = 0;
			}
		}

		if (n == EulParOdd) {
			x = -x;
			y = -y;
			z = -z;
		}
		if (f == EulFrmR) {
			float t = x;
			x = z;
			z = t;
		}

		boost::numeric::ublas::vector<double> euler(3);
		euler(0) = x;
		euler(1) = y;
		euler(2) = z;

		return euler;
	}

	boost::numeric::ublas::vector<double> naive(
			const boost::numeric::ublas::matrix<double>& m) const {
		boost::numeric::ublas::vector<double> q(3);
		q(0) = ::atan2(m(2, 0), m(2, 2));
		q(1) = ::asin(-m(2, 1));
		q(2) = ::atan2(m(0, 1), m(1, 1));

		return q;
	}
};

#endif /* ROTATIONMATRIX3X3TOEULER_H_ */
