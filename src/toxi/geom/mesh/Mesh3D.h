#pragma once

#ifndef __MESH3D_H__
#define __MESH3D_H__

#include < vector >

namespace toxi
{
	namespace geom
	{
		namespace mesh
		{
			class Vec2D;
			class Vec3D;
			class Sphere;
			class AABB;
			class Vertex;
			class Face;

			class Mesh3D
			{
			public:
				Mesh3D(void);
				~Mesh3D(void);

				virtual Mesh3D* addFace(toxi::geom::Vec3D * a, toxi::geom::Vec3D * b, toxi::geom::Vec3D * c) = 0;
				virtual Mesh3D* addFace(toxi::geom::Vec3D * a, toxi::geom::Vec3D * b, toxi::geom::Vec3D * c, toxi::geom::Vec2D * uvA, toxi::geom::Vec2D * uvB,	toxi::geom::Vec2D * uvC) = 0;
				virtual Mesh3D* addFace(toxi::geom::Vec3D * a, toxi::geom::Vec3D * b, toxi::geom::Vec3D * c, toxi::geom::Vec3D * n) = 0;
				virtual Mesh3D* addFace(toxi::geom::Vec3D * a, toxi::geom::Vec3D * b, toxi::geom::Vec3D * c, toxi::geom::Vec3D * n,toxi::geom:: Vec2D * uvA,
					toxi::geom::Vec2D * uvB, toxi::geom::Vec2D * uvC) = 0;
				virtual Mesh3D* addMesh( Mesh3D* m );
				virtual AABB center( Vec3D origin );
				virtual Mesh3D* clear();
				virtual Vec3D computeCentroid();
				virtual Mesh3D* computeFaceNormals();
				virtual Mesh3D* computeVertexNormals();
				virtual Mesh3D* faceOutwards();
				virtual Mesh3D* flipVertexOrder();
				virtual Mesh3D* flipYAxis();
				virtual AABB * getBoundingBox();
				virtual Sphere getBoundingSphere();
				virtual Vertex getClosestVertexToPoint( Vec3D p );
				virtual std::vector< toxi::geom::mesh::Face > getFaces();
				virtual int getNumFaces();
				virtual int getNumVertices();
				virtual std::vector< toxi::geom::mesh::Vertex> getVertices();
				virtual Mesh3D* init( std::string name, int numV, int numF );
				virtual Mesh3D* setName( std::string name );
			};
		}
	}
}

#endif