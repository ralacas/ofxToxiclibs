#ifndef __SCALE_MAP_TEST_H__
#define __SCALE_MAP_TEST_H__

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class ScaleMapTest : public CppUnit::TestFixture
{
public:
	CPPUNIT_TEST_SUITE( ScaleMapTest );
	CPPUNIT_TEST( constructorTest );
	CPPUNIT_TEST( assignmentOperatorOverloading );
	CPPUNIT_TEST( clippedValue );
	CPPUNIT_TEST( median );
	CPPUNIT_TEST( getMappedValueFor );
	CPPUNIT_TEST( getMappedMedian );
	CPPUNIT_TEST( gettersAndSetters );
	CPPUNIT_TEST_SUITE_END();

	void constructorTest( void );
	void assignmentOperatorOverloading( void );
	void clippedValue( void );
	void median( void );
	void getMappedValueFor( void );
	void getMappedMedian( void );
	void gettersAndSetters( void );
};

#endif // !__SCALE_MAP_TEST_H__