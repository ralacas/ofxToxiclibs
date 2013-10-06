//#ifndef __MATH_UTILS_TEST_H__
//#define __MATH_UTILS_TEST_H__

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include < cmath >

class RandomTest : public CppUnit::TestFixture
{
public:	
	CPPUNIT_TEST_SUITE( RandomTest );

	CPPUNIT_TEST( randomDouble );

	CPPUNIT_TEST_SUITE_END();

	void randomDouble( void );
};

//#endif