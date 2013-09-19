#ifndef __VECMATH_UTIL_TEST_H__
#define __VECMATH_UTIL_TEST_H__

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class VecMathUtilTest : public CppUnit::TestFixture
{
public:
	CPPUNIT_TEST_SUITE( VecMathUtilTest );
	CPPUNIT_TEST( doubleToLongBits );
	CPPUNIT_TEST( floatToIntBis );
	CPPUNIT_TEST_SUITE_END();

	void doubleToLongBits( void );
	void floatToIntBis( void );
};

#endif

