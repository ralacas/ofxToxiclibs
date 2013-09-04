#pragma once

#ifndef __SPHERE_H__
#define __SPHERE_H__

namespace toxi
{
	namespace geom
	{
		class Vec2D;
		class Vec3D;
		class Ray3D;
		class Triangle3D;
		class Mesh3D;
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
			toxi::geom::Mesh3D * toMesh( int res ); // TODO: change implementation in Sphere.cpp
			toxi::geom::Mesh3D * toMesh( toxi::geom::Mesh3D * mesh, int res );
		};
	}
}

#endif