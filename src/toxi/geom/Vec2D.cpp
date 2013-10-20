#include "Vec2D.h"
#include "Vec3D.h"
#include "Rect.h"
#include "Line2D.h"
#include "Polygon2D.h"
#include "VecMathUtil.h"

toxi::geom::Vec2D toxi::geom::Vec2D::X_AXIS = toxi::geom::Vec2D( 1, 0 );
toxi::geom::Vec2D toxi::geom::Vec2D::Y_AXIS = toxi::geom::Vec2D( 0, 1 );
toxi::geom::Vec2D toxi::geom::Vec2D::ZERO = toxi::geom::Vec2D( 0, 0 );
toxi::geom::Vec2D toxi::geom::Vec2D::MIN_VALUE( FLT_MIN, FLT_MIN );
toxi::geom::Vec2D toxi::geom::Vec2D::MAX_VALUE( FLT_MAX, FLT_MAX );


toxi::geom::Vec2D::Vec2D( const double & _x, const double & _y )
{
	this->x = _x;
	this->y = _y;
}

toxi::geom::Vec2D::Vec2D( const double & theta )
{
	this->x = toxi::math::MathUtils::cos( theta );
	this->y = toxi::math::MathUtils::sin( theta );
}

toxi::geom::Vec2D::Vec2D( const Vec2D & v )
{
	this->x = v.x;
	this->y = v.y;
}

toxi::geom::Vec2D::Vec2D(  ) :
	x(0),
	y(0)
{
}

toxi::geom::Vec2D::~Vec2D(void)
{
}

double toxi::geom::Vec2D::angleBetween( Vec2D & v )
{
	return std::acos( dot( v ) );
}

double toxi::geom::Vec2D::angleBetween( Vec2D & v, const bool & forceNormalize )
{
	double theta;
	if (forceNormalize) {
		theta = getNormalized().dot(v.getNormalized());
	} else {
		theta = dot(v);
	}
	return (double) std::acos(toxi::math::MathUtils::clipNormalized(theta));
}

toxi::geom::Vec2D toxi::geom::Vec2D::add( const double & _x, const double & _y )
{
	Vec2D v = Vec2D( _x + getX(), _y + getY() );
	return v;
}

toxi::geom::Vec2D toxi::geom::Vec2D::add( Vec2D & v )
{
	Vec2D _v = Vec2D( v.x + getX(), v.y + getY() );
	return _v;
}

toxi::geom::Vec3D toxi::geom::Vec2D::bisect( Vec2D & b )
{
	Vec2D diff = this->sub( b );
	Vec2D sum = this->add( b );
	double dot = diff.dot( sum );
	return Vec3D( diff.getX(), diff.getY(), -dot / 2 );
}

double toxi::geom::Vec2D::cross( Vec2D & v )
{
	return ( getX() * v.getY() ) - ( getY() * v.getX() );
}

double toxi::geom::Vec2D::distanceTo( Vec2D & v )
{
	double dx = getX() - v.getX();
	double dy = getY() - v.getY();
	return std::sqrt(dx * dx + dy * dy);
}

double toxi::geom::Vec2D::distanceToSquared( Vec2D & v )
{
	double dx = getX() - v.getX();
	double dy = getY() - v.getY();
	return dx * dx + dy * dy;
}

double toxi::geom::Vec2D::dot( Vec2D & v )
{
	return getX() * v.getX() + getY() * v.getY();
}

bool toxi::geom::Vec2D::equalsWithTolerance( Vec2D & v, const double & tolerance )
{
	double diff = getX() - v.getX();
	//std::cout << diff << std::endl;
	if (toxi::math::MathUtils::isNan( diff )) {
		//std::cout << "1" << std::endl;
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		//std::cout << "2" << std::endl;
		return false;
	}
	diff = getY() - v.getY();
	if (toxi::math::MathUtils::isNan(diff)) {
		//std::cout << "3" << std::endl;
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		std::cout << "4" << std::endl;
		return false;
	}
	return true;
}

toxi::geom::Vec2D toxi::geom::Vec2D::getCartesian()
{
	Vec2D v = Vec2D( 0, 0 );
	double xx = (double) (getX() * std::cos( getY() ));
	v.y = (double) (getX() *std::sin( getY() ));
	v.x = xx;
	return v;
}

double toxi::geom::Vec2D::getComponent( const int & id )
{
	switch ( id ) {
	case 0:
		return getX();
	case 1:
		return getY();
	default:
		std::cerr << "Please define an existing Axis. Vec2D only has 0 and 1." << std::endl;
		return 0;
	}
}

double toxi::geom::Vec2D::getComponent( toxi::geom::Vec2D::Axis axis )
{
	switch( axis )
	{
	case X:
		return getX();
	case Y:
		return getY();
	default:
		return 0;
	}
}

toxi::geom::Vec2D toxi::geom::Vec2D::constrain( Rect & r )
{
	this->x = toxi::math::MathUtils::clip( getX(), r.x, r.x + r.width );
	this->y = toxi::math::MathUtils::clip( getY(), r.y, r.y + r.height );
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::constrain( Polygon2D & poly )
{
	double minD = FLT_MAX;
	toxi::geom::Vec2D q;
	for (toxi::geom::Line2D l : poly.getEdges()) {
		toxi::geom::Vec2D c = l.closestPointTo( * this );
		double d = c.distanceToSquared( *this );
		if (d < minD) {
			q = c;
			minD = d;
		}
	}
	this->set( q.getX(), q.getY() );
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::constrain( Vec2D & min, Vec2D & max )
{
	this->x = toxi::math::MathUtils::clip( getX(), min.getX(), max.getX() );
	this->y = toxi::math::MathUtils::clip( getY(), min.getY(), max.getY() );
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::floor( void )
{
	this->x = toxi::math::MathUtils::floor( getX() );
	this->y = toxi::math::MathUtils::floor( getY() );
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::getFloored()
{
	return toxi::geom::Vec2D( *this ).floor();
}

toxi::geom::Vec2D toxi::geom::Vec2D::getFrac()
{
	return toxi::geom::Vec2D( *this ).frac();
}

toxi::geom::Vec2D toxi::geom::Vec2D::frac()
{
	this->x -= toxi::math::MathUtils::floor( getX() );
	this->y -= toxi::math::MathUtils::floor( getY() );
	return *this;
}


toxi::geom::Vec2D toxi::geom::Vec2D::getInverted()
{
	return Vec2D( -getX(), -getY() );
}

toxi::geom::Vec2D toxi::geom::Vec2D::getLimited( const double & lim )
{
	if ( magSquared() > lim * lim ) {
		return getNormalizedTo( lim );
	}
	return Vec2D( getX(), getY() );
}

toxi::geom::Vec2D toxi::geom::Vec2D::getMapped( toxi::math::ScaleMap & map )
{
	return Vec2D( map.getClippedValueFor( getX() ), map.getClippedValueFor( getY() ) );
}

toxi::geom::Vec2D toxi::geom::Vec2D::getNormalized()
{
	return toxi::geom::Vec2D( *this ).normalize();
}

toxi::geom::Vec2D toxi::geom::Vec2D::getNormalizedTo( const double & len )
{
	Vec2D v = Vec2D( getX(), getX() );
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
	double t = getX();
	this->x = -getY();
	this->y = t;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::toPolar()
{
	double r = toxi::math::MathUtils::sqrt( x * x + y * y );
	this->y = std::atan2( getY(), getX() );
	this->x = r;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::reciprocal()
{
	this->x = 1.0 / getX();
	this->y = 1.0 / getY();
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::reflect( Vec2D & normal )
{
	return set( normal.scale( dot( normal ) * 2 ).subSelf( *this ) );
}

toxi::geom::Vec2D toxi::geom::Vec2D::getReflected( Vec2D & normal )
{
	Vec2D v = Vec2D( getX(), getY() );
	return v.reflect(normal);
}

toxi::geom::Vec2D toxi::geom::Vec2D::rotate( const double & theta )
{
	double co = std::cos( theta );
	double si = std::sin(theta);
	double xx = co * getX() - si * getY();
	this->y = si * getX() + co * getY();
	this->x = xx;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::getRotated( const double & theta )
{
	Vec2D v = Vec2D( *this );
	return v.rotate( theta );
}

toxi::geom::Vec2D toxi::geom::Vec2D::roundTo( const double & prec )
{
	this->x = toxi::math::MathUtils::roundTo(getX(), prec);
	this->y = toxi::math::MathUtils::roundTo(getY(), prec);
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::getRoundedTo( const double & prec )
{
	Vec2D v = Vec2D( *this );
	return v.roundTo( prec );
}

toxi::geom::Vec2D toxi::geom::Vec2D::signum()
{
	this->x = (x < 0 ? -1 : x == 0 ? 0 : 1);
	this->y = (y < 0 ? -1 : y == 0 ? 0 : 1);
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::getSignum()
{
	Vec2D v = Vec2D( *this );
	return v.signum();
}

toxi::geom::Vec2D toxi::geom::Vec2D::subSelf( const double & a, const double & b )
{
	this->x -= a;
	this->y -= b;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::subSelf( Vec2D & v )
{
	this->x -= v.getX();
	this->y -= v.getY();
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::set( const double & x, const double & y )
{
	this->x = x;
	this->y = y;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::set( Vec2D & v )
{
	this->x = v.getX();
	this->y = v.getY();
	return *this;
}

double toxi::geom::Vec2D::heading()
{
	return std::atan2(getY(), getX());
}

toxi::geom::Vec2D toxi::geom::Vec2D::interpolateTo( Vec2D & v, const double & f )
{
	Vec2D  vr = Vec2D( this->getX() + ( v.getX() - getX() ) * f, getY() + ( v.getY() - getY() ) * f );
	return vr;
}

toxi::geom::Vec2D toxi::geom::Vec2D::interpolateTo( Vec2D & v, const double & f, toxi::math::InterpolateStrategy * s )
{
	Vec2D vr = Vec2D( s->interpolate(getX(), v.getX(), f), s->interpolate(getY(), v.getY(), f) );
	return vr;
}

bool toxi::geom::Vec2D::isInCircle( Vec2D & sO, const double & sR )
{
	double d = sub( sO ).magSquared();
	return ( d <= sR * sR );
}

bool toxi::geom::Vec2D::isInRectangle( Rect & r )
{
	if ( getX() < r.x || getX() > r.x + r.width ) {
		return false;
	}
	if ( getY() < r.y || getY() > r.y + r.height ) {
		return false;
	}
	return true;
}

bool toxi::geom::Vec2D::isInTriangle( Vec2D & a, Vec2D & b, Vec2D & c )
{
	Vec2D v1 = sub(a).normalize();
	Vec2D v2 = sub(b).normalize();
	Vec2D v3 = sub(c).normalize();

	double total_angles = std::acos(v1.dot(v2));
	total_angles += std::acos(v2.dot(v3));
	total_angles += std::acos(v3.dot(v1));

	return (toxi::math::MathUtils::abs( total_angles - toxi::math::MathUtils::TWO_PI) <= 0.005f);
}

bool toxi::geom::Vec2D::isMajorAxis( const double & tol )
{
	double ax = toxi::math::MathUtils::abs( getX() );
	double ay = toxi::math::MathUtils::abs( getY() );
	double itol = 1 - tol;
	if (ax > itol) {
		return (ay < tol);
	} else if (ay > itol) {
		return (ax < tol);
	}
	return false;
}

bool toxi::geom::Vec2D::isZeroVector()
{
	return toxi::math::MathUtils::abs( getX() ) < toxi::math::MathUtils::EPS
		&& toxi::math::MathUtils::abs( getY() ) < toxi::math::MathUtils::EPS;
}

double toxi::geom::Vec2D::magnitude()
{
	return std::sqrt( getX() * getX() + getY() * getY());
}

double toxi::geom::Vec2D::magSquared()
{
	return getX() * getX() + getY() * getY();
}

toxi::geom::Vec2D toxi::geom::Vec2D::max( Vec2D & v )
{
	return Vec2D( toxi::math::MathUtils::max( getX(), v.getX() ), toxi::math::MathUtils::max( getY(), v.getY() ) );
}

toxi::geom::Vec2D toxi::geom::Vec2D::max( Vec2D & v1, Vec2D & v2 )
{
	return Vec2D( toxi::math::MathUtils::max( v1.getX(), v1.getX() ), toxi::math::MathUtils::max( v1.getY(), v2.getY() ) );
}

toxi::geom::Vec2D toxi::geom::Vec2D::min( Vec2D & v )
{
	return Vec2D( toxi::math::MathUtils::min( getX(), v.getX() ), toxi::math::MathUtils::min( getX(), v.getX() ) );
}

toxi::geom::Vec2D toxi::geom::Vec2D::min( Vec2D & v1, Vec2D & v2 )
{
	return Vec2D( toxi::math::MathUtils::min( v1.getX(), v2.getX() ), toxi::math::MathUtils::min( v1.getY(), v2.getY() ) );
}

toxi::geom::Vec2D toxi::geom::Vec2D::scale( const double & s )
{
	return Vec2D(getX() * s, getY() * s);
}

toxi::geom::Vec2D toxi::geom::Vec2D::scale( const double & a, const double & b )
{
	return Vec2D(getX() * a, getY() * b);
}

toxi::geom::Vec2D toxi::geom::Vec2D::scale( Vec2D & s )
{
	return Vec2D(getX() * s.getX(), getY() * s.getY() );
}

toxi::geom::Vec2D toxi::geom::Vec2D::sub( const double & a, const double & b )
{
	return Vec2D(getX() - a, getY() - b);
}

toxi::geom::Vec2D toxi::geom::Vec2D::sub( const Vec2D & v ) const
{
	return Vec2D(this->getX() - v.getX(), this->getY() - v.getY());
}

toxi::geom::Vec2D toxi::geom::Vec2D::tangentNormalOfEllipse( Vec2D & eO, Vec2D & eR )
{
	Vec2D p = this->sub( eO );

	double xr2 = eR.getX() * eR.getX();
	double yr2 = eR.getY() * eR.getY();

	return Vec2D( p.getX() / xr2, p.getY() / yr2 ).normalize();
}

std::vector< double > toxi::geom::Vec2D::toVector()
{
	std::vector < double > vec;
	vec.push_back( getX() );
	vec.push_back( getY() );
	return vec;
}

toxi::geom::Vec2D toxi::geom::Vec2D::scaleSelf( const float & s )
{
	this->x *= s;
	this->y *= s;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::scaleSelf( Vec2D & v )
{
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::scaleSelf( const float & s1, const float & s2 )
{
	this->x *= s1;
	this->y *= s2;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::addSelf( const double & a, const double & b )
{
	this->x += a;
	this->y += b;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::addSelf( Vec2D & v )
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::randomVector( void )
{
	return Vec2D( toxi::math::MathUtils::random( -1, 1), toxi::math::MathUtils::random( -1, 1 ) );
}

toxi::geom::Vec2D toxi::geom::Vec2D::abs()
{
	this->x = toxi::math::MathUtils::abs( getX() );
	this->y = toxi::math::MathUtils::abs( getY() );
	return *this;
}

/*bool toxi::geom::Vec2D::operator==( const Vec2D & v1 ) const
{
	std::cout << " this: " << this->toString() << " v1: " << v1.toString() << std::endl;
	if( *this->x == *v1.x && *this->y == *v1.y )
	{
		return true;
	}
	else 
	{
		return false;
	}
}*/


toxi::geom::Vec2D toxi::geom::Vec2D::getAbs( void )
{
	return Vec2D( *this ).abs();
}

toxi::geom::Vec2D toxi::geom::Vec2D::getConstrained( toxi::geom::Polygon2D & poly )
{
	return Vec2D( *this ).constrain( poly );
}

toxi::geom::Vec2D toxi::geom::Vec2D::getConstrained( toxi::geom::Rect & rec )
{
	return Vec2D( *this ).constrain( rec );
}

int toxi::geom::Vec2D::hashCode()
{
	long bits = 1L;
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits(static_cast< float > ( getX() ) );
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits(static_cast< float > ( getY() ) );
	return (int) (bits ^ (bits >> 16));
}

toxi::geom::Vec2D toxi::geom::Vec2D::interpolateToSelf( Vec2D & v, const float & f )
{
	this->x += ( v.getX() - this->getX() ) * f;
	this->y += ( v.getY() - this->getY() ) * f;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::interpolateToSelf( Vec2D & v, const float & f, toxi::math::InterpolateStrategy * s  )
{
	this->x = s->interpolate( getX(), v.getX(), static_cast< double > ( f ) );
	this->y = s->interpolate( getY(), v.getY(), static_cast< double > ( f ) );
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::invert()
{
	this->x = -getX();
	this->y = -getY();
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::jitter( const double & j )
{
	return jitter( j, j );
}

toxi::geom::Vec2D toxi::geom::Vec2D::jitter( const double & jx, const double & jy )
{
	this->x += toxi::math::MathUtils::normalizedRandom() * jx;
	this->y += toxi::math::MathUtils::normalizedRandom() * jy;
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::jitter( Vec2D & jv )
{
	return jitter( jv.getX(), jv.getY() );
}

toxi::geom::Vec2D toxi::geom::Vec2D::limit( const float & lim )
{
	if( magSquared() > lim * lim )
	{
		return normalize().scaleSelf( lim );
	}

	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::maxSelf( Vec2D & v )
{
	this->x = toxi::math::MathUtils::max( getX(), v.getX() );
	this->y = toxi::math::MathUtils::max( getY(), v.getY() );
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::minSelf( Vec2D & v )
{
	this->x = toxi::math::MathUtils::min( getX(), v.getX() );
	this->y = toxi::math::MathUtils::min( getY(), v.getY() );
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::normalizeTo( const float & len )
{
	float mag = (float) toxi::math::MathUtils::sqrt(getX() * getX() + getY() * getY());
	if (mag > 0) {
		mag = len / mag;
		this->x *= mag;
		this->y *= mag;
	}
	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::perpendicular()
{
	double t = getX();
	this->x = -getY();
	this->y = t;
	return *this;
}

double toxi::geom::Vec2D::positiveHeading()
{
	double dist = toxi::math::MathUtils::sqrt( getX() * getX() + getY() * getY() );
	if( y >= 0 )
	{
		return std::acos( getX() / dist );
	}
	else 
	{
		return std::acos( -getX() / dist ) + toxi::math::MathUtils::PI;
	}
}

toxi::geom::Vec2D toxi::geom::Vec2D::setComponent( Axis & id, const float & val )
{
	switch( id )
	{
	case X:
		this->x = val;
		break;
	case Y:
		this->y = val;
		break;
	}

	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::setComponent( const int & id, const float & val )
{
	switch( id )
	{
	case 0:
		this->x = val;
		break;
	case 1:
		this->y = val;
		break;
	}

	return *this;
}

toxi::geom::Vec2D toxi::geom::Vec2D::snapToAxis()
{
	if( toxi::math::MathUtils::abs( getX() ) < 0.5 )
	{
		this->x = 0;
	} else 
	{
		this->x = getX() < 0 ? -1 : 1;
		this->y = 0;
	}

	if( toxi::math::MathUtils::abs( getY() ) < 0.5 )
	{
		this->y  = 0;
	} else
	{
		this->y = getY() < 0 ? -1 : 1;
		this->x = 0;	
	}

	return *this;
}

std::string toxi::geom::Vec2D::toString()
{
	std::stringstream ss;
	ss << "{x:" << this->getX() << ", y:" << this->getY() << "}";
	return ss.str();
}

const double toxi::geom::Vec2D::getX() const
{
	return x;
}

const double toxi::geom::Vec2D::getY() const
{
	return y;
}

toxi::geom::Vec3D toxi::geom::Vec2D::to3DXY()
{
	return toxi::geom::Vec3D();
}

toxi::geom::Vec3D toxi::geom::Vec2D::to3DXZ()
{
	return toxi::geom::Vec3D();
}

toxi::geom::Vec3D toxi::geom::Vec2D::to3DYZ()
{
	return toxi::geom::Vec3D();
}

toxi::geom::Vec2D toxi::geom::Vec2D::roundToAxis()
{

}

/*inline std::ostream & operator << (std::ostream& stream, const toxi::geom::Vec2D & v) {
	std::cout << "ACTUALLY OVERLOADED " << std::endl;
	stream << "{x:" << v.getX() << ", y:" << v.getY() << "}";
}*/