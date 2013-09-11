#pragma once

#ifndef __SPHERE_H__
#define __SPHERE_H__

//#include "Ray3D.h"
//#include "Triangle3D.h"
#include "Vec3D.h"
//#include "mesh/SphereFunction.h"
//#include "mesh/SurfaceMeshBuilder.h"
#include "mesh/Mesh3D.h"

namespace toxi
{
	namespace geom
	{
		class Vec2D;
		class Vec3D;
		class Ray3D;
		class Triangle3D;
		class toxi::geom::mesh::Mesh3D;
		class SphereFunction;
		class SurfaceMeshBuilder;
		class Sphere : public Vec3D
		{
		public:
			Sphere(void);
			Sphere( float radius );
			Sphere( Vec3D v, float r );
			~Sphere(void);

			static double EARTH_RADIUS;
			float radius;

			bool containsPoint( Vec3D * p );
			float * intersectRay( Ray3D * ray );
			bool intersectSphereTriangle( Triangle3D * t, Vec3D * result );
			double surfaceDistanceBetween( toxi::geom::Vec2D * p,  toxi::geom::Vec2D * q );
			Vec3D tangentPlaneNormalAt( Vec3D * q );
			//toxi::geom::mesh::Mesh3D * toMesh( int res ); // TODO: change implementation in Sphere.cpp
			toxi::geom::mesh::Mesh3D * toMesh( toxi::geom::mesh::Mesh3D * mesh, int res );
		};
	}
}

#endif