#pragma once

#include "ReadonlyVec3D.h"
#include "Vec3D.h"

namespace toxi
{
	namespace geom
	{
		class Axis3D
		{
		public:
			Axis3D( Vec3D vec );
			~Axis3D(void);

			Vec3D getVector( void );

			static Vec3D X_AXIS;
			static Vec3D Y_AXIS;
			static Vec3D Z_AXIS;
			static Vec3D ZERO;
			static Vec3D MIN_VALUE;
			static Vec3D MAX_VALUE;

		private: 
			Vec3D vector;
		};
	}
}
