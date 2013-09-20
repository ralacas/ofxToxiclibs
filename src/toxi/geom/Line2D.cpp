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
	toxi::geom::Vec2D * v = b->sub( a );
	float t = p.sub( a )->dot( v ) / v->magSquared();
	if( t < 0.0 )
	{
		return new toxi::geom::Vec2D( *a );
	}
	else if( t > 1.0 )
	{
		return new toxi::geom::Vec2D( *b );
	}

	return a->add( v->scaleSelf( t ) );
}

toxi::geom::LineIntersection * toxi::geom::Line2D::intersectLine( Line2D * l )
{
	LineIntersection * isec = nullptr;
	float denom = (l->b->getY() - l->a->getY()) * (b->getX() - a->getX()) - (l->b->getX() - l->a->getX())
		* ( b->getY() - a->getY() );

	float na = (l->b->getX() - l->a->getX()) * (a->getY() - l->a->getY()) - (l->b->getY() - l->a->getY())
		* (a->getX() - l->a->getX());
	float nb = (b->getX() - a->getX()) * (a->getY() - l->a->getY()) - (b->getY() - a->getY()) * (a->getX() - l->a->getX());

	if (denom != 0.0) {
		float ua = na / denom;
		float ub = nb / denom;
		Vec2D * i = a->interpolateTo(b, ua);
		if (ua >= 0.0f && ua <= 1.0 && ub >= 0.0 && ub <= 1.0) {
			isec = new LineIntersection(toxi::geom::LineIntersection::Type::INTERSECTING, *i, ua, ub);
		} else {
			isec = new LineIntersection(toxi::geom::LineIntersection::Type::NON_INTERSECTING, *i, ua, ub);
		}
	} else {
		if (na == 0.0 && nb == 0.0) {
			if (distanceToPoint(l->a) == 0.0) {
				isec = new LineIntersection(toxi::geom::LineIntersection::Type::COINCIDENT, nullptr);
			} else {
				isec = new LineIntersection(toxi::geom::LineIntersection::Type::COINCIDENT_NO_INTERSECT,
					nullptr);
			}
		} else {
			isec = new LineIntersection(toxi::geom::LineIntersection::Type::PARALLEL, nullptr);
		}
	}
	return isec;
}

std::string toxi::geom::Line2D::toString()
{
	std::stringstream ss;
	ss << a->toString() << " -> " << b->toString();
	return ss.str();
}

float toxi::geom::Line2D::getLength()
{
	return a->distanceTo( b );
}

float toxi::geom::Line2D::distanceToPoint( Vec2D * p )
{
	return closestPointTo( *p )->distanceTo( p );
}
