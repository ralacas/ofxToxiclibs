/**
 * ofxToxicLibsTestCases - Test Suite for Double Range Module.
 *
 * @author		Andy Liebke<coding@andysmiles4games.com>
 * @file		Source/DoubleRangeTest.cpp
 * @version 	1.0.0 07-Jul-13
 * @copyright	Copyright (c) 2013 by Andy Liebke. All rights reserved. (http://www.andysmiles4games.com)
 */
#include "DoubleRangeTest.h"
#include <toxi/util/DoubleRange.h>

/**
 * Tests the "getRange" method.
 */
void DoubleRangeTest::getRangeTest(void)
{
	toxi::util::datatypes::DoubleRange range(2.0, 8.0);
	
	CPPUNIT_ASSERT(range.getRange() == 6.0);
}