#pragma once

#include "Vec3D.h"

#include < string >
#include < sstream >

namespace toxi
{
	namespace geom
	{
		class Vec3D;
		class IsectData3D
		{
		public:
			IsectData3D(void);
			~IsectData3D(void);

			void clear();
			std::string toString();

			bool isIntersection;
			float dist;
			toxi::geom::Vec3D * pos; // TODO: every pointer needs to be deleted.
			toxi::geom::Vec3D * dir;
			toxi::geom::Vec3D * normal;
		};
	}
}


