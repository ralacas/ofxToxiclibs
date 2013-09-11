#ifndef __SHAPE_2D_H__
#define __SHAPE_2D_H__

#pragma once

#include "Circle.h"
//#include "Polygon2D.h"

namespace toxi
{
	namespace geom
	{
		class Vec2D;
		class Rect;
		class Circle;
		class Polygon2D;
		class Shape2D
		{
		public:
			virtual bool containsPoint( toxi::geom::Vec2D * p ) = 0;
			virtual float getArea( ) = 0;
			virtual toxi::geom::Circle * getBoundingCircle() = 0;
			virtual toxi::geom::Rect * getBounds() = 0;
			virtual float getCircumference() = 0;
			virtual toxi::geom::Vec2D * getRandomPoint() = 0;
			virtual toxi::geom::Polygon2D * toPolygon2D() = 0;
		};
	}
}

#endif