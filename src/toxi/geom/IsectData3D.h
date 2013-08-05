#pragma once

#include < string >
#include < sstream >
#include "Vec3D.h"

namespace toxi
{
	namespace geom
	{
		class IsectData3D
		{
		public:
			IsectData3D(void);
			~IsectData3D(void);

			void clear();
			std::string toString();

			bool isIntersection;
			float dist;
			Vec3D pos;
			Vec3D dir;
			Vec3D normal;
		};
	}
}


