#pragma once

#ifndef __TRIANGLEMESH_H__
#define __TRIANGLEMESH_H__

#include < string >
#include < vector >
#include < map >
#include <utility>

#include "../IsectData3D.h"
#include "../Ray3D.h"
#include "../Triangle3D.h"
#include "../Matrix4x4.h"
#include "../TriangleIntersector.h"
//#include "../Matrix4x4.h"
//#include "../Quaternion.h"
//#include "../Sphere.h"
//#include "../TriangleIntersector.h"
#include "../Vec3D.h"
//#include "Face.h"
//#include "Mesh3D.h"
//#include "OBJWriter.h"
//#include "STLWriter.h"
//#include "Vertex.h"
//#include "WETriangleMesh.h"

namespace toxi 
{
	namespace geom
	{
		namespace mesh
		{
			class Sphere;
			class AABB;
			class Mesh3D;
			class Vec3D;
			class Vertex;
			class Face;
			class Vec2D;
			class IsectData3D;
			class Ray3D;
			class Triangle3D;
			class OBJWriter;
			class Matrix4x4;
			class WETriangleMesh;
			class STLWriter;
			class TriangleIntersector;
			class TriangleMesh// : public Mesh3D
			{
			public:
				TriangleMesh( void );
				TriangleMesh( std::string name );
				TriangleMesh( std::string name, int numV, int numF );

				~TriangleMesh( void );
				static int DEFAULT_NUM_VERTICES;
				static int DEFAULT_NUN_FACES;
				static int DEFAULT_STRIDE;

				std::string name;
				std::map< toxi::geom::Vec3D, toxi::geom::mesh::Vertex > vertices;
				std::vector< Face > faces;

				//TODO they should always return a pointer to themselves
				TriangleMesh* addFace( toxi::geom::Vec3D * a, toxi::geom::Vec3D * b, toxi::geom::Vec3D * c );
				TriangleMesh* addFace( toxi::geom::Vec3D * a, toxi::geom::Vec3D * b, toxi::geom::Vec3D * c, toxi::geom::Vec2D * uvA,
					toxi::geom::Vec2D * uvB, toxi::geom::Vec2D * uvC );
				TriangleMesh* addFace( toxi::geom::Vec3D * a, toxi::geom::Vec3D * b, toxi::geom::Vec3D * c, toxi::geom::Vec3D * n );
				TriangleMesh* addFace( toxi::geom::Vec3D * a, toxi::geom::Vec3D * b, toxi::geom::Vec3D * c, toxi::geom::Vec3D * n, toxi::geom::Vec2D * uvA,
					toxi::geom::Vec2D * uvB, toxi::geom::Vec2D * uvC );
				TriangleMesh* addMesh( Mesh3D& m );
				toxi::geom::AABB * center( toxi::geom::Vec3D * origin );
				Vertex checkVertex( toxi::geom::Vec3D * v );
				TriangleMesh* clear();
				toxi::geom::Vec3D computeCentroid();
				TriangleMesh* computeFaceNormals();
				TriangleMesh* computeVertexNormals();
				Vertex createVertex( toxi::geom::Vec3D v, int id );
				TriangleMesh* faceOutwards();
				TriangleMesh* flipVertexOrder();
				TriangleMesh* flipYAxis();
				toxi::geom::AABB * getBoundingBox();
				//toxi::geom::Sphere * getBoundingSphere();
				Vertex getClosestVertexToPoint( toxi::geom::Vec3D p );
				std::vector< float> * getFaceNormalsAsArray();
				std::vector< float> * getFaceNormalsAsArray( int offset, int stride );
				std::vector< Face > getFaces();
				toxi::geom::IsectData3D getIntersectionData();
				std::vector< float> * getMeshAsVertexArray();
				std::vector< float> * getMeshAsVertexArray( int offset, int strie );
				std::vector< float> * getNormalsForUniqueVerticesArray();
				int getNumFaces();
				int getNumVertices();
				TriangleMesh* getRotatedAroundAxis( toxi::geom::Vec3D axis, float theta );
				TriangleMesh* getRotatedX( float theta );
				TriangleMesh* getRotatedY( float theta );
				TriangleMesh* getRotatedZ( float theta );
				TriangleMesh* getScaled( float factor );
				TriangleMesh* getScaled( toxi::geom::Vec3D scale );
				TriangleMesh* getTranslated( toxi::geom::Vec3D trans );
				std::vector< float> * getUniqueVerticesAsArray();
				Vertex getVertexAtPoint( toxi::geom::Vec3D v );
				Vertex getVertexForID( int id );
				std::vector< float> * getVertexNormalsAsArray();
				std::vector< float> * getVertexNormalsAsArray( int offset, int stride );
				std::vector< Vertex > getVertices();
				TriangleMesh* init( std::string name, int numV, int numF );
				bool intersectsRay( toxi::geom::Ray3D ray );
				toxi::geom::Triangle3D perforateFace( Face f, float size );
				TriangleMesh* pointTowards( toxi::geom::Vec3D dir );
				TriangleMesh* pointTowards( toxi::geom::Vec3D dir, toxi::geom::Vec3D forward );
				void remove( Face f );
				TriangleMesh* rotateAroundAxis( toxi::geom::Vec3D axis, float theta );
				TriangleMesh* rotateX( float theta );
				TriangleMesh* rotateY( float theta );
				TriangleMesh* rotateZ( float theta );
				void saveAsOBJ( OBJWriter * obj );
				void saveAsOBJ( OBJWriter * obj, bool saveNormals );
				void saveAsOBJ( std::string path );
				void saveAsOBJ( std::string path, bool saveNormals );
				void saveAsSTL( std::string path );
				void saveAsSTL( std::string path, bool useFlippedY );
				TriangleMesh* scale( float scale );
				TriangleMesh* scale( float _x, float _y, float _z );
				TriangleMesh* setName( std::string name );
				std::string toString();
				WETriangleMesh toWEMesh();
				TriangleMesh* transform( toxi::geom::Matrix4x4 mat );
				TriangleMesh* transform( toxi::geom::Matrix4x4 mat, bool updateNormals );
				TriangleMesh* translate( float _x, float _y, float _z );
				TriangleMesh* translate( toxi::geom::Vec3D trans );
				TriangleMesh* updateVertex( toxi::geom::Vec3D orig, toxi::geom::Vec3D newPos );

				

			protected:
				void handleSaveAsStl( STLWriter stl, bool useFlippedY );


			protected:
				toxi::geom::AABB * bounds;
				toxi::geom::Vec3D * centroid;
				int numVertices;
				int numFaces;
				toxi::geom::Matrix4x4 * matrix;
				toxi::geom::TriangleIntersector * intersector;
				int uniqueVertexID;


			private:

			};
		}
	}
}

#endif