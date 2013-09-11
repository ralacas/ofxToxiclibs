#ifndef __POLYGON_2D_H__
#define __POLYGON_2D_H__

#pragma once

//#include "Vec2D.h"

namespace toxi
{
	namespace geom
	{
		class Vec2D;
		class Polygon2D
		{
		public:
			Polygon2D(void);
			~Polygon2D(void);

			Polygon2D add( float x, float y );
			Polygon2D add( toxi::geom::Vec2D * v );
		};

	}
}

#endif