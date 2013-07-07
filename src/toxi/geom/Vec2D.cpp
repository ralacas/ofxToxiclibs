#include "Vec2D.h"


toxi::geom::Vec2D::Vec2D( double _x, double _y )
{
	this->x = _x;
	this->y = _y;
}


toxi::geom::Vec2D::~Vec2D(void)
{
}

float toxi::geom::Vec2D::angleBetween( Vec2D v )
{
	return (float) std::acos(dot(v));
}

float toxi::geom::Vec2D::angleBetween( Vec2D v, bool forceNormalize )
{
	double theta;
	if (forceNormalize) {
		theta = getNormalized().dot(v.getNormalized());
	} else {
		theta = dot(v);
	}
	return (float) std::acos(toxi::math::MathUtils::clipNormalized(theta));
}

toxi::geom::Vec2D toxi::geom::Vec2D::add( float _x, float _y )
{
	Vec2D v = Vec2D( _x, _y );
	return v;
}

toxi::geom::Vec2D toxi::geom::Vec2D::add( Vec2D v )
{
	Vec2D v = Vec2D( v.x, v.y );
	return v;
}

toxi::geom::Vec3D toxi::geom::Vec2D::bisect( Vec2D b )
{
	Vec2D diff = this->sub(b);
	Vec2D sum = this->add(b);
	float dot = diff.dot(sum);
	return Vec3D(diff.x, diff.y, -dot / 2)
}

int toxi::geom::Vec2D::compareTo( Vec2D v )
{
	if (x == v.x && y == v.y) {
		return 0;
	}
	float a = magSquared();
	float b = v.magSquared();
	if (a < b) {
		return -1;
	}
	return +1;
}

float toxi::geom::Vec2D::cross( Vec2D v )
{
	return (x * v.y) - (y * v.x);
}

float toxi::geom::Vec2D::distanceTo( Vec2D v )
{
	float dx = x - v.x;
	float dy = y - v.y;
	return (float) std::sqrt(dx * dx + dy * dy);
}

float toxi::geom::Vec2D::distanceToSquared( Vec2D v )
{
	float dx = x - v.x;
	float dy = y - v.y;
	return dx * dx + dy * dy;
}

float toxi::geom::Vec2D::dot( Vec2D v )
{
	return x * v.x + y * v.y;
}

bool toxi::geom::Vec2D::equals( Vec2D v )
{
	return v.x == this->x && v.y == this->y;
}

bool toxi::geom::Vec2D::equalsWithTolerance( Vec2D v, float tolerance )
{
	float diff = x - v.x;
	if (toxi::math::MathUtils::isNan( diff )) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	diff = y - v.y;
	if (toxi::math::MathUtils::isNan(diff)) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	return true;
}

toxi::geom::Vec2D toxi::geom::Vec2D::getCartesian()
{
	Vec2D v = Vec2D( 0, 0 );
	float xx = (float) (x * std::cos(y));
	v.y = (float) (x *std::sin(y));
	v.x = xx;
	return v;
}

float toxi::geom::Vec2D::getComponent( int id )
{
	switch (id) {
	case 0:
		return x;
	case 1:
		return y;
	}
}
