#pragma once

#ifndef __TRIANGLE3D_H__
#define __TRIANGLE3D_H__

#include < vector >
#include < string >

//#include "AABB.h"
//#include "Triangle3D.h"
#include "Vec3D.h"
//#include "../math/MathUtils.h"

namespace toxi
{
	namespace geom
	{
		class Vec3D;
		class AABB;
		class Triangle3D
		{
		public:
			Triangle3D(void);
			Triangle3D( const Vec3D & a, const Vec3D & b, const Vec3D & c );
			~Triangle3D(void);

			toxi::geom::Vec3D a, b, c; // TODO: pointers here
			toxi::geom::Vec3D normal, centroid;

			static Triangle3D createEquilateralFrom( Vec3D & a, Vec3D & b );

			Vec3D closestPointOnSurface( Vec3D & p );
			Vec3D computeCentroid( );
			Vec3D computeNormal();
			bool containsPoint( Vec3D & p );
			Triangle3D flipVertexOrder( );
			Vec3D fromVarycentric( Vec3D & v );
			toxi::geom::AABB getBoundingBox( );
			Vec3D getClosestPointTo( Vec3D & v );
			std::vector< Vec3D > getVertexVector();
			bool isClockWiseInXY();
			bool isClockWiseInXZ();
			bool isClockWiseInYZ();
			bool isSameClockDir( Vec3D & a, Vec3D & b, Vec3D & p, Vec3D & norm );
			void set( Vec3D & a2, Vec3D & b2, Vec3D & c2 );
			Vec3D toBarycentric( Vec3D & p );
			std::string toString();
			//TODO: implement this class
		};
	}
}

#endif
