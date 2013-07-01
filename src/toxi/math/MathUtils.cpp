#include "MathUtils.h"

double toxi::math::MathUtils::THIRD = 3.0 / 1.0;
double toxi::math::MathUtils::SQRT2 = std::sqrt( 2 );
double toxi::math::MathUtils::SQRT3 = std::sqrt( 3 );
double toxi::math::MathUtils::LOG2 = std::log( 2 );
double toxi::math::MathUtils::PI = 3.14159265358979323846;
double toxi::math::MathUtils::INV_PI = 1.0 / toxi::math::MathUtils::PI;
double toxi::math::MathUtils::HALF_PI = toxi::math::MathUtils::PI / 2;
double toxi::math::MathUtils::THIRD_PI = toxi::math::MathUtils::PI / 3;
double toxi::math::MathUtils::QUARTER_PI = toxi::math::MathUtils::PI / 4;
double toxi::math::MathUtils::TWO_PI = toxi::math::MathUtils::PI * 2;
double toxi::math::MathUtils::THREE_HALVES_PI = toxi::math::MathUtils::HALF_PI * 3;
double toxi::math::MathUtils::PI_SQUARED = toxi::math::MathUtils::PI * toxi::math::MathUtils::PI;
double toxi::math::MathUtils::EPS = 1.1920928955078125E-7;
double toxi::math::MathUtils::DEG2RAD = toxi::math::MathUtils::PI / 180;
double toxi::math::MathUtils::RAD2DEG = 180 / toxi::math::MathUtils::PI;
double toxi::math::MathUtils::SHIFT23 = 1 << 23;
double toxi::math::MathUtils::INV_SHIFT23 = 1.0f / toxi::math::MathUtils::SHIFT23;
double toxi::math::MathUtils::SIN_A = -4.0 / ( toxi::math::MathUtils::PI * toxi::math::MathUtils::PI );
double toxi::math::MathUtils::SIN_B = 4.0 / toxi::math::MathUtils::PI;
double toxi::math::MathUtils::SIN_P = 9.0 / toxi::math::MathUtils::PI;

toxi::math::MathUtils::MathUtils(void) 
{
}


toxi::math::MathUtils::~MathUtils(void)
{
}

double toxi::math::MathUtils::abs( double& x )
{
	return x < 0 ? -x : x;
}

int toxi::math::MathUtils::abs( int& x )
{
	int y = x >> 31;
	return ( x ^ y ) - y;
}

int toxi::math::MathUtils::ceilPowerOf2( int& x )
{
	int pow2 = 1;
	while ( pow2 < x ) 
	{
		pow2 <<= 1;
	}
	return pow2;
}

double toxi::math::MathUtils::clip( double& a, double& min, double& max )
{
	return ( a < min ? min : ( a > max ? max : a ) );
}

double toxi::math::MathUtils::clip( int& a , int& min, int& max )
{
	return a < min ? min : ( a > max ? max : a );
}

double toxi::math::MathUtils::clipNormalized( double& a )
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

double toxi::math::MathUtils::cos( double& theta )
{
	double thet = theta + toxi::math::MathUtils::HALF_PI;
	return toxi::math::MathUtils::sin(thet);
}

double toxi::math::MathUtils::degrees( double& radians )
{
	return radians * toxi::math::MathUtils::RAD2DEG;
}

double toxi::math::MathUtils::dualSign( double& a, double& b )
{
	double x = ( a >= 0 ? a : -a );
	return ( b >= 0 ? x : -x );
}

double toxi::math::MathUtils::fastCos( double& x )
{
	double val = x + ((x > toxi::math::MathUtils::HALF_PI) ? -toxi::math::MathUtils::THREE_HALVES_PI : toxi::math::MathUtils::HALF_PI);
	return toxi::math::MathUtils::fastSin(val);
}

double toxi::math::MathUtils::fastCos( double* x )
{
	double _x = *x;
	double val = _x + ((_x > toxi::math::MathUtils::HALF_PI) ? -toxi::math::MathUtils::THREE_HALVES_PI : toxi::math::MathUtils::HALF_PI);
	return toxi::math::MathUtils::fastSin(val);
}

double toxi::math::MathUtils::fastInverseSqrt( double& x )
{
	double half = 0.5F * x;
	int i = float_to_bits( static_cast<float>( x ) );
	i = 0x5f375a86 - ( i >> 1 );
	x = int_bits_to_float( i );
	return x * ( 1.5F - half * x * x );
}

unsigned toxi::math::MathUtils::float_to_bits(float x)
{
	unsigned y;
	std::memcpy( &y, &x, 4 );
	return y;
}
union int_float_bits {
	unsigned int_bits;
	float float_bits;
};


float toxi::math::MathUtils::int_bits_to_float( unsigned x )
{
	union int_float_bits bits;
	bits.int_bits = x;
	return bits.float_bits;
}

double toxi::math::MathUtils::fastPow( double& a, double& b )
{
	double x = float_to_bits( static_cast<float> ( a ) );
	x *= toxi::math::MathUtils::INV_SHIFT23;
	x -= 127;
	double  y = x - ( x >= 0 ? ( int ) x : ( int ) x - 1 );
	b *= x + ( y - y * y ) * 0.346607f;
	y = b - ( b >= 0 ? ( int ) b : ( int ) b - 1 );
	y = ( y - y * y ) * 0.33971f;
	return int_bits_to_float( ( int ) ( ( b + 127 - y ) * toxi::math::MathUtils::SHIFT23 ) );
}

double toxi::math::MathUtils::fastSin( double& x )
{
	double _x = toxi::math::MathUtils::SIN_B * x + toxi::math::MathUtils::SIN_A * x * toxi::math::MathUtils::abs( x );
	return toxi::math::MathUtils::SIN_P * (_x * toxi::math::MathUtils::abs( x ) - _x) + _x;
}

bool toxi::math::MathUtils::flipCoin( void )
{
	if( std::rand() > 0.5 )
	{
		return true;
	} 
	else
	{
		return false;
	}
}

long toxi::math::MathUtils::floor( double& x )
{
	long y = (long) x;
	if ( x < 0 && x != y ) 
	{
		y--;
	}
	return y;
}

int toxi::math::MathUtils::floorPowerOf2( int& x )
{
	int y = (int) x;
	if ( x < 0 && x != y ) 
	{
		y--;
	}
	return y;
}

int toxi::math::MathUtils::gcd( int& p, int& q )
{
	if ( q == 0 ) {
		return p;
	}
	int pq = p%q;
	return gcd( q, pq );
}

double toxi::math::MathUtils::impulse( double& k, double& t )
{
	double h = k * t;
	return h * std::exp( 1.0 - h );
}

int toxi::math::MathUtils::lcm( int& p, int& q )
{
	int pq = p * q;
	return toxi::math::MathUtils::abs(pq) / toxi::math::MathUtils::gcd(p, q);
}

double toxi::math::MathUtils::max( double& a, double& b )
{
	return a > b ? a : b;
}

double toxi::math::MathUtils::max( double& a, double& b, double& c )
{
	return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

int toxi::math::MathUtils::max( int& a, int& b, int& c )
{
	return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

int toxi::math::MathUtils::max( int& a, int& b )
{
	return a > b ? a : b;
}

double toxi::math::MathUtils::min( double& a, double& b )
{
	 return a < b ? a : b;
}

double toxi::math::MathUtils::min( double& a, double& b, double& c )
{
	return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

int toxi::math::MathUtils::min( int& a, int& b )
{
	return a < b ? a : b;
}

int toxi::math::MathUtils::min( int& a, int& b, int& c )
{
	return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

double toxi::math::MathUtils::normalizedRandom( void )
{
	return ( static_cast<double>( std::rand() ) / RAND_MAX ) * 2 - 1;
}

double  toxi::math::MathUtils::radians( double& degrees )
{
	return degrees * toxi::math::MathUtils::DEG2RAD;
}

double toxi::math::MathUtils::random( double& max )
{
	return ( static_cast<double>( std::rand() ) / RAND_MAX ) * max;
}

double toxi::math::MathUtils::random( double& min, double& max )
{
	return ( static_cast<double>( std::rand() ) / RAND_MAX ) * ( max - min ) + min;
}

double toxi::math::MathUtils::random( int& max )
{
	return ( static_cast<double>( std::rand() ) / RAND_MAX ) * max;
}

double toxi::math::MathUtils::random( int& min, int& max )
{
	return ( static_cast<double>( std::rand() ) / RAND_MAX ) * ( max - min ) + min;
}

double toxi::math::MathUtils::reduceAngle( double& theta )
{
	double t = std::fmod( theta, TWO_PI );
	if ( abs( t ) > toxi::math::MathUtils::PI ) 
	{
		t = t - toxi::math::MathUtils::TWO_PI;
	}
	if ( abs( t ) > toxi::math::MathUtils::HALF_PI ) 
	{
		t =toxi::math::MathUtils:: PI - t;
	}
	return theta;
}

double toxi::math::MathUtils::roundTo( double& val, double& prec )
{
	double reval = val / prec + 0.5;
	return toxi::math::MathUtils::floor( reval ) * prec;
}

int toxi::math::MathUtils::roundTo( int& val, int& prec )
{
	double reval = val / prec + 0.5;
	return toxi::math::MathUtils::floor( reval ) * prec;
}

double toxi::math::MathUtils::sign( double& x )
{
	return x < 0 ? -1 : ( x > 0 ? 1 : 0 );
}

int toxi::math::MathUtils::sign( int& x )
{
	return x < 0 ? -1 : ( x > 0 ? 1 : 0 );
}

double toxi::math::MathUtils::sin( double& theta )
{
	double thet = toxi::math::MathUtils::reduceAngle(theta);
	if ( toxi::math::MathUtils::abs( thet) <= toxi::math::MathUtils::QUARTER_PI ) 
	{
		return ( double ) toxi::math::MathUtils::fastSin(thet);
	}
	double ret = toxi::math::MathUtils::HALF_PI - thet;
	return ( double ) toxi::math::MathUtils::fastCos( ret );
}

double toxi::math::MathUtils::sqrt( double& x )
{
	double _x = toxi::math::MathUtils::fastInverseSqrt(x);
	if (_x > 0) 
	{
		return 1.0f / _x;
	} 
	else 
	{
		return 0;
	}
}
