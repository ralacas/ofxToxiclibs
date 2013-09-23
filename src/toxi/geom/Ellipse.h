#ifndef __ELLIPSE_H__
#define __ELLIPSE_H__

#pragma once

#include "Vec2D.h"
#include "../util/datatypes/BiasedFloatRange.h"
#include <vector>
//#include "Shape2D.h"

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
			Ellipse( const float & rx, const float & ry );
			Ellipse( const float & x, const float & y, const float & r );
			Ellipse( const float & x, const float & y, const float & rx, const float & ry );
			Ellipse( const Vec2D & v, const float & r );
			Ellipse( const Vec2D & v, const Vec2D & r );
			~Ellipse(void);

			static int DEFAULT_RES;
			Vec2D radius;
			float focus;

			bool containsPoint( Vec2D & p );
			float getArea();
			toxi::geom::Circle getBoundingCircle();
			toxi::geom::Rect getBounds();
			float getCircumference();
			std::vector< Vec2D > getFoci();
			Vec2D getRadii();
			Vec2D getRandomPoint();
			Ellipse setRadii( Vec2D & v );
			Ellipse setRadii( const float & rx, const float & ry );
			Polygon2D toPolygon2D();
			Polygon2D toPolygon2D( const int & res );


		};

	}
}

#endif