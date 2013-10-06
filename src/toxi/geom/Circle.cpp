#include "Circle.h"


toxi::geom::Circle::Circle(void)
{

}

toxi::geom::Circle::Circle( const float & radius )
{

}

toxi::geom::Circle::Circle( const Vec2D & origin, const float & radius )
{

}

toxi::geom::Circle::Circle( const float & x, const float & y, const float & r )
{

}

toxi::geom::Circle::~Circle(void)
{
}

toxi::geom::Circle toxi::geom::Circle::newBoundingCircle( const std::vector< Vec2D > & vertices )
{
	Vec2D origin = Vec2D();
	double maxD = 0;
	for (Vec2D v : vertices) {
		origin.addSelf( v );
	}
	origin.scaleSelf(1.0f / vertices.size());
	for (Vec2D v : vertices) {
		double d = origin.distanceToSquared( v );
		if (d > maxD) {
			maxD = d;
		}
	}
	return Circle( origin, (float) toxi::math::MathUtils::sqrt( maxD ) );
}
