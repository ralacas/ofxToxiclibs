#pragma once

#include "Vec3D.h"

namespace toxi
{
	namespace geom
	{
		class AABB
		{
		public:
			AABB(void);
			~AABB(void);

			Vec3D getMin();
			Vec3D getMax();
		};
	}
}


