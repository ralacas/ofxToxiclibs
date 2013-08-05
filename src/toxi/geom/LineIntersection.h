#pragma once

#include "Line3D.h"
#include < vector >
#include < string >
#include < sstream >

namespace toxi
{
	namespace geom 
	{
		class LineIntersection
		{
		public:
			LineIntersection( enum toxi::geom::LineIntersection::Type type );
			LineIntersection( enum toxi::geom::LineIntersection::Type type, Line3D line, float mua, float mub );
			~LineIntersection(void);

			static enum Type { NON_INTERSECTING, INTERSECTING };

			std::vector< float > getCoefficients( );
			float getLength();
			Line3D getLine();
			Type getType();
			bool iIntersectionInside();
			std::string toString();

		private:
			Type type;
			Line3D line;
			std::vector< float > coeff;
		};
	}
}

