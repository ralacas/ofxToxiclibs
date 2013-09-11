#ifndef __ELLIPSE_H__
#define __ELLIPSE_H__
// IM HERE
#pragma once

#include "Vec2D.h"
//#include "Shape2D.h"
#include "../util/datatypes/BiasedFloatRange.h"
#include <vector>

namespace toxi
{
	namespace geom
	{
		class Vec2D;
		class Circle;
		class Rect;
		class Shape2D;
		class BiasedFloatRange;
		class Polygon2D;
		class Ellipse  : public toxi::geom::Vec2D
		{
		public:
			Ellipse( void );
			Ellipse( float rx, float ry );
			Ellipse( float x, float y, float r );
			Ellipse( float x, float y, float rx, float ry );
			Ellipse( Vec2D * v, float r );
			Ellipse( Vec2D * v, Vec2D * r );
			~Ellipse(void);

			static int DEFAULT_RES;
			Vec2D * radius;
			float focus;

			bool containsPoint( Vec2D * p );
			float getArea();
			toxi::geom::Circle * getBoundingCircle();
			toxi::geom::Rect * getBounds();
			float getCircumference();
			std::vector< Vec2D * > getFoci();
			Vec2D * getRadii();
			Vec2D * getRandomPoint();
			Ellipse * setRadii( Vec2D * v );
			Ellipse * setRadii( float rx, float ry );
			Polygon2D * toPolygon2D();
			Polygon2D * toPolygon2D( int res );


		};

	}
}

#endif