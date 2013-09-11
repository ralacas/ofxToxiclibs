#ifndef __RAY_2D_H__
#define __RAY_2D_H__

#pragma once

#include "Vec2D.h"

namespace toxi
{
	namespace geom
	{
		//class Vec2D;
		class Ray2D : public toxi::geom::Vec2D
		{
		public:
			Ray2D(void);
			~Ray2D(void);

			toxi::geom::Vec2D * getDirection();
			toxi::geom::Vec2D * getPointAtDistance( float tmin );
		};


	}
}

#endif