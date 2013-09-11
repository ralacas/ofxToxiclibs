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
		class Circle : public toxi::geom::Ellipse
		{
		public:
			Circle(void);
			Circle( toxi::geom::Vec2D * origin, float radius );
			Circle( float x, float y, float r );
			~Circle(void);

			
		};
	}
}

#endif