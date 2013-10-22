#include "DoubleRangeTest.h"
#include <toxi/util/datatypes/DoubleRange.h>
#include "../../../../src/toxi/math/MathUtils.h"

/**
 * Tests the "getRange" method.
 */
void DoubleRangeTest::construktorTest(void)
{
	toxi::util::datatypes::DoubleRange range(2.0, 8.0);
	bool r1 = ( range.getMin() == 2.0 && range.getMax() == 8.0 ) ? true : false;

	toxi::util::datatypes::DoubleRange range2 = toxi::util::datatypes::DoubleRange();
	bool r2 = ( range2.getMin() == 0.0 && range2.getMax() == 0.0 && range2.getCurrent() ==  0.0 ) ? true : false;

	toxi::util::datatypes::DoubleRange copyRange = toxi::util::datatypes::DoubleRange( range );
	bool r3 = ( copyRange.getMin() == 2.0 && copyRange.getMax() == 8.0 ) ? true : false;

	double min = 100.0;
	double max = 10.0;
	std::vector< double > samples;
	for( int i = 0; i < 10; i++ )
	{
		double rnd = toxi::math::MathUtils::random( 0, 500 );
		samples.push_back( rnd );
		min = toxi::math::MathUtils::min( rnd, min );
		max = toxi::math::MathUtils::max( rnd, max );
	}

	toxi::util::datatypes::DoubleRange range3( &samples );
	bool r4 = ( range3.getMin() == min && range3.getMax() == max ) ? true : false;
	
	CPPUNIT_ASSERT( r1 && r2 && r3 &r4 );
}

void DoubleRangeTest::adjustCurrent( void )
{
	toxi::util::datatypes::DoubleRange range( 1.0, 10.0 );
	range.setCurrent( 5.0 );
	range.adjustCurrentBy( 1.5 );

	CPPUNIT_ASSERT( range.getCurrent() == 6.5 );
}

void DoubleRangeTest::getMedian( void )
{
	toxi::util::datatypes::DoubleRange range( 1.0, 9.0 );
	double median = range.getMedian();

	CPPUNIT_ASSERT( median == 5.0 );
}

void DoubleRangeTest::getRange( void )
{
	toxi::util::datatypes::DoubleRange range(2.0, 8.0);
	bool r1 = range.getRange() == 6.0 ? true : false;
}

void DoubleRangeTest::isValueInRange( void )
{
	toxi::util::datatypes::DoubleRange range( 10.0, 100.0 );
	bool r1 = range.isValueInRange( 45.2355 );
	bool r2 = !range.isValueInRange( 300.456666 );

	CPPUNIT_ASSERT( r1 && r2 );
}

void DoubleRangeTest::pickRandom( void )
{
	toxi::util::datatypes::DoubleRange range( 10.0, 100.0 );
	double rand = range.pickRandom();

	CPPUNIT_ASSERT( rand > range.getMin() && rand < range.getMax() && rand == range.getCurrent() );
}

void DoubleRangeTest::setCurrent( void )
{
	toxi::util::datatypes::DoubleRange range( 10.0, 100.0 );
	range.setCurrent( 30.2323 );
	bool r1 = range.getCurrent() == 30.2323 ? true : false;

	range.setCurrent( 500.0 );
	bool r2 = range.getCurrent() == range.getMax() ? true : false;

	CPPUNIT_ASSERT( r1 && r2 );
}

void DoubleRangeTest::toVector( void )
{
	toxi::util::datatypes::DoubleRange range( 10.0, 100.0 );
	std::vector< double > v = range.toVector( 0.5 );
	bool r1 = true;
	for( auto it = v.begin(); it != v.end(); ++it )
	{
		double val = *it;
		r1 = ( val >= range.getMin() && val <= range.getMax() ) ? true : false;
		r1 = (std::fmod( *it, 0.5 ) == 0) ? true : false;
	}

	CPPUNIT_ASSERT( r1 );
}

void DoubleRangeTest::getters( void )
{
	toxi::util::datatypes::DoubleRange range( 50.0, 100.0 );
	bool r1 = ( range.getMin() == 50.0 && range.getMax() == 100.0 && range.getCurrent() == 50.0 ) ? true : false;

	CPPUNIT_ASSERT( r1 );
}

void DoubleRangeTest::assignmentOperatorOverloading( void )
{
	toxi::util::datatypes::DoubleRange range( 50.0, 100.0 );
	toxi::util::datatypes::DoubleRange range2 = range;

	bool r1 = ( range2.getMin() == range.getMin() && range2.getMax() == range.getMax() && range2.getCurrent() == range.getCurrent() ) ? true : false;

	CPPUNIT_ASSERT( r1 );
}
