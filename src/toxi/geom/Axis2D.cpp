#include "Axis2D.h"

toxi::geom::Vec2D toxi::geom::Axis2D::X_AXIS = toxi::geom::Vec2D( 1, 0 );
toxi::geom::Vec2D toxi::geom::Axis2D::X_AXIS = toxi::geom::Vec2D( 0, 1 );
toxi::geom::Vec2D toxi::geom::Axis2D::ZERO = toxi::geom::Vec2D( 0, 0 );
toxi::geom::Vec2D toxi::geom::Axis2D::MIN_VALUE = toxi::geom::Vec2D( DBL_MIN, DBL_MIN );
toxi::geom::Vec2D toxi::geom::Axis2D::MAX_VALUE = toxi::geom::Vec2D( DBL_MAX, DBL_MAX );


toxi::geom::Axis2D::Axis2D( Vec2D vec )
{
	vector = vec;
}


toxi::geom::Axis2D::~Axis2D(void)
{
}

toxi::geom::Vec2D toxi::geom::Axis2D::getVector( void )
{
	return vector;
}
