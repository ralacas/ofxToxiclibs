#pragma once

#ifndef __SURFACEFUNCTION_H__
#define __SURFACEFUNCTION_H__

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

				Vec3D computeVertexFor( Vec3D p, float phi, float theta );
				float getPhiRange();
				int getPhiResolutionLimit( int res );
				float getThetaRange();
				int getThetaResolutionLimit( int res );
			};
		}
	}
}

#endif
