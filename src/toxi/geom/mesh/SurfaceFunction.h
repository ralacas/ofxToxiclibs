#pragma once

#ifndef __SURFACEFUNCTION_H__
#define __SURFACEFUNCTION_H__

#include "../Sphere.h"
#include "../Vec3D.h"

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			class Vec3D;
			class SurfaceFunction
			{
			public:
				SurfaceFunction(void);
				~SurfaceFunction(void);

				toxi::geom::Vec3D * computeVertexFor( toxi::geom::Vec3D * p, float phi, float theta );
				float getPhiRange();
				int getPhiResolutionLimit( int res );
				float getThetaRange();
				int getThetaResolutionLimit( int res );
			};
		}
	}
}

#endif
