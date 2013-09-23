#pragma once

#ifndef __SPHERE_H__
#define __SPHERE_H__

//#include "Ray3D.h"
//#include "Triangle3D.h"
#include "Vec3D.h"
//#include "mesh/SphereFunction.h"
//#include "mesh/SurfaceMeshBuilder.h"
//#include "mesh/Mesh3D.h"

namespace toxi
{
	namespace geom
	{
		class Vec2D;
		class Vec3D;
		class Ray3D;
		class Triangle3D;
		//class toxi::geom::mesh::Mesh3D;
		class SphereFunction;
		class SurfaceMeshBuilder;
		class Sphere : public Vec3D
		{
		public:
			Sphere(void);
			Sphere( const float & radius );
			Sphere( const Vec3D & v, const float & r );
			~Sphere(void);

			static double EARTH_RADIUS;
			float radius;

			bool containsPoint( Vec3D & p );
			float intersectRay( Ray3D & ray );
			bool intersectSphereTriangle( Triangle3D & t, Vec3D & result );
			double surfaceDistanceBetween( const toxi::geom::Vec2D & p, const toxi::geom::Vec2D & q );
			Vec3D tangentPlaneNormalAt( Vec3D & q );
			//toxi::geom::mesh::Mesh3D * toMesh( int res ); // TODO: change implementation in Sphere.cpp
			//toxi::geom::mesh::Mesh3D * toMesh( toxi::geom::mesh::Mesh3D * mesh, int res );
		};
	}
}

#endif