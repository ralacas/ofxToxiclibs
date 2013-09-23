#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#pragma once

//#include "Vec2D.h"
#include "Ellipse.h"
#include <vector>

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
			Circle( const float & radius );
			Circle( const toxi::geom::Vec2D & origin, const float & radius );
			Circle( const float & x, const float & y, const float & r );
			~Circle(void);

			static Circle newBoundingCircle( const std::vector< Vec2D > & vertices );
			
		};
	}
}

#endif