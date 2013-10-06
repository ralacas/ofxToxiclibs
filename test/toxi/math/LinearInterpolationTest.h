#ifndef __LINEAR_INTERPOLATION_TEST_H__
#define __LINEAR_INTERPOLATION_TEST_H__

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class LinearInterpolationTest : public CppUnit::TestFixture
{
public:
	CPPUNIT_TEST_SUITE( LinearInterpolationTest );
	CPPUNIT_TEST( interpolate );
	CPPUNIT_TEST_SUITE_END();

	void interpolate( void );
};

#endif