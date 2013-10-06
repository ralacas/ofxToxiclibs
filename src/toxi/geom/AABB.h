#pragma once

#ifndef __AABB_H__
#define __AABB_H__

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "mesh/Mesh3D.h"
#include "Ray3D.h"

namespace toxi
{
	namespace geom
	{
		class Ray3D;
		class TriangleMesh;
		class MathUtils;
		class mesh::Mesh3D;
		class Vec3D;
		class AABB : public Vec3D
		{
		public:
			AABB( void );
			static AABB fromMinMax( const Vec3D & min, const Vec3D & max ) 
			{
				toxi::geom::Vec3D a = toxi::geom::Vec3D::min( min, max );
				toxi::geom::Vec3D b = toxi::geom::Vec3D::max( min , max );
				return AABB( a.interpolateTo( b, 0.5 ), b.sub( a ).scaleSelf( 0.5 ) );
			}

			static AABB getBoundingBox( std::vector<Vec3D> points  )
			{
				if ( points.size() == 0 ) {
					return NULL;
				}
				Vec3D min = Vec3D::max_value();
				Vec3D max = Vec3D::min_value();
				for (Vec3D p : points) {
					min.minSelf( p );
					max.maxSelf( p );
				}
				return fromMinMax(min, max);
			}

			AABB( AABB &box );
			AABB( const double & extend );
			AABB( const Vec3D & point, const double & extend );
			AABB( const Vec3D & point, const Vec3D & extend );

			~AABB(void);

			Vec3D getMin();
			Vec3D getMax();
			bool containsPoint( Vec3D & point );
			//Sphere getBoundingSphere();
			Vec3D getExtend(  );
			Vec3D getNormalForPoint( Vec3D & p );
			AABB * growToContainPoint( const Vec3D & p );
			bool intersectsBox( AABB & box );
			Vec3D intersectsRay( Ray3D & ray, const float & minDist, const float & maxDist );
			//bool intersectsSphere(Sphere s );
			bool intersectsSphere( const toxi::geom::Vec3D & c, const float & r );
			//bool intersectsTriangle( Triangle3D tri );
			bool planeBoxOverlap( Vec3D & normal, const float & d, const Vec3D & maxBox );
			AABB * set( const toxi::geom::AABB & box );
			AABB * set( const float & a, const float & b, const float & c );
			AABB * set( const Vec3D & v );
			AABB * setExtend( const Vec3D & extend );
			bool testAxis( const float & a, const float & b, const float & fa, const float & fb, const float & va, const float & vb, const float & wa, const float & wb, const float & ea, const float & eb );
			//mesh::Mesh3D toMesh( void );
			std::string toString( void );
			AABB * updateBound( void );
			Vec3D sub( const float & a, const float & b, const float & c);
			Vec3D sub( const double & a, const double & b, const double & c);
			Vec3D sub( const Vec3D & v);
			Vec3D add( const float & a, const float & b, const float & c);
			Vec3D add( const double & a, const double & b, const double & c);
			Vec3D add( const Vec3D & v);

		private:
			toxi::geom::Vec3D extent, min, max;
			double x, y, z;
		};
	}
}

#endif
