#include "Line2D.h"


toxi::geom::Line2D::Line2D(void)
{
}

toxi::geom::Line2D::Line2D(float x1, float y1, float x2, float y2)
{
	this->a = new toxi::geom::Vec2D( x1, y1 );
	this->b = new toxi::geom::Vec2D( x2, y2 );
}
toxi::geom::Line2D::~Line2D(void)
{
}
