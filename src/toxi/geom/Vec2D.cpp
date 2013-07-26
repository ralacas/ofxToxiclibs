#include "Vec2D.h"


toxi::geom::Vec2D::Vec2D( double _x, double _y )
{
	this->x = _x;
	this->y = _y;
}


toxi::geom::Vec2D::~Vec2D(void)
{
}

double toxi::geom::Vec2D::angleBetween( Vec2D v )
{
	return (double) std::acos(dot(v));
}

double toxi::geom::Vec2D::angleBetween( Vec2D v, bool forceNormalize )
{
	double theta;
	if (forceNormalize) {
		theta = getNormalized().dot(v.getNormalized());
	} else {
		theta = dot(v);
	}
	return (double) std::acos(toxi::math::MathUtils::clipNormalized(theta));
}

toxi::geom::Vec2D toxi::geom::Vec2D::add( double _x, double _y )
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
	double dot = diff.dot(sum);
	return Vec3D(diff.x, diff.y, -dot / 2)
}

int toxi::geom::Vec2D::compareTo( Vec2D v )
{
	if (x == v.x && y == v.y) {
		return 0;
	}
	double a = magSquared();
	double b = v.magSquared();
	if (a < b) {
		return -1;
	}
	return +1;
}

double toxi::geom::Vec2D::cross( Vec2D v )
{
	return (x * v.y) - (y * v.x);
}

double toxi::geom::Vec2D::distanceTo( Vec2D v )
{
	double dx = x - v.x;
	double dy = y - v.y;
	return (double) std::sqrt(dx * dx + dy * dy);
}

double toxi::geom::Vec2D::distanceToSquared( Vec2D v )
{
	double dx = x - v.x;
	double dy = y - v.y;
	return dx * dx + dy * dy;
}

double toxi::geom::Vec2D::dot( Vec2D v )
{
	return x * v.x + y * v.y;
}

bool toxi::geom::Vec2D::equals( Vec2D v )
{
	return v.x == this->x && v.y == this->y;
}

bool toxi::geom::Vec2D::equalsWithTolerance( Vec2D v, double tolerance )
{
	double diff = x - v.x;
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
	double xx = (double) (x * std::cos(y));
	v.y = (double) (x *std::sin(y));
	v.x = xx;
	return v;
}

double toxi::geom::Vec2D::getComponent( int id )
{
	switch (id) {
	case 0:
		return x;
	case 1:
		return y;
	}
}

toxi::geom::Vec2D toxi::geom::Vec2D::constrain( Rect r )
{
	Vec2D v = Vec2D( 0, 0 );
	v.x = toxi::math::MathUtils::clip( x, r.x, r.x + r.width );
	v.y = toxi::math::MathUtils::clip( y, r.y, r.y + r.height );
	return v;
}

toxi::geom::Vec2D toxi::geom::Vec2D::floor( void )
{
	Vec2D v = Vec2D(0, 0);
	v.x = toxi::math::MathUtils::floor( x );
	v.y = toxi::math::MathUtils::floor( y );
	return v;
}

toxi::geom::Vec2D toxi::geom::Vec2D::getFloored()
{
	return this->floor();
}

toxi::geom::Vec2D toxi::geom::Vec2D::getFrac()
{
	return this->frac();
}

toxi::geom::Vec2D toxi::geom::Vec2D::frac()
{
	Vec2D v = Vec2D( x, y );
	v.x -= toxi::math::MathUtils::floor( x );
	v.y -= toxi::math::MathUtils::floor( y );
}


toxi::geom::Vec2D toxi::geom::Vec2D::getInverted()
{
	return Vec2D( -x, -y );
}

toxi::geom::Vec2D toxi::geom::Vec2D::getLimited( double lim )
{
	if ( magSquared() > lim * lim ) {
		return getNormalizedTo( lim );
	}
	return Vec2D( x, y );
}

toxi::geom::Vec2D toxi::geom::Vec2D::getMapped( toxi::math::ScaleMap map )
{
	return Vec2D( map.getClippedValueFor( x ), map.getClippedValueFor( y ) );
}

toxi::geom::Vec2D toxi::geom::Vec2D::getNormalized()
{
	return normalize();
}

toxi::geom::Vec2D toxi::geom::Vec2D::getNormalizedTo( double len )
{
	Vec2D v = Vec2D( x, y );
	double mag = (double) toxi::math::MathUtils::sqrt( x * x + y * y );
	if (mag > 0) {
		mag = len / mag;
		v.x *= mag;
		v.y *= mag;
	}
	return v;
}

toxi::geom::Vec2D toxi::geom::Vec2D::normalize()
{
	double mag = x * x + y * y;
	if (mag > 0) {
		mag = 1.0 / toxi::math::MathUtils::sqrt( mag );
		this->x *= mag;
		this->y *= mag;
	}
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::getPerpendicular()
{
	double t = this->x;
	this->x = -y;
	this->y = t;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::toPolar()
{
	double r = toxi::math::MathUtils::sqrt( x * x + y * y );
	y = std::atan2( y, x );
	x = r;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::reciprocal()
{
	x = 1.0 / x;
	y = 1.0 / y;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::reflect( Vec2D normal )
{
		return set(normal.scale(dot(normal) * 2).subSelf(this));
}

toxi::geom::Vec2D toxi::geom::Vec2D::getReflected( Vec2D normal )
{
	Vec2D v = Vec2D( x, y );
	return v.reflect();
}

toxi::geom::Vec2D toxi::geom::Vec2D::rotate( double theta )
{
	double co = std::cos( theta );
	double si = std::sin(theta);
	double xx = co * x - si * y;
	y = si * x + co * y;
	x = xx;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::getRotated( double theta )
{
	Vec2D v = Vec2D( x, y );
	return v.rotate( theta );
}

toxi::geom::Vec2D toxi::geom::Vec2D::roundTo( double prec )
{
	x = toxi::math::MathUtils::roundTo(x, prec);
	y = toxi::math::MathUtils::roundTo(y, prec);
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::getRoundedTo( double prec )
{
	Vec2D v = Vec2D( x, y );
	return v.roundTo( prec );
}

toxi::geom::Vec2D toxi::geom::Vec2D::signum()
{
	x = (x < 0 ? -1 : x == 0 ? 0 : 1);
	y = (y < 0 ? -1 : y == 0 ? 0 : 1);
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::getSignum()
{
	Vec2D v = Vec2D( x, y );
	return v.signum();
}

toxi::geom::Vec2D toxi::geom::Vec2D::subSelf( double a, double b )
{
	x -= a;
	y -= b;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::subSelf( Vec2D *v )
{
	x -= v->x;
	y -= v->y;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::set( double x, double y )
{
	this->x = x;
	this->y = y;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::set( Vec2D v )
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}

double toxi::geom::Vec2D::heading()
{
	return std::atan2(y, x);
}

toxi::geom::Vec2D toxi::geom::Vec2D::interpolateTo( Vec2D v, double f )
{
	Vec2D vr = Vec2D( x + (v.x - x) * f, y + (v.y - y) * f );
	return vr;
}

toxi::geom::Vec2D toxi::geom::Vec2D::interpolateTo( Vec2D v, double f, toxi::math::InterpolateStrategy s )
{
	Vec2D vr = Vec2D( s.interpolate(x, v.x, f), s.interpolate(y, v.y, f) );
	return vr;
}

bool toxi::geom::Vec2D::isInCircle( Vec2D sO, double sR )
{
	float d = sub( sO ).magSquared();
	return ( d <= sR * sR );
}

bool toxi::geom::Vec2D::isInRectangle( Rect r )
{
	if ( x < r.x || x > r.x + r.width ) {
		return false;
	}
	if ( y < r.y || y > r.y + r.height ) {
		return false;
	}
	return true;
}

bool toxi::geom::Vec2D::isInTriangle( Vec2D a, Vec2D b, Vec2D c )
{
	Vec2D v1 = sub(a).normalize();
	Vec2D v2 = sub(b).normalize();
	Vec2D v3 = sub(c).normalize();

	double total_angles = std::acos(v1.dot(v2));
	total_angles += std::acos(v2.dot(v3));
	total_angles += std::acos(v3.dot(v1));

	return (toxi::math::MathUtils::abs( total_angles - toxi::math::MathUtils::TWO_PI) <= 0.005f);
}

bool toxi::geom::Vec2D::isMajorAxis( double tol )
{
	float ax = toxi::math::MathUtils::abs(x);
	float ay = toxi::math::MathUtils::abs(y);
	float itol = 1 - tol;
	if (ax > itol) {
		return (ay < tol);
	} else if (ay > itol) {
		return (ax < tol);
	}
	return false;
}

bool toxi::geom::Vec2D::isZeroVector()
{
	return toxi::math::MathUtils::abs(x) < toxi::math::MathUtils::EPS
		&& toxi::math::MathUtils::abs(y) < toxi::math::MathUtils::EPS;
}

double toxi::geom::Vec2D::magnitude()
{
	return std::sqrt(x * x + y * y);
}

double toxi::geom::Vec2D::magSquared()
{
	return x * x + y * y;
}

toxi::geom::Vec2D toxi::geom::Vec2D::max( Vec2D v )
{
	return Vec2D( toxi::math::MathUtils::max( x, v.x ), toxi::math::MathUtils::max( x, v.x ) );
}

toxi::geom::Vec2D toxi::geom::Vec2D::min( Vec2D v )
{
	return Vec2D( toxi::math::MathUtils::min( x, v.x ), toxi::math::MathUtils::min( x, v.x ) );
}

toxi::geom::Vec2D toxi::geom::Vec2D::scale( double s )
{
	return Vec2D(x * s, y * s);
}

toxi::geom::Vec2D toxi::geom::Vec2D::scale( double a, double b )
{
	return Vec2D(x * a, y * b);
}

toxi::geom::Vec2D toxi::geom::Vec2D::scale( Vec2D s )
{
	return Vec2D(x * s.x, y * s.y);
}

toxi::geom::Vec2D toxi::geom::Vec2D::sub( double a, double b )
{
	return Vec2D(x - a, y - b);
}

toxi::geom::Vec2D toxi::geom::Vec2D::sub( Vec2D v )
{
	return Vec2D(x - v.x, y - v.y);
}

toxi::geom::Vec2D toxi::geom::Vec2D::tangentNormalOfEllipse( Vec2D eO, Vec2D eR )
{
	Vec2D p = this->sub(eO);

	float xr2 = eR.x * eR.x;
	float yr2 = eR.y * eR.y;

	return Vec2D(p.x / xr2, p.y / yr2).normalize();
}

double* toxi::geom::Vec2D::toArray( double a )
{
	double arr[2] = { x, y };
	return arr;
}



