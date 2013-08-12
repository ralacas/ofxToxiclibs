#pragma once

#include "..\Vec3D.h"

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
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

