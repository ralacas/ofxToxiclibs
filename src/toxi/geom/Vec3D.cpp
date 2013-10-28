#include "Vec3D.h"
#include "Axis3D.h"
#include "Vec2D.h"
#include "Vec4D.h"
#include "VecMathUtil.h"
#include "AABB.h"

toxi::geom::Vec3D::Vec3D(void)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
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
	this->x = x;
	this->y = y;
	this->z = z;
}

toxi::geom::Vec3D::Vec3D( const toxi::geom::Vec3D & v )
{
	this->x = v.getX();
	this->y = v.getY();
	this->z = v.getZ();
}

toxi::geom::Vec3D::~Vec3D(void)
{
}

toxi::geom::Vec3D toxi::geom::Vec3D::add( const double & _a, const double & _b, const double & _c )
{
	return Vec3D( _a, _b, _c );
}

toxi::geom::Vec3D toxi::geom::Vec3D::add( const Vec3D & v )
{
	return Vec3D( v.getX(), v.getY(), v.getZ() );
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
	if ( x == v.getX() && y == v.getY() && z == v.getZ() ) {
		return 0;
	}
	float a = magSquared();
	float b = v.magSquared();
	if (a < b) {
		return -1;
	}
	return +1;
}

toxi::geom::Vec3D toxi::geom::Vec3D::crossInto( const Vec3D & v)
{
	Vec3D result;
	double vx = v.getX();
	double vy = v.getY();
	double vz = v.getZ();
	result.x = this->y * vz - vy * this->z;
	result.y = this->z * vx - vz * this->x;
	result.z = this->x * vy - vx * this->y;
	return result;
}

double toxi::geom::Vec3D::distanceTo( const Vec3D & v )
{
	double dx = this->x - v.getX();
	double dy = this->y - v.getY();
	double dz = this->z - v.getZ();
	return toxi::math::MathUtils::sqrt(dx * dx + dy * dy + dz * dz);
}

double toxi::geom::Vec3D::distanceToSquared( const Vec3D & v )
{
	double dx = this->x - v.getX();
	double dy = this->y - v.getY();
	double dz = this->z - v.getZ();
	return dx * dx + dy * dy + dz * dz;
}

float toxi::geom::Vec3D::dot( const toxi::geom::Vec3D & v ) const
{
	return static_cast< float > ( this->x * v.getX() + this->y * v.getY() + this->z * v.getZ() );
}

bool toxi::geom::Vec3D::equals( const Vec3D & vv )
{
	return (this->x == vv.getX() && this->y == vv.getY() && this->z == vv.getZ() );
}

bool toxi::geom::Vec3D::equalsWithTolerance( const Vec3D & v, const float & tolerance )
{
	double diff = this->x - v.getX();
	if (toxi::math::MathUtils::isNan(diff)) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	diff = this->y - v.getY();
	if (toxi::math::MathUtils::isNan(diff)) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	diff = this->z - v.getZ();
	if (toxi::math::MathUtils::isNan(diff)) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	return true;
}

toxi::geom::Vec3D toxi::geom::Vec3D::abs()
{
	this->x = toxi::math::MathUtils::abs(this->x);
	this->y = toxi::math::MathUtils::abs(this->y);
	this->z = toxi::math::MathUtils::abs(this->z);
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::cartesian()
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

toxi::geom::Vec3D toxi::geom::Vec3D::floor()
{
	this->x = toxi::math::MathUtils::floor( this->x );
	this->y = toxi::math::MathUtils::floor( this->y );
	this->z = toxi::math::MathUtils::floor( this->z );
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::frac()
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
	Vec3D v = Vec3D( *this );
	if (v.magSquared() > lim * lim) {
		return v.getNormalizedTo(lim);
	}
	return v;
}

toxi::geom::Vec3D toxi::geom::Vec3D::getMapped( const toxi::math::ScaleMap & map )
{
	return Vec3D(map.getClippedValueFor(this->x),
		map.getClippedValueFor(this->y),
		map.getClippedValueFor(this->z));
}

toxi::geom::Vec3D toxi::geom::Vec3D::getNormalized()
{
	return Vec3D( *this ).normalize();
}

toxi::geom::Vec3D toxi::geom::Vec3D::getNormalizedTo( const float & len )
{
	return  Vec3D( *this ).normalizeTo( len );
}

toxi::geom::Vec3D toxi::geom::Vec3D::getReciprocal()
{
	return Vec3D( *this).reciprocal();
}

toxi::geom::Vec3D toxi::geom::Vec3D::getReflected( const Vec3D & normal )
{
	return Vec3D( *this).reflect( normal );
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedAroundAxis( const Vec3D & axis, const float & theta )
{
	return Vec3D( *this).rotateAroundAxis(axis, theta );
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedX( const float & theta )
{
	return Vec3D( *this).rotateX(theta);
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedY( const float & theta )
{
	return Vec3D( *this).rotateY(theta);
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedZ( const float & theta )
{
	return Vec3D( *this).rotateZ(theta);
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRoundedTo( const float & prec )
{
	return Vec3D( *this).roundTo(prec);
}

toxi::geom::Vec3D toxi::geom::Vec3D::getSignum()
{
	return Vec3D( *this).signum();
}

toxi::geom::Vec3D toxi::geom::Vec3D::getSpherical()
{
	return Vec3D( *this).toSpherical();
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
	return Vec3D(x + (v.getX() - x) * f, y + (v.getY() - y) * f, z
		+ (v.getZ() - z) * f);
}

toxi::geom::Vec3D toxi::geom::Vec3D::interpolateTo( const toxi::geom::Vec3D & v, const double & f, toxi::math::InterpolateStrategy * s )
{
	return Vec3D(s->interpolate(x, v.getX(), f),
		s->interpolate(y, v.getY(), f), s->interpolate(z, v.getZ(), f));
}

bool toxi::geom::Vec3D::isInAABB( const  toxi::geom::AABB & box )
{
	//TODO
	Vec3D min = Vec3D(); //box->getMin();
	Vec3D max = Vec3D();// box->getMax();
	if (x < min.getX() || x > max.getX()) {
		return false;
	}
	if (y < min.getY() || y > max.getY()) {
		return false;
	}
	if (z < min.getZ() || z > max.getZ()) {
		return false;
	}
	return true;
}

bool toxi::geom::Vec3D::isInAABB( const Vec3D & boxOrigin, const Vec3D & boxExtent )
{
	double w = boxExtent.getX();
	if (x < boxOrigin.getX() - w || x > boxOrigin.getX() + w) {
		return false;
	}
	w = boxExtent.getY();
	if (y < boxOrigin.getY() - w || y > boxOrigin.getY() + w) {
		return false;
	}
	w = boxExtent.getZ();
	if (z < boxOrigin.getZ() - w || z > boxOrigin.getZ() + w) {
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

bool toxi::geom::Vec3D::isZeroVector() const
{
	return toxi::math::MathUtils::abs( x ) < toxi::math::MathUtils::EPS
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
	return Vec3D(x * s.getX(), y * s.getY(), z * s.getZ());
}

toxi::geom::Vec3D toxi::geom::Vec3D::sub( const float & a, const float & b, const float & c )
{
	return Vec3D(x - a, y - b, z - c);
}

toxi::geom::Vec3D toxi::geom::Vec3D::sub( const Vec3D & v )
{
	return Vec3D(x - v.getX(), y - v.getY(), z - v.getZ());
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

std::vector< double> toxi::geom::Vec3D::toVector()
{
	std::vector< double > vector;
	vector.push_back( this->getX() );
	vector.push_back( this->getY() );
	vector.push_back( this->getZ() );
	return vector;
}

void toxi::geom::Vec3D::toArray4( const float & arr, const float & w )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::constrain( const toxi::geom::AABB & box )
{
	return constrain(box.getMin(), box.getMax());
}

toxi::geom::Vec3D toxi::geom::Vec3D::constrain( const Vec3D & min, const Vec3D & max )
{
	this->x = toxi::math::MathUtils::clip(this->x, min.getX(), max.getX());
	this->y = toxi::math::MathUtils::clip(this->y, min.getY(), max.getY());
	this->z = toxi::math::MathUtils::clip(this->z, min.getZ(), max.getZ());
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
	return Vec3D( toxi::math::MathUtils::min( a.getX(), b.getX() ), toxi::math::MathUtils::min( a.getY(),
		b.getY() ), toxi::math::MathUtils::min( a.getZ(), b.getZ() ) );
}

toxi::geom::Vec3D toxi::geom::Vec3D::max( const Vec3D & a, const Vec3D & b )
{
	return Vec3D( toxi::math::MathUtils::max( a.getX(), b.getX() ), toxi::math::MathUtils::max( a.getY(),
		b.getY() ), toxi::math::MathUtils::max( a.getZ(), b.getZ() ) );
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
	return Vec3D(DBL_MAX, DBL_MAX, DBL_MAX);
}

toxi::geom::Vec3D toxi::geom::Vec3D::min_value()
{
	return Vec3D(DBL_MIN, DBL_MIN, DBL_MIN);
}

toxi::geom::Vec3D toxi::geom::Vec3D::maxSelf( const Vec3D & v )
{
	this->x = toxi::math::MathUtils::max( this->x, v.getX() );
	this->y = toxi::math::MathUtils::max( this->y, v.getY() );
	this->z = toxi::math::MathUtils::max( this->z, v.getZ() );
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::minSelf( const Vec3D & v )
{
	this->x = toxi::math::MathUtils::min( this->x, v.getX() );
	this->y = toxi::math::MathUtils::min( this->y, v.getY() );
	this->z = toxi::math::MathUtils::min( this->z, v.getZ() );
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
	this->x = v.getX();
	this->y = v.getY();
	this->z = v.getZ();
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

toxi::geom::Vec3D toxi::geom::Vec3D::addSelf( const Vec3D & v )
{
	this->x += v.getX();
	this->y += v.getY();
	this->z += v.getZ();
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
	double cx = y * v.getZ() - v.getY() * z;
	double cy = z * v.getX() - v.getZ() * x;
	this->z = x * v.getY() - v.getX() * y;
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
	this->x -= _v.getX();
	this->y -= _v.getY();
	this->z -= _v.getZ();
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
	this->x += (v.getX() - this->x) * f;
	this->y += (v.getY() - this->y) * f;
	this->z += (v.getZ() - this->z) * f;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::limit( const float & lim )
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
	this->y = si * x + co * y;
	this->x = xx;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::rotateY( const float & theta )
{
	double co = toxi::math::MathUtils::cos(theta);
	double si = toxi::math::MathUtils::sin(theta);
	double xx = co * x - si * z;
	this->z = si * x + co * z;
	this->x = xx;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::rotateX( const float & theta )
{
	double co = toxi::math::MathUtils::cos(theta);
	double si = toxi::math::MathUtils::sin(theta);
	double zz = co * z - si * y;
	this->y = si * z + co * y;
	this->z = zz;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::rotateAroundAxis( const Vec3D & axis, const float & theta )
{
	double ax = axis.getX();
	double ay = axis.getY();
	double az = axis.getZ();
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
	this->x = xx;
	this->y = yy;
	this->z = zz;
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
	this->z = (float) std::asin(y / radius);
	this->y = (float) std::atan(zz / xx) + (xx < 0.0 ? toxi::math::MathUtils::PI : 0);
	this->x = radius;
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

double toxi::geom::Vec3D::getX() const
{
	return x;
}

double toxi::geom::Vec3D::getY() const
{
	return y;
}

double toxi::geom::Vec3D::getZ() const
{
	return z;
}

bool toxi::geom::Vec3D::isRightAroundThis( double val, double goal )
{
	bool ret;

	if( val >= 0.0 ) 
	{
		ret = ( val >= (goal - 0.01) && val <= (goal += 0.01) ) ? true : false;
	}
	else 
	{
		ret = ( val >= (goal - 0.01) && val <= (goal += 0.01) ) ? true : false;
	}


	return ret;
}

toxi::geom::Vec3D toxi::geom::Vec3D::getCrossed( const  Vec3D & v )
{
	Vec3D _v = Vec3D();
	_v.setX( getY() * v.getZ() - v.getY() * getZ() );
	_v.setY( getZ() * v.getX() - v.getZ() * getX() );
	_v.setZ( getX() * v.getY() - v.getX() * getY() );
	return _v;
}

toxi::geom::Vec3D toxi::geom::Vec3D::cross( const Vec3D & v )
{
	this->setX( getY() * v.getZ() - v.getY() * getZ() );
	this->setY( getZ() * v.getX() - v.getZ() * getX() );
	this->setZ( getX() * v.getY() - v.getX() * getY() );
	return *this;
}
