#include "Vec3D.h"
#include "Axis3D.h"
#include "Vec2D.h"
#include "Vec4D.h"
#include "VecMathUtil.h"
#include "AABB.h"

toxi::geom::Vec3D::Vec3D(void)
{
}

toxi::geom::Vec3D::Vec3D(const float & x, const float & y, const float & z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}

toxi::geom::Vec3D::Vec3D( const int & x, const int & y, const int & z )
{
	this->x = static_cast< float > ( x );
	this->y = static_cast< float > ( y );
	this->z = static_cast< float > ( z );
}

toxi::geom::Vec3D::Vec3D( const double & x, const double & y, const double & z )
{
	this->x = static_cast< float > ( x );
	this->y = static_cast< float > ( y );
	this->z = static_cast< float > ( z );
}

toxi::geom::Vec3D::~Vec3D(void)
{
}

toxi::geom::Vec3D toxi::geom::Vec3D::add( const double & _a, const double & _b, const double & _c )
{
	this->x += _a;
	this->y += _b;
	this->z += _c;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::add( const Vec3D & v )
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

float toxi::geom::Vec3D::angleBetween( const Vec3D & v )
{
	return std::acos(dot(v));
}

float toxi::geom::Vec3D::angleBetween( Vec3D & v, const bool & forceNormalize )
{
	float theta;
	if (forceNormalize) {
		theta = getNormalized().dot(v.getNormalized());
	} else {
		theta = dot(v);
	}
	return std::acos(theta);
}

int toxi::geom::Vec3D::compareTo( const Vec3D & v )
{
	if ( x == v.x && y == v.y && z == v.z ) {
		return 0;
	}
	float a = magSquared();
	float b = v.magSquared();
	if (a < b) {
		return -1;
	}
	return +1;
}

toxi::geom::Vec3D toxi::geom::Vec3D::copy()
{
	return Vec3D( this->x, this->y, this->z );
}

toxi::geom::Vec3D toxi::geom::Vec3D::cross( const  Vec3D & v )
{
	return Vec3D(y * v.z - v.y * z, z * v.x - v.z * x, x
		* v.y - v.x * y);
}

toxi::geom::Vec3D toxi::geom::Vec3D::crossInto( const Vec3D & v)
{
	Vec3D result;
	double vx = v.x;
	double vy = v.y;
	double vz = v.z;
	result.x = this->y * vz - vy * this->z;
	result.y = this->z * vx - vz * this->x;
	result.z = this->x * vy - vx * this->y;
	return result;
}

double toxi::geom::Vec3D::distanceTo( const Vec3D & v )
{
	double dx = this->x - v.x;
	double dy = this->y - v.y;
	double dz = this->z - v.z;
	return toxi::math::MathUtils::sqrt(dx * dx + dy * dy + dz * dz);
}

double toxi::geom::Vec3D::distanceToSquared( const Vec3D & v )
{
	double dx = this->x - v.x;
	double dy = this->y - v.y;
	double dz = this->z - v.z;
	return dx * dx + dy * dy + dz * dz;
}

float toxi::geom::Vec3D::dot( const toxi::geom::Vec3D & v )
{
	return static_cast< float > ( this->x * v.x + this->y * v.y + this->z * v.z );
}

bool toxi::geom::Vec3D::equals( const Vec3D & vv )
{
	return (this->x == vv.x && this->y == vv.y && this->z == vv.z );
}

bool toxi::geom::Vec3D::equalsWithTolerance( const Vec3D & v, const float & tolerance )
{
	double diff = this->x - v.x;
	if (toxi::math::MathUtils::isNan(diff)) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	diff = this->y - v.y;
	if (toxi::math::MathUtils::isNan(diff)) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	diff = this->z - v.z;
	if (toxi::math::MathUtils::isNan(diff)) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	return true;
}

toxi::geom::Vec3D toxi::geom::Vec3D::getAbs()
{
	this->x = toxi::math::MathUtils::abs(this->x);
	this->y = toxi::math::MathUtils::abs(this->y);
	this->z = toxi::math::MathUtils::abs(this->z);
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::getCartesian()
{
	float a = (float) (x * std::cos(this->z));
	float xx = (float) (a * std::cos(this->y));
	float yy = (float) (x * std::sin(this->z));
	float zz = (float) (a * std::sin(this->y));
	this->x = xx;
	this->y = yy;
	this->z = zz;
	return *this;
}

toxi::geom::Axis3D toxi::geom::Vec3D::getClosestAxis()
{
	double ax = toxi::math::MathUtils::abs(this->x);
	double ay = toxi::math::MathUtils::abs(this->y);
	double az = toxi::math::MathUtils::abs(this->z);
	if (ax > ay && ax > az) {
		return toxi::geom::Axis3D::X_AXIS();
	}
	if (ay > ax && ay > az) {
		return toxi::geom::Axis3D::Y_AXIS();
	}
	if (az > ax && az > ay) {
		return toxi::geom::Axis3D::Z_AXIS();
	}
	return toxi::geom::Axis3D( Vec3D(0, 0, 0));
}

double toxi::geom::Vec3D::getComponent( const int & id )
{
	switch (id) {
	case 0:
		return this->x;
	case 1:
		return this->y;
	case 2:
		return this->z;
	}
}

toxi::geom::Vec3D toxi::geom::Vec3D::getConstrained( const AABB & box )
{
	return Vec3D(this->x, this->y, this->z).constrain(box);
}

toxi::geom::Vec3D toxi::geom::Vec3D::getFloored()
{
	this->x = toxi::math::MathUtils::floor( this->x );
	this->y = toxi::math::MathUtils::floor( this->y );
	this->z = toxi::math::MathUtils::floor( this->z );
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::getFrac()
{
	this->x -= toxi::math::MathUtils::floor( this->x );
	this->y -= toxi::math::MathUtils::floor( this->y );
	this->z -= toxi::math::MathUtils::floor( this->z );
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::getInverted()
{
	return Vec3D( -this->x, -this->y, -this->z );
}

toxi::geom::Vec3D toxi::geom::Vec3D::getLimited( const float & lim )
{
	if (magSquared() > lim * lim) {
		return getNormalizedTo(lim);
	}
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::getMapped( const toxi::math::ScaleMap & map )
{
	return Vec3D(map.getClippedValueFor(this->x),
		map.getClippedValueFor(this->y),
		map.getClippedValueFor(this->z));
}

toxi::geom::Vec3D toxi::geom::Vec3D::getNormalized()
{
	return this->normalize();
}

toxi::geom::Vec3D toxi::geom::Vec3D::getNormalizedTo( const float & len )
{
	return this->normalizeTo( len );
}

toxi::geom::Vec3D toxi::geom::Vec3D::getReciprocal()
{
	return copy().reciprocal();
}

toxi::geom::Vec3D toxi::geom::Vec3D::getReflected( const Vec3D & normal )
{
	return copy().reflect( normal );
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedAroundAxis( const Vec3D & axis, const float & theta )
{
	return copy().rotateAroundAxis(axis, theta );
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedX( const float & theta )
{
	return copy().rotateX(theta);
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedY( const float & theta )
{
	return copy().rotateY(theta);
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedZ( const float & theta )
{
	return copy().rotateZ(theta);
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRoundedTo( const float & prec )
{
	return copy().roundTo(prec);
}

toxi::geom::Vec3D toxi::geom::Vec3D::getSignum()
{
	return copy().signum();
}

toxi::geom::Vec3D toxi::geom::Vec3D::getSpherical()
{
	return copy().toSpherical();
}

float toxi::geom::Vec3D::headingXY()
{
	return (float) std::atan2(y, x);
}

float toxi::geom::Vec3D::headingXZ()
{
	return (float) std::atan2(z, x);
}

float toxi::geom::Vec3D::headingYZ()
{
	return (float) std::atan2(y, z);
}

toxi::geom::Vec3D toxi::geom::Vec3D::interpolateTo( const Vec3D & v, const double & f )
{
	return Vec3D(x + (v.x - x) * f, y + (v.y - y) * f, z
		+ (v.z - z) * f);
}

toxi::geom::Vec3D toxi::geom::Vec3D::interpolateTo( const toxi::geom::Vec3D & v, const double & f, const toxi::math::InterpolateStrategy & s )
{
	return Vec3D(s.interpolate(x, v.x, f),
		s.interpolate(y, v.y, f), s.interpolate(z, v.z, f));
}

bool toxi::geom::Vec3D::isInAABB( const  toxi::geom::AABB & box )
{
	//TODO
	Vec3D min = Vec3D(); //box->getMin();
	Vec3D max = Vec3D();// box->getMax();
	if (x < min.x || x > max.x) {
		return false;
	}
	if (y < min.y || y > max.y) {
		return false;
	}
	if (z < min.z || z > max.z) {
		return false;
	}
	return true;
}

bool toxi::geom::Vec3D::isInAABB( const Vec3D & boxOrigin, const Vec3D & boxExtent )
{
	double w = boxExtent.x;
	if (x < boxOrigin.x - w || x > boxOrigin.x + w) {
		return false;
	}
	w = boxExtent.y;
	if (y < boxOrigin.y - w || y > boxOrigin.y + w) {
		return false;
	}
	w = boxExtent.z;
	if (z < boxOrigin.z - w || z > boxOrigin.z + w) {
		return false;
	}
	return true;
}

bool toxi::geom::Vec3D::isMajorAxis( const float & tolerance )
{
	double ax = toxi::math::MathUtils::abs(x);
	double ay = toxi::math::MathUtils::abs(y);
	double az = toxi::math::MathUtils::abs(z);
	double itol = 1 - tolerance;
	if (ax > itol) {
		if (ay < tolerance) {
			return (az < tolerance);
		}
	} else if (ay > itol) {
		if (ax < tolerance) {
			return (az < tolerance);
		}
	} else if (az > itol) {
		if (ax < tolerance) {
			return (ay < tolerance);
		}
	}
	return false;
}

bool toxi::geom::Vec3D::isZeroVector()
{
	return toxi::math::MathUtils::abs(x) < toxi::math::MathUtils::EPS
		&& toxi::math::MathUtils::abs(y) < toxi::math::MathUtils::EPS
		&& toxi::math::MathUtils::abs(z) < toxi::math::MathUtils::EPS;
}

float toxi::geom::Vec3D::magnitude()
{
	return (float) toxi::math::MathUtils::sqrt(x * x + y * y + z * z);
}

float toxi::geom::Vec3D::magSquared() const
{
	return static_cast< float> ( x * x + y * y + z * z );
}

toxi::geom::Vec3D toxi::geom::Vec3D::scale( const float & s )const
{
	return Vec3D(x * s, y * s, z * s);
}

toxi::geom::Vec3D toxi::geom::Vec3D::scale( const float & a, const float & b, const float & c )const
{
	return Vec3D(x * a, y * b, z * c);
}

toxi::geom::Vec3D toxi::geom::Vec3D::scale( const Vec3D & s ) const
{
	return Vec3D(x * s.x, y * s.y, z * s.z);
}

toxi::geom::Vec3D toxi::geom::Vec3D::sub( const float & a, const float & b, const float & c )
{
	return Vec3D(x - a, y - b, z - c);
}

toxi::geom::Vec3D toxi::geom::Vec3D::sub( const Vec3D & v )
{
	return Vec3D(x - v.x, y - v.y, z - v.z);
}

toxi::geom::Vec2D toxi::geom::Vec3D::to2DXY()
{
	return toxi::geom::Vec2D( x, y );
}

toxi::geom::Vec2D toxi::geom::Vec3D::to2DXZ()
{
	return Vec2D( x, z );
}

toxi::geom::Vec2D toxi::geom::Vec3D::to2DYZ()
{
	return Vec2D( y, z );
}

toxi::geom::Vec4D toxi::geom::Vec3D::to4D()
{
	return Vec4D( x, y, z, 1 );
}

toxi::geom::Vec4D toxi::geom::Vec3D::to4D( const double & w )
{
	return Vec4D( x, y, z, w );
}

void toxi::geom::Vec3D::toArray( const float& arr )
{
	// TODO
}

void toxi::geom::Vec3D::toArray4( const float & arr, const float & w )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::constrain( const toxi::geom::AABB & box )
{
	//TODO
	//return constrain(box.getMin(), box.getMax());
}

toxi::geom::Vec3D toxi::geom::Vec3D::constrain( const Vec3D & min, const Vec3D & max )
{
	this->x = toxi::math::MathUtils::clip(this->x, min.x, max.x);
	this->y = toxi::math::MathUtils::clip(this->y, min.y, max.y);
	this->z = toxi::math::MathUtils::clip(this->z, min.z, max.z);
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::normalize( void )
{
	float mag = (float)toxi::math::MathUtils::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	if (mag > 0) {
		mag = 1.0f / mag;
		this->x *= mag;
		this->y *= mag;
		this->z *= mag;
	}
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::normalizeTo( const double & len )
{
	double mag = toxi::math::MathUtils::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	if (mag > 0) {
		mag = len / mag;
		this->x *= mag;
		this->y *= mag;
		this->z *= mag;
	}
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::min( const Vec3D & a, const Vec3D & b )
{
	return Vec3D( toxi::math::MathUtils::min( a.x, b.x ), toxi::math::MathUtils::min( a.y,
		b.y ), toxi::math::MathUtils::min( a.z, b.z ) );
}

toxi::geom::Vec3D toxi::geom::Vec3D::max( const Vec3D & a, const Vec3D & b )
{
	return Vec3D( toxi::math::MathUtils::max( a.x, b.x ), toxi::math::MathUtils::max( a.y,
		b.y ), toxi::math::MathUtils::max( a.z, b.z ) );
}

toxi::geom::Vec3D toxi::geom::Vec3D::scaleSelf( const float & s )
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::max_value()
{
	return Vec3D(FLT_MAX, FLT_MAX, FLT_MAX);
}

toxi::geom::Vec3D toxi::geom::Vec3D::min_value()
{
	return Vec3D(FLT_MIN, FLT_MIN, FLT_MIN);
}

toxi::geom::Vec3D toxi::geom::Vec3D::maxSelf( const Vec3D & v )
{
	this->x = toxi::math::MathUtils::max( this->x, v.x );
	this->y = toxi::math::MathUtils::max( this->y, v.y );
	this->z = toxi::math::MathUtils::max( this->z, v.z );
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::minSelf( const Vec3D & v )
{
	this->x = toxi::math::MathUtils::min( this->x, v.x );
	this->y = toxi::math::MathUtils::min( this->y, v.y );
	this->z = toxi::math::MathUtils::min( this->z, v.z );
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::X_AXIS()
{
	return Vec3D( 1, 0, 0 );
}

toxi::geom::Vec3D toxi::geom::Vec3D::Y_AXIS()
{
	return Vec3D( 0, 1, 0 );
}

toxi::geom::Vec3D toxi::geom::Vec3D::Z_AXIS()
{
	return Vec3D( 0, 0, 1 );
}

toxi::geom::Vec3D toxi::geom::Vec3D::set( const Vec3D & v )
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::set( const float & x, const float & y, const float & z )
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::set( const double & x, const double & y, const double & z )
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

std::string toxi::geom::Vec3D::toString()
{
	std::stringstream ss;
	ss << "{x:" << this->x << ", y:" << this->y << ", z:" << this->z << "}";
	return ss.str( );
}

toxi::geom::Vec3D toxi::geom::Vec3D::addSelf( const Vec3D & v )
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::addSelf( const float & a, const float & b, const float & c )
{
	this->x += a;
	this->y += b;
	this->z += c;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::clear()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::crossSelf( const Vec3D & v )
{
	double cx = y * v.z - v.y * z;
	double cy = z * v.x - v.z * x;
	this->z = x * v.y - v.x * y;
	this->y = cy;
	this->x = cx;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::subSelf( const float & a, const float & b, const float & c )
{
	this->x -= a;
	this->y -= b;
	this->z -= c;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::subSelf( const Vec3D & _v )
{
	this->x -= _v.x;
	this->y -= _v.y;
	this->z -= _v.z;
	return *this;
}

int toxi::geom::Vec3D::hashCode()
{
	long bits = 1;
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits( static_cast< float > ( x ));
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits(static_cast< float > ( y ));
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits(static_cast< float > ( z ));
	return (int ) ( bits ^ ( bits >> 16 ) );
}

toxi::geom::Vec3D toxi::geom::Vec3D::invert()
{
	this->x *= -1;
	this->y *= -1;
	this->z *= -1;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::interpolateToSelf( const Vec3D & v, const float & f )
{
	this->x += (v.x - this->x) * f;
	this->y += (v.y - this->y) * f;
	this->z += (v.z - this->z) * f;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::limit( float lim )
{
	if ( magSquared() > lim * lim ) {
		return normalize().scaleSelf( lim );
	}
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::reciprocal()
{
	this->x = 1.0 / x;
	this->y = 1.0 / y;
	this->z = 1.0 / z;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::reflect( const Vec3D & normal )
{
	return set(normal.scale(this->dot(normal) * 2).subSelf( *this));
}

toxi::geom::Vec3D toxi::geom::Vec3D::rotateZ( const float & theta )
{
	double co = toxi::math::MathUtils::cos(theta);
	double si = toxi::math::MathUtils::sin(theta);
	double xx = co * x - si * y;
	y = si * x + co * y;
	x = xx;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::rotateY( const float & theta )
{
	double co = toxi::math::MathUtils::cos(theta);
	double si = toxi::math::MathUtils::sin(theta);
	double xx = co * x - si * z;
	z = si * x + co * z;
	x = xx;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::rotateX( const float & theta )
{
	double co = toxi::math::MathUtils::cos(theta);
	double si = toxi::math::MathUtils::sin(theta);
	double zz = co * z - si * y;
	y = si * z + co * y;
	z = zz;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::rotateAroundAxis( const Vec3D & axis, const float & theta )
{
	double ax = axis.x;
	double ay = axis.y;
	double az = axis.z;
	double ux = ax * x;
	double uy = ax * y;
	double uz = ax * z;
	double vx = ay * x;
	double vy = ay * y;
	double vz = ay * z;
	double wx = az * x;
	double wy = az * y;
	double wz = az * z;
	double si = toxi::math::MathUtils::sin(theta);
	double co = toxi::math::MathUtils::cos(theta);
	double xx = (float) (ax * (ux + vy + wz)
		+ (x * (ay * ay + az * az) - ax * (vy + wz)) * co + (-wy + vz)
		* si);
	double yy = (float) (ay * (ux + vy + wz)
		+ (y * (ax * ax + az * az) - ay * (ux + wz)) * co + (wx - uz)
		* si);
	double zz = (float) (az * (ux + vy + wz)
		+ (z * (ax * ax + ay * ay) - az * (ux + vy)) * co + (-vx + uy)
		* si);
	x = xx;
	y = yy;
	z = zz;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::roundTo( const double & prec )
{
	this->x = toxi::math::MathUtils::roundTo(this->x, prec);
	this->y = toxi::math::MathUtils::roundTo(this->y, prec);
	this->z = toxi::math::MathUtils::roundTo(this->z, prec);
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::toSpherical()
{
	double xx = toxi::math::MathUtils::abs(x) <= toxi::math::MathUtils::EPS ? toxi::math::MathUtils::EPS : x;
	double zz = z;

	float radius = (float) toxi::math::MathUtils::sqrt((xx * xx) + (y * y) + (zz * zz));
	z = (float) std::asin(y / radius);
	y = (float) std::atan(zz / xx) + (xx < 0.0 ? toxi::math::MathUtils::PI : 0);
	x = radius;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::signum()
{
	this->x = (x < 0 ? -1 : x == 0 ? 0 : 1);
	this->y = (y < 0 ? -1 : y == 0 ? 0 : 1);
	this->z = (z < 0 ? -1 : z == 0 ? 0 : 1);
	return *this;
}

void toxi::geom::Vec3D::setX( const double & _x )
{
	this->x = _x;
}

void toxi::geom::Vec3D::setY( const double & _y )
{
this->y = _y;
}

void toxi::geom::Vec3D::setZ( const double & _z )
{
	this->z = _z;
}
