#pragma once

#include "Vec2D.h"

namespace toxi
{
	namespace geom
	{
		class Axis2D
		{
		public:
			Axis2D(Vec2D vec);
			~Axis2D(void);

		public:
			Vec2D getVector( void );
			static Vec2D X_AXIS;
			static Vec2D Y_AXIS;
			static Vec2D ZERO;
			static Vec2D MIN_VALUE;
			static Vec2D MAX_VALUE;

		private:
			Vec2D vector;
		};


	}
}
