#pragma once

#ifndef __RAY3D_H__
#define __RAY3D_H__

#include < string >
#include "Line3D.h"
#include "Vec3D.h"

namespace toxi
{
	namespace geom
	{
		class Vec3D;
		class Line3D;
		class Ray3D :
			public toxi::geom::Vec3D
		{
		public:
			Ray3D(void);
			Ray3D( float x, float y, float z, toxi::geom::Vec3D * d );
			Ray3D( toxi::geom::Vec3D * o, toxi::geom::Vec3D * d );
			~Ray3D(void);

			toxi::geom::Vec3D * dir;

			toxi::geom::Vec3D * getDirection( );
			toxi::geom::Vec3D * getPointAtDistance( float d );
			float getDistanceToPoint( toxi::geom::Vec3D * v );
			toxi::geom::Ray3D setDirection( toxi::geom::Vec3D * v );
			toxi::geom::Line3D toLine3DWithPointAtDistance( float dist );
			std::string toString();
		};
	}
}

#endif