#pragma once

#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>

#undef max
#undef min

namespace toxi
{
	namespace math
	{
		class MathUtils
		{
			public:
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

				union int_float_bits
				{
					unsigned int_bits;
					float float_bits;
				};

				static double abs( const double & x );
				static float abs( const float & x );
				static int abs( const int & x );

				static int ceilPowerOf2( const int & x );
				static int floorPowerOf2( const int & x );

				static double clip( const double & a, const double & min, const double & max );
				static float clip( const float & a, const float & min, const float & max );
				static int clip( const int & a , const int & min, const int & max );
				static long clip( const long & a, const long & min, const long & max );

				static int clipNormalized( const int & a );
				static int clipNormalized( const long & a );
				static float clipNormalized( const float & a );
				static double clipNormalized( const double & a );

				static float cos( const int & theta );
				static double cos( const double & theta );
				static float cos( const float & theta );

				static double sin( const double & theta );
				static float sin( const float & theta );
				static float sin( const int & theta );

				static double degrees( const double & radians );
				static double radians( const double & degrees );
				static float degrees( const float & radians );
				static float radians( const float & degrees );
				static float degrees( const int & radians );
				static float radians( const int & degrees );

				static long floor( const double & x );
				static int floor( const float & x );

				static bool flipCoin( void );
				static double dualSign( const double & a, const double & b );
				static float dualSign( const float & a, const float & b );
				static int gcd( const int & p, const int & q );
				static double impulse( const double & k, const double & t );
				static float impulse( const float & k, const float & t );
				static int lcm( const int & p, const int & q );

				// TODO: find some faster implementations of those functions
				static double fastCos( const double & x);
				static double fastInverseSqrt( const double & x );
				static double fastPow( const double & a, const double & b );
				static double fastSin( const double & x );

				static double max( const double & a, const double & b );
				static double max( const double & a, const double & b, const double & c );
				static float max( const float & a, const float & b );
				static float max( const float & a, const float & b, const float & c );
				static int max( const int & a, const int & b );
				static int max( const int & a, const int & b, const int & c );
				static long max( const long & a, const long & b );
				static long max( const long & a, const long & b, const long & c );

				static double min( const double & a, const double & b );
				static double min( const float & a, const float & b );
				static double min( const double & a, const double & b, const double & c );
				static float min( const float & a, const float & b, const float & c );
				static int min( const int & a, const int & b );
				static int min( const int & a, const int & b, const int & c );
				static int min( const int & values );

				static double normalizedRandom( void );
				static double random( const double & max );
				static double random( const double & min, const double & max );
				static float random( const float & max );
				static float random( const float & min, const float & max );
				static double random( const int & max );
				static double random( const int & min, const int & max );

				static double reduceAngle( const double & theta );
				static float reduceAngle( const float & theta );

				static double roundTo( const double & val, const double & prec );
				static float roundTo( const float & val, const float & prec );
				static int roundTo( const int & val, const int & prec );

				static int sign( const double & x );
				static int sign( const float & x );
				static int sign( const int & x );
				
				static double sqrt( const double & x );
				static float sqrt( const float & x );

				//TODO
				static unsigned floatToBits( const float & x );
				static float intBitsToFloat ( unsigned x );

				static bool isNan( const double & d );
		};
	}
}

#endif
