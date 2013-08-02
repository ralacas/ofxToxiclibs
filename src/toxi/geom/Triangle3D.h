#pragma once

#include "Vec3D.h"
#include "Triangle3D.h"
#include "AABB.h"
#include "Line3D.h"
#include < vector >
#include < string >

namespace toxi
{
	namespace geom
	{
		class Triangle3D
		{
		public:
			Triangle3D(void);
			Triangle3D( Vec3D a, Vec3D b, Vec3D c );
			~Triangle3D(void);

			Vec3D a, b, c;
			Vec3D normal, centroid;

			static Triangle3D createEquilateralFrom( Vec3D a, Vec3D b );

			Vec3D closesPointOnSurface( Vec3D p );
			Vec3D computeCentroid( );
			bool containsPoint( Vec3D p );
			Triangle3D flipVertexOrder( );
			Vec3D fromVarycentric( Vec3D v );
			AABB getBoundingBox( );
			Vec3D getClosestPointTo( Vec3D v );
			std::vector< Vec3D > getVertexVector();
			bool isClockWiseInXY();
			bool isClockWiseInXZ();
			bool isClockWiseInYZ();
			bool isSameClockDir( Vec3D a, Vec3D b, Vec3D p, Vec3D norm );
			void set( Vec3D a2, Vec3D b2, Vec3D c2 );
			Vec3D toBarycentric( Vec3D p );
			std::string toString();
			//TODO: implement this class
		};
	}
}


