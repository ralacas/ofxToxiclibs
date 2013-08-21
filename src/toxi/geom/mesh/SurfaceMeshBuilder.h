#pragma once

#ifndef __SURFACEMESHBUILDER_H__
#define __SURFACEMESHBUILDER_H__

#include "../Vec3D.h"

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			
			class Vec2D;
			class SurfaceFunction;
			class Mesh3D;
			class TriangleMesh;
			class Vec3D;
			class SurfaceMeshBuilder :
				public toxi::geom::Vec3D
			{
			public:
				SurfaceMeshBuilder( SurfaceFunction function );
				~SurfaceMeshBuilder(void);

				Mesh3D createMesh( int res );
				Mesh3D createMesh( Mesh3D mesh, int res, float size );
				Mesh3D createMesh( Mesh3D mesh, int res, float size, bool isClosed );

				SurfaceFunction getFunction();
				void setFunction( SurfaceFunction function );

			protected:
				SurfaceFunction function;
			};

		}
	}
}

#endif
