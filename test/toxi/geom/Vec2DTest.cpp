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

void Vec2DTest::angleBetweenTest( void )
{
	Vec2D * v1 = new Vec2D( 5, 15 );
	Vec2D * v2 = new Vec2D( 10, -20 );

	double angle = v1->angleBetween( v2 );
	bool r1 = toxi::math::MathUtils::isNan( angle );

	double angle2 = v1->angleBetween( v2, true );


	delete v1;
	delete v2;


	CPPUNIT_ASSERT( false );
}

void Vec2DTest::crossTest( void )
{
	Vec2D * v = new Vec2D( 10, 10 );
	Vec2D * toCross = new Vec2D( 5, 10 );
	double cross = v->cross( toCross );

	CPPUNIT_ASSERT( cross == 50.0 ? true : false );

	delete v;
	delete toCross;
}

void Vec2DTest::distanceToTest( void )
{
	Vec2D * v1 = new Vec2D( 10, 10 );
	Vec2D * v2 = new Vec2D( 5, 10 );

	double dist = v1->distanceTo( v2 );
	bool r1 = dist == 5.0 ? true : false;

	double distSquared = v1->distanceToSquared( v2 );
	bool r2 = distSquared == 25.0 ? true : false;

	CPPUNIT_ASSERT( r1 && r2 );

	delete v1;
	delete v2;
}

void Vec2DTest::dotTest( void )
{
	Vec2D * v1 = new Vec2D( 10, 10 );
	Vec2D * v2 = new Vec2D( 5, 10 );
	double dot = v1->dot( v2 );

	CPPUNIT_ASSERT( dot == 150.0 ? true : false );

	delete v1;
	delete v2;
}

void Vec2DTest::equalsTest( void )
{
	Vec2D v1 = Vec2D( 123.45, 678.12 );
	Vec2D v2 = Vec2D( 123.45, 678.12 );
	bool r1 = v1 == v2;

	v2.addSelf( 0.4, 0.4 );
	bool r2 = v1.equalsWithTolerance( &v2, 0.5 );

	v2.subSelf( 1.0, 1.0 );
	bool r3 = v1.equalsWithTolerance( &v2, 0.7 );

	CPPUNIT_ASSERT( r1 && r2 && r3 );
}


