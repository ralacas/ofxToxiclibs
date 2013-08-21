#pragma once

#include "Vec3D.h"

namespace toxi
{
	namespace geom
	{
		class Vec3D;
		class Axis3D
		{
		public:
			Axis3D( toxi::geom::Vec3D * vec );
			~Axis3D(void);

			toxi::geom::Vec3D * getVector( void );

			static toxi::geom::Axis3D * X_AXIS();
			static toxi::geom::Axis3D * Y_AXIS();
			static toxi::geom::Axis3D * Z_AXIS();
			static toxi::geom::Vec3D * ZERO;
			static toxi::geom::Vec3D * MIN_VALUE;
			static toxi::geom::Vec3D * MAX_VALUE;

		private: 
			toxi::geom::Vec3D * vector;
		};
	}
}
