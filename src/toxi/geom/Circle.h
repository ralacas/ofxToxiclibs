#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#pragma once

//#include "Vec2D.h"
#include "Ellipse.h"

namespace toxi
{
	namespace geom
	{
		class Ellipse;
		class Vec2D;
		class Circle : toxi::geom::Ellipse
		{
		public:
			Circle(void);
			Circle( toxi::geom::Vec2D * origin, float radius );
			~Circle(void);

			
		};
	}
}

#endif