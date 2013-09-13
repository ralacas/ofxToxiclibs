/**
 * ofxToxicLibsTestCases - Test Suite for Vec2D Module.
 *
 * @author		Marcel Schwittlick<lzrm@mrzl.net>
 * @file		Source/Vec2DTest.h
 * @version 	1.0.0 11-Jul-13
 * @copyright	Copyright (c) 2013 by Marcel Schwittlick. All rights reserved. (http://www.mrzl.net)
 */
#include "Vec2DTest.h"
#include <toxi/geom/Vec2D.h>

using namespace toxi::geom;

void Vec2DTest::constuctorTest()
{
	Vec2D v = Vec2D( 10, 20 );
	bool r1 = ( v.getX() == 10.0 && v.getY() == 20.0 ) ? true : false;

	Vec2D v2 = Vec2D( v );
	bool r2 = ( v2.getX() == 10.0 && v2.getY() == 20.0 ) ? true : false;

	Vec2D v3 = Vec2D( toxi::math::MathUtils::QUARTER_PI );
	bool r3 = ( v3.getX() == toxi::math::MathUtils::cos( toxi::math::MathUtils::QUARTER_PI) && v3.getY() == toxi::math::MathUtils::sin( toxi::math::MathUtils::QUARTER_PI ) ) ? true : false;

	std::cout << r1 << r2 << r3 << std::endl;
	CPPUNIT_ASSERT( r1 && r2 && r3 );
}

void Vec2DTest::operatorOverloadingTest()
{
	Vec2D v1 = Vec2D( 40.0, 50.0 );
	Vec2D v2 = v1;
	bool r1 = ( v2.getX() == 40.0 && v2.getY() == 50.0 ) ? true : false;
}

void Vec2DTest::failedTest()
{
	CPPUNIT_ASSERT( false );
}


