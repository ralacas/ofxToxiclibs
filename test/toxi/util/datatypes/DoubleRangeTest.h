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
		CPPUNIT_TEST( construktorTest );
		CPPUNIT_TEST( adjustCurrent );
		CPPUNIT_TEST( getMedian );
		CPPUNIT_TEST( getRange );
		CPPUNIT_TEST( isValueInRange );
		CPPUNIT_TEST( pickRandom );
		CPPUNIT_TEST( setCurrent );
		CPPUNIT_TEST( toVector );
		CPPUNIT_TEST( getters );
		CPPUNIT_TEST( assignmentOperatorOverloading );
		CPPUNIT_TEST_SUITE_END();
		
	public:	
		/**
		 * Tests the construktor method.
		 */
		void construktorTest(void);
		void adjustCurrent( void );
		void getMedian( void );
		void getRange( void );
		void isValueInRange( void );
		void pickRandom( void );
		void setCurrent( void );
		void toVector( void );
		void getters( void );
		void assignmentOperatorOverloading( void );
};

#endif