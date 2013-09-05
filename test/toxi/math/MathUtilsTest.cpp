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
