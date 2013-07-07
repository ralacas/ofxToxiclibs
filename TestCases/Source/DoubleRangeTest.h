/**
 * ofxToxicLibsTestCases - Test Suite for Double Range Module.
 *
 * @author		Andy Liebke<coding@andysmiles4games.com>
 * @file		Source/DoubleRangeTest.h
 * @version 	1.0.0 07-Jul-13
 * @copyright	Copyright (c) 2013 by Andy Liebke. All rights reserved. (http://www.andysmiles4games.com)
 */
#ifndef __DOUBLE_RANGE_TEST_H__
#define __DOUBLE_RANGE_TEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

/**
 * Test Suite for the DoubleRange module.
 */
class DoubleRangeTest : public CppUnit::TestFixture
{
	public:
		CPPUNIT_TEST_SUITE(DoubleRangeTest);
		CPPUNIT_TEST(getRangeTest);
		CPPUNIT_TEST_SUITE_END();
		
	public:	
		/**
		 * Tests the "getRange" method.
		 */
		void getRangeTest(void);
};

#endif