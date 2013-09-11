#pragma once

#ifndef __SPHEREFUNCTION_H__
#define __SPHEREFUNCTION_H__



//#include "../Sphere.h"
//#include "SurfaceFunction.h"
#include "../Vec3D.h"
//#include "../../math/MathUtils.h"

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			//class toxi::geom::Sphere;
			//class toxi::geom::Vec3D;
			class Sphere;
			class SurfaceFunction;
			class Vec3D;
			class SphereFunction //: public SurfaceFunction //TODO FIX THIS INHERITANCE
			{
			public:
				SphereFunction(void);
				SphereFunction( float radius );
				SphereFunction( Sphere * s );
				~SphereFunction(void);

				Sphere * sphere;

				toxi::geom::Vec3D * computeVertexFor( toxi::geom::Vec3D * p, float phi, float theta );
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