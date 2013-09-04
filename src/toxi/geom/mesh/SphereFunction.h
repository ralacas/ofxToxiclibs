#pragma once

#ifndef __SPHEREFUNCTION_H__
#define __SPHEREFUNCTION_H__

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			class Sphere;
			class Vec3D;
			class SurfaceFunction;
			class SphereFunction :
				public SurfaceFunction
			{
			public:
				SphereFunction(void);
				SphereFunction( float radius );
				SphereFunction( Sphere s );
				~SphereFunction(void);

				Sphere * sphere;

				Vec3D computeVertexFor( Vec3D p, float phi, float theta );
				float getPhiRange();
				int getPhiResolutionLimit(int res );
				float getThetaRange();
				int getThetaResolutionLimit( int res );
				void setMaxPhi( float max );
				void setMaxTheta( float max );

			protected:
				float phiRange;
				float thetaRange;
			};

		}
	}
}

#endif