#pragma once

#include "..\Vec3D.h"
#include "..\Vec2D.h"
#include "SurfaceFunction.h"
#include "Mesh3D.h"
#include "TriangleMesh.h"

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
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


