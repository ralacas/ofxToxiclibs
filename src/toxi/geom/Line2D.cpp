#include "Line2D.h"


toxi::geom::Line2D::Line2D(void)
{
}

toxi::geom::Line2D::Line2D(float x1, float y1, float x2, float y2)
{
	this->a = new toxi::geom::Vec2D( x1, y1 );
	this->b = new toxi::geom::Vec2D( x2, y2 );
}

toxi::geom::Line2D::Line2D( Vec2D * v1, Vec2D * v2 )
{
	this->a = v1;
	this->b = v2;
}

toxi::geom::Line2D::~Line2D(void)
{
}

toxi::geom::Vec2D * toxi::geom::Line2D::closestPointTo( toxi::geom::Vec2D p )
{
	toxi::geom::Vec2D v = b->sub( *a );
	float t = p.sub( *a ).dot( v ) / v.magSquared();
	if( t < 0.0 )
	{
		return new toxi::geom::Vec2D( *a );
	}
	else if( t > 1.0 )
	{
		return new toxi::geom::Vec2D( *b );
	}

	return &a->add( v.scaleSelf( t ) );
}
