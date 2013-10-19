#include "Vec2DTest.h"
#include <toxi/geom/Vec2D.h>
#include <toxi/geom/Vec3D.h>
#include <toxi/geom/Rect.h>
#include <toxi/geom/Polygon2D.h>

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
	CPPUNIT_ASSERT( r1 );
}

void Vec2DTest::failedTest()
{
	CPPUNIT_ASSERT( false );
}

void Vec2DTest::angleBetweenTest( void )
{
	Vec2D v1 = Vec2D( 5, 15 );
	Vec2D v2 = Vec2D( 10, -20 );

	double angle = v1.angleBetween( v2 );
	bool r1 = toxi::math::MathUtils::isNan( angle );

	double angle2 = v1.angleBetween( v2, true );

	CPPUNIT_ASSERT( false );
}

void Vec2DTest::crossTest( void )
{
	Vec2D v = Vec2D( 10, 10 );
	Vec2D toCross = Vec2D( 5, 10 );
	double cross = v.cross( toCross );

	CPPUNIT_ASSERT( cross == 50.0 ? true : false );
}

void Vec2DTest::distanceToTest( void )
{
	Vec2D v1 = Vec2D( 10, 10 );
	Vec2D v2 = Vec2D( 5, 10 );

	double dist = v1.distanceTo( v2 );
	bool r1 = dist == 5.0 ? true : false;

	double distSquared = v1.distanceToSquared( v2 );
	bool r2 = distSquared == 25.0 ? true : false;

	CPPUNIT_ASSERT( r1 && r2 );
}

void Vec2DTest::dotTest( void )
{
	Vec2D v1 = Vec2D( 10, 10 );
	Vec2D v2 =  Vec2D( 5, 10 );
	double dot = v1.dot( v2 );

	CPPUNIT_ASSERT( dot == 150.0 ? true : false );
}

void Vec2DTest::equalsTest( void )
{
	Vec2D v1 = Vec2D( 123.45, 678.12 );
	Vec2D v2 = Vec2D( 123.45, 678.12 );
	bool r1 = v1 == v2;

	v2.addSelf( 0.4, 0.4 );
	bool r2 = v1.equalsWithTolerance( v2, 0.5 );

	v2.subSelf( 1.0, 1.0 );
	bool r3 = v1.equalsWithTolerance( v2, 0.7 );
	CPPUNIT_ASSERT( r1 && r2 && r3 );
}

void Vec2DTest::getComponentTest( void )
{
	Vec2D v1 = Vec2D( 10.5, 100.1 );
	double comp1 = v1.getComponent( toxi::geom::Vec2D::Axis::X );
	double comp2 = v1.getComponent( 1 );
	bool r1 = comp1 == 10.5 ? true : false;
	bool r2 = comp2 == 100.1 ? true : false;

	CPPUNIT_ASSERT(  r1 && r2 );
}

void Vec2DTest::headingTest( void )
{
	Vec2D v1 = Vec2D( 1, 1 );
	double heading = v1.heading();
	double to_comp = 0.785398;
	bool r1 = ( heading >= to_comp - 0.00001 && heading <= to_comp + 0.00001 ) ? true : false;
	CPPUNIT_ASSERT( r1 );
}

void Vec2DTest::hashCodeTest( void )
{
	Vec2D v = Vec2D( 10, 10 );
	int hashCode = v.hashCode();
	bool r1 = hashCode == 603980737 ? true : false;

	CPPUNIT_ASSERT( r1 );
}

void Vec2DTest::isInCircle( void )
{
	Vec2D v = Vec2D( 1, 1 );
	bool isInCircle1 = v.isInCircle( Vec2D( 1, 1), 0.1 );
	bool isInCircle2 = !v.isInCircle( Vec2D( 3, 3), 1.5 );

	CPPUNIT_ASSERT( isInCircle1 && isInCircle2 );
}

void Vec2DTest::isInRectangle( void )
{
	Vec2D v = Vec2D( 10, 10 );
	bool isInRect1 = v.isInRectangle( toxi::geom::Rect( 0, 0, 11, 11) );
	bool isInRect2 = !v.isInRectangle( toxi::geom::Rect( 0, 0, 9, 9 ) );

	CPPUNIT_ASSERT( isInRect1 && isInRect2 );
}

void Vec2DTest::isInTriangle( void )
{
	Vec2D v = Vec2D( 5, 5 );
	bool isInTriangle1 = v.isInTriangle( Vec2D( 0, 0 ), Vec2D( 10, 0), Vec2D( 0, 10 ) );
	bool isInTriangle2 = !v.isInTriangle( Vec2D( 10, 10 ), Vec2D( 20, 10 ), Vec2D( 10, 20 ) );

	CPPUNIT_ASSERT( isInTriangle1 && isInTriangle2 );
}

void Vec2DTest::isMajorAxis( void )
{
	Vec2D v = Vec2D( 11, 0 );
	bool r1 = v.isMajorAxis( 0.2 );
	
	v.setComponent( toxi::geom::Vec2D::Axis::Y, 1 );
	bool r2 = !v.isMajorAxis( 0.2 );

	CPPUNIT_ASSERT( r1 && r2 );
}

void Vec2DTest::isZeroVector( void )
{
	Vec2D v = Vec2D(0, 0 );
	bool r1 = v.isZeroVector();
	v.setComponent( toxi::geom::Vec2D::Axis::Y, 1 );

	bool r2 = !v.isZeroVector();

	CPPUNIT_ASSERT( r1 && r2 );
}

void Vec2DTest::magnitudeTest( void )
{
	Vec2D v = Vec2D( 10, 20 );
	double mag = v.magnitude();
	double resMag = 22.360679626464844;
	bool r1 = ( mag <= resMag + 0.000001 ) ? true : false;
	bool r2 = ( mag >= resMag - 0.000001 ) ? true : false;

	CPPUNIT_ASSERT( r1 && r2 );
}

void Vec2DTest::magSquaredTest( void )
{
	Vec2D v = Vec2D( 10, 20 );
	double mag = v.magSquared();
	double resMag = 500.0;
	bool r1 = ( mag <= resMag + 0.000001 ) ? true : false;
	bool r2 = ( mag >= resMag - 0.000001 ) ? true : false;

	CPPUNIT_ASSERT( r1 && r2 );
}

void Vec2DTest::positiveHeadingTest( void )
{
	Vec2D v = Vec2D( 2, 2 );
	double pos = v.positiveHeading();

	v.set( 20, 20 );
	double pos2 = v.positiveHeading();

	bool r1 = pos == pos2 ? true : false;

	CPPUNIT_ASSERT( r1 );
}

void Vec2DTest::bisectTest( void )
{
	Vec2D v1 = Vec2D( 10, 20 );
	Vec2D v2 = Vec2D( 3, 2 );
	Vec3D bis = v1.bisect( v2 );
	bool r1 = ( bis.getX() == 7.0 && bis.getY() == 18.0 && bis.getZ() == -243.5 ) ? true : false;

	CPPUNIT_ASSERT( r1 );
	//delete bis;
}

void Vec2DTest::absTest( void )
{
	Vec2D v = Vec2D( -10, 10 );
	v.abs();
	bool r1 = ( v.getX() > 0.0 && v.getY() > 0.0 ) ? true : false;

	CPPUNIT_ASSERT( r1 );
}

void Vec2DTest::constrainTest( void )
{
	Vec2D v = Vec2D( 100, 100 );
	Polygon2D poly = Polygon2D( );
	poly.add(0.0, 0.0)->add(10.0, 20.0 )->add(-10.0, 20.0 )->add(10.0, -20.0 )->add(20.0, 50.0 )->add(-10.0, -20.0 );

	v.constrain(poly);

	bool r1 = ( v.getX() == 20.0 && v.getY() == 50.0) ? true : false;

	Vec2D v2 = Vec2D( -50, 100 );
	Rect rect = Rect(0, 0, -20, 50 );
	v2.constrain(rect);

	bool r2 = ( v2.getX() == 0.0 && v2.getY() == 50.0) ? true : false;

	Vec2D v3 = Vec2D( -50, - 50 );
	Vec2D v2_t1 = Vec2D( -80, -20 );
	Vec2D v2_t2 = Vec2D( -20, 0 );
	v3.constrain( v2_t1, v2_t2 );

	bool r3 = ( v3.getX() == -50.0 && v3.getY() == -20.0) ? true : false;

	CPPUNIT_ASSERT( r1 && r2 && r3 );
}

void Vec2DTest::floorTest( void )
{
	Vec2D v = Vec2D( 10.4, 9.8 );
	v.floor();

	bool r = ( v.getX() == 10.0 && v.getY() == 9.0 ) ? true : false;

	CPPUNIT_ASSERT( r );
}

void Vec2DTest::fracTest( void )
{
	Vec2D v = Vec2D( 10.4, 9.8 );
	v.frac();

	bool r = (v.getX() <= 0.41 && v.getX() >= 0.39 && v.getY() <= 0.81 && v.getY() >= 0.79 ) ? true : false;

	CPPUNIT_ASSERT( r );
}

void Vec2DTest::invertTest( void )
{
	Vec2D v = Vec2D( 10.4, 9.8 );
	v.invert();

	bool r = (v.getX() == -10.4 && v.getY() == -9.8 ) ? true : false;

	CPPUNIT_ASSERT( r );
}

void Vec2DTest::normalizeTest( void )
{
	Vec2D v = Vec2D( 10, 5 );
	v.normalize();

	bool r = ( v.getX() <= 0.9 && v.getX() >= 0.894 && v.getY() <= 0.45 && v.getY() >= 0.44 ) ? true : false;

	CPPUNIT_ASSERT( r );
}

void Vec2DTest::limitTest( void )
{
	Vec2D v = Vec2D( 10, 10 );
	v.limit( 5 );

	bool r = ( v.getX() <= 3.55 && v.getX() >= 3.52 && v.getY() <= 3.55 && v.getY() >= 3.52 ) ? true : false;

	CPPUNIT_ASSERT( r );
}

void Vec2DTest::normalizeToTest( void )
{
	Vec2D v = Vec2D( 10, 10 );
	v.normalizeTo( 5.0 );

	bool r1 = ( v.getX() <= 3.54 && v.getX() >= 3.53 && v.getY() <= 3.54 && v.getY() >= 3.53 ) ? true : false;
	
	CPPUNIT_ASSERT( r1 );
}

void Vec2DTest::addSelfTest( void )
{
	Vec2D v1 = Vec2D( 10, 10 );
	v1.addSelf( v1 );

	bool r1 = ( v1.getX() == 20.0 && v1.getY() == 20.0 ) ? true : false;

	v1.addSelf(5.0, 5.0 );

	bool r2 = ( v1.getX() == 25.0 && v1.getY() == 25.0 ) ? true : false;

	CPPUNIT_ASSERT( r1 && r2 );
}

void Vec2DTest::subSelfTest( void )
{
	Vec2D v1 = Vec2D( 25, 25 );
	Vec2D vSub = Vec2D( 10, 10);
	v1.subSelf( vSub );

	bool r1 = ( v1.getX() == 15.0 && v1.getY() == 15.0 ) ? true : false;

	v1.subSelf(5.0, 5.0 );

	bool r2 = ( v1.getX() == 10.0 && v1.getY() == 10.0 ) ? true : false;

	CPPUNIT_ASSERT( r1 && r2 );
}

void Vec2DTest::setTest( void )
{
	Vec2D v = Vec2D( 10, 10 );
	v.set( 5, 8 );

	bool r = ( v.getX() == 5.0 && v.getY() == 8.0 ) ? true : false;

	Vec2D vSet = Vec2D( 20, 20 );
	v.set( vSet );

	bool r2 = ( v.getX() == 20.0 && v.getY() == 20.0 ) ? true : false;

	CPPUNIT_ASSERT( r && r2 );
}

void Vec2DTest::setComponent( void )
{
	Vec2D v = Vec2D( 10, 10 );
	v.setComponent(0, 20 );

	bool r1 = ( v.getX() == 20.0 && v.getY() == 10.0) ? true : false;

	toxi::geom::Vec2D::Axis axis = toxi::geom::Vec2D::Axis::X;
	v.setComponent( axis, 30.0 );

	bool r2 = ( v.getX() == 30.0 && v.getY() == 10.0) ? true : false;

	CPPUNIT_ASSERT( r1 && r2 );
}

void Vec2DTest::perpendicularTest( void )
{
	Vec2D v = Vec2D( 10, 10 );
	v.perpendicular();

	bool r = ( v.getX() == -10.0 && v.getY() == 10.0 ) ? true : false;

	CPPUNIT_ASSERT( r );
}

void Vec2DTest::toPolarTest( void )
{
	Vec2D v = Vec2D( 10, 10 );
	v.toPolar();

	std::cout << "heay" << std::endl;
	std::cout << v << std::endl;

	bool r = ( v.getX() == -10.0 && v.getY() == 10.0 ) ? true : false;

	CPPUNIT_ASSERT( r );
}

void Vec2DTest::reflectTest( void )
{
	Vec2D v = Vec2D( 10, 10 );
	v.reflect( Vec2D( 1, 1 ) );

	bool r = ( v.getX() == 30.0 && v.getY() == 30.0 ) ? true : false;

	CPPUNIT_ASSERT( r );
}

void Vec2DTest::recuprocalTest( void )
{
	Vec2D v = Vec2D( 10, 10 );
	v.reciprocal();

	bool r = ( v.getX() == 0.1 && v.getY() == 0.1 ) ? true : false;

	CPPUNIT_ASSERT( r );
}

void Vec2DTest::roundToTest( void )
{
	Vec2D v = Vec2D( 10, 10 );
	v.roundTo( 13.0 );

	bool r = ( v.getX() == 13.0 && v.getY() == 13.0 ) ? true : false;

	CPPUNIT_ASSERT( r );
}

void Vec2DTest::rotateTest( void )
{
	Vec2D v = Vec2D( 10, 10 );
	v.rotate( 1.1 );

	bool r = ( v.getX() <= 4.4 && v.getX() <= -4.2 && v.getY() >= 13.4 && v.getY() <= 13.5 ) ? true : false;

	CPPUNIT_ASSERT( r );
}


