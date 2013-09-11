#ifndef __LINE2D_H__
#define __LINE2D_H__

#pragma once

#include "Vec2D.h"

namespace toxi
{
	namespace geom
	{
		class Vec2D;
		class Line2D
		{
		public:
			Line2D(void);
			Line2D( float x1, float y1, float x2, float y2 );
			~Line2D(void);

			toxi::geom::Vec2D * a, * b;
		};


	}
}

#endif