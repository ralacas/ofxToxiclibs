#pragma once

#ifndef __VEC4D_H__
#define __VEC4D_H__

namespace toxi
{
	namespace geom
	{
		class Vec4D
		{
		public:
			Vec4D(void);
			Vec4D( float x, float y, float z, float w );
			Vec4D( Vec3D v, float w );
			virtual ~Vec4D(void);
			//TODO: implement


			float x, y, z, w;
		};
	}
}

#endif