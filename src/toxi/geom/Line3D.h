#pragma once

#ifndef __LINE3D_H__
#define __LINE3D_H__

#include "Vec3D.h"
#include "AABB.h"
#include "LineIntersection.h"
#include "../math/MathUtils.h"

#include < vector >
#include < string >

namespace toxi
{
	namespace geom
	{
		class LineIntersection;
		class Ray3D;
		class Vec3D;
		class AABB;
		class MathUtils;
		class Line3D
		{
		public:
			Line3D(void);
			Line3D( float x1, float y1, float z1, float x2, float y2, float z2 );
			Line3D( toxi::geom::Vec3D * a, toxi::geom::Vec3D * b );
			~Line3D(void);

			toxi::geom::Vec3D * a, * b;
			
			toxi::geom::LineIntersection closestLineTo( toxi::geom::Line3D l );
			toxi::geom::Vec3D closestPointTo( toxi::geom::Vec3D p );
			bool equals(Line3D _l);
			toxi::geom::AABB getBounds();
			toxi::geom::Vec3D getDirection();
			float getLength();
			float getLengthSquared();
			toxi::geom::Vec3D getMidPoint();
			toxi::geom::Vec3D getNormal();
			bool hasEndPoint( toxi::geom::Vec3D p );
			int hashCode();
			int hashCodeWithDirection();
			toxi::geom::Line3D offsetAndGrowBy( float offset, float scale, toxi::geom::Vec3D ref );
			toxi::geom::Line3D scaleLength( float scale );
			toxi::geom::Line3D set( toxi::geom::Vec3D _a, toxi::geom::Vec3D _b );
			std::vector< toxi::geom::Vec3D > splitIntoSegments( float stepLength, bool addFirst );
			toxi::geom::Ray3D toRay3D();
			std::string toString();
		};

	}
}

#endif