#include "Line3D.h"
#include "Vec3D.h"
#include "LineIntersection.h"
#include "LineIntersection3D.h"
#include "AABB.h"

toxi::geom::Line3D::Line3D(void)
{
}

toxi::geom::Line3D::Line3D( const float & x1, const float & y1, const float & z1, const float & x2, const float & y2, const float & z2 )
{
	this->a = Vec3D( x1, y1, z1 );
	this->b = Vec3D( x2, y2, z2 );
}

toxi::geom::Line3D::Line3D( const toxi::geom::Vec3D & a, const toxi::geom::Vec3D & b )
{
	this->a = a;
	this->b = b;
}

toxi::geom::Line3D::~Line3D(void)
{
}

toxi::geom::LineIntersection3D toxi::geom::Line3D::closestLineTo(  toxi::geom::Line3D & l )
{
	Vec3D p43 = l.a.sub( l.b );
	if ( p43.isZeroVector() ) {
		return LineIntersection3D( LineIntersection3D::Type::NON_INTERSECTING );
	}
	Vec3D p21 = b.sub( a );
	if ( p21.isZeroVector() ) {
		return LineIntersection3D( LineIntersection3D::Type::NON_INTERSECTING );
	}
	Vec3D p13 = a.sub( l.a );

	double d1343 = p13.getX() * p43.getX() + p13.getY() * p43.getY() + p13.getZ() * p43.getZ();
	double d4321 = p43.getX() * p21.getX() + p43.getY() * p21.getY() + p43.getZ() * p21.getZ();
	double d1321 = p13.getX() * p21.getX() + p13.getY() * p21.getY() + p13.getZ() * p21.getZ();
	double d4343 = p43.getX() * p43.getX() + p43.getY() * p43.getY() + p43.getZ() * p43.getZ();
	double d2121 = p21.getX() * p21.getX() + p21.getY() * p21.getY() + p21.getZ() * p21.getZ();

	double denom = d2121 * d4343 - d4321 * d4321;
	if ( toxi::math::MathUtils::abs( denom ) < toxi::math::MathUtils::EPS ) {
		return toxi::geom::LineIntersection3D( LineIntersection3D::Type::NON_INTERSECTING );
	}
	double numer = d1343 * d4321 - d1321 * d4343;
	float mua = ( float ) ( numer / denom );
	float mub = ( float ) ( ( d1343 + d4321 * mua ) / d4343 );

	Vec3D pa = a.add( p21.scaleSelf( mua ) );
	Vec3D pb = l.a.add( p43.scaleSelf( mub ) );
	return  toxi::geom::LineIntersection3D( toxi::geom::LineIntersection3D::Type::INTERSECTING, Line3D(pa, pb), mua,
		mub);
}

toxi::geom::Vec3D toxi::geom::Line3D::closestPointTo( toxi::geom::Vec3D & p )
{
	Vec3D v = b.sub( a );
	float t = p.sub( a ).dot( v ) / v.magSquared();
	// Check to see if t is beyond the extents of the line segment
	if ( t < 0.0f ) {
		return Vec3D( a );
	} else if ( t > 1.0f ) {
		return Vec3D( b );
	}
	// Return the point between 'a' and 'b'
	return a.add( v.scaleSelf( t ) );
}

toxi::geom::AABB toxi::geom::Line3D::getBounds()
{
	return AABB( a, b );
}

toxi::geom::Vec3D toxi::geom::Line3D::getDirection()
{
	return b.sub( a ).normalize();
}

float toxi::geom::Line3D::getLength()
{
	return static_cast< float > ( a.distanceTo( b ) );
}

float toxi::geom::Line3D::getLengthSquared()
{
	return static_cast< float > ( a.distanceToSquared( b ) );
}

toxi::geom::Vec3D toxi::geom::Line3D::getMidPoint()
{
	return a.add( b ).scaleSelf( 0.5 );
}

toxi::geom::Vec3D toxi::geom::Line3D::getNormal()
{
	return b.getCrossed( a );
}

bool toxi::geom::Line3D::hasEndPoint( const toxi::geom::Vec3D & p )
{
	//TODO
	return true;
}

int toxi::geom::Line3D::hashCode()
{
	return a.hashCode() + b.hashCode();
}

int toxi::geom::Line3D::hashCodeWithDirection()
{
	long bits = 1;
	bits = 31L * bits + a.hashCode();
	bits = 31L * bits + b.hashCode();
	return ( int ) ( bits ^ ( bits >> 1 ) );
}

toxi::geom::Line3D toxi::geom::Line3D::offsetAndGrowBy( const float & offset, const float & scale, const toxi::geom::Vec3D & ref )
{
	Vec3D m = getMidPoint();
	Vec3D d = getDirection();
	Vec3D n = a.getCrossed( d ).normalize();
	if ( m.sub( ref ).dot( n ) < 0 ) {
		n.invert();
	}
	n.normalizeTo( offset );
	a.addSelf( n );
	b.addSelf( n );
	d.scaleSelf( scale );
	a.subSelf( d );
	b.addSelf( d );
	return *this;
}

toxi::geom::Line3D toxi::geom::Line3D::scaleLength( const float & scale )
{
	float delta = ( 1 - scale ) * 0.5f;
	Vec3D newA = a.interpolateTo( b, delta );
	b.interpolateToSelf( a, delta );
	a.set( newA );
	return *this;
}

toxi::geom::Line3D toxi::geom::Line3D::set( const toxi::geom::Vec3D & _a, const toxi::geom::Vec3D &  _b )
{
	a = toxi::geom::Vec3D ( _a );
	b = toxi::geom::Vec3D ( _b );
	return *this;
}

std::vector< toxi::geom::Vec3D > toxi::geom::Line3D::splitIntoSegments( const  float & stepLength, const bool & addFirst )
{
	std::vector< toxi::geom::Vec3D > segments;
	if ( addFirst ) {
		segments.push_back( a );
	}
	double dist = a.distanceTo( b );
	if ( dist > stepLength ) {
		Vec3D pos = a;
		Vec3D step = b.sub( a ).limit( stepLength );
		while ( dist > stepLength ) {
			pos.addSelf( step );
			segments.push_back( pos );
			dist -= stepLength;
		}
	}
	segments.push_back( b );
	return segments;
}

toxi::geom::Ray3D toxi::geom::Line3D::toRay3D()
{
	return toxi::geom::Ray3D( a, getDirection() );
}

std::string toxi::geom::Line3D::toString()
{
	std::stringstream ss;
	ss << a << " -> " << b;
	return ss.str();
}
