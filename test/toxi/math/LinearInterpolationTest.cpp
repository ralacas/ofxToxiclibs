#include "LinearInterpolationTest.h"
#include "../../../src/toxi/math/LinearInterpolation.h"

void LinearInterpolationTest::interpolate( void )
{
	// double
	toxi::math::LinearInterpolation stat = toxi::math::LinearInterpolation();
	double val = stat.interpolate(0.0, 10.0, 0.5 );
	bool r1 = ( val == 5.0) ? true : false;

	//float
	float val2 = stat.interpolate(0.0f, 100.0f, 0.5f );
	bool r2 = val2 == 50.0 ? true : false;
	CPPUNIT_ASSERT( r1 && r2 );
}
