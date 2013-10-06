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
#include "../Vec3D.h"
#include "../AABB.h"
#include "Mesh3D.h"

namespace toxi 
{
	namespace geom
	{
		namespace mesh
		{
			class Sphere;
			class toxi::geom::AABB;
			class Mesh3D;
			class toxi::geom::Vec3D;
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
			class TriangleMesh : public Mesh3D
			{
			public:
				TriangleMesh( void );
				TriangleMesh( const std::string & name );
				TriangleMesh( const std::string & name, const int & numV, const int & numF );

				~TriangleMesh( void );
				static int DEFAULT_NUM_VERTICES;
				static int DEFAULT_NUN_FACES;
				static int DEFAULT_STRIDE;

				std::string name;
				std::map< toxi::geom::Vec3D, toxi::geom::mesh::Vertex > vertices;
				std::vector< Face > faces;

				//TODO they should always return a pointer to themselves
				TriangleMesh * addFace( const toxi::geom::Vec3D & a, const toxi::geom::Vec3D &  b, const toxi::geom::Vec3D &  c );
				TriangleMesh * addFace( const toxi::geom::Vec3D &  a, const toxi::geom::Vec3D &  b, const toxi::geom::Vec3D &  c, const toxi::geom::Vec2D  & uvA,
					const toxi::geom::Vec2D  & uvB, const toxi::geom::Vec2D  & uvC );
				TriangleMesh  *addFace( const toxi::geom::Vec3D &  a, const toxi::geom::Vec3D &  b, const toxi::geom::Vec3D &  c, const toxi::geom::Vec3D &  n );
				TriangleMesh * addFace( const toxi::geom::Vec3D &  a, const toxi::geom::Vec3D &  b, const toxi::geom::Vec3D &  c, const toxi::geom::Vec3D &  n, const toxi::geom::Vec2D  & uvA,
					const toxi::geom::Vec2D  & uvB, const toxi::geom::Vec2D  & uvC );
				toxi::geom::AABB center( toxi::geom::Vec3D & origin );
				Vertex checkVertex( const toxi::geom::Vec3D &  v );
				TriangleMesh * clear();	
				toxi::geom::Vec3D * computeCentroid();
				TriangleMesh * computeFaceNormals();
				TriangleMesh * computeVertexNormals();
				Vertex createVertex( const toxi::geom::Vec3D & v, const int & id );
				TriangleMesh * faceOutwards();
				TriangleMesh * flipVertexOrder();
				TriangleMesh * flipYAxis();
				toxi::geom::AABB * getBoundingBox();
				Vertex * getClosestVertexToPoint( const toxi::geom::Vec3D & p );
				std::vector< double>  getFaceNormalsAsArray();
				std::vector< double>  getFaceNormalsAsArray( const int & offset, int & stride );
				std::vector< Face > getFaces();
				toxi::geom::IsectData3D getIntersectionData();
				std::vector< double>  getMeshAsVertexArray();
				std::vector< double>  getMeshAsVertexArray( const int & offset, int & strie );
				std::vector< double>  getNormalsForUniqueVerticesArray();
				int getNumFaces();
				int getNumVertices();
				TriangleMesh * getRotatedAroundAxis( const toxi::geom::Vec3D & axis, const float & theta );
				TriangleMesh * getRotatedX( const float & theta );
				TriangleMesh * getRotatedY( const float & theta );
				TriangleMesh * getRotatedZ( const float & theta );
				TriangleMesh * getScaled( const float & factor );
				TriangleMesh * getScaled( const toxi::geom::Vec3D & scale );
				TriangleMesh * getTranslated( const toxi::geom::Vec3D & trans );
				std::vector< float>  getUniqueVerticesAsArray();
				Vertex getVertexAtPoint( const toxi::geom::Vec3D & v );
				Vertex getVertexForID( const int & id );
				std::vector< float>  getVertexNormalsAsArray();
				std::vector< float>  getVertexNormalsAsArray( const int & offset, int & stride );
				std::vector< Vertex > getVertices();
				TriangleMesh * init( const std::string & name, const int & numV, const int & numF );
				bool intersectsRay( toxi::geom::Ray3D & ray );
				toxi::geom::Triangle3D perforateFace( Face & f, const float & size );
				TriangleMesh * pointTowards( toxi::geom::Vec3D & dir );
				TriangleMesh * pointTowards( toxi::geom::Vec3D & dir, toxi::geom::Vec3D & forward );
				void remove( const Face & f );
				TriangleMesh * rotateAroundAxis( const toxi::geom::Vec3D & axis, const float & theta );
				TriangleMesh * rotateX( const float & theta );
				TriangleMesh * rotateY( const float & theta );
				TriangleMesh * rotateZ( const float & theta );
				void saveAsOBJ(  OBJWriter  & obj );
				void saveAsOBJ(  OBJWriter  & obj, const bool & saveNormals );
				void saveAsOBJ( const std::string & path );
				void saveAsOBJ( const std::string & path, const bool & saveNormals );
				void saveAsSTL( const std::string & path );
				void saveAsSTL( const std::string & path, const bool & useFlippedY );
				TriangleMesh * scale( const float & scale );
				TriangleMesh * scale( const float & _x, const float & _y, const float & _z );
				TriangleMesh * setName( const std::string & name );
				std::string toString();
				WETriangleMesh * toWEMesh();
				TriangleMesh * transform( toxi::geom::Matrix4x4 & mat );
				TriangleMesh * transform( toxi::geom::Matrix4x4 & mat, const bool & updateNormals );
				TriangleMesh * translate( const float & _x, const float & _y, const float & _z );
				TriangleMesh * translate( const toxi::geom::Vec3D & trans );
				TriangleMesh * updateVertex( const toxi::geom::Vec3D & orig, const toxi::geom::Vec3D & newPos );

				

			protected:
				void handleSaveAsStl( STLWriter & stl, const bool & useFlippedY );

				toxi::geom::AABB  bounds;
				toxi::geom::Vec3D  centroid;
				int numVertices;
				int numFaces;
				toxi::geom::Matrix4x4  matrix;
				toxi::geom::TriangleIntersector  intersector;
				int uniqueVertexID;

				toxi::geom::mesh::Mesh3D  * addMesh( toxi::geom::mesh::Mesh3D *  m );
				Vertex  getClosestVertexToPoint( const Vec3D  & p );

			};
		}
	}
}

#endif