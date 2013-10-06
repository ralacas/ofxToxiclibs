#include "MathUtilsTest.h"
#include <toxi/math/MathUtils.h>

using namespace toxi::math;

/**
 * Tests the abs method.
 */
void MathUtilsTest::absInt(void)
{
	int abs = toxi::math::MathUtils::abs( - 1 );
	
	CPPUNIT_ASSERT( abs == 1);
}

void MathUtilsTest::absFloat( void )
{
	float val = -1.1f;
	float valToCompare = 1.1f;
	float abs = toxi::math::MathUtils::abs( val );

	CPPUNIT_ASSERT( abs == valToCompare );
}

void MathUtilsTest::absDouble( void )
{
	double abs = toxi::math::MathUtils::abs( -1.234 );

	CPPUNIT_ASSERT( abs == 1.234);
}

void MathUtilsTest::ceilPowerOf2( void )
{
	int value = 127;
	int toCompareTo = 128;
	int ceilPowerOfTwo1 = toxi::math::MathUtils::ceilPowerOf2( value );

	int value2 = 4000;
	int toCompareTo2 = 4096;
	int ceilPowerOfTwo2 = toxi::math::MathUtils::ceilPowerOf2( value2 );

	CPPUNIT_ASSERT( ceilPowerOfTwo1 == toCompareTo && ceilPowerOfTwo2 == toCompareTo2 );
}


void MathUtilsTest::floorPowerOf2( void )
{
	int value = 129;
	int toCompareTo = 128;
	int floorPowerOfTwo1 = toxi::math::MathUtils::floorPowerOf2( value );

	int value2 = 4100;
	int toCompareTo2 = 4096;
	int floorPowerOfTwo2 = toxi::math::MathUtils::floorPowerOf2( value2 );

	CPPUNIT_ASSERT( floorPowerOfTwo1 == toCompareTo && floorPowerOfTwo2 == toCompareTo2 );
}


void MathUtilsTest::clipInt( void )
{
	int val = 666;
	int compare = 600;
	int compare2 = 700;

	int result = toxi::math::MathUtils::clip( val, 0, compare );
	int result2 = toxi::math::MathUtils::clip( val, compare2, 800 );

	CPPUNIT_ASSERT( result == compare && result2 == compare2 );
}

void MathUtilsTest::clipLong( void )
{
	long val = 345676;
	long compare = 300000;
	long compare2 = 500000;

	long result = toxi::math::MathUtils::clip( val, ( long ) ( 0 ), compare );
	long result2 = toxi::math::MathUtils::clip( val, compare2, ( long ) ( 600000 ) );

	CPPUNIT_ASSERT( result == compare && result2 == compare2);
}

void MathUtilsTest::clipFloat( void )
{
	float val = 45.345f;
	float compare = 45.1f;
	float compare2 = 55.5f;

	float result = toxi::math::MathUtils::clip( val, 0.0f, compare );
	float result2 = toxi::math::MathUtils::clip( val, compare2, 60.0f );

	CPPUNIT_ASSERT( result == compare && result2 == compare2 );
}

void MathUtilsTest::clipDouble( void )
{
	double val = 945.12345678;
	double compare = 670.7654321;
	double compare2 = 1050.13572454444;

	double result = toxi::math::MathUtils::clip( val, 0.0, compare );
	double result2 = toxi::math::MathUtils::clip( val, compare2, 2000.0 );

	CPPUNIT_ASSERT( result == compare && result2 == compare2 );
}

void MathUtilsTest::clipNormalizedInt( void )
{
	int val1 = 2;
	int val2 = -10;

	int res1 = MathUtils::clipNormalized( val1 );
	int res2 = MathUtils::clipNormalized( val2 );

	

	CPPUNIT_ASSERT( res1 == 1 && res2 == 0 );
}

void MathUtilsTest::clipNormalizedLong( void )
{
	long val1 = 2;
	long val2 = -10;

	int res1 = MathUtils::clipNormalized( val1 );
	int res2 = MathUtils::clipNormalized( val2 );

	CPPUNIT_ASSERT( res1 == 1 && res2 == 0 );
}

void MathUtilsTest::clipNormalizedFloat( void )
{
	float val1 = 2.0f;
	float val2 = -10.0f;
	float val3 = 0.4567f;

	float res1 = MathUtils::clipNormalized( val1 );
	float res2 = MathUtils::clipNormalized( val2 );
	float res3 = MathUtils::clipNormalized( val3 );

	CPPUNIT_ASSERT( res1 == ( float ) ( 1.0 ) && res2 == ( float ) ( 0.0 ) && res3 == val3 );
}

void MathUtilsTest::clipNormalizedDouble( void )
{
	double val1 = 2.0f;
	double val2 = -10.0f;
	double val3 = 0.4567f;

	double res1 = MathUtils::clipNormalized( val1 );
	double res2 = MathUtils::clipNormalized( val2 );
	double res3 = MathUtils::clipNormalized( val3 );

	CPPUNIT_ASSERT( res1 == 1.0 && res2 == 0.0 && res3 == val3 );
}

void MathUtilsTest::cos( void )
{
	int deg = 90;
	float res1 = 0.0;
	float sin = MathUtils::cos( MathUtils::radians( deg ) );

	float deg2 = 180;
	float res2 = -1.0;
	float sin2 = MathUtils::cos( MathUtils::radians( deg2 ) );

	double deg3 = 0.0;
	double res3 = 1.0;
	double sin3 = MathUtils::cos( MathUtils::radians( deg3 ) );

	CPPUNIT_ASSERT( sin >= res1 - 0.00001 && sin <= res1 + 0.000001 && sin2 == res2 && sin3 == res3 );
}

void MathUtilsTest::sin( void )
{
	int deg = 90;
	float res1 = 1.0;
	float sin = MathUtils::sin( MathUtils::radians( deg ) );

	float deg2 = 180;
	float res2 = 0.0;
	float sin2 = MathUtils::sin( MathUtils::radians( deg2 ) );

	double deg3 = 270.0;
	double res3 = -1.0;
	double sin3 = MathUtils::sin( MathUtils::radians( deg3 ) );

	CPPUNIT_ASSERT( sin == res1 && sin2 >= res2 - 0.000001 && sin2 <= res2 + 0.00001 && sin3 == res3 );
}

void MathUtilsTest::radians( void )
{
	double degree = 180.0;
	double rad = MathUtils::radians( degree );

	CPPUNIT_ASSERT( rad == MathUtils::PI );
}

void MathUtilsTest::degree( void )
{
	double rad = MathUtils::PI;
	double deg = MathUtils::degrees( rad );

	CPPUNIT_ASSERT( deg == 180.0 );
}

void MathUtilsTest::floor( void )
{
	float toFloor1 = 111.11f;
	int toCompare1 = 111;
	int result1 = MathUtils::floor( toFloor1 );
	bool test1 = toCompare1 == result1 ? true : false;

	double toFloor2 = 84638405.19283756;
	long toCompare2 = 84638405;
	long result2 = MathUtils::floor( toFloor2 );
	bool test2 = toCompare2 == result2 ? true : false;

	CPPUNIT_ASSERT( test1 && test2 );
}

void MathUtilsTest::flipCoin( void )
{
	bool wasZero = false;
	bool wasOne = false;
	for( int i = 0; i < 100; i++ ) 
	{
		bool coin = MathUtils::flipCoin();
		if( coin == true )
		{
			wasOne = true;
		}

		if( coin == false ) 
		{
			wasZero = true;
		}
	}

	CPPUNIT_ASSERT( wasZero && wasOne );
}

void MathUtilsTest::dualSign( void )
{
	CPPUNIT_ASSERT( false );
}

void MathUtilsTest::gcd( void )
{
	int first = 10;
	int second = 20;

	int gdc = MathUtils::gcd( first, second );
	bool correct = gdc == first ? true : false;

	int first2 = 198;
	int second2 = 148;

	int gdc2 = MathUtils::gcd( first2, second2 );
	bool correct2 = gdc2 == 2 ? true : false;

	CPPUNIT_ASSERT( correct && correct2 );
}

void MathUtilsTest::impulse( void )
{
	double k1 = 10;
	double x1 = 1 / k1;

	double res1 = MathUtils::impulse( k1, x1 );
	bool first = res1 == 1.0 ? true : false;

	float k2 = 50;
	float x2 = 1 / k2;

	float res2 = MathUtils::impulse( k2, x2 );
	bool second = res2 == 1.0 ? true : false;

	CPPUNIT_ASSERT( first && second );
}

void MathUtilsTest::lcm( void )
{
	int f1 = 20;
	int f2 = 12;

	int res1 = MathUtils::lcm( f1, f2 );
	bool first = res1 == 60 ? true : false;

	int k1 = 34;
	int k2 = 134;
	int res2 = MathUtils::lcm( k1, k2 );
	bool second = res2 == 2278 ? true : false;

	CPPUNIT_ASSERT( first && second );
}

void MathUtilsTest::maxTest( void )
{
	// two doules
	double m1 = 13452.237634539;
	double m2 = 13452.237634639;

	double mr = MathUtils::max( m1, m2 );
	bool first = mr == m2 ? true : false;

	// two floats
	float r1 = 34.4556f;
	float r2 = 34.5f;
	double rr = MathUtils::max( r1, r2 );
	bool second = rr == r2 ? true : false;

	// three doubles
	double d1 = 23.27374647;
	double d2 = 23.45567;
	double d3 = 24.74747474646464;
	double dr = MathUtils::max( d1, d2, d3 );
	bool third = dr == d3 ? true : false;

	//three floats
	float t1 = 78.7878f;
	float t2 = 90.38393f;
	float t3 = 12.202f;
	float tr = MathUtils::max( t1, t2, t3 );
	bool fourth = tr == t2 ? true : false;

	//two ints
	int z1 = 12;
	int z2 = 1;
	int tz = MathUtils::max( z1, z2 );
	bool fifth = tz == z1 ? true : false;

	//three ints
	int u1 = 45;
	int u2 = 189;
	int u3 = 2000;
	int ur = MathUtils::max( u1, u2, u3 );
	bool sixth = ur == u3 ? true : false;


	// two longs
	long l1 = 18181818;
	long l2 = 22222222;
	long lr = MathUtils:: max( l1, l2 );
	bool seventh = lr == l2 ? true : false;

	//three longs 
	long o1 = 989898;
	long o2 = 23;
	long o3 = 44444444;
	long or = MathUtils::max( o1, o2, o3 );
	bool eighth = or == o3 ? true : false;

	CPPUNIT_ASSERT( first && second && third && fourth && fifth && sixth && seventh && eighth );
}

void MathUtilsTest::minTest( void )
{
	// two doules
	double m1 = 13452.237634539;
	double m2 = 13452.237634639;

	double mr = MathUtils::min( m1, m2 );
	bool first = mr == m1 ? true : false;

	// two floats
	float r1 = 34.4556f;
	float r2 = 34.5f;
	double rr = MathUtils::min( r1, r2 );
	bool second = rr == r1 ? true : false;

	// three doubles
	double d1 = 23.27374647;
	double d2 = 23.45567;
	double d3 = 24.74747474646464;
	double dr = MathUtils::min( d1, d2, d3 );
	bool third = dr == d1 ? true : false;

	//three floats
	float t1 = 78.7878f;
	float t2 = 90.38393f;
	float t3 = 12.202f;
	float tr = MathUtils::min( t1, t2, t3 );
	bool fourth = tr == t3 ? true : false;

	//two ints
	int z1 = 12;
	int z2 = 1;
	int tz = MathUtils::min( z1, z2 );
	bool fifth = tz == z2 ? true : false;

	//three ints
	int u1 = 45;
	int u2 = 189;
	int u3 = 2000;
	int ur = MathUtils::min( u1, u2, u2 );
	bool sixth = ur == u1 ? true : false;

	// two longs
	long l1 = 181818181;
	long l2 = 222222222;
	long lr = MathUtils:: min( l1, l2 );
	bool seventh = lr == l1 ? true : false;

	//three longs 
	long o1 = 9898989;
	long o2 = 23;
	long o3 = 444444444;
	long or = MathUtils::min( o1, o2, o3 );
	bool eighth = or == o2 ? true : false;

	CPPUNIT_ASSERT( first && second && third && fourth && fifth && sixth && seventh && eighth );
}

void MathUtilsTest::random( void )
{
	//normalized random double
	double n1 = MathUtils::normalizedRandom();
	bool nr1 = ( n1 > -1 && n1 < 1 ) ? true : false;

	//normalized random float
	float n2 = ( float ) ( MathUtils::normalizedRandom() );
	bool nr2 = ( n2 > -1 && n2 < 1 ) ? true : false;

	// random double
	double d1 = MathUtils::random( 10 );
	bool dr = ( d1 > 0 && d1 < 10 ) ? true : false;

	// random float 
	double f1 = MathUtils::random( 145 );
	bool fr = ( f1 > 0 && f1 < 145 ) ? true : false;

	// range random double
	double a1 = MathUtils::random( 222222, 444444444 );
	bool ar = ( a1 > 222222 && a1 < 444444444 );

	// range random float
	double w1 = MathUtils::random( 12.345, 13.0 );
	bool wr = ( w1 > 12.345 && w1 < 13.0 );

	// int random
	double o1 = MathUtils::random( 5 );
	bool or = ( o1 > 0 && o1 < 5 );

	// range random int
	double p1 = MathUtils::random( 3, 10 );
	bool pr = ( p1 > 3 && p1 < 10 );

	CPPUNIT_ASSERT( nr1 && nr2 && dr && fr && ar && wr && or && pr );
}

void MathUtilsTest::reduceAngle( void )
{
	// testing double
	double outOfRange = 100.26262626262;
	double inRange = MathUtils::reduceAngle( outOfRange );
	bool r1 = ( inRange > -MathUtils::QUARTER_PI && inRange < MathUtils::QUARTER_PI ) ? true : false;

	//testing float
	float outOfRange2 = 245.23f;
	double inRange2 = MathUtils::reduceAngle( outOfRange );
	bool r2 = ( inRange > -MathUtils::QUARTER_PI && inRange < MathUtils::QUARTER_PI ) ? true : false;

	CPPUNIT_ASSERT( r1 && r2 );
}

void MathUtilsTest::sign( void )
{
	// double
	double r1 = -124;
	int sr1 = MathUtils::sign( r1 );
	bool rs = sr1 == -1 ? true : false;

	//float
	float e1 = 34;
	int se1 = MathUtils::sign( e1 );
	bool re = se1 == 1 ? true : false;

	// int
	int i1 = 0;
	int si1 = MathUtils::sign( i1 );
	bool ri = si1 == 0 ? true : false;

	CPPUNIT_ASSERT( rs && re && ri );
}
