#ifndef __LINE2D_H__
#define __LINE2D_H__

#pragma once

#include "Vec2D.h"
#include "LineIntersection.h"
#include <vector>

namespace toxi
{
	namespace geom
	{
		class Vec2D;
		class Line2D
		{
		public:
			Line2D(void);
			Line2D( Vec2D * v1, Vec2D * v2 );
			Line2D( float x1, float y1, float x2, float y2 );	
			~Line2D(void);

			inline bool operator == (const Line2D & lhs)
			{
				return ( *lhs.a == *this->a && *lhs.b == *this->b );
			}

			toxi::geom::Vec2D * a, * b;

			Vec2D * closestPointTo( Vec2D v );
			toxi::geom::LineIntersection * intersectLine( Line2D * l );
			float distanceToPoint( Vec2D * p );
			std::string toString();
			float getLength();
		};


	}
}

#endif