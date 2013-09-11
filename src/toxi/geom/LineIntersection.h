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
		class LineIntersection
		{
		public:
			static enum Type { NON_INTERSECTING, INTERSECTING };

			LineIntersection( enum toxi::geom::LineIntersection::Type type );
			LineIntersection( enum toxi::geom::LineIntersection::Type type, toxi::geom::Line3D line, float mua, float mub );
			~LineIntersection(void);

			std::vector< float > getCoefficients();
			float getLength();
			toxi::geom::Line3D * getLine();
			Type getType();
			bool iIntersectionInside();
			std::string toString();

		private:
			Type type;
			toxi::geom::Line3D * line;
			std::vector< float > coeff;
		};
	}
}

#endif