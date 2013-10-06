#pragma once

#ifndef __MESH3D_H__
#define __MESH3D_H__

#include < vector >

//#include "../Sphere.h"
//#include "../Vec2D.h"
#include "../Vec3D.h"

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			class Sphere;
			//class AABB;
			class Vec2D;
			class Vertex;
			class Face;
			class Vec3D;
			class Mesh3D
			{
			public:
				Mesh3D(void);
				~Mesh3D(void);

				virtual Mesh3D* addFace(const toxi::geom::Vec3D & a, const toxi::geom::Vec3D & b, const toxi::geom::Vec3D & c) = 0;
				virtual Mesh3D* addFace(const toxi::geom::Vec3D & a, const toxi::geom::Vec3D & b, const toxi::geom::Vec3D & c, const toxi::geom::Vec2D & uvA, const toxi::geom::Vec2D & uvB,	const toxi::geom::Vec2D & uvC) = 0;
				virtual Mesh3D* addFace(const toxi::geom::Vec3D & a, const toxi::geom::Vec3D & b, const toxi::geom::Vec3D & c, const toxi::geom::Vec3D & n) = 0;
				virtual Mesh3D* addFace(const toxi::geom::Vec3D & a, const toxi::geom::Vec3D & b, const toxi::geom::Vec3D & c, const toxi::geom::Vec3D & n, const toxi::geom::Vec2D & uvA,
					const toxi::geom::Vec2D & uvB, const toxi::geom::Vec2D & uvC) = 0;
				virtual Mesh3D* addMesh( Mesh3D* m ) = 0;
				virtual toxi::geom::AABB center( toxi::geom::Vec3D  &origin ) = 0;
				virtual Mesh3D* clear() = 0;
				virtual toxi::geom::Vec3D * computeCentroid() = 0;
				virtual Mesh3D* computeFaceNormals() = 0;
				virtual Mesh3D* computeVertexNormals() = 0;
				virtual Mesh3D* faceOutwards() = 0;
				virtual Mesh3D* flipVertexOrder() = 0;
				virtual Mesh3D* flipYAxis() = 0;
				virtual toxi::geom::AABB * getBoundingBox() = 0;
				//virtual toxi::geom::Sphere * getBoundingSphere() = 0;
				virtual Vertex * getClosestVertexToPoint( const toxi::geom::Vec3D & p ) = 0;
				virtual std::vector< toxi::geom::mesh::Face > getFaces() = 0;
				virtual int getNumFaces() = 0;
				virtual int getNumVertices()  = 0;
				virtual std::vector< toxi::geom::mesh::Vertex> getVertices() = 0;
				virtual Mesh3D* init( const std::string & name, const int & numV, const int & numF ) = 0;
				virtual Mesh3D* setName( const std::string & name ) = 0;
			};
		}
	}
}

#endif