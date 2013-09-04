#include "Vec3D.h"


toxi::geom::Vec3D::Vec3D(void)
{
}

toxi::geom::Vec3D::Vec3D(float x, float y, float z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}

toxi::geom::Vec3D::Vec3D( int x, int y, int z )
{
	this->x = static_cast< float > ( x );
	this->y = static_cast< float > ( y );
	this->z = static_cast< float > ( z );
}

toxi::geom::Vec3D::Vec3D( double x, double y, double z )
{
	this->x = static_cast< float > ( x );
	this->y = static_cast< float > ( y );
	this->z = static_cast< float > ( z );
}

toxi::geom::Vec3D::~Vec3D(void)
{
}

toxi::geom::Vec3D toxi::geom::Vec3D::add( double _a, double _b, double _c )
{
	this->x += _a;
	this->y += _b;
	this->z += _c;
	return *this;
}

toxi::geom::Vec3D * toxi::geom::Vec3D::add( Vec3D * v )
{
	this->x += v->x;
	this->y += v->y;
	this->z += v->z;
	return this;
}

float toxi::geom::Vec3D::angleBetween( Vec3D * v )
{
	return std::acos(dot(v));
}

float toxi::geom::Vec3D::angleBetween( Vec3D * v, bool forceNormalize )
{
	float theta;
	if (forceNormalize) {
		theta = getNormalized().dot(&v->getNormalized());
	} else {
		theta = dot(v);
	}
	return std::acos(theta);
}

int toxi::geom::Vec3D::compareTo( Vec3D * v )
{
	if ( x == v->x && y == v->y && z == v->z ) {
		return 0;
	}
	float a = magSquared();
	float b = v->magSquared();
	if (a < b) {
		return -1;
	}
	return +1;
}

toxi::geom::Vec3D toxi::geom::Vec3D::copy()
{
	return Vec3D( this->x, this->y, this->z );
}

toxi::geom::Vec3D toxi::geom::Vec3D::cross( Vec3D * v )
{
	return Vec3D(y * v->z - v->y * z, z * v->x - v->z * x, x
		* v->y - v->x * y);
}

toxi::geom::Vec3D toxi::geom::Vec3D::crossInto( Vec3D * v)
{
	Vec3D result;
	float vx = v->x;
	float vy = v->y;
	float vz = v->z;
	result.x = this->y * vz - vy * this->z;
	result.y = this->z * vx - vz * this->x;
	result.z = this->x * vy - vx * this->y;
	return result;
}

float toxi::geom::Vec3D::distanceTo( Vec3D * v )
{
	float dx = this->x - v->x;
	float dy = this->y - v->y;
	float dz = this->z - v->z;
	return (float) toxi::math::MathUtils::sqrt(dx * dx + dy * dy + dz * dz);
}

float toxi::geom::Vec3D::distanceToSquared( Vec3D * v )
{
	float dx = this->x - v->x;
	float dy = this->y - v->y;
	float dz = this->z - v->z;
	return dx * dx + dy * dy + dz * dz;
}

float toxi::geom::Vec3D::dot( Vec3D * v )
{
	return this->x * v->x + this->y * v->y + this->z * v->z;
}

bool toxi::geom::Vec3D::equals( Vec3D * vv )
{
	return (this->x == vv->x && this->y == vv->y && this->z == vv->z );
}

bool toxi::geom::Vec3D::equalsWithTolerance( Vec3D * v, float tolerance )
{
	float diff = this->x - v->x;
	if (toxi::math::MathUtils::isNan(diff)) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	diff = this->y - v->y;
	if (toxi::math::MathUtils::isNan(diff)) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	diff = this->z - v->z;
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

toxi::geom::Axis3D * toxi::geom::Vec3D::getClosestAxis()
{
	float ax = toxi::math::MathUtils::abs(this->x);
	float ay = toxi::math::MathUtils::abs(this->y);
	float az = toxi::math::MathUtils::abs(this->z);
	if (ax > ay && ax > az) {
		return toxi::geom::Axis3D::X_AXIS();
	}
	if (ay > ax && ay > az) {
		return toxi::geom::Axis3D::Y_AXIS();
	}
	if (az > ax && az > ay) {
		return toxi::geom::Axis3D::Z_AXIS();
	}
	return new toxi::geom::Axis3D(new Vec3D(0, 0, 0));
}

float toxi::geom::Vec3D::getComponent( int id )
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

toxi::geom::Vec3D toxi::geom::Vec3D::getConstrained( AABB * box )
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

toxi::geom::Vec3D toxi::geom::Vec3D::getLimited( float lim )
{
	if (magSquared() > lim * lim) {
		return getNormalizedTo(lim);
	}
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::getMapped( toxi::math::ScaleMap * map )
{
	return Vec3D(map->getClippedValueFor(this->x),
		map->getClippedValueFor(this->y),
		map->getClippedValueFor(this->z));
}

toxi::geom::Vec3D toxi::geom::Vec3D::getNormalized()
{
	return this->normalize();
}

toxi::geom::Vec3D toxi::geom::Vec3D::getNormalizedTo( float len )
{
	return this->normalizeTo( len );
}

toxi::geom::Vec3D toxi::geom::Vec3D::getReciprocal()
{
	return copy().reciprocal();
}

toxi::geom::Vec3D toxi::geom::Vec3D::getReflected( Vec3D *normal )
{
	return copy().reflect( normal );
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedAroundAxis( Vec3D * axis, float theta )
{
	return copy().rotateAroundAxis(axis, theta );
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedX( float theta )
{
	return copy().rotateX(theta);
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedY( float theta )
{
	return copy().rotateY(theta);
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedZ( float theta )
{
	return copy().rotateZ(theta);
}

toxi::geom::Vec3D toxi::geom::Vec3D::getRoundedTo( float prec )
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

toxi::geom::Vec3D toxi::geom::Vec3D::interpolateTo( Vec3D * v, float f )
{
	return Vec3D(x + (v->x - x) * f, y + (v->y - y) * f, z
		+ (v->z - z) * f);
}

toxi::geom::Vec3D toxi::geom::Vec3D::interpolateTo( toxi::geom::Vec3D * v, float f, toxi::math::InterpolateStrategy * s )
{
	return Vec3D(s->interpolate(x, v->x, f),
		s->interpolate(y, v->y, f), s->interpolate(z, v->z, f));
}

bool toxi::geom::Vec3D::isInAABB( toxi::geom::AABB * box )
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

bool toxi::geom::Vec3D::isInAABB( Vec3D * boxOrigin, Vec3D * boxExtent )
{
	float w = boxExtent->x;
	if (x < boxOrigin->x - w || x > boxOrigin->x + w) {
		return false;
	}
	w = boxExtent->y;
	if (y < boxOrigin->y - w || y > boxOrigin->y + w) {
		return false;
	}
	w = boxExtent->z;
	if (z < boxOrigin->z - w || z > boxOrigin->z + w) {
		return false;
	}
	return true;
}

bool toxi::geom::Vec3D::isMajorAxis( float tolerance )
{
	float ax = toxi::math::MathUtils::abs(x);
	float ay = toxi::math::MathUtils::abs(y);
	float az = toxi::math::MathUtils::abs(z);
	float itol = 1 - tolerance;
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

float toxi::geom::Vec3D::magSquared()
{
	return x * x + y * y + z * z;
}

toxi::geom::Vec3D toxi::geom::Vec3D::scale( float s )
{
	return Vec3D(x * s, y * s, z * s);
}

toxi::geom::Vec3D toxi::geom::Vec3D::scale( float a, float b, float c )
{
	return Vec3D(x * a, y * b, z * c);
}

toxi::geom::Vec3D toxi::geom::Vec3D::scale( Vec3D * s )
{
	return Vec3D(x * s->x, y * s->y, z * s->z);
}

toxi::geom::Vec3D toxi::geom::Vec3D::sub( float a, float b, float c )
{
	return Vec3D(x - a, y - b, z - c);
}

toxi::geom::Vec3D toxi::geom::Vec3D::sub( Vec3D * v )
{
	return Vec3D(x - v->x, y - v->y, z - v->z);
}

toxi::geom::Vec2D toxi::geom::Vec3D::to2DXY()
{
	return Vec2D( x, y );
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

toxi::geom::Vec4D toxi::geom::Vec3D::to4D( float w )
{
	return Vec4D( x, y, z, w );
}

void toxi::geom::Vec3D::toArray( float& arr )
{
	// TODO
}

void toxi::geom::Vec3D::toArray4( float& arr, float w )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::constrain( toxi::geom::AABB * box )
{
	//TODO
	//return constrain(box->getMin(), box->getMax());
}

toxi::geom::Vec3D toxi::geom::Vec3D::constrain( Vec3D * min, Vec3D * max )
{
	this->x = toxi::math::MathUtils::clip(this->x, min->x, max->x);
	this->y = toxi::math::MathUtils::clip(this->y, min->y, max->y);
	this->z = toxi::math::MathUtils::clip(this->z, min->z, max->z);
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::normalize( void )
{
	float mag = (float)toxi::math::MathUtils::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	if (mag > 0) {
		mag = 1.0 / mag;
		this->x *= mag;
		this->y *= mag;
		this->z *= mag;
	}
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::normalizeTo( double len )
{
	float mag = (float) toxi::math::MathUtils::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	if (mag > 0) {
		mag = len / mag;
		this->x *= mag;
		this->y *= mag;
		this->z *= mag;
	}
	return *this;
}

toxi::geom::Vec3D * toxi::geom::Vec3D::min( Vec3D * a, Vec3D * b )
{
	return new Vec3D( toxi::math::MathUtils::min( a->x, b->x ), toxi::math::MathUtils::min( a->y,
		b->y ), toxi::math::MathUtils::min( a->z, b->z ) );
}

toxi::geom::Vec3D * toxi::geom::Vec3D::max( Vec3D * a, Vec3D * b )
{
	return new Vec3D( toxi::math::MathUtils::max( a->x, b->x ), toxi::math::MathUtils::max( a->y,
		b->y ), toxi::math::MathUtils::max( a->z, b->z ) );
}

toxi::geom::Vec3D toxi::geom::Vec3D::scaleSelf( float s )
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

toxi::geom::Vec3D toxi::geom::Vec3D::maxSelf( Vec3D * v )
{
	this->x = toxi::math::MathUtils::max( this->x, v->x );
	this->y = toxi::math::MathUtils::max( this->y, v->y );
	this->z = toxi::math::MathUtils::max( this->z, v->z );
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::minSelf( Vec3D * v )
{
	this->x = toxi::math::MathUtils::min( this->x, v->x );
	this->y = toxi::math::MathUtils::min( this->y, v->y );
	this->z = toxi::math::MathUtils::min( this->z, v->z );
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

toxi::geom::Vec3D toxi::geom::Vec3D::set( Vec3D * v )
{
	this->x = v->x;
	this->y = v->y;
	this->z = v->z;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::set( float x, float y, float z )
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::set( double x, double y, double z )
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

toxi::geom::Vec3D toxi::geom::Vec3D::addSelf( Vec3D * v )
{
	this->x += v->x;
	this->y += v->y;
	this->z += v->z;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::addSelf( float a, float b, float c )
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

toxi::geom::Vec3D toxi::geom::Vec3D::crossSelf( Vec3D * v )
{
	float cx = y * v->z - v->y * z;
	float cy = z * v->x - v->z * x;
	this->z = x * v->y - v->x * y;
	this->y = cy;
	this->x = cx;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::subSelf( float a, float b, float c )
{
	this->x -= a;
	this->y -= b;
	this->z -= c;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::subSelf( Vec3D * _v )
{
	this->x -= _v->x;
	this->y -= _v->y;
	this->z -= _v->z;
	return *this;
}

int toxi::geom::Vec3D::hashCode()
{
	long bits = 1;
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits(x);
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits(y);
	bits = 31L * bits + toxi::geom::VecMathUtil::floatToIntBits(z);
	return (int ) ( bits ^ ( bits >> 32 ) );
}

toxi::geom::Vec3D toxi::geom::Vec3D::invert()
{
	this->x *= -1;
	this->y *= -1;
	this->z *= -1;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::interpolateToSelf( Vec3D * v, float f )
{
	this->x += (v->x - this->x) * f;
	this->y += (v->y - this->y) * f;
	this->z += (v->z - this->z) * f;
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

toxi::geom::Vec3D toxi::geom::Vec3D::reflect( Vec3D * normal )
{
	return set(&normal->scale(this->dot(normal) * 2).subSelf(this));
}

toxi::geom::Vec3D toxi::geom::Vec3D::rotateZ( float theta )
{
	float co = (float) toxi::math::MathUtils::cos(theta);
	float si = (float) toxi::math::MathUtils::sin(theta);
	float xx = co * x - si * y;
	y = si * x + co * y;
	x = xx;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::rotateY( float theta )
{
	float co = (float) toxi::math::MathUtils::cos(theta);
	float si = (float) toxi::math::MathUtils::sin(theta);
	float xx = co * x - si * z;
	z = si * x + co * z;
	x = xx;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::rotateX( float theta )
{
	float co = (float) toxi::math::MathUtils::cos(theta);
	float si = (float) toxi::math::MathUtils::sin(theta);
	float zz = co * z - si * y;
	y = si * z + co * y;
	z = zz;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::rotateAroundAxis( Vec3D* axis, float theta )
{
	float ax = axis->x;
	float ay = axis->y;
	float az = axis->z;
	float ux = ax * x;
	float uy = ax * y;
	float uz = ax * z;
	float vx = ay * x;
	float vy = ay * y;
	float vz = ay * z;
	float wx = az * x;
	float wy = az * y;
	float wz = az * z;
	double si = toxi::math::MathUtils::sin(theta);
	double co = toxi::math::MathUtils::cos(theta);
	float xx = (float) (ax * (ux + vy + wz)
		+ (x * (ay * ay + az * az) - ax * (vy + wz)) * co + (-wy + vz)
		* si);
	float yy = (float) (ay * (ux + vy + wz)
		+ (y * (ax * ax + az * az) - ay * (ux + wz)) * co + (wx - uz)
		* si);
	float zz = (float) (az * (ux + vy + wz)
		+ (z * (ax * ax + ay * ay) - az * (ux + vy)) * co + (-vx + uy)
		* si);
	x = xx;
	y = yy;
	z = zz;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::roundTo( float prec )
{
	this->x = toxi::math::MathUtils::roundTo(this->x, prec);
	this->y = toxi::math::MathUtils::roundTo(this->y, prec);
	this->z = toxi::math::MathUtils::roundTo(this->z, prec);
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::toSpherical()
{
	float xx = toxi::math::MathUtils::abs(x) <= toxi::math::MathUtils::EPS ? toxi::math::MathUtils::EPS : x;
	float zz = z;

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
