#include "Axis3D.h"

toxi::geom::Vec3D toxi::geom::Axis3D::X_AXIS = toxi::geom::Vec3D( 1, 0, 0 );
toxi::geom::Vec3D toxi::geom::Axis3D::Y_AXIS = toxi::geom::Vec3D( 0, 1, 0);
toxi::geom::Vec3D toxi::geom::Axis3D::Z_AXIS = toxi::geom::Vec3D( 0, 0, 1);
toxi::geom::Vec3D toxi::geom::Axis3D::ZERO = toxi::geom::Vec3D( 0, 0, 0);
toxi::geom::Vec3D toxi::geom::Axis3D::MIN_VALUE = toxi::geom::Vec3D( DBL_MIN, DBL_MIN, DBL_MIN );
toxi::geom::Vec3D toxi::geom::Axis3D::MAX_VALUE = toxi::geom::Vec3D( DBL_MAX, DBL_MAX, DBL_MAX );

toxi::geom::Axis3D::Axis3D(Vec3D vec)
{
	vector = vec;
}


toxi::geom::Axis3D::~Axis3D(void)
{
}

toxi::geom::Vec3D toxi::geom::Axis3D::getVector( void )
{
	return vector;
}
