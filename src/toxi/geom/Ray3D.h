#pragma once

#ifndef __RAY3D_H__
#define __RAY3D_H__

#include < string >

#include "Vec3D.h"

namespace toxi
{
	namespace geom
	{
		class Vec3D;
		class Line3D;
		class Ray3D :
			public Vec3D
		{
		public:
			Ray3D(void);
			Ray3D( const float & x, const float & y, const float & z, const toxi::geom::Vec3D & d );
			Ray3D( const toxi::geom::Vec3D & o, const toxi::geom::Vec3D & d );
			~Ray3D(void);

			toxi::geom::Vec3D dir;

			toxi::geom::Vec3D getDirection( );
			toxi::geom::Vec3D getPointAtDistance( const float & d );
			float getDistanceToPoint( const toxi::geom::Vec3D & v );
			toxi::geom::Ray3D setDirection( const toxi::geom::Vec3D & v );
			toxi::geom::Line3D toLine3DWithPointAtDistance( const float & dist );
			std::string toString();
		};
	}
}

#endif