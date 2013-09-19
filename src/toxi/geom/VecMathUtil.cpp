#include "VecMathUtil.h"

toxi::geom::VecMathUtil::VecMathUtil(void)
{
}


toxi::geom::VecMathUtil::~VecMathUtil(void)
{
}

long toxi::geom::VecMathUtil::doubleToLongBits( double d )
{
	if( d == 0.0 ) {
		return 0L;
	}
	else
	{
		union types {
			double dou;
			long lo;
		};

		types t;
		t.dou = d;
		long returnLong = t.lo;
		return returnLong;
	}
}

int toxi::geom::VecMathUtil::floatToIntBits( float f )
{
	if( f == 0.0 )
	{
		return 0;
	}
	else
	{
		union types {
			float fl;
			int in;
		};
		types t;
		t.fl = f;
		int returnInt = t.in;
		return returnInt;
	}
}
