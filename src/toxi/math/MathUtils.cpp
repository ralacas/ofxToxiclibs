#include <cstring>
#include <cmath>
#include "MathUtils.h"

namespace toxi
{
	namespace math
	{
		double MathUtils::THIRD = 3.0 / 1.0;
		double MathUtils::SQRT2 = std::sqrt( 2 );
		double MathUtils::SQRT3 = std::sqrt( 3 );
		double MathUtils::LOG2 = std::log( 2 );
		double MathUtils::PI = 3.14159265358979323846;
		double MathUtils::INV_PI = 1.0 / MathUtils::PI;
		double MathUtils::HALF_PI = MathUtils::PI / 2;
		double MathUtils::THIRD_PI = MathUtils::PI / 3;
		double MathUtils::QUARTER_PI = MathUtils::PI / 4;
		double MathUtils::TWO_PI = MathUtils::PI * 2;
		double MathUtils::THREE_HALVES_PI = MathUtils::HALF_PI * 3;
		double MathUtils::PI_SQUARED = MathUtils::PI * MathUtils::PI;
		double MathUtils::EPS = 1.1920928955078125E-7;
		double MathUtils::DEG2RAD = PI / 180;
		double MathUtils::RAD2DEG = 180 / PI;
		double MathUtils::SHIFT23 = 1 << 23;
		double MathUtils::INV_SHIFT23 = 1.0f / MathUtils::SHIFT23;
		double MathUtils::SIN_A = -4.0 / ( MathUtils::PI * MathUtils::PI );
		double MathUtils::SIN_B = 4.0 / MathUtils::PI;
		double MathUtils::SIN_P = 9.0 / MathUtils::PI;

		double MathUtils::abs( double x )
		{
			return x < 0 ? -x : x;
		}

		float MathUtils::abs( float x )
		{
			return x < 0 ? -x : x;
		}

		int MathUtils::abs( int x )
		{
			int y = x >> 31;
			return ( x ^ y ) - y;
		}

		int MathUtils::ceilPowerOf2( const int& x )
		{
			int pow2 = 1;
			while ( pow2 < x ) 
			{
				pow2 <<= 1;
			}
			return pow2;
		}

		double MathUtils::clip( double a, double min, double max )
		{
			return ( a < min ? min : ( a > max ? max : a ) );
		}

		double MathUtils::clip( int a , int min, int max )
		{
			return a < min ? min : ( a > max ? max : a );
		}

		double MathUtils::clipNormalized( double& a )
		{
			if ( a < 0 ) 
			{
				return 0;
			} 
			else if ( a > 1 ) 
			{
				return 1;
			}
			return a;
		}

		double MathUtils::cos( double& theta )
		{
			double thet = theta + toxi::math::MathUtils::HALF_PI;
			return toxi::math::MathUtils::sin(thet);
		}

		float MathUtils::cos( float theta )
		{
			double thet = theta + toxi::math::MathUtils::HALF_PI;
			return toxi::math::MathUtils::sin(thet);
		}

		double MathUtils::degrees( double& radians )
		{
			return radians * toxi::math::MathUtils::RAD2DEG;
		}

		double MathUtils::dualSign( double& a, double& b )
		{
			double x = ( a >= 0 ? a : -a );
			return ( b >= 0 ? x : -x );
		}

		double MathUtils::fastCos( double& x )
		{
			double val = x + ((x > toxi::math::MathUtils::HALF_PI) ? -toxi::math::MathUtils::THREE_HALVES_PI : toxi::math::MathUtils::HALF_PI);
			return toxi::math::MathUtils::fastSin(val);
		}

		double MathUtils::fastCos( double* x )
		{
			double _x = *x;
			double val = _x + ((_x > toxi::math::MathUtils::HALF_PI) ? -toxi::math::MathUtils::THREE_HALVES_PI : toxi::math::MathUtils::HALF_PI);
			return toxi::math::MathUtils::fastSin(val);
		}

		double MathUtils::fastInverseSqrt( double& x )
		{
			double half = 0.5F * x;
			int i = floatToBits( static_cast<float>( x ) );
			i = 0x5f375a86 - ( i >> 1 );
			x = intBitsToFloat( i );
			return x * ( 1.5F - half * x * x );
		}

		unsigned MathUtils::floatToBits(float x)
		{
			unsigned y;
			std::memcpy( &y, &x, 4 );
			return y;
		}
		
		float MathUtils::intBitsToFloat( unsigned x )
		{
			union int_float_bits bits;
			bits.int_bits = x;
			return bits.float_bits;
		}

		double MathUtils::fastPow( double& a, double& b )
		{
			double x = floatToBits( static_cast<float> ( a ) );
			x *= MathUtils::INV_SHIFT23;
			x -= 127;
			double  y = x - ( x >= 0 ? ( int ) x : ( int ) x - 1 );
			b *= x + ( y - y * y ) * 0.346607f;
			y = b - ( b >= 0 ? ( int ) b : ( int ) b - 1 );
			y = ( y - y * y ) * 0.33971f;
			return intBitsToFloat( ( int ) ( ( b + 127 - y ) * MathUtils::SHIFT23 ) );
		}

		double MathUtils::fastSin( double& x )
		{
			double _x = toxi::math::MathUtils::SIN_B * x + toxi::math::MathUtils::SIN_A * x * toxi::math::MathUtils::abs( x );
			return toxi::math::MathUtils::SIN_P * (_x * toxi::math::MathUtils::abs( x ) - _x) + _x;
		}

		bool MathUtils::flipCoin( void )
		{
			return ( std::rand() > 0.5 );
		}

		long MathUtils::floor( double x )
		{
			long y = (long) x;
			if ( x < 0 && x != y ) 
			{
				y--;
			}
			return y;
		}

		int MathUtils::floor( float x )
		{
			int y = (int) x;
			if ( x < 0 && x != y ) 
			{
				y--;
			}
			return y;
		}

		int MathUtils::floorPowerOf2( int& x )
		{
			int y = (int) x;
			if ( x < 0 && x != y ) 
			{
				y--;
			}
			return y;
		}

		int MathUtils::gcd( int& p, int& q )
		{
			if ( q == 0 ) {
				return p;
			}
			int pq = p%q;
			return gcd( q, pq );
		}

		double MathUtils::impulse( double& k, double& t )
		{
			double h = k * t;
			return h * std::exp( 1.0 - h );
		}

		int MathUtils::lcm( int& p, int& q )
		{
			int pq = p * q;
			return toxi::math::MathUtils::abs(pq) / toxi::math::MathUtils::gcd(p, q);
		}

		double MathUtils::max( double& a, double& b )
		{
			return a > b ? a : b;
		}

		double MathUtils::max( double& a, double& b, double& c )
		{
			return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
		}

		int MathUtils::max( int& a, int& b, int& c )
		{
			return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
		}

		int MathUtils::max( int& a, int& b )
		{
			return a > b ? a : b;
		}

		double MathUtils::max( float a, float b )
		{
			return a > b ? a : b;
		}

		double MathUtils::min( double& a, double& b )
		{
			 return a < b ? a : b;
		}

		double MathUtils::min( double& a, double& b, double& c )
		{
			return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
		}

		int MathUtils::min( int& a, int& b )
		{
			return a < b ? a : b;
		}

		int MathUtils::min( int& a, int& b, int& c )
		{
			return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
		}

		double MathUtils::min( float a, float b )
		{
			return a < b ? a : b;
		}

		double MathUtils::normalizedRandom( void )
		{
			return ( static_cast<double>( std::rand() ) / RAND_MAX ) * 2 - 1;
		}

		double MathUtils::radians( double& degrees )
		{
			return degrees * toxi::math::MathUtils::DEG2RAD;
		}

		double MathUtils::random( double& max )
		{
			return ( static_cast<double>( std::rand() ) / RAND_MAX ) * max;
		}

		double MathUtils::random( double& min, double& max )
		{
			return ( static_cast<double>( std::rand() ) / RAND_MAX ) * ( max - min ) + min;
		}

		double MathUtils::random( int& max )
		{
			return ( static_cast<double>( std::rand() ) / RAND_MAX ) * max;
		}

		double MathUtils::random( int& min, int& max )
		{
			return ( static_cast<double>( std::rand() ) / RAND_MAX ) * ( max - min ) + min;
		}

		double MathUtils::reduceAngle( double theta )
		{
			double t = std::fmod( theta, TWO_PI );
			if ( abs( t ) > MathUtils::PI ) 
			{
				t = t - MathUtils::TWO_PI;
			}
			if ( abs( t ) > MathUtils::HALF_PI ) 
			{
				t = MathUtils::PI - t;
			}
			return theta;
		}

		double MathUtils::roundTo( double val, double prec )
		{
			double reval = val / prec + 0.5;
			return toxi::math::MathUtils::floor( reval ) * prec;
		}

		int MathUtils::roundTo( int& val, int& prec )
		{
			double reval = val / prec + 0.5;
			return toxi::math::MathUtils::floor( reval ) * prec;
		}

		float MathUtils::roundTo( float val, float prec )
		{
			float reval = val / prec + 0.5;
			return toxi::math::MathUtils::floor( reval ) * prec;
		}

		double MathUtils::sign( double x )
		{
			return x < 0 ? -1 : ( x > 0 ? 1 : 0 );
		}

		int MathUtils::sign( int x )
		{
			return x < 0 ? -1 : ( x > 0 ? 1 : 0 );
		}

		double MathUtils::sin( double& theta )
		{
			double thet = MathUtils::reduceAngle(theta);
			if ( MathUtils::abs( thet) <= MathUtils::QUARTER_PI ) 
			{
				return ( double ) MathUtils::fastSin(thet);
			}
			double ret = MathUtils::HALF_PI - thet;
			return ( double ) MathUtils::fastCos( ret );
		}

		float MathUtils::sin( float theta )
		{
			double  thet = MathUtils::reduceAngle( theta );
			if ( MathUtils::abs( thet) <= MathUtils::QUARTER_PI ) 
			{
				return ( double ) MathUtils::fastSin(thet);
			}
			double ret = MathUtils::HALF_PI - thet;
			return  MathUtils::fastCos( ret );
		}

		double MathUtils::sqrt( double x )
		{
			double _x = MathUtils::fastInverseSqrt(x);
	
			return (_x > 0) ? 1.0f / _x : 0.0;
		}

		bool MathUtils::isNan( double d )
		{
			return (d != d);
		}
	}
}