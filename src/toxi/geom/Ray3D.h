#pragma once
#include "Vec3D.h"

namespace toxi
{
	namespace geom
	{
		class Ray3D :
			public toxi::geom::Vec3D
		{
		public:
			Ray3D(void);
			~Ray3D(void);

			Vec3D getDirection( );
			Vec3D getPointAtDistance( float d );
		};
	}
}


