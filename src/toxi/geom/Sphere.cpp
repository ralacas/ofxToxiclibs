#include "Sphere.h"
#include "mesh/Mesh3D.h"
#include "mesh/SurfaceMeshBuilder.h"
#include "Ray3D.h"
#include "Triangle3D.h"
#include "Vec2D.h"

double toxi::geom::Sphere::EARTH_RADIUS = (2 * 6378.1370 + 6356.752314245) / 3.0;

toxi::geom::Sphere::Sphere(void)
{
	toxi::geom::Sphere( Vec3D(), 1 );
}

toxi::geom::Sphere::Sphere( const float & radius )
{
	toxi::geom::Sphere( Vec3D(), radius );
}

toxi::geom::Sphere::Sphere( const Vec3D & v, const float & radius )
{
	//TODO call super constructor
	this->radius = radius;
}


toxi::geom::Sphere::~Sphere(void)
{
}

bool toxi::geom::Sphere::containsPoint( Vec3D & p )
{
	float d = this->sub(p).magSquared();
	return (d <= radius * radius);
}

float toxi::geom::Sphere::intersectRay( Ray3D & ray )
{
	float result[ 2 ];
	Vec3D q = ray.sub( *this );
	float distSquared = q.magSquared();
	float v = -q.dot( ray.getDirection() );
	float d = radius * radius - (distSquared - v * v);
	if (d >= 0.0) {
		d = (float) toxi::math::MathUtils::sqrt(d);
		float a = v + d;
		float b = v - d;
		if (!(a < 0 && b < 0)) {
			if (a > 0 && b > 0) {
				if (a > b) {
					float t = a;
					a = b;
					b = t;
				}
			} else {
				if (b > 0) {
					float t = a;
					a = b;
					b = t;
				}
			}
		}
		result[ 0] = a;
		result[ 1 ] = b ;
	}
	return result[0];
}

bool toxi::geom::Sphere::intersectSphereTriangle( Triangle3D & t, Vec3D & result )
{
	// Find Vec3D P on triangle ABC closest to sphere center
	result.set( t.closestPointOnSurface( *this ) );

	// Sphere and triangle intersect if the (squared) distance from sphere
	// center to Vec3D p is less than the (squared) sphere radius
	Vec3D v = result.sub( *this );
	return v.magSquared() <= radius * radius;
}

double toxi::geom::Sphere::surfaceDistanceBetween( const Vec2D & p, const Vec2D & q )
{
	double t1 = toxi::math::MathUtils::sin(p.getY()) * toxi::math::MathUtils::sin(q.getY());
	double t2 = toxi::math::MathUtils::cos(p.getY()) * toxi::math::MathUtils::cos(q.getY());
	double t3 = toxi::math::MathUtils::cos(p.getX() - q.getX());
	double t4 = t2 * t3;
	double t5 = t1 + t4;
	double dist = std::atan(-t5 / toxi::math::MathUtils::sqrt(-t5 * t5 + 1)) + 2
		* std::atan(1);
	if (toxi::math::MathUtils::isNan(dist)) {
		dist = 0;
	} else {
		dist *= radius;
	}
	return dist;
}

toxi::geom::Vec3D toxi::geom::Sphere::tangentPlaneNormalAt( Vec3D & q )
{
	return q.sub( *this ).normalize();
}


/*toxi::geom::mesh::Mesh3D * toxi::geom::Sphere::toMesh( toxi::geom::mesh::Mesh3D * mesh, int res )
{
	toxi::geom::mesh::SurfaceMeshBuilder builder = toxi::geom::mesh::SurfaceMeshBuilder( );//new toxi::geom::mesh::SphereFunction(this->radius)); // TODO: this might be wrong
	
	return builder.createMesh(mesh, res, 1);
}*/