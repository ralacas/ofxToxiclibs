#include "Circle.h"


toxi::geom::Circle::Circle(void)
{

}

toxi::geom::Circle::Circle( float radius )
{

}

toxi::geom::Circle::Circle( Vec2D * origin, float radius )
{

}

toxi::geom::Circle::Circle( float x, float y, float r )
{

}

toxi::geom::Circle::~Circle(void)
{
}

toxi::geom::Circle * toxi::geom::Circle::newBoundingCircle( std::vector< Vec2D > * vertices )
{
	Vec2D origin = Vec2D();
	float maxD = 0;
	for (Vec2D v : *vertices) {
		origin.addSelf( &v );
	}
	origin.scaleSelf(1 / vertices->size());
	for (Vec2D v : *vertices) {
		float d = origin.distanceToSquared( &v);
		if (d > maxD) {
			maxD = d;
		}
	}
	return new Circle( &origin, (float) toxi::math::MathUtils::sqrt(maxD));
}
