#ifndef __POLYGON_2D_H__
#define __POLYGON_2D_H__

#pragma once

//#include "Vec2D.h"
#include <vector>

namespace toxi
{
	namespace geom
	{
		class Vec2D;
		class Line2D;
		class Polygon2D
		{
		public:
			Polygon2D(void);
			~Polygon2D(void);

			std::vector< Vec2D * > vertices;

			Polygon2D add( float x, float y );
			Polygon2D add( toxi::geom::Vec2D * v );
			std::vector< Line2D * > getEdges();
		};

	}
}

#endif