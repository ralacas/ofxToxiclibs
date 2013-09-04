#pragma once

#ifndef __SURFACEMESHBUILDER_H__
#define __SURFACEMESHBUILDER_H__

#include "../Vec2D.h"
#include "../Vec3D.h"
#include "SurfaceFunction.h"
#include "TriangleMesh.h"

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			
			//class Vec2D;
			class SurfaceFunction;// TODO this too.
			class Mesh3D;
			class TriangleMesh;
			//class Vec3D; //TODO this might fuck things up
			class SurfaceMeshBuilder :
				public toxi::geom::Vec3D
			{
			public:
				SurfaceMeshBuilder();
				SurfaceMeshBuilder( SurfaceFunction * function );
				//SurfaceMeshBuilder( SphereFunction * f );
				~SurfaceMeshBuilder(void);

				Mesh3D * createMesh( int res );
				Mesh3D * createMesh( Mesh3D * mesh, int res, float size );
				Mesh3D * createMesh( Mesh3D * mesh, int res, float size, bool isClosed );

				toxi::geom::mesh::SurfaceFunction * getFunction();
				void setFunction( SurfaceFunction * function );

			protected:
				toxi::geom::mesh::SurfaceFunction * function;
			};

		}
	}
}

#endif
