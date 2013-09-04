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

/**
 * Tests the "normalize" method.
 */
void Vec2DTest::normalizeTest(void)
{
	toxi::geom::Vec2D v(2.0, 2.0);
	std::cout << "Testing normalize() function from Vec2D." << std::endl;
	CPPUNIT_ASSERT(v.normalize().x == 1.0);
} 