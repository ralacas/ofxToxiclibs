#include "Ray2D.h"


toxi::geom::Ray2D::Ray2D(void)
{
}


toxi::geom::Ray2D::~Ray2D(void)
{
}

toxi::geom::Vec2D toxi::geom::Ray2D::getPointAtDistance( const float & tmin )
{
	return toxi::geom::Vec2D( 0.0, 0.0);
}

toxi::geom::Vec2D toxi::geom::Ray2D::getDirection()
{
	return toxi::geom::Vec2D( 0.0, 0.0);
}
