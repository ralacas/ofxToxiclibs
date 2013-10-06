#pragma once

#ifndef __LINEINTERSECTION_H__
#define __LINEINTERSECTION_H__

#include < vector >
#include < string >
#include < sstream >

//#include "Line3D.h"

namespace toxi
{
	namespace geom 
	{
		class Line3D;
		class Vec2D;
		class LineIntersection
		{
		public:
			static enum Type { COINCIDENT, COINCIDENT_NO_INTERSECT, PARALLEL, NON_INTERSECTING, INTERSECTING };

			LineIntersection( enum toxi::geom::LineIntersection::Type type );
			LineIntersection( enum toxi::geom::LineIntersection::Type type, Vec2D * pos );
			LineIntersection( enum toxi::geom::LineIntersection::Type type, toxi::geom::Vec2D line, float mua, float mub );
			~LineIntersection(void);

			std::vector< float > getCoefficients();
			float getLength();
			toxi::geom::Vec2D * getLine();
			Type getType();
			bool iIntersectionInside();
			std::string toString();
			Vec2D getPos();

		private:
			Type type;
			toxi::geom::Vec2D * line;
			std::vector< float > coeff;
		};
	}
}

#endif