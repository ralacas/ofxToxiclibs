#pragma once

#include <stdlib.h>
#include <iostream>
#include <math.h>

namespace toxi
{
	namespace math
	{
		class MathUtils
		{
		public:
			MathUtils(void);
			~MathUtils(void);

			static double THIRD;
			static double SQRT2;
			static double SQRT3;
			static double LOG2;
			static double PI;
			static double INV_PI;
			static double HALF_PI;
			static double THIRD_PI;
			static double QUARTER_PI;
			static double TWO_PI;
			static double THREE_HALVES_PI;
			static double PI_SQUARED;
			static double EPS;
			static double DEG2RAD;
			static double RAD2DEG;
			static double SHIFT23;
			static double INV_SHIFT23;
			static double SIN_A;
			static double SIN_B;
			static double SIN_P;

			static double abs( double& x );
			static int abs( int& x );
			static int ceilPowerOf2( int& x );
			static double clip( double& a, double& min, double& max );
			static double clip( int& a , int& min, int& max );
			static double clipNormalized( double& a );
			static double cos( double& theta );
			static double degrees( double& radians );
			static double dualSign( double& a, double& b );
			static double fastCos( double& x);
			static double fastCos( double* x);
			static double fastInverseSqrt( double& x );
			static double fastPow( double& a, double& b );
			static double fastSin( double& x );
			static bool flipCoin( void );
			static long floor( double& x );
			static int floorPowerOf2( int& x );
			static int gcd( int& p, int& q );
			static double impulse( double& k, double& t );
			static int lcm( int& p, int& q );
			static double max( double& a, double& b );
			static double max( double& a, double& b, double& c );
			static double max( double& values);
			static int max( int& a, int& b );
			static int max( int& a, int& b, int& c );
			static double min( double& a, double& b );
			static double min( double& a, double& b, double& c );
			static int min( int& a, int& b );
			static int min( int& a, int& b, int& c );
			static int min( int& values );
			static double normalizedRandom( void );
			static double radians( double& degrees );
			static double random( double& max );
			static double random( double& min, double& max );
			static double random( int& max );
			static double random( int& min, int& max );
			static double reduceAngle( double& theta );
			static double roundTo( double& val, double& prec );
			static int roundTo( int& val, int& prec );
			static double sign( double& x );
			static int sign( int& x );
			static double sin( double& theta );
			static double sqrt( double& x );

			static unsigned float_to_bits( float x );
			static float int_bits_to_float ( unsigned x );

			static bool isNan( double d );
		};

	}
}


