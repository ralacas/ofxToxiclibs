#pragma once
#include "vec3d.h"
#include "mesh/Mesh3D.h"
#include "mesh/SurfaceMeshBuilder.h"
#include "mesh/SphereFunction.h"

namespace toxi
{
	namespace geom
	{
		class Sphere :
			public toxi::geom::Vec3D
		{
		public:
			Sphere(void);
			Sphere( float radius );
			Sphere( Vec3D v, float r );
			~Sphere(void);

			static double EARTH_RADIUS;
			float radius;

			bool containsPoint( Vec3D p );
			float * intersectRay( Ray3D ray );
			bool intersectSphereTriangle( Triangle3D t, Vec3D result );
			double surfaceDistanceBetween( Vec2D p, Vec2D q );
			Vec3D tangentPlaneNormalAt( Vec3D q );
			toxi::geom::mesh::Mesh3D toMesh( int res );
			toxi::geom::mesh::Mesh3D toMesh( toxi::geom::mesh::Mesh3D mesh, int res );
		};
	}
}


