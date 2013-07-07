#include "Axis2D.h"

toxi::geom::ReadonlyVec2D toxi::geom::Axis2D::X_AXIS = toxi::geom::ReadonlyVec2D::create( 1, 0 );
toxi::geom::ReadonlyVec2D toxi::geom::Axis2D::X_AXIS = toxi::geom::ReadonlyVec2D::create( 0, 1 );
toxi::geom::ReadonlyVec2D toxi::geom::Axis2D::ZERO = toxi::geom::ReadonlyVec2D::create( 0, 0 );
toxi::geom::ReadonlyVec2D toxi::geom::Axis2D::MIN_VALUE = toxi::geom::ReadonlyVec2D::create( DBL_MIN, DBL_MIN );
toxi::geom::ReadonlyVec2D toxi::geom::Axis2D::MAX_VALUE = toxi::geom::ReadonlyVec2D::create( DBL_MAX, DBL_MAX );


toxi::geom::Axis2D::Axis2D( ReadonlyVec2D vec )
{
	vector = vec;
}


toxi::geom::Axis2D::~Axis2D(void)
{
}

toxi::geom::ReadonlyVec2D toxi::geom::Axis2D::getVector( void )
{
	return vector;
}
