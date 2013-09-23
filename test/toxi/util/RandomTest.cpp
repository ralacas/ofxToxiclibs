#include "RandomTest.h"
#include "../../../src/toxi/util/Random.h"


void RandomTest::randomDouble( void )
{
	double min = 99.0;
	double max = 2222.2334;
	bool r1 = true;
	for( int i = 0; i < 100; i++ ) 
	{
		double rnd = toxi::util::Random::getRandom( min, max );
		if( rnd < min || rnd > max )
		{
			r1 = false;
		}
	}

	long min_l = 100000;
	long max_l = 9000000;
	bool r2 = true;
	for( int i = 0; i < 100; i++ ) 
	{
		long rnd = toxi::util::Random::getRandom( min_l, max_l );
		if( rnd < min_l || rnd > max_l )
		{
			r2 = false;
		}
	}

	CPPUNIT_ASSERT( r1 && r2 );
}

