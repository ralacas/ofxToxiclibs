#include "Ellipse.h"
#include "Rect.h"
#include "Circle.h"
#include "Polygon2D.h"

int toxi::geom::Ellipse::DEFAULT_RES = 10;


toxi::geom::Ellipse::Ellipse(void)
{

}

toxi::geom::Ellipse::Ellipse(const float & rx, const float & ry )
{
}

toxi::geom::Ellipse::Ellipse(const float & x, const float & y, const float & r )
{
}

toxi::geom::Ellipse::Ellipse(const float & x, const float & y, const float & rx, const float & ry )
{
	
}

toxi::geom::Ellipse::Ellipse( const toxi::geom::Vec2D & v, const float & r )
{
}

toxi::geom::Ellipse::Ellipse( const toxi::geom::Vec2D & v, const toxi::geom::Vec2D & r )
{
}


toxi::geom::Ellipse::~Ellipse(void)
{
}

bool toxi::geom::Ellipse::containsPoint( toxi::geom::Vec2D & p )
{
	std::vector< Vec2D > foci = getFoci();
	return p.distanceTo( foci[ 0 ] ) + p.distanceTo(  foci[ 1 ] ) < 2 * toxi::math::MathUtils::max( radius.getX(), radius.getY() );
}

float toxi::geom::Ellipse::getArea()
{
	return static_cast< float > ( toxi::math::MathUtils::PI * radius.getX() * radius.getY() );
}

toxi::geom::Circle toxi::geom::Ellipse::getBoundingCircle()
{
	return toxi::geom::Circle( static_cast< float > ( getX() ), static_cast< float > ( getY() ), static_cast< float > ( toxi::math::MathUtils::max( radius.getX(), radius.getY() ) ) );
}

toxi::geom::Rect toxi::geom::Ellipse::getBounds()
{
	return toxi::geom::Rect( toxi::geom::Vec2D::getSub( radius ), toxi::geom::Vec2D::add( radius ), Rect::NORMAL );
}

float toxi::geom::Ellipse::getCircumference()
{
	return static_cast< float > ( toxi::math::MathUtils::sqrt( 0.5 * radius.magSquared() ) * toxi::math::MathUtils::TWO_PI );
}

std::vector< toxi::geom::Vec2D > toxi::geom::Ellipse::getFoci()
{
	std::vector< Vec2D > foci;
	if( radius.getX() > radius.getY() )
	{
		foci.push_back( getSub( focus, 0 ) );
		foci.push_back( add( focus, 0 ) );
	}
	else
	{
		foci.push_back( getSub( 0, focus ) );
		foci.push_back( add( 0, focus ) );
	}
	return foci;
}

toxi::geom::Vec2D toxi::geom::Ellipse::getRadii()
{
	return radius;
}

toxi::geom::Vec2D toxi::geom::Ellipse::getRandomPoint()
{
	double theta = toxi::math::MathUtils::random( toxi::math::MathUtils::TWO_PI );
	toxi::util::datatypes::BiasedFloatRange * rnd = new toxi::util::datatypes::BiasedFloatRange(0.0F, 1.0F, 1.0F, static_cast< float > ( toxi::math::MathUtils::SQRT2 ) );
	return toxi::geom::Vec2D(theta).scaleSelf( radius.getScaled(rnd->pickRandom()) )
		.addSelf( this->getX(), this->getY());
}

toxi::geom::Ellipse toxi::geom::Ellipse::setRadii( const float & rx, const float & ry )
{
	radius.set( rx, ry );
 	focus = static_cast< float > ( radius.magnitude() );
	return *this;
}

toxi::geom::Ellipse toxi::geom::Ellipse::setRadii( toxi::geom::Vec2D & v )
{
	return setRadii( static_cast< float > ( v.getX() ), static_cast< float > ( v.getY() ) );
}

toxi::geom::Polygon2D toxi::geom::Ellipse::toPolygon2D()
{
	return toPolygon2D( this->DEFAULT_RES );
}

toxi::geom::Polygon2D toxi::geom::Ellipse::toPolygon2D( const int & res )
{
	Polygon2D poly = Polygon2D();
	double step = toxi::math::MathUtils::TWO_PI / res;
	for (int i = 0; i < res; i++) {
		poly.add( toxi::geom::Vec2D(i * step).scaleSelf( radius).addSelf( this->getX(), this->getY()) );
	}
	return poly;
}
