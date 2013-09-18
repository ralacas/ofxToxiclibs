#include "ScaleMapTest.h"
#include "../../../src/toxi/math/ScaleMap.h"
#include <typeinfo>


void ScaleMapTest::constructorTesting( void )
{

	toxi::math::ScaleMap map = toxi::math::ScaleMap( 0.0, 10.0, 50.0, 100.0 );
	bool r1 = ( *map.interval == 10.0 ) ? true : false;
	bool r2 = ( *map.mapRange == 50.0 ) ? true : false;
	bool r3 = ( map.mapFunction != nullptr ) ? true : false;
	bool r4 = ( map.in != nullptr && map.out != nullptr ) ? true : false;
	
	toxi::math::ScaleMap map2 ( map );
	bool r5 = ( *map2.interval == 10.0 ) ? true : false;
	bool r6 = ( *map2.mapRange == 50.0 ) ? true : false;

	CPPUNIT_ASSERT( r1 && r2 && r3 && r4 && r5 && r6 );
}

void ScaleMapTest::assignmentOperatorOverloading( void )
{
	toxi::math::ScaleMap map = toxi::math::ScaleMap( 0.0, 10.0, 50.0, 100.0 );
	toxi::math::ScaleMap map2 = map;

	bool r1 = ( *map2.interval == 10.0 ) ? true : false;
	bool r2 = ( *map.mapRange == 50.0 ) ? true : false;
	bool r3 = ( map.mapFunction != nullptr ) ? true : false;
	bool r4 = ( map.in != nullptr && map.out != nullptr ) ? true : false;

	CPPUNIT_ASSERT( r1 && r2 && r3 && r4 );
}

void ScaleMapTest::clippedValue( void )
{
	toxi::math::ScaleMap map = toxi::math::ScaleMap( 0.0, 10.0, 50.0, 100.0 );
	double v = map.getClippedValueFor( 0.25 );
	bool r1 = v == 51.25 ? true : false;

	CPPUNIT_ASSERT( r1 );
}

void ScaleMapTest::median( void )
{
	toxi::math::ScaleMap map = toxi::math::ScaleMap( 0.0, 10.0, 50.0, 100.0 );
	double med1 = map.getInputMedian();
	bool r1 = med1 == 5.0 ? true : false;

	double medOut = map.getOutputMedian();
	bool r2 = medOut == 75.0 ? true : false;

	CPPUNIT_ASSERT( r1 && r2 );
}

void ScaleMapTest::getMappedValueFor( void )
{
	toxi::math::ScaleMap map = toxi::math::ScaleMap( 0.0, 10.0, 50.0, 100.0 );
	double val = map.getMappedValueFor( 5.0 );
	bool r1 = val == 75.0 ? true : false;

	CPPUNIT_ASSERT( r1 );
}

void ScaleMapTest::getMappedMedian( void )
{
	toxi::math::ScaleMap map = toxi::math::ScaleMap( 0.0, 10.0, 50.0, 100.0 );
	double val = map.getMappedMedian();
	double r1 = val == 52.5 ? true : false;

	CPPUNIT_ASSERT( r1 );
}

void ScaleMapTest::gettersAndSetters( void )
{
	toxi::math::ScaleMap map = toxi::math::ScaleMap( 0.0, 10.0, 50.0, 100.0 );
	
	map.setInputRange( 5.0, 10.0 );
	bool r1 = map.in->getMin() == 5.0 ? true : false;
	bool r2 = map.in->getMax() == 10.0 ? true : false;

	map.setOutputRange( 100.0, 200.0 );
	bool r3 = map.out->getMin() == 100.0 ? true : false;
	bool r4 = map.out->getMax() == 200.0 ? true : false;

	bool r5 = map.getInputRange()->getMin() == 5.0 ? true : false;
	bool r6 = map.getInputRange()->getMax() == 10.0 ? true : false;
	bool r7 = map.getOutputRange()->getMin() == 100.0 ? true : false;
	bool r8 = map.getOutputRange()->getMax() == 200.0 ? true : false;

	CPPUNIT_ASSERT( r1 && r2 && r3 && r4 && r5 && r6 && r7 && r8 );
}
