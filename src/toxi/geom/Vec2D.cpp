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


toxi::geom::Vec2D::Vec2D( double _x, double _y )
{
	this->x = new double;
	this->y = new double;

	*this->x = _x;
	*this->y = _y;
}

toxi::geom::Vec2D::Vec2D( double theta )
{
	this->x = new double;
	this->y = new double;

	*this->x = toxi::math::MathUtils::cos( theta );
	*this->y = toxi::math::MathUtils::sin( theta );
}

toxi::geom::Vec2D::Vec2D( const Vec2D & v )
{
	this->x = new double;
	this->y = new double;

	this->x = v.x;
	this->y = v.y;
}

toxi::geom::Vec2D::Vec2D(  )
{
	this->x = new double;
	this->y = new double;

	*this->x = 0;
	*this->y = 0;
}

toxi::geom::Vec2D::~Vec2D(void)
{
	delete x;
	delete y;
}

double toxi::geom::Vec2D::angleBetween( Vec2D * v )
{
	return ( double ) std::acos( dot( v ) );
}

double toxi::geom::Vec2D::angleBetween( Vec2D * v, bool forceNormalize )
{
	double theta;
	if (forceNormalize) {
		theta = getNormalized()->dot(v->getNormalized());
	} else {
		theta = dot(v);
	}
	return (double) std::acos(toxi::math::MathUtils::clipNormalized(theta));
}

toxi::geom::Vec2D * toxi::geom::Vec2D::add( double _x, double _y )
{
	Vec2D * v = new Vec2D( _x + *this->x, _y + *this->y );
	return v;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::add( Vec2D * v )
{
	Vec2D * _v = new Vec2D( *v->x + *this->x, *v->y + *this->y );
	return _v;
}

toxi::geom::Vec3D * toxi::geom::Vec2D::bisect( Vec2D * b )
{
	Vec2D diff = *this->sub( b );
	Vec2D sum = *this->add( b );
	double dot = diff.dot( &sum );
	return new Vec3D( *diff.x, *diff.y, -dot / 2);
}

double toxi::geom::Vec2D::cross( Vec2D * v )
{
	return (*x * *v->y) - (*y * *v->x);
}

double toxi::geom::Vec2D::distanceTo( Vec2D * v )
{
	double dx = x - v->x;
	double dy = y - v->y;
	return (double) std::sqrt(dx * dx + dy * dy);
}

double toxi::geom::Vec2D::distanceToSquared( Vec2D * v )
{
	double dx = x - v->x;
	double dy = y - v->y;
	return dx * dx + dy * dy;
}

double toxi::geom::Vec2D::dot( Vec2D * v )
{
	return *x * *v->x + *y * *v->y;
}

bool toxi::geom::Vec2D::equalsWithTolerance( Vec2D * v, double tolerance )
{
	double diff = x - v->x;
	if (toxi::math::MathUtils::isNan( diff )) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	diff = y - v->y;
	if (toxi::math::MathUtils::isNan(diff)) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	return true;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getCartesian()
{
	Vec2D v = Vec2D( 0, 0 );
	double xx = (double) (*x * std::cos( *y ));
	*v.y = (double) (*x *std::sin( *y ));
	*v.x = xx;
	return &v;
}

double toxi::geom::Vec2D::getComponent( int id )
{
	switch (id) {
	case 0:
		return *x;
	case 1:
		return *y;
	}
}

double toxi::geom::Vec2D::getComponent( toxi::geom::Vec2D::Axis * axis )
{
	switch( *axis )
	{
	case X:
		return *x;
	case Y:
		return *y;
	}
}

toxi::geom::Vec2D * toxi::geom::Vec2D::constrain( Rect * r )
{
	*x = toxi::math::MathUtils::clip( *x, r->x, r->x + r->width );
	*y = toxi::math::MathUtils::clip( *y, r->y, r->y + r->height );
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::constrain( Polygon2D * poly )
{
	float minD = FLT_MAX;
	toxi::geom::Vec2D q;
	for (toxi::geom::Line2D *l : poly->getEdges()) {
		toxi::geom::Vec2D * c = l->closestPointTo( * this );
		float d = c->distanceToSquared(this);
		if (d < minD) {
			q = *c;
			minD = d;
		}
	}
	this->x = q.x;
	this->y = q.y;
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::constrain( Vec2D * min, Vec2D * max )
{
	*this->x = toxi::math::MathUtils::clip( *x, *min->x, *max->x );
	*this->y = toxi::math::MathUtils::clip( *y, *min->y, *max->y );
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::floor( void )
{
	*this->x = toxi::math::MathUtils::floor( *this->x );
	*this->y = toxi::math::MathUtils::floor( *this->y );
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getFloored()
{
	return toxi::geom::Vec2D( *this ).floor();
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getFrac()
{
	return toxi::geom::Vec2D( *this ).frac();
}

toxi::geom::Vec2D * toxi::geom::Vec2D::frac()
{
	*this->x -= toxi::math::MathUtils::floor( *x );
	*this->y -= toxi::math::MathUtils::floor( *y );
	return this;
}


toxi::geom::Vec2D * toxi::geom::Vec2D::getInverted()
{
	return new Vec2D( -*x, -*y );
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getLimited( double lim )
{
	if ( magSquared() > lim * lim ) {
		return getNormalizedTo( lim );
	}
	return new Vec2D( *x, *y );
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getMapped( toxi::math::ScaleMap * map )
{
	return new Vec2D( map->getClippedValueFor( *x ), map->getClippedValueFor( *y ) );
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getNormalized()
{
	return toxi::geom::Vec2D( *this ).normalize();
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getNormalizedTo( double len )
{
	Vec2D * v = new Vec2D( getX(), getX() );
	double mag = (double) toxi::math::MathUtils::sqrt( *x * *x + *y * *y );
	if (mag > 0) {
		mag = len / mag;
		*v->x *= mag;
		*v->y *= mag;
	}
	return v;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::normalize()
{
	double mag = *x * *x + *y * *y;
	if (mag > 0) {
		mag = 1.0 / toxi::math::MathUtils::sqrt( mag );
		*this->x *= mag;
		*this->y *= mag;
	}
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getPerpendicular()
{
	double t = *this->x;
	*this->x = -*this->y;
	*this->y = t;
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::toPolar()
{
	double r = toxi::math::MathUtils::sqrt( *x * *x + *y * *y );
	*this->y = std::atan2( getY(), getX() );
	*this->x = r;
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::reciprocal()
{
	*this->x = 1.0 / *this->x;
	*this->y = 1.0 / *this->y;
	return this;
}

toxi::geom::Vec2D* toxi::geom::Vec2D::reflect( Vec2D * normal )
{
	return set(normal->scale(dot(normal) * 2)->subSelf( this));
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getReflected( Vec2D * normal )
{
	Vec2D * v = new Vec2D( *x, *y );
	return v->reflect(normal);
}

toxi::geom::Vec2D * toxi::geom::Vec2D::rotate( double theta )
{
	double co = std::cos( theta );
	double si = std::sin(theta);
	double xx = co * *this->x - si * *this->y;
	*this->y = si * *this->x + co * *this->y;
	*this->x = xx;
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getRotated( double theta )
{
	Vec2D * v = new Vec2D( *this );
	return v->rotate( theta );
}

toxi::geom::Vec2D * toxi::geom::Vec2D::roundTo( double prec )
{
	*this->x = toxi::math::MathUtils::roundTo(*x, prec);
	*this->y = toxi::math::MathUtils::roundTo(*y, prec);
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getRoundedTo( double prec )
{
	Vec2D * v = new Vec2D( *this );
	return v->roundTo( prec );
}

toxi::geom::Vec2D * toxi::geom::Vec2D::signum()
{
	*this->x = (x < 0 ? -1 : x == 0 ? 0 : 1);
	*this->y = (y < 0 ? -1 : y == 0 ? 0 : 1);
	return this;
}

toxi::geom::Vec2D* toxi::geom::Vec2D::getSignum()
{
	Vec2D * v = new Vec2D( *this );
	return v->signum();
}

toxi::geom::Vec2D * toxi::geom::Vec2D::subSelf( double a, double b )
{
	*this->x -= a;
	*this->y -= b;
	return this;
}

toxi::geom::Vec2D*  toxi::geom::Vec2D::subSelf( Vec2D * v )
{
	*this->x -= v->getX();
	*this->y -= v->getY();
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::set( double x, double y )
{
	*this->x = x;
	*this->y = y;
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::set( Vec2D * v )
{
	this->x = v->x;
	this->y = v->y;
	return this;
}

double toxi::geom::Vec2D::heading()
{
	return std::atan2(getY(), getX());
}

toxi::geom::Vec2D * toxi::geom::Vec2D::interpolateTo( Vec2D * v, double f )
{
	Vec2D  * vr = new Vec2D( *this->x + (*v->x - *this->x) * f, *this->y + (*v->y - *this->y) * f );
	return vr;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::interpolateTo( Vec2D * v, double f, toxi::math::InterpolateStrategy s )
{
	Vec2D * vr = new Vec2D( s.interpolate(*this->x, *v->x, f), s.interpolate(*this->y, *v->y, f) );
	return vr;
}

bool toxi::geom::Vec2D::isInCircle( Vec2D * sO, double sR )
{
	float d = sub( sO )->magSquared();
	return ( d <= sR * sR );
}

bool toxi::geom::Vec2D::isInRectangle( Rect * r )
{
	if ( *this->x < r->x || *this->x > r->x + r->width ) {
		return false;
	}
	if ( *this->y < r->y || *this->y > r->y + r->height ) {
		return false;
	}
	return true;
}

bool toxi::geom::Vec2D::isInTriangle( Vec2D * a, Vec2D * b, Vec2D * c )
{
	Vec2D * v1 = sub(a)->normalize();
	Vec2D * v2 = sub(b)->normalize();
	Vec2D * v3 = sub(c)->normalize();

	double total_angles = std::acos(v1->dot(v2));
	total_angles += std::acos(v2->dot(v3));
	total_angles += std::acos(v3->dot(v1));

	return (toxi::math::MathUtils::abs( total_angles - toxi::math::MathUtils::TWO_PI) <= 0.005f);
}

bool toxi::geom::Vec2D::isMajorAxis( double tol )
{
	float ax = toxi::math::MathUtils::abs( *this->x );
	float ay = toxi::math::MathUtils::abs( *this->y );
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
	return toxi::math::MathUtils::abs( *this->x ) < toxi::math::MathUtils::EPS
		&& toxi::math::MathUtils::abs( *this->y ) < toxi::math::MathUtils::EPS;
}

double toxi::geom::Vec2D::magnitude()
{
	return std::sqrt( *this->x * *this->x + *this->y * *this->y);
}

double toxi::geom::Vec2D::magSquared()
{
	return *this->x * *this->x + *this->y * *this->y;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::max( Vec2D * v )
{
	return new Vec2D( toxi::math::MathUtils::max( *this->x, *v->x ), toxi::math::MathUtils::max( *this->x, *v->x ) );
}

toxi::geom::Vec2D * toxi::geom::Vec2D::max( Vec2D * v1, Vec2D * v2 )
{
	return new Vec2D( toxi::math::MathUtils::max( *v1->x, *v2->x ), toxi::math::MathUtils::max( *v1->y, *v2->y ) );
}

toxi::geom::Vec2D * toxi::geom::Vec2D::min( Vec2D * v )
{
	return new Vec2D( toxi::math::MathUtils::min( *this->x, *v->x ), toxi::math::MathUtils::min( *this->x, *v->x ) );
}

toxi::geom::Vec2D * toxi::geom::Vec2D::min( Vec2D * v1, Vec2D * v2 )
{
	return new Vec2D( toxi::math::MathUtils::min( *v1->x, *v2->x ), toxi::math::MathUtils::min( *v1->y, *v2->y ) );
}

toxi::geom::Vec2D * toxi::geom::Vec2D::scale( double s )
{
	return new Vec2D(*this->x * s, *this->y * s);
}

toxi::geom::Vec2D * toxi::geom::Vec2D::scale( double a, double b )
{
	return new Vec2D(*this->x * a, *this->y * b);
}

toxi::geom::Vec2D * toxi::geom::Vec2D::scale( Vec2D * s )
{
	return new Vec2D(*this->x * *s->x, *this->y * *s->y );
}

toxi::geom::Vec2D * toxi::geom::Vec2D::sub( double a, double b )
{
	return new Vec2D(*this->x - a, *this->y - b);
}

toxi::geom::Vec2D * toxi::geom::Vec2D::sub( Vec2D * v )
{
	return new Vec2D(this->x - v->x, this->y - v->y);
}

toxi::geom::Vec2D * toxi::geom::Vec2D::tangentNormalOfEllipse( Vec2D * eO, Vec2D * eR )
{
	Vec2D * p = this->sub( eO );

	float xr2 = *eR->x * *eR->x;
	float yr2 = *eR->y * *eR->y;

	return Vec2D(*p->x / xr2, *p->y / yr2).normalize();
}

std::vector< float > toxi::geom::Vec2D::toVector()
{
	std::vector < float > vec;
	vec.push_back( getX() );
	vec.push_back( getY() );
	return vec;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::scaleSelf( float s )
{
	*this->x *= s;
	*this->y *= s;
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::scaleSelf( Vec2D * v )
{
	*this->x *= *v->x;
	*this->y *= *v->y;
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::scaleSelf( float s1, float s2 )
{
	*this->x *= s1;
	*this->y *= s2;
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::addSelf( double a, double b )
{
	*this->x += a;
	*this->y += b;
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::addSelf( Vec2D * v )
{
	*this->x += *v->x;
	*this->y += *v->y;
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::randomVector( void )
{
	return new Vec2D( toxi::math::MathUtils::random( -1, 1), toxi::math::MathUtils::random( -1, 1 ) );
}

toxi::geom::Vec2D*  toxi::geom::Vec2D::abs()
{
	*this->x = toxi::math::MathUtils::abs( *this->x );
	*this->y = toxi::math::MathUtils::abs( *this->y );
	return this;
}

bool toxi::geom::Vec2D::operator==( const Vec2D v1 )
{
	if( this->x == v1.x && this->y == v1.y )
	{
		return true;
	}
	else 
	{
		return false;
	}
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getAbs( void )
{
	return Vec2D( *this ).abs();
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getConstrained( toxi::geom::Polygon2D * poly )
{
	return Vec2D( *this ).constrain( poly );
}

toxi::geom::Vec2D * toxi::geom::Vec2D::getConstrained( toxi::geom::Rect * rec )
{
	return Vec2D( *this ).constrain( rec );
}

int toxi::geom::Vec2D::hashCode()
{
	long bits = 1L;
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits(getX());
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits(getY());
	return (int) (bits ^ (bits >> 32));
}

toxi::geom::Vec2D * toxi::geom::Vec2D::interpolateToSelf( Vec2D * v, float f )
{
	*this->x += ( v->x - this->x ) * f;
	*this->y += ( v->y - this->y ) * f;
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::interpolateToSelf( Vec2D * v, float f, toxi::math::InterpolateStrategy s  )
{
	*this->x = s.interpolate( *this->x, *v->x, static_cast< double > ( f ) );
	*this->y = s.interpolate( *this->y, *v->y, static_cast< double > ( f ) );
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::invert()
{
	*this->x = -*this->x;
	*this->y = -*this->y;
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::jitter( float j )
{
	return jitter( j, j );
}

toxi::geom::Vec2D * toxi::geom::Vec2D::jitter( float jx, float jy )
{
	*this->x += toxi::math::MathUtils::normalizedRandom() * jx;
	*this->y += toxi::math::MathUtils::normalizedRandom() * jy;
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::jitter( Vec2D * jv )
{
	return jitter( *jv->x, *jv->y );
}

toxi::geom::Vec2D * toxi::geom::Vec2D::limit( float lim )
{
	if( magSquared() > lim * lim )
	{
		return normalize()->scaleSelf( lim );
	}

	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::maxSelf( Vec2D * v )
{
	*this->x = toxi::math::MathUtils::max( *this->x, *v->x );
	*this->y = toxi::math::MathUtils::max( *this->y, *v->y );
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::minSelf( Vec2D * v )
{
	*this->x = toxi::math::MathUtils::min( *this->x, *v->x );
	*this->y = toxi::math::MathUtils::max( *this->y, *v->y );
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::normalizeTo( float len )
{
	float mag = (float) toxi::math::MathUtils::sqrt(*this->x * *this->x + *this->y * *this->y);
	if (mag > 0) {
		mag = len / mag;
		*this->x *= mag;
		*this->y *= mag;
	}
	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::perpendicular()
{
	float t = *this->x;
	*this->x = -*this->y;
	*this->y = t;
	return this;
}

float toxi::geom::Vec2D::positiveHeading()
{
	double dist = toxi::math::MathUtils::sqrt( *this->x * *this->x + *this->y * *this->y );
	if( y >= 0 )
	{
		return std::acosf( *this->x / dist );
	}
	else 
	{
		return std::acosf( -*this->x / dist ) + toxi::math::MathUtils::PI;
	}
}

toxi::geom::Vec2D * toxi::geom::Vec2D::setComponent( Axis * id, float val )
{
	switch( *id )
	{
	case X:
		*this->x = val;
		break;
	case Y:
		*this->y = val;
		break;
	}

	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::setComponent( int id, float val )
{
	switch( id )
	{
	case 0:
		*this->x = val;
		break;
	case 1:
		*this->y = val;
		break;
	}

	return this;
}

toxi::geom::Vec2D * toxi::geom::Vec2D::snapToAxis()
{
	if( toxi::math::MathUtils::abs( *this->x ) < 0.5 )
	{
		*this->x = 0;
	} else 
	{
		*this->x = this->x < 0 ? -1 : 1;
		*this->y = 0;
	}

	if( toxi::math::MathUtils::abs( *this->y ) < 0.5 )
	{
		*this->y  = 0;
	} else
	{
		*this->y = this->y < 0 ? -1 : 1;
		*this->x = 0;
	}

	return this;
}

std::string toxi::geom::Vec2D::toString()
{
	std::stringstream ss;
	ss << "{x:" << this->x << ", y:" << this->y << "}";
	return ss.str();
}

double toxi::geom::Vec2D::getX()
{
	return *x;
}

double toxi::geom::Vec2D::getY()
{
	return *y;
}