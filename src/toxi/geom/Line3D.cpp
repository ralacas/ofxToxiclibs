#include "Line3D.h"

toxi::geom::Line3D::Line3D(void)
{
}

toxi::geom::Line3D::Line3D( float x1, float y1, float z1, float x2, float y2, float z2 )
{
	this->a = Vec3D( x1, y1, z1 );
	this->b = Vec3D( x2, y2, z2 );
}

toxi::geom::Line3D::Line3D( toxi::geom::Vec3D a, toxi::geom::Vec3D b )
{
	this->a = a;
	this->b = b;
}

toxi::geom::Line3D::~Line3D(void)
{
}

toxi::geom::LineIntersection toxi::geom::Line3D::closestLineTo( toxi::geom::Line3D l )
{
	Vec3D p43 = l.a.sub( l.b );
	if ( p43.isZeroVector() ) {
		return LineIntersection( LineIntersection::Type::NON_INTERSECTING );
	}
	Vec3D p21 = b.sub( a );
	if ( p21.isZeroVector() ) {
		return LineIntersection( LineIntersection::Type::NON_INTERSECTING );
	}
	Vec3D p13 = a.sub( l.a );

	double d1343 = p13.x * p43.x + p13.y * p43.y + p13.z * p43.z;
	double d4321 = p43.x * p21.x + p43.y * p21.y + p43.z * p21.z;
	double d1321 = p13.x * p21.x + p13.y * p21.y + p13.z * p21.z;
	double d4343 = p43.x * p43.x + p43.y * p43.y + p43.z * p43.z;
	double d2121 = p21.x * p21.x + p21.y * p21.y + p21.z * p21.z;

	double denom = d2121 * d4343 - d4321 * d4321;
	if (toxi::math::MathUtils::abs( denom ) < toxi::math::MathUtils::EPS ) {
		return toxi::geom::LineIntersection( LineIntersection::Type::NON_INTERSECTING );
	}
	double numer = d1343 * d4321 - d1321 * d4343;
	float mua = ( float ) ( numer / denom );
	float mub = ( float ) ( ( d1343 + d4321 * mua ) / d4343 );

	Vec3D pa = a.add( p21.scaleSelf( mua ) );
	Vec3D pb = l.a.add( p43.scaleSelf( mub ) );
	return toxi::geom::LineIntersection( toxi::geom::LineIntersection::Type::INTERSECTING, Line3D(pa, pb), mua,
		mub);
}

toxi::geom::Vec3D toxi::geom::Line3D::closestPointTo( toxi::geom::Vec3D p )
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

bool toxi::geom::Line3D::equals( toxi::geom::Line3D _l )
{
	return ( a.equals( _l.a ) || a.equals( _l.b ) )
		&& ( b.equals( _l.b ) || b.equals( _l.a ) );
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
	return a.distanceTo( b );
}

float toxi::geom::Line3D::getLengthSquared()
{
	return a.distanceToSquared( b );
}

toxi::geom::Vec3D toxi::geom::Line3D::getMidPoint()
{
	return a.add( b ).scaleSelf( 0.5 );
}

toxi::geom::Vec3D toxi::geom::Line3D::getNormal()
{
	return b.cross( a );
}

bool toxi::geom::Line3D::hasEndPoint( toxi::geom::Vec3D p )
{
	return a.equals( p ) || b.equals( p );
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
	return ( int ) ( bits ^ ( bits >> 32 ) );
}

toxi::geom::Line3D toxi::geom::Line3D::offsetAndGrowBy( float offset, float scale, toxi::geom::Vec3D ref )
{
	Vec3D m = getMidPoint();
	Vec3D d = getDirection();
	Vec3D n = a.cross( d ).normalize();
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

toxi::geom::Line3D toxi::geom::Line3D::scaleLength( float scale )
{
	float delta = ( 1 - scale ) * 0.5f;
	Vec3D newA = a.interpolateTo( b, delta );
	b.interpolateToSelf( a, delta );
	a.set( newA );
	return *this;
}

toxi::geom::Line3D toxi::geom::Line3D::set( toxi::geom::Vec3D _a, toxi::geom::Vec3D _b )
{
	a = Vec3D ( _a );
	b = Vec3D ( _b );
}

std::vector< toxi::geom::Vec3D > toxi::geom::Line3D::splitIntoSegments( float stepLength, bool addFirst )
{
	std::vector< toxi::geom::Vec3D > segments;
	if ( addFirst ) {
		segments.push_back( a.copy() );
	}
	float dist = a.distanceTo(b);
	if ( dist > stepLength ) {
		Vec3D pos = a.copy();
		Vec3D step = b.sub( a ).limit( stepLength );
		while ( dist > stepLength ) {
			pos.addSelf( step );
			segments.push_back( pos );
			dist -= stepLength;
		}
	}
	segments.push_back( b.copy() );
	return segments;
}

toxi::geom::Ray3D toxi::geom::Line3D::toRay3D()
{
	return Ray3D( a.copy(), getDirection() );
}

std::string toxi::geom::Line3D::toString()
{
	std::stringstream ss;
	ss << a.toString() << " -> " << b.toString();
	return ss.str();
}
