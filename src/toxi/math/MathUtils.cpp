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

		double MathUtils::abs( const double x )
		{
			return x < 0 ? -x : x;
		}

		float MathUtils::abs( const float x )
		{
			return x < 0 ? -x : x;
		}

		int MathUtils::abs( const int x )
		{
			int y = x >> 31;
			return ( x ^ y ) - y;
		}

		/*
		* Rounds up the value to the nearest higher power^2 value.
		*/
		int MathUtils::ceilPowerOf2( const int x )
		{
			int pow2 = 1;
			while ( pow2 < x ) 
			{
				pow2 <<= 1;
			}
			return pow2;
		}

		double MathUtils::clip( const double a, const double min, const double max )
		{
			return ( a < min ? min : ( a > max ? max : a ) );
		}

		int MathUtils::clip( const int a , const int min, const int max )
		{
			return a < min ? min : ( a > max ? max : a );
		}

		long MathUtils::clip( const long a , const long min, const long max )
		{
			return a < min ? min : ( a > max ? max : a );
		}

		float MathUtils::clip( const float a , const float min, const float max )
		{
			return a < min ? min : ( a > max ? max : a );
		}

		int MathUtils::clipNormalized( const int a )
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

		int MathUtils::clipNormalized( const long a )
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

		float MathUtils::clipNormalized( const float a )
		{
			if ( a < 0.0f ) 
			{
				return 0.0f;
			} 
			else if ( a > 1.0f ) 
			{
				return 1.0f;
			}
			return a;
		}

		double MathUtils::clipNormalized( const double a )
		{
			if ( a < 0 ) 
			{
				return 0.0;
			} 
			else if ( a > 1.0 ) 
			{
				return 1.0;
			}
			return a;
		}

		double MathUtils::cos( const double theta )
		{
			return std::cos( theta );
		}

		float MathUtils::cos( const float theta )
		{
			return ( float ) ( cos( static_cast< double > ( theta ) ) );
		}

		float MathUtils::cos( const int theta )
		{
			return ( float ) ( cos( static_cast< float > ( theta ) ) );
		}

		double MathUtils::degrees( const double radians )
		{
			return radians * toxi::math::MathUtils::RAD2DEG;
		}

		float MathUtils::degrees( const float radians )
		{
			return static_cast< float > ( degrees( static_cast< double > ( radians ) ) );
		}

		float MathUtils::degrees( const int radians )
		{
			return degrees( static_cast< float > ( radians ) );
		}

		double MathUtils::dualSign( const double a, const double b )
		{
			double x = ( a >= 0 ? a : -a );
			return ( b >= 0 ? x : -x );
		}

		float MathUtils::dualSign( const float a, const float b )
		{
			float x = ( a >= 0 ? a : -a );
			return ( b >= 0 ? x : -x );
		}

		double MathUtils::fastCos( const double x )
		{
			double val = x + ((x > toxi::math::MathUtils::HALF_PI) ? -toxi::math::MathUtils::THREE_HALVES_PI : toxi::math::MathUtils::HALF_PI);
			return toxi::math::MathUtils::fastSin(val);
		}

		double MathUtils::fastInverseSqrt( const double x )
		{
			double half = 0.5F * x;
			int i = floatToBits( static_cast<float>( x ) );
			i = 0x5f375a86 - ( i >> 1 );
			float _x = intBitsToFloat( i );
			return x * ( 1.5F - half * _x * _x );
		}


		unsigned MathUtils::floatToBits(const float x)
		{
			//TODO
			std::cerr << "The untested floatToBits function has just been called. Handle with care." << std::endl;
			unsigned int y;
			std::memcpy( &y, &x, 4 );
			return y;
		}
		
		float MathUtils::intBitsToFloat( unsigned x )
		{
			//TODO
			std::cerr << "The untested intBitsToFloat function has just been called. Handle with care." << std::endl;
			union int_float_bits bits;
			bits.int_bits = x;
			return bits.float_bits;
		}

		double MathUtils::fastPow( const double a, const double b )
		{
			double x = floatToBits( static_cast<float> ( a ) );
			x *= MathUtils::INV_SHIFT23;
			x -= 127;
			double y = x - ( x >= 0 ? ( int ) x : ( int ) x - 1 );
			double _b = b;
			_b *= x + ( y - y * y ) * 0.346607f;
			y = _b - ( _b >= 0 ? ( int ) _b : ( int ) _b - 1 );
			y = ( y - y * y ) * 0.33971f;
			return intBitsToFloat( ( int ) ( ( _b + 127 - y ) * MathUtils::SHIFT23 ) );
		}

		double MathUtils::fastSin( const double x )
		{
			double _x = toxi::math::MathUtils::SIN_B * x + toxi::math::MathUtils::SIN_A * x * toxi::math::MathUtils::abs( x );
			return toxi::math::MathUtils::SIN_P * (_x * toxi::math::MathUtils::abs( x ) - _x) + _x;
		}

		bool MathUtils::flipCoin( void )
		{
			return ( std::rand() % 100 > 50 );
		}

		long MathUtils::floor( const double x )
		{
			long y = (long) x;
			if ( x < 0 && x != y ) 
			{
				y--;
			}
			return y;
		}

		int MathUtils::floor( const float x )
		{
			int y = (int) x;
			if ( x < 0 && x != y ) 
			{
				y--;
			}
			return y;
		}

		int MathUtils::floorPowerOf2( const int x )
		{
			
			return ( int ) std::pow( 2.0, ( int ) ( std::log( x ) / toxi::math::MathUtils::LOG2 ) );
		}

		int MathUtils::gcd( const int p, const int q )
		{
			if ( q == 0 ) {
				return p;
			}
			int pq = p%q;
			return gcd( q, pq );
		}

		double MathUtils::impulse( const double k, const double t )
		{
			double h = k * t;
			return h * std::exp( 1.0 - h );
		}

		float MathUtils::impulse( const float k, const float t )
		{
			float h = k * t;
			return static_cast < float > ( h * std::exp( 1.0 - h ) );
		}

		int MathUtils::lcm( const int p, const int q )
		{
			int pq = p * q;
			return toxi::math::MathUtils::abs(pq) / toxi::math::MathUtils::gcd(p, q);
		}

		double MathUtils::max( const double a, const double b )
		{
			return a > b ? a : b;
		}

		double MathUtils::max( const double a, const double b, const double c )
		{
			return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
		}

		int MathUtils::max( const int a, const int b, const int c )
		{
			return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
		}

		int MathUtils::max( const int a, const int b )
		{
			return a > b ? a : b;
		}

		float MathUtils::max( const float a, const float b )
		{
			return a > b ? a : b;
		}

		float MathUtils::max( const float a, const float b, const float c )
		{
			return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
		}

		long MathUtils::max( const long a, const long b )
		{
			return a > b ? a : b;
		}

		long MathUtils::max( const long a, const long b, const long c )
		{
			return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
		}

		double MathUtils::min( const double a, const double b )
		{
			 return a < b ? a : b;
		}

		double MathUtils::min( const double a, const double b, const double c )
		{
			return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
		}

		int MathUtils::min( const int a, const int b )
		{
			return a < b ? a : b;
		}

		int MathUtils::min( const int a, const int b, const int c )
		{
			return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
		}

		double MathUtils::min( const float a, const float b )
		{
			return a < b ? a : b;
		}

		float MathUtils::min( const float a, const float b, const float c )
		{
			return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
		}

		double MathUtils::normalizedRandom( void )
		{
			
			return ( static_cast<double>( std::rand() ) / RAND_MAX ) * 2 - 1;
		}

		double MathUtils::radians( const double degrees )
		{
			return degrees * toxi::math::MathUtils::DEG2RAD;
		}

		float MathUtils::radians( const float degrees )
		{
			return static_cast< float > ( radians( static_cast< double > ( degrees ) ) );
		}

		float MathUtils::radians( const int degrees )
		{
			return radians( static_cast< float > ( degrees ) );
		}

		double MathUtils::random( const double max )
		{
			return ( static_cast<double>( std::rand() ) / RAND_MAX ) * max;
		}

		double MathUtils::random( const double min, const double max )
		{
			return ( static_cast<double>( std::rand() ) / RAND_MAX ) * ( max - min ) + min;
		}

		double MathUtils::random( const int max )
		{
			double f = std::rand()  / (double)RAND_MAX;
			double r = (  f ) * max;
			return r;
		}

		double MathUtils::random( const int min, const int max )
		{
			return ( static_cast<double>( std::rand() ) / RAND_MAX ) * ( max - min ) + min;
		}

		float MathUtils::random( const float max )
		{
			return ( static_cast< float >( std::rand() ) / RAND_MAX ) * max;
		}

		float MathUtils::random( const float min, const float max )
		{
			return ( static_cast< float >( std::rand() ) / RAND_MAX ) * ( max - min ) + min;
		}

		double MathUtils::reduceAngle( const double theta )
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
			return t;
		}

		float MathUtils::reduceAngle( const float theta )
		{
			float t = static_cast< float > ( std::fmod( theta, MathUtils::TWO_PI ) );
			if ( abs( t ) > MathUtils::PI ) 
			{
				t = t - static_cast< float > ( MathUtils::TWO_PI );
			}
			if ( abs( t ) > MathUtils::HALF_PI ) 
			{
				t = static_cast< float > ( MathUtils::PI ) - t;
			}
			return t;
		}

		double MathUtils::roundTo( const double val, const double prec )
		{
			double reval = val / prec + 0.5;
			return toxi::math::MathUtils::floor( reval ) * prec;
		}

		int MathUtils::roundTo( const int val, const int prec )
		{
			double reval = val / prec + 0.5;
			return toxi::math::MathUtils::floor( reval ) * prec;
		}

		float MathUtils::roundTo( const float val, const float prec )
		{
			float reval = val / prec + 0.5f;
			return toxi::math::MathUtils::floor( reval ) * prec;
		}

		int MathUtils::sign( const double x )
		{
			return x < 0 ? -1 : ( x > 0 ? 1 : 0 );
		}

		int MathUtils::sign( const int x )
		{
			return x < 0 ? -1 : ( x > 0 ? 1 : 0 );
		}

		int MathUtils::sign( const float x )
		{
			return x < 0 ? -1 : ( x > 0 ? 1 : 0 );
		}

		double MathUtils::sin( const double theta )
		{
			return std::sin( theta );		}

		float MathUtils::sin( const float theta )
		{
			return std::sinf( theta );
		}

		float MathUtils::sin( const int theta )
		{
			return sin( static_cast< float > ( theta ) );
		}

		double MathUtils::sqrt( const double x )
		{
			return std::sqrt( x );
		}

		float MathUtils::sqrt( const float x )
		{
			return static_cast< float > ( std::sqrt( x ) );
		}

		bool MathUtils::isNan( const double d ) {
			//std::cerr << "The untested isNan function has just been called. Handle with care." << std::endl;
			return (d != d);
		}
	}
}