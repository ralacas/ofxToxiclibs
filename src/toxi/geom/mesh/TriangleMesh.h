#pragma once

#include < string >
#include < vector >
#include < map >
#include "Face.h"
#include "OBJWriter.h"
#include "STLWriter.h"
#include "WETriangleMesh.h"
#include "../Vec3D.h"
#include "../Vec2D.h"
#include "Vertex.h"
#include "../Matrix4x4.h"
#include "../TriangleIntersector.h"
#include "../Sphere.h"
#include "../Quaternion.h"

namespace toxi 
{
	namespace geom
	{
		namespace mesh
		{
			class TriangleMesh : public Mesh3D
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
				std::map< Vec3D, Vertex > vertices;
				std::vector< Face > faces;

				//TODO they should always return a pointer to themselves
				TriangleMesh* addFace( Vec3D * a, Vec3D * b, Vec3D * c );
				TriangleMesh* addFace( Vec3D * a, Vec3D * b, Vec3D * c, Vec2D * uvA,
					Vec2D * uvB, Vec2D * uvC );
				TriangleMesh* addFace( Vec3D * a, Vec3D * b, Vec3D * c, Vec3D * n );
				TriangleMesh* addFace( Vec3D * a, Vec3D * b, Vec3D * c, Vec3D * n, Vec2D * uvA,
					Vec2D * uvB, Vec2D * uvC );
				TriangleMesh* addMesh( Mesh3D& m );
				AABB center( Vec3D * origin );
				Vertex checkVertex( Vec3D * v );
				TriangleMesh* clear();
				Vec3D computeCentroid();
				TriangleMesh* computeFaceNormals();
				TriangleMesh* computeVertexNormals();
				Vertex createVertex( Vec3D v, int id );
				TriangleMesh* faceOutwards();
				TriangleMesh* flipVertexOrder();
				TriangleMesh* flipYAxis();
				AABB getBoundingBox();
				Sphere getBoundingSphere();
				Vertex getClosestVertexToPoint( Vec3D p );
				std::vector< float> * getFaceNormalsAsArray();
				std::vector< float> * getFaceNormalsAsArray( int offset, int stride );
				std::vector< Face > getFaces();
				IsectData3D getIntersectionData();
				std::vector< float> * getMeshAsVertexArray();
				std::vector< float> * getMeshAsVertexArray( int offset, int strie );
				std::vector< float> * getNormalsForUniqueVerticesArray();
				int getNumFaces();
				int getNumVertices();
				TriangleMesh* getRotatedAroundAxis( Vec3D axis, float theta );
				TriangleMesh* getRotatedX( float theta );
				TriangleMesh* getRotatedY( float theta );
				TriangleMesh* getRotatedZ( float theta );
				TriangleMesh* getScaled( float factor );
				TriangleMesh* getScaled( Vec3D scale );
				TriangleMesh* getTranslated( Vec3D trans );
				std::vector< float> * getUniqueVerticesAsArray();
				Vertex getVertexAtPoint( Vec3D v );
				Vertex getVertexForID( int id );
				std::vector< float> * getVertexNormalsAsArray();
				std::vector< float> * getVertexNormalsAsArray( int offset, int stride );
				std::vector< Vertex > getVertices();
				TriangleMesh* init( std::string name, int numV, int numF );
				bool intersectsRay( Ray3D ray );
				Triangle3D perforateFace( Face f, float size );
				TriangleMesh* pointTowards( Vec3D dir );
				TriangleMesh* pointTowards( Vec3D dir, Vec3D forward );
				void remove( Face f );
				TriangleMesh* rotateAroundAxis( Vec3D axis, float theta );
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
				TriangleMesh* transform( Matrix4x4 mat );
				TriangleMesh* transform( Matrix4x4 mat, bool updateNormals );
				TriangleMesh* translate( float _x, float _y, float _z );
				TriangleMesh* translate( Vec3D trans );
				TriangleMesh* updateVertex( Vec3D orig, Vec3D newPos );


			protected:
				void handleSaveAsStl( STLWriter stl, bool useFlippedY );


			protected:
				AABB bounds;
				Vec3D centroid;
				int numVertices;
				int numFaces;
				Matrix4x4 matrix;
				TriangleIntersector intersector;
				int uniqueVertexID;


			private:

			};
		}
	}
}