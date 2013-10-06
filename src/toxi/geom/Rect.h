#ifndef __RECT_H__
#define __RECT_H__

#pragma once

#include "Shape2D.h"
//#include "Vec2D.h"
//#include "Circle.h"
//#include "Polygon2D.h"
//#include "Line2D.h"
//#include "Ray2D.h"
#include <string>
#include <vector>


namespace toxi
{
	namespace geom
	{
		class Circle;
		class Line2D;
		class Shape2D;
		class Ray2D;
		class Vec2D;
		class Rect : public toxi::geom::Shape2D
		{
		public:
			enum CreationType { NORMAL, CENTER };
			enum EdgeType { TOP, RIGHT, BOTTOM, LEFT };

			Rect( void );
			Rect( const float & x, const float & y, const float & w, const float & h );
			Rect( Vec2D & p1, Vec2D & p2, const CreationType & type );
			Rect( const Rect & toCopy );
	
			static Rect getBoundingRect( const std::vector< Vec2D > & vertices );

			~Rect(void);

			bool containsPoint( toxi::geom::Vec2D & p );
			float getArea( );
			float getAspect();
			toxi::geom::Circle getBoundingCircle();
			toxi::geom::Rect getBounds();
			float getCircumference();
			toxi::geom::Vec2D getRandomPoint();
			toxi::geom::Polygon2D toPolygon2D();
			toxi::geom::Polygon2D toPolygon2D( const float & radius, const int & res );
			std::string toString();

			float getBottom();
			float getLeft();
			float getRight();
			float getTop();
			Vec2D getMappedPointInRect( const Vec2D & p );
			Vec2D getBottomLeft();
			Vec2D getBottomRight();
			Vec2D getTopLeft();
			Vec2D getTopRight();
			Vec2D getCentroid();
			Vec2D getDimensions();
			Line2D getEdge( const EdgeType & edgeType );
			Rect growToContainPoint( Vec2D & p );
			int hashCode();
			Rect intersectionRectWith( Rect & r );
			//TODO
			/*Vec2D * intersectsRay( toxi::geom::Ray2D * ray, float minDist, float maxDist ); */
			bool intersectsRect( Rect & rect );
			Rect scale( const float & s );
			Rect set( const float & x, const float & y, const float & w, const float & h );
			Rect set( const Rect & r );
			Rect setDimension( const Vec2D & dim );
			Rect setPosition( const Vec2D & pos );
			Rect translate( const float & dx, const float & dy );
			Rect translate( const Vec2D & offset );
			Rect unionRectWith( const Rect & r );
			void toPolyArc( Polygon2D & poly, Vec2D & o, const double & radius, const double & theta, const int &res );

			double x, y, width, height;
		};
	}
}

#endif