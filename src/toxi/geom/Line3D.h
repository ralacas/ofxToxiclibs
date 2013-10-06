#pragma once

#ifndef __LINE3D_H__
#define __LINE3D_H__

#include < vector >
#include < string >

#include "Vec3D.h"

namespace toxi
{
	namespace geom
	{
		class LineIntersection;
		class LineIntersection3D;
		class Ray3D;
		class Vec3D;
		class AABB;
		class MathUtils;
		class Line3D
		{
		public:
			Line3D( void );
			Line3D( const float & x1, const float & y1, const float & z1, const float & x2, const float & y2, const float & z2 );
			Line3D( const toxi::geom::Vec3D & a, const toxi::geom::Vec3D & b );
			~Line3D( void );

			toxi::geom::Vec3D a, b;
			
			toxi::geom::LineIntersection3D closestLineTo( toxi::geom::Line3D & l );
			toxi::geom::Vec3D closestPointTo( toxi::geom::Vec3D & p );
			toxi::geom::AABB getBounds();
			toxi::geom::Vec3D getDirection();
			float getLength();
			float getLengthSquared();
			toxi::geom::Vec3D getMidPoint();
			toxi::geom::Vec3D getNormal();
			bool hasEndPoint( const toxi::geom::Vec3D & p );
			int hashCode();
			int hashCodeWithDirection();
			toxi::geom::Line3D offsetAndGrowBy( const float & offset, const float & scale, const toxi::geom::Vec3D & ref );
			toxi::geom::Line3D scaleLength( const float & scale );
			toxi::geom::Line3D set( const toxi::geom::Vec3D & _a, const toxi::geom::Vec3D & _b );
			std::vector< toxi::geom::Vec3D > splitIntoSegments( const float & stepLength, const bool & addFirst );
			toxi::geom::Ray3D toRay3D();
			std::string toString();
		};

	}
}

#endif