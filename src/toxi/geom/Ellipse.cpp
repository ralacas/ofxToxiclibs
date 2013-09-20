#include "Ellipse.h"
#include "Rect.h"
#include "Circle.h"
#include "Polygon2D.h"

int toxi::geom::Ellipse::DEFAULT_RES = 10;


toxi::geom::Ellipse::Ellipse(void)
{

}

toxi::geom::Ellipse::Ellipse(float rx, float ry )
{
}

toxi::geom::Ellipse::Ellipse(float x, float y, float r )
{
}

toxi::geom::Ellipse::Ellipse(float x, float y, float rx, float ry )
{
	//Shape2D::
}

toxi::geom::Ellipse::Ellipse( toxi::geom::Vec2D * v, float r )
{
}

toxi::geom::Ellipse::Ellipse( toxi::geom::Vec2D * v, toxi::geom::Vec2D * r )
{
}


toxi::geom::Ellipse::~Ellipse(void)
{
	delete radius;
}

bool toxi::geom::Ellipse::containsPoint( toxi::geom::Vec2D * p )
{
	std::vector< Vec2D * > foci = getFoci();
	return p->distanceTo( foci[ 0 ] ) + p->distanceTo(  foci[ 1 ] ) < 2 * toxi::math::MathUtils::max( radius->getX(), radius->getY() );
}

float toxi::geom::Ellipse::getArea()
{
	return toxi::math::MathUtils::PI * radius->getX() * radius->getY();
}

toxi::geom::Circle * toxi::geom::Ellipse::getBoundingCircle()
{
	return new toxi::geom::Circle( getX(), getY(), toxi::math::MathUtils::max( radius->getX(), radius->getY() ) );
}

toxi::geom::Rect * toxi::geom::Ellipse::getBounds()
{
	return new toxi::geom::Rect( *toxi::geom::Vec2D::sub( radius ), *toxi::geom::Vec2D::add( radius ), Rect::NORMAL );
}

float toxi::geom::Ellipse::getCircumference()
{
	return ( float ) toxi::math::MathUtils::sqrt( 0.5 * radius->magSquared() ) * toxi::math::MathUtils::TWO_PI;
}

std::vector< toxi::geom::Vec2D * > toxi::geom::Ellipse::getFoci()
{
	std::vector< Vec2D * > foci;
	if( radius->getX() > radius->getY() )
	{
		foci.push_back( sub( focus, 0 ) );
		foci.push_back( add( focus, 0 ) );
	}
	else
	{
		foci.push_back( sub( 0, focus ) );
		foci.push_back( add( 0, focus ) );
	}
	return foci;
}

toxi::geom::Vec2D * toxi::geom::Ellipse::getRadii()
{
	return radius;
}

toxi::geom::Vec2D * toxi::geom::Ellipse::getRandomPoint()
{
	float theta = toxi::math::MathUtils::random( toxi::math::MathUtils::TWO_PI );
	toxi::util::datatypes::BiasedFloatRange * rnd = new toxi::util::datatypes::BiasedFloatRange(0.0, 1.0, 1.0, toxi::math::MathUtils::SQRT2);
	return toxi::geom::Vec2D(theta).scaleSelf( radius->scale(rnd->pickRandom()) )
		->addSelf( this->getX(), this->getY());
}

toxi::geom::Ellipse * toxi::geom::Ellipse::setRadii( float rx, float ry )
{
	radius->set( rx, ry );
	focus = radius->magnitude();
	return this;
}

toxi::geom::Ellipse * toxi::geom::Ellipse::setRadii( toxi::geom::Vec2D * v )
{
	return setRadii( v->getX(), v->getY() );
}

toxi::geom::Polygon2D * toxi::geom::Ellipse::toPolygon2D()
{
	return toPolygon2D( this->DEFAULT_RES );
}

toxi::geom::Polygon2D * toxi::geom::Ellipse::toPolygon2D( int res )
{
	Polygon2D * poly = new Polygon2D();
	float step = toxi::math::MathUtils::TWO_PI / res;
	for (int i = 0; i < res; i++) {
		poly->add( *Vec2D(i * step).scaleSelf( radius)->addSelf( this->getX(), this->getY()) );
	}
	return poly;
}
