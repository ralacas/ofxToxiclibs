#include "Axis3D.h"
#include "Vec3D.h"

toxi::geom::Axis3D::Axis3D( )
{
	this->vector = new Vec3D( 0, 0, 0 );
}

toxi::geom::Axis3D::Axis3D( const toxi::geom::Vec3D & vec )
{
	this->vector = new Vec3D( vec );
}


toxi::geom::Axis3D::~Axis3D(void)
{
	delete vector;
}

toxi::geom::Vec3D toxi::geom::Axis3D::getVector( void )
{
	return *vector;
}

toxi::geom::Axis3D toxi::geom::Axis3D::Z_AXIS()
{
	return Axis3D( Vec3D( 0, 0, 1 ) );
}

toxi::geom::Axis3D toxi::geom::Axis3D::Y_AXIS()
{
	return Axis3D( Vec3D( 0, 1, 0 ) );
}

toxi::geom::Axis3D toxi::geom::Axis3D::X_AXIS()
{
	return Axis3D( Vec3D( 1, 0, 0 ) );
}
