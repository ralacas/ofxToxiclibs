#include "Axis3D.h"

toxi::geom::Vec3D * toxi::geom::Axis3D::X_AXIS( (1, 0, 0 ) );// = toxi::geom::Vec3D( 1, 0, 0 );
toxi::geom::Vec3D * toxi::geom::Axis3D::Y_AXIS( ( 0, 1, 0 ) );// = toxi::geom::Vec3D( 0, 1, 0);
toxi::geom::Vec3D * toxi::geom::Axis3D::Z_AXIS( ( 0, 0, 1 ) );// = toxi::geom::Vec3D( 0, 0, 1);
toxi::geom::Vec3D * toxi::geom::Axis3D::ZERO( ( 0, 0, 0 ) );// = toxi::geom::Vec3D( 0, 0, 0);
toxi::geom::Vec3D * toxi::geom::Axis3D::MIN_VALUE( ( DBL_MIN, DBL_MIN, DBL_MIN ) );// = toxi::geom::Vec3D( DBL_MIN, DBL_MIN, DBL_MIN );
toxi::geom::Vec3D * toxi::geom::Axis3D::MAX_VALUE( ( DBL_MAX, DBL_MAX, DBL_MAX ) );// = toxi::geom::Vec3D( DBL_MAX, DBL_MAX, DBL_MAX );

toxi::geom::Axis3D::Axis3D( toxi::geom::Vec3D * vec )
{
	vector = vec;
}


toxi::geom::Axis3D::~Axis3D(void)
{
}

toxi::geom::Vec3D * toxi::geom::Axis3D::getVector( void )
{
	return vector;
}

toxi::geom::Axis3D * toxi::geom::Axis3D::Z_AXIS()
{
	return new Axis3D(new Vec3D( 0, 0, 1 ) );
}

toxi::geom::Axis3D * toxi::geom::Axis3D::Y_AXIS()
{
	return new Axis3D(new Vec3D( 0, 1, 0 ) );
}

toxi::geom::Axis3D * toxi::geom::Axis3D::X_AXIS()
{
	return new Axis3D(new Vec3D( 1, 0, 0 ) );
}
