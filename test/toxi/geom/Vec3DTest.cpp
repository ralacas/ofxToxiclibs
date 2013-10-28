#include "Vec3DTest.h"
#include <toxi/geom/Vec3D.h>

using namespace toxi::geom;

void Vec3DTest::contructorTest( void )
{
	Vec3D v = Vec3D( 10, 20, 30 );
	Vec3D v2 = Vec3D( 10.0F, 20.0F, 30.0F );
	Vec3D v3 = Vec3D( 10.0, 20.0, 30.0 );
	Vec3D v4 = Vec3D( v );

	bool r1 = ( isRightAroundThis( v.getX(), 10 ), isRightAroundThis( v.getY(), 20 ), isRightAroundThis( v.getZ(), 30 ) ) ? true : false;
	bool r2 = ( isRightAroundThis( v2.getX(), 10 ), isRightAroundThis( v2.getY(), 20 ), isRightAroundThis( v2.getZ(), 30 ) ) ? true : false;
	bool r3 = ( isRightAroundThis( v3.getX(), 10 ), isRightAroundThis( v3.getY(), 20 ), isRightAroundThis( v3.getZ(), 30 ) ) ? true : false;
	bool r4 = ( isRightAroundThis( v4.getX(), 10 ), isRightAroundThis( v4.getY(), 20 ), isRightAroundThis( v4.getZ(), 30 ) ) ? true : false;

	CPPUNIT_ASSERT( r1 && r2 && r3 && r4 );
	
}

bool Vec3DTest::isRightAroundThis( double val, double goal )
{
	bool ret;

	if( val >= 0.0 ) 
	{
		ret = ( val >= (goal - 0.01) && val <= (goal += 0.01) ) ? true : false;
	}
	else 
	{
		ret = ( val >= (goal - 0.01) && val <= (goal += 0.01) ) ? true : false;
	}


	return ret;
}

void Vec3DTest::staticAxisTest( void )
{
	Vec3D x = toxi::geom::Vec3D::X_AXIS();
	Vec3D y = toxi::geom::Vec3D::Y_AXIS();
	Vec3D z = toxi::geom::Vec3D::Z_AXIS();

	Vec3D vx = Vec3D( 1, 0, 0 );
	Vec3D vy = Vec3D( 0, 1, 0 );
	Vec3D vz = Vec3D( 0, 0, 1 );

	bool r1 = ( x == vx && y == vy && z == vz ) ? true : false;

	CPPUNIT_ASSERT( r1 );
}

void Vec3DTest::equalsOperatorOverloadTest( void )
{
	Vec3D v1 = Vec3D( 10, 20, 10 );
	Vec3D v2 = Vec3D( 10, 20, 10 );

	bool r1 = ( v1 == v2 ) ? true : false;

	CPPUNIT_ASSERT( r1 );
}

void Vec3DTest::minMaxTest( void )
{
	Vec3D vMin = Vec3D( 10, 10, 10 );
	Vec3D vMax = Vec3D( 11, 9, 11 );

	Vec3D minResult = Vec3D( 10, 9, 10 );
	Vec3D min = toxi::geom::Vec3D::min( vMin, vMax );

	bool r1 = ( min == minResult ) ? true : false;

	Vec3D maxResult = Vec3D( 11, 10, 11 );
	Vec3D max = toxi::geom::Vec3D::max( vMin, vMax );

	bool r2 = ( max == maxResult ) ? true : false;

	CPPUNIT_ASSERT( r1 && r2 );
}

void Vec3DTest::minMaxValueTest( void )
{
	Vec3D vMin = Vec3D::min_value();
	Vec3D vMax = Vec3D::max_value();

	bool r1 = ( isRightAroundThis( vMin.getX(), DBL_MIN ), isRightAroundThis( vMin.getY(), DBL_MIN ), isRightAroundThis( vMin.getZ(), DBL_MIN ) ) ? true : false;
	bool r2 = ( isRightAroundThis( vMax.getX(), DBL_MAX ), isRightAroundThis( vMax.getY(), DBL_MAX ), isRightAroundThis( vMax.getZ(), DBL_MAX ) ) ? true : false;

	CPPUNIT_ASSERT( r1 && r2 );
}

void Vec3DTest::crossTest( void )
{
	Vec3D v = Vec3D( 8, 9, 10 );
	Vec3D vCopy = Vec3D( v );

	Vec3D v2 = Vec3D( 1, 2, 3 );
	Vec3D v2Copy = Vec3D( v2 );

	Vec3D crossResult = Vec3D( 7, -14, 7 );

	Vec3D vres = v.getCrossed( v2 );	
	bool r1 = ( crossResult == vres && v == vCopy && v2 == v2Copy ) ? true : false;

	std::cout << v << " " << v2 << " " << vres << std::endl;

	v.cross( v2 );
	bool r2 = ( v == crossResult ) ? true : false;

	std::cout << v << " " << v2 << " " << vres << std::endl;

	//std::cout << r2 << std::endl << v << std::endl;
	//std::cout << vres << std::endl;

	CPPUNIT_ASSERT( r1 && r2 );
}
