#include "VecMathUtilTest.h"
#include "toxi/geom/VecMathUtil.h"

void VecMathUtilTest::doubleToLongBits( void )
{
	double d = 100.1;
	long l = toxi::geom::VecMathUtil::doubleToLongBits( d );
	bool r1 = l == 1717986918 ? true : false;
	CPPUNIT_ASSERT( r1 );
}

void VecMathUtilTest::floatToIntBis( void )
{
	float f = 10.342f;
	int i = toxi::geom::VecMathUtil::floatToIntBits( f );
	bool r1 = i == 1092974805 ? true : false;
	CPPUNIT_ASSERT( r1 );
}
