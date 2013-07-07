#pragma once

#include "ReadonlyVec2D.h"

namespace toxi
{
	namespace geom
	{
		class Axis2D
		{
		public:
			Axis2D(ReadonlyVec2D vec);
			~Axis2D(void);

		public:
			ReadonlyVec2D getVector( void );
			static ReadonlyVec2D X_AXIS;
			static ReadonlyVec2D Y_AXIS;
			static ReadonlyVec2D ZERO;
			static ReadonlyVec2D MIN_VALUE;
			static ReadonlyVec2D MAX_VALUE;

		private:
			ReadonlyVec2D vector;
		};


	}
}
