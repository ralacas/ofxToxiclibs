#include "Triangle3D.h"
#include "Vec3D.h"
#include "AABB.h"
#include "Line3D.h"


toxi::geom::Triangle3D::Triangle3D(void)
{
}

toxi::geom::Triangle3D::Triangle3D(Vec3D * a, Vec3D * b, Vec3D * c )
{
	this->a = a;
	this->b = b;
	this->c = c;
}

toxi::geom::Triangle3D::~Triangle3D(void)
{
}

toxi::geom::Triangle3D toxi::geom::Triangle3D::createEquilateralFrom( Vec3D * a, Vec3D * b )
{
	Vec3D c = a->interpolateTo( b, 0.5 );
	Vec3D dir = b->sub( a );
	Vec3D n = a->cross( &dir.normalize( ) );
	c.addSelf( &n.normalizeTo( dir.magnitude() * toxi::math::MathUtils::SQRT3 / 2 ) );
	return Triangle3D( a, b, &c );
}

toxi::geom::Vec3D toxi::geom::Triangle3D::closestPointOnSurface( Vec3D * p )
{
	Vec3D ab = b->sub( a );
	Vec3D ac = c->sub( a );
	Vec3D bc = c->sub( b );

	Vec3D pa = p->sub( a );
	Vec3D pb = p->sub( b );
	Vec3D pc = p->sub( c );

	Vec3D ap = a->sub( p );
	Vec3D bp = b->sub( p );
	Vec3D cp = c->sub( p );

	// Compute parametric position s for projection P' of P on AB,
	// P' = A + s*AB, s = snom/(snom+sdenom)
	float snom = pa.dot( &ab );

	// Compute parametric position t for projection P' of P on AC,
	// P' = A + t*AC, s = tnom/(tnom+tdenom)
	float tnom = pa.dot( &ac );

	if ( snom <= 0.0f && tnom <= 0.0f ) {
		return *a; // Vertex region early out
	}

	float sdenom = pb.dot( &a->sub( b ) );
	float tdenom = pc.dot( &a->sub( c ) );

	// Compute parametric position u for projection P' of P on BC,
	// P' = B + u*BC, u = unom/(unom+udenom)
	float unom = pb.dot( &bc );
	float udenom = pc.dot( &b->sub( c ) );

	if ( sdenom <= 0.0f && unom <= 0.0f ) {
		return *b; // Vertex region early out
	}
	if ( tdenom <= 0.0f && udenom <= 0.0f ) {
		return *c; // Vertex region early out
	}

	// P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
	Vec3D n = ab.cross( &ac );
	float vc = n.dot( &ap.crossSelf( &bp ) );

	// If P outside AB and within feature region of AB,
	// return projection of P onto AB
	if ( vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f ) {
		// return a + snom / (snom + sdenom) * ab;
		return *a->add( &ab.scaleSelf( snom / ( snom + sdenom ) ) );
	}

	// P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
	float va = n.dot( &bp.crossSelf( &cp ) );
	// If P outside BC and within feature region of BC,
	// return projection of P onto BC
	if ( va <= 0.0f && unom >= 0.0f && udenom >= 0.0f ) {
		// return b + unom / (unom + udenom) * bc;
		return *b->add( &bc.scaleSelf( unom / ( unom + udenom ) ) );
	}

	// P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
	float vb = n.dot( &cp.crossSelf( &ap ) );
	// If P outside CA and within feature region of CA,
	// return projection of P onto CA
	if ( vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f ) {
		// return a + tnom / (tnom + tdenom) * ac;
		return *a->add( &ac.scaleSelf( tnom / ( tnom + tdenom ) ) );
	}

	// P must project inside face region. Compute Q using barycentric
	// coordinates
	float u = va / ( va + vb + vc );
	float v = vb / ( va + vb + vc );
	float w = 1.0f - u - v; // = vc / (va + vb + vc)
	// return u * a + v * b + w * c;
	return a->scale( u ).addSelf( &b->scale( v ) ).addSelf( &c->scale( w ) );
}

toxi::geom::Vec3D toxi::geom::Triangle3D::computeCentroid()
{
	this->centroid = &a->add( b )->addSelf( c ).scaleSelf( 1.0 / 3 );
	return *centroid;
}

bool toxi::geom::Triangle3D::containsPoint( Vec3D * p )
{
	Vec3D v0 = c->sub( a );
	Vec3D v1 = b->sub( a );
	Vec3D v2 = p->sub( a );

	// Compute dot products
	float dot00 = v0.dot( &v0 );
	float dot01 = v0.dot( &v1 );
	float dot02 = v0.dot( &v2 );
	float dot11 = v1.dot( &v1 );
	float dot12 = v1.dot( &v2 );

	// Compute barycentric coordinates
	float invDenom = 1.0f / ( dot00 * dot11 - dot01 * dot01 );
	float u = ( dot11 * dot02 - dot01 * dot12 ) * invDenom;
	float v = ( dot00 * dot12 - dot01 * dot02 ) * invDenom;

	// Check if point is in triangle
	return ( u >= 0.0 ) && ( v >= 0.0 ) && ( u + v <= 1.0 );
}

toxi::geom::Triangle3D toxi::geom::Triangle3D::flipVertexOrder()
{
	Vec3D t = *a;
	a = c;
	c = &t;
	return *this;
}

toxi::geom::Vec3D toxi::geom::Triangle3D::fromVarycentric( Vec3D * v )
{
	return Vec3D( a->x * v->x + b->x * v->y + c->x * v->z, a->y * v->x
		+ b->y * v->y + c->y * v->z, a->z * v->x + b->z * v->y + c->z
		* v->z );
}

toxi::geom::AABB toxi::geom::Triangle3D::getBoundingBox()
{
	Vec3D min = *Vec3D::min( Vec3D::min( a, b ), c );
	Vec3D max = *Vec3D::max( Vec3D::max( a, b ), c );
	return AABB(min, max);
}

toxi::geom::Vec3D toxi::geom::Triangle3D::getClosestPointTo( Vec3D * v )
{
	Line3D edge = Line3D( a, b );
	Vec3D * Rab = edge.closestPointTo( v );
	Vec3D * Rbc = edge.set( b, c ).closestPointTo( v );
	Vec3D * Rca = edge.set( c, a ).closestPointTo( v );

	float dAB = v->sub( Rab ).magSquared();
	float dBC = v->sub( Rbc ).magSquared();
	float dCA = v->sub( Rca ).magSquared();

	float min = dAB;
	Vec3D result = *Rab;

	if (dBC < min) {
		min = dBC;
		result = *Rbc;
	}
	if (dCA < min) {
		result = *Rca;
	}

	return result;
}

std::vector< toxi::geom::Vec3D > toxi::geom::Triangle3D::getVertexVector()
{
	std::vector< Vec3D > array;
	array.push_back( *a );
	array.push_back( *b );
	array.push_back( *c );
	return array;

}

bool toxi::geom::Triangle3D::isClockWiseInXY()
{
	float determ = ( b->x - a->x ) * ( c->y - a->y ) - ( c->x - a->x ) * ( b->y - a->y );
	return ( determ < 0.0 );
}

bool toxi::geom::Triangle3D::isClockWiseInXZ()
{
	float determ = (b->x - a->x) * (c->z - a->z) - (c->x - a->x) * (b->z - a->z);
	return (determ < 0.0);
}

bool toxi::geom::Triangle3D::isClockWiseInYZ()
{
	float determ = ( b->x - a->x ) * ( c->z - a->z ) - ( c->x - a->x ) * ( b->z - a->z );
	return ( determ < 0.0 );
}

bool toxi::geom::Triangle3D::isSameClockDir( Vec3D * a, Vec3D * b, Vec3D * p, Vec3D * norm )
{
	float determ = ( b->y - a->y ) * ( c->z - a->z ) - ( c->y - a->y ) * ( b->z - a->z );
	return ( determ < 0.0 );
}

void toxi::geom::Triangle3D::set( Vec3D * a2, Vec3D * b2, Vec3D * c2 )
{
	this->a = a2;
	this->b = b2;
	this->c = c2;
}

toxi::geom::Vec3D toxi::geom::Triangle3D::toBarycentric( Vec3D * p )
{
	Vec3D e = b->sub( a ).cross( &c->sub( a ) );
	Vec3D n = e.getNormalized();

	// Compute twice area of triangle ABC
	float areaABC = n.dot( &e );
	// Compute lambda1
	float areaPBC = n.dot( &b->sub( p ).cross( &c->sub( p ) ) );
	float l1 = areaPBC / areaABC;

	// Compute lambda2
	float areaPCA = n.dot( &c->sub( p ).cross( &a->sub( p ) ) );
	float l2 = areaPCA / areaABC;

	// Compute lambda3
	float l3 = 1.0f - l1 - l2;

	return Vec3D(l1, l2, l3);
}

std::string toxi::geom::Triangle3D::toString()
{
	std::stringstream ss;
	ss << "Triangle3D: " << a->toString() << ", " << b->toString() << ", " << c->toString();
	return ss.str();
}

toxi::geom::Vec3D toxi::geom::Triangle3D::computeNormal()
{
	normal = &a->sub(c).crossSelf(&a->sub(b)).normalize();
	return *normal;
}
