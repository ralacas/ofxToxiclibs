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
		CPPUNIT_TEST( failedTest );
		CPPUNIT_TEST( angleBetweenTest );
		CPPUNIT_TEST( crossTest );
		CPPUNIT_TEST( distanceToTest );
		CPPUNIT_TEST( dotTest );
		CPPUNIT_TEST( equalsTest );
		CPPUNIT_TEST( getComponentTest );
		CPPUNIT_TEST( headingTest );
		CPPUNIT_TEST( hashCodeTest );
		CPPUNIT_TEST( isInCircle );
		CPPUNIT_TEST( isInRectangle );
		CPPUNIT_TEST( isInTriangle );
		CPPUNIT_TEST( isMajorAxis );
		CPPUNIT_TEST( isZeroVector );
		CPPUNIT_TEST( magnitudeTest );
		CPPUNIT_TEST( magSquaredTest );
		CPPUNIT_TEST( positiveHeadingTest );

		CPPUNIT_TEST( bisectTest );

		CPPUNIT_TEST( absTest );
		CPPUNIT_TEST( constrainTest );
		CPPUNIT_TEST( floorTest );
		CPPUNIT_TEST( fracTest );
		CPPUNIT_TEST( invertTest );
		CPPUNIT_TEST( limitTest );
		CPPUNIT_TEST( normalizeTest );
		CPPUNIT_TEST( normalizeToTest );

		CPPUNIT_TEST_SUITE_END();
		
	public:	
		void constuctorTest( void );
		void operatorOverloadingTest( void );
		void failedTest( void );
		void angleBetweenTest( void );
		void crossTest( void );
		void distanceToTest( void );
		void dotTest( void );
		void equalsTest( void );
		void getComponentTest( void );
		void headingTest( void );
		void hashCodeTest( void );
		void isInCircle( void );
		void isInRectangle( void );
		void isInTriangle( void );
		void isMajorAxis( void );
		void isZeroVector( void );
		void magnitudeTest( void );
		void magSquaredTest( void );
		void positiveHeadingTest( void );

		void bisectTest( void );

		void absTest( void );
		void constrainTest( void );
		void floorTest( void );
		void fracTest( void );
		void invertTest( void );
		void limitTest( void );
		void normalizeTest( void );
		void normalizeToTest( void );
};

#endif