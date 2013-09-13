/**
 * ofxToxicLibsTestCases - Test Suite for Vec2D Module.
 *
 * @author		Marcel Schwittlick<lzrm@mrzl.net>
 * @file		Source/Vec2DTest.h
 * @version 	1.0.0 11-Jul-13
 * @copyright	Copyright (c) 2013 by Marcel Schwittlick. All rights reserved. (http://www.mrzl.net)
 */
#ifndef __VEC2D_TEST_H__
#define __VEC2D_TEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

/**
 * Test Suite for the Vec2D module.
 */
class Vec2DTest : public CppUnit::TestFixture
{
	public:
		CPPUNIT_TEST_SUITE(Vec2DTest);
		CPPUNIT_TEST( constuctorTest );
		CPPUNIT_TEST( operatorOverloadingTest );
		//CPPUNIT_TEST(getRangeTest);
		CPPUNIT_TEST(failedTest );
		CPPUNIT_TEST_SUITE_END();
		
	public:	
		void constuctorTest();
		void operatorOverloadingTest();
		void failedTest();
		/**
		 * Tests the "getRange" method.
		 */
};

#endif