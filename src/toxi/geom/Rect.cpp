#include "Rect.h"
#include "Polygon2D.h"
#include "Line2D.h"
#include "VecMathUtil.h"
#include "../math/MathUtils.h"
#include <sstream>

toxi::geom::Rect::Rect(void)
{
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

toxi::geom::Rect::Rect( const float & x, const float & y, const float & w, const float & h )
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
}

toxi::geom::Rect::Rect( const double & x, const double & y, const double & w, const double & h )
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
}

toxi::geom::Rect::Rect( Vec2D & p1, Vec2D & p2, const CreationType & type )
{
	switch( type ) 
	{
	case NORMAL:
		{
			Vec2D tl = toxi::geom::Vec2D::min( p1, p2 );
			Vec2D br = toxi::geom::Vec2D::max( p1, p2 );
			this->x = tl.getX();
			this->y = tl.getY();
			this->width = br.getX() - x;
			this->height = br.getY() - y;
		}
		break;
	case CENTER:
		{
			Vec2D _p1 = p1.sub( p2 );
			Vec2D _p2 = p1.add( p2 );
			Vec2D tl = toxi::geom::Vec2D::min(_p1, _p2);
			Vec2D br = toxi::geom::Vec2D::max(_p1, _p2);
			this->x = tl.getX();
			this->y = tl.getY();
			this->width = br.getX() - x;
			this->height = br.getY() - y;
		}
		break;
	default:
		break;
	}
}

toxi::geom::Rect::Rect(const Rect & toCopy )
{
	this->x = toCopy.x;
	this->y = toCopy.y;
	this->width = toCopy.width;
	this->height = toCopy.height;
}


toxi::geom::Rect::~Rect(void)
{
}

bool toxi::geom::Rect::containsPoint( toxi::geom::Vec2D & p )
{
	double px = p.getX();
	double py = p.getY();
	if (px < x || px >= x + width) {
		return false;
	}
	if (py < y || py >= y + height) {
		return false;
	}
	return true;
}

float toxi::geom::Rect::getArea()
{
	return static_cast< float > ( width * height);
}

toxi::geom::Circle toxi::geom::Rect::getBoundingCircle()
{
	return toxi::geom::Circle( getCentroid(), static_cast< float > ( Vec2D( width, height).magnitude() / 2 ) );
}

toxi::geom::Rect toxi::geom::Rect::getBounds()
{
	return *this;
}

float toxi::geom::Rect::getCircumference()
{
	return static_cast< float > ( 2 * width + 2 * height );
}

toxi::geom::Vec2D toxi::geom::Rect::getRandomPoint()
{
	return Vec2D( toxi::math::MathUtils::random( x, x + width ), toxi::math::MathUtils::random( y, y + height ) );
}

toxi::geom::Polygon2D toxi::geom::Rect::toPolygon2D()
{
	Polygon2D poly = Polygon2D();
	poly.add(Vec2D(x, y));
	poly.add(Vec2D(x + width, y));
	poly.add(Vec2D(x + width, y + height));
	poly.add(Vec2D(x, y + height));
	return poly;
}

toxi::geom::Polygon2D toxi::geom::Rect::toPolygon2D( const float & radius, const int & res )
{
	Polygon2D poly = Polygon2D();
	toPolyArc(poly, Vec2D(x + width - radius, y + radius), radius,
		-toxi::math::MathUtils::HALF_PI, res);
	toPolyArc(poly, Vec2D(x + width - radius, y + height - radius),
		radius, 0, res);
	toPolyArc(poly, Vec2D(x + radius, y + height - radius), radius,
		toxi::math::MathUtils::HALF_PI, res);
	toPolyArc(poly, Vec2D(x + radius, y + radius), radius,
		toxi::math::MathUtils::PI, res);
	return poly;
}

float toxi::geom::Rect::getAspect()
{
	return static_cast< float > ( width / height) ;
}

std::string toxi::geom::Rect::toString()
{
	std::stringstream ss;
	ss << "rect: {x:" << x << ", y:" << y << ", width:" << width << ", height:" << height << "}";
	return ss.str();
}

float toxi::geom::Rect::getBottom()
{
	return static_cast< float > ( y + height) ;
}

float toxi::geom::Rect::getLeft()
{
	return static_cast< float > ( x );
}

float toxi::geom::Rect::getRight()
{
	return static_cast< float> ( x + width) ;
}

float toxi::geom::Rect::getTop()
{
	return static_cast< float > ( y );
}

toxi::geom::Vec2D toxi::geom::Rect::getMappedPointInRect( const Vec2D & p )
{
	return Vec2D( ( p.getX() - x ) / width, ( p.getY() - y ) / height );
}

toxi::geom::Vec2D toxi::geom::Rect::getBottomLeft()
{
	return Vec2D(x, y + height);
}

toxi::geom::Vec2D toxi::geom::Rect::getBottomRight()
{
	return Vec2D(x + width, y + height);
}

toxi::geom::Vec2D toxi::geom::Rect::getTopLeft()
{
	return Vec2D( x, y );
}

toxi::geom::Vec2D toxi::geom::Rect::getTopRight()
{
	return Vec2D( x + width, y );
}

toxi::geom::Vec2D toxi::geom::Rect::getCentroid()
{
	return Vec2D(x + width * 0.5f, y + height * 0.5f);
}

toxi::geom::Vec2D toxi::geom::Rect::getDimensions()
{
	return Vec2D(width, height);
}

toxi::geom::Line2D toxi::geom::Rect::getEdge( const EdgeType & edgeType )
{
	Line2D edge;
	switch( edgeType )
	{
	case TOP:
		edge = Line2D(x, y, x + width, y);
		break;
	case RIGHT:
		edge = Line2D(x + width, y, x + width, y + height);
		break;
	case BOTTOM:
		edge = Line2D(x, y + height, x + width, y + height);
		break;
	case LEFT:
		edge = Line2D(x, y, x, y + height);
		break;
	}
	return edge;
}

toxi::geom::Rect toxi::geom::Rect::growToContainPoint( Vec2D & p )
{
	if (!containsPoint( p )) {
		if (p.getX() < x) {
			width = getRight() - p.getX();
			x = p.getX();
		} else if (p.getX() > getRight()) {
			width = p.getX() - x;
		}
		if (p.getY() < y) {
			height = getBottom() - p.getY();
			y = p.getY();
		} else if (p.getY() > getBottom()) {
			height = p.getY() - y;
		}
	}
	return *this;
}

int toxi::geom::Rect::hashCode()
{
	long bits = 1L;
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits( static_cast< float > ( x ) );
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits( static_cast< float > ( y ) );
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits( static_cast< float > ( width ) );
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits( static_cast< float > ( height ) );
	return (int) (bits ^ (bits >> 1));
}

toxi::geom::Rect toxi::geom::Rect::intersectionRectWith( Rect & r )
{
	Rect isec;
	if (intersectsRect(r)) {
		double x1 = toxi::math::MathUtils::max(x, r.x);
		double y1 = toxi::math::MathUtils::max(y, r.y);
		double x2 = toxi::math::MathUtils::min(getRight(), r.getRight());
		double y2 = toxi::math::MathUtils::min(getBottom(), r.getBottom());
		isec = Rect(x1, y1, x2 - x1, y2 - y1);
	}
	return isec;
}

/*
toxi::geom::Vec2D * toxi::geom::Rect::intersectsRay( toxi::geom::Ray2D * ray, float minDist, float maxDist )
{
	Vec2D invDir = ray->getDirection()->reciprocal();
	bool signDirX = invDir.x < 0;
	bool signDirY = invDir.y < 0;
	Vec2D min = getTopLeft();
	Vec2D max = getBottomRight();
	Vec2D bbox = signDirX ? max : min;
	float tmin = (bbox.x - ray->x) * invDir.x;
	bbox = signDirX ? min : max;
	float tmax = (bbox.x - ray->x) * invDir.x;
	bbox = signDirY ? max : min;
	float tymin = (bbox.y - ray->y) * invDir.y;
	bbox = signDirY ? min : max;
	float tymax = (bbox.y - ray->y) * invDir.y;
	if ((tmin > tymax) || (tymin > tmax)) {
		return nullptr;
	}
	if (tymin > tmin) {
		tmin = tymin;
	}
	if (tymax < tmax) {
		tmax = tymax;
	}
	if ((tmin < maxDist) && (tmax > minDist)) {
		return ray->getPointAtDistance(tmin);
	}
	return nullptr;
}
*/

bool toxi::geom::Rect::intersectsRect( Rect & r )
{
	return !(x > r.x + r.width || x + width < r.x || y > r.y + r.height || y
		+ height < r.y);
}

toxi::geom::Rect toxi::geom::Rect::scale( const float & s )
{
	Vec2D c = getCentroid();
	width *= s;
	height *= s;
	x = c.getX() - width * 0.5f;
	y = c.getY() - height * 0.5f;
	return *this;
}

toxi::geom::Rect toxi::geom::Rect::set( const float & x, const float & y, const float & w, const float & h )
{
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	return *this;
}

toxi::geom::Rect toxi::geom::Rect::set( const Rect & r )
{
	this->x = r.x;
	this->y = r.y;
	this->width = r.width;
	this->height = r.height;
	return *this;
}

toxi::geom::Rect toxi::geom::Rect::setDimension( const Vec2D & dim )
{
	this->width = dim.getX();
	this->height = dim.getY();
	return *this;
}

toxi::geom::Rect toxi::geom::Rect::setPosition( const Vec2D & pos )
{
	this->x = pos.getX();
	this->y = pos.getY();
	return *this;
}

toxi::geom::Rect toxi::geom::Rect::translate( const float & dx, const float & dy )
{
	this->x += dx;
	this->y += dy;
	return *this;
}

toxi::geom::Rect toxi::geom::Rect::translate( const Vec2D & offset )
{
	this->x += offset.getX();
	this->y += offset.getY();
	return *this;
}

toxi::geom::Rect toxi::geom::Rect::unionRectWith( const Rect & r )
{
	double x1 = toxi::math::MathUtils::min(x, r.x);
	double x2 = toxi::math::MathUtils::max(x + width, r.x + r.width);
	double w = x2 - x1;
	double y1 = toxi::math::MathUtils::min(y, r.y);
	double y2 = toxi::math::MathUtils::max(y + height, r.y + r.height);
	double h = y2 - y1;
	return Rect(x1, y1, w, h);
}

void toxi::geom::Rect::toPolyArc( Polygon2D & poly, Vec2D & o, const double & radius, const double & theta, const int & res )
{
	for (int i = 0; i <= res; i++) {
		poly.add( o.add(Vec2D(theta + i * toxi::math::MathUtils::HALF_PI / res)
			.scaleSelf( static_cast< float > ( radius  ) ) ) );
	}
}

toxi::geom::Rect toxi::geom::Rect::getBoundingRect( const std::vector< Vec2D > & vertices )
{
	Vec2D first = vertices.at(0);
	Rect bounds = toxi::geom::Rect(first.getX(), first.getY(), 0, 0);

	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		Vec2D v = *it;
		bounds.growToContainPoint( v );
	}

	return bounds;
}
