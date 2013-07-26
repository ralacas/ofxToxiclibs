#include "Vec3D.h"


toxi::geom::Vec3D::Vec3D(void)
{
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

toxi::geom::Vec3D toxi::geom::Vec3D::add( Vec3D v )
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

float toxi::geom::Vec3D::angleBetween( Vec3D v )
{
	return std::acos(dot(v));
}

float toxi::geom::Vec3D::angleBetween( Vec3D v, bool forceNormalize )
{
	float theta;
	if (forceNormalize) {
		theta = getNormalized().dot(v.getNormalized());
	} else {
		theta = dot(v);
	}
	return std::acos(theta);
}

int toxi::geom::Vec3D::compareTo( Vec3D v )
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

toxi::geom::Vec3D toxi::geom::Vec3D::cross( Vec3D v )
{
	return Vec3D(y * v.z - v.y * z, z * v.x - v.z * x, x
		* v.y - v.x * y);
}

toxi::geom::Vec3D toxi::geom::Vec3D::crossInto( Vec3D v)
{
	Vec3D result;
	float vx = v.x();
	float vy = v.y();
	float vz = v.z();
	result.x = this->y * vz - vy * this->z;
	result.y = this->z * vx - vz * this->x;
	result.z = this->x * vy - vx * this->y;
	return result;
}

float toxi::geom::Vec3D::distanceTo( Vec3D v )
{
	float dx = this->x - v.x();
	float dy = this->y - v.y();
	float dz = this->z - v.z();
	return (float) toxi::math::MathUtils::sqrt(dx * dx + dy * dy + dz * dz);
}

float toxi::geom::Vec3D::distanceToSquared( Vec3D v )
{
	float dx = this->x - v.x();
	float dy = this->y - v.y();
	float dz = this->z - v.z();
	return dx * dx + dy * dy + dz * dz;
}

float toxi::geom::Vec3D::dot( Vec3D v )
{
	return this->x * v.x() + this->y * v.y() + this->z * v.z();
}

bool toxi::geom::Vec3D::equals( Vec3D vv )
{
	return (this->x == vv.x() && this->y == vv.y() && this->z == vv.z());
}

bool toxi::geom::Vec3D::equalsWithTolerance( Vec3D v, float tolerance )
{
	float diff = this->x - v.x();
	if (toxi::math::MathUtils::isNan(diff)) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	diff = this->sy - v.y();
	if (toxi::math::MathUtils::isNan(diff)) {
		return false;
	}
	if ((diff < 0 ? -diff : diff) > tolerance) {
		return false;
	}
	diff = this->z - v.z();
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
	float ax = toxi::math::MathUtils::abs(this->x);
	float ay = toxi::math::MathUtils::abs(this->y);
	float az = toxi::math::MathUtils::abs(this->z);
	if (ax > ay && ax > az) {
		return toxi::geom::Axis3D::X_AXIS;
	}
	if (ay > ax && ay > az) {
		return toxi::geom::Axis3D::Y_AXIS;
	}
	if (az > ax && az > ay) {
		return toxi::geom::Axis3D::Z_AXIS;
	}
	return Axis3D(Vec3D(0, 0, 0));
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

toxi::geom::Vec3D toxi::geom::Vec3D::getConstrained( AABB box )
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

toxi::geom::Vec3D toxi::geom::Vec3D::getMapped( toxi::math::ScaleMap map )
{
	return Vec3D(map.getClippedValueFor(this->x),
		map.getClippedValueFor(this->),
		map.getClippedValueFor(this->z));
}

toxi::geom::Vec3D toxi::geom::Vec3D::getNormalized()
{
	return normalize();
}

toxi::geom::Vec3D toxi::geom::Vec3D::getNormalizedTo( float len )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::getReciprocal()
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::getReflected( Vec3D normal )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedAroundAxis( Vec3D axis, float theta )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedX( float theta )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedY( float theta )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::getRotatedZ( float theta )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::getRoundedTo( float prec )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::getSignum()
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::getSpherical()
{

}

float toxi::geom::Vec3D::headingXY()
{

}

float toxi::geom::Vec3D::headingXZ()
{

}

float toxi::geom::Vec3D::headingYZ()
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::interpolateTo( Vec3D v, float f, toxi::math::InterpolateStrategy s )
{

}

bool toxi::geom::Vec3D::isInAABB( Vec3D boxOrigin, Vec3D boxExtent )
{

}

bool toxi::geom::Vec3D::isMajorAxis( float tolerance )
{

}

bool toxi::geom::Vec3D::isZeroVector()
{

}

float toxi::geom::Vec3D::magnitude()
{

}

float toxi::geom::Vec3D::magSquared()
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::scale( float s )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::scale( float a, float b, float c )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::scale( Vec3D s )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::sub( float a, float b, float c )
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::sub( Vec3D v )
{

}

toxi::geom::Vec2D toxi::geom::Vec3D::to2DXY()
{

}

toxi::geom::Vec2D toxi::geom::Vec3D::to2DXZ()
{

}

toxi::geom::Vec2D toxi::geom::Vec3D::to2DYZ()
{

}

toxi::geom::Vec4D toxi::geom::Vec3D::to4D()
{

}

toxi::geom::Vec4D toxi::geom::Vec3D::to4D( float w )
{

}

void toxi::geom::Vec3D::toArray( float& arr )
{

}

void toxi::geom::Vec3D::toArray4( float& arr, float w )
{

}

float toxi::geom::Vec3D::x()
{

}

float toxi::geom::Vec3D::y()
{

}

float toxi::geom::Vec3D::z()
{

}

toxi::geom::Vec3D toxi::geom::Vec3D::constrain( AABB box )
{
	return constrain(box.getMin(), box.getMax());
}

toxi::geom::Vec3D toxi::geom::Vec3D::constrain( Vec3D min, Vec3D max )
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

toxi::geom::Vec3D toxi::geom::Vec3D::min( Vec3D a, Vec3D b )
{
	return Vec3D( toxi::math::MathUtils::min( a.x(), b.x() ), toxi::math::MathUtils::min( a.y(),
		b.y() ), toxi::math::MathUtils::min( a.z(), b.z() ) );
}

toxi::geom::Vec3D toxi::geom::Vec3D::max( Vec3D a, Vec3D b )
{
	return Vec3D( toxi::math::MathUtils::max( a.x(), b.x() ), toxi::math::MathUtils::max( a.y(),
		b.y() ), toxi::math::MathUtils::max( a.z(), b.z() ) );
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

toxi::geom::Vec3D toxi::geom::Vec3D::maxSelf( Vec3D v )
{
	this->x = toxi::math::MathUtils::max( this->x, v.x() );
	this->y = toxi::math::MathUtils::max( this->y, v.y() );
	this->z = toxi::math::MathUtils::max( this->z, v.z() );
	return *this;
}

toxi::geom::Vec3D toxi::geom::Vec3D::minSelf( Vec3D v )
{
	this->x = toxi::math::MathUtils::min( this->x, v.x() );
	this->y = toxi::math::MathUtils::min( this->y, v.y() );
	this->z = toxi::math::MathUtils::min( this->z, v.z() );
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

toxi::geom::Vec3D toxi::geom::Vec3D::set( Vec3D v )
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
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
