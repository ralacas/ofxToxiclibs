#ifndef __POLYGON_2D_H__
#define __POLYGON_2D_H__

#pragma once

//#include "Vec2D.h"
//#include "Circle.h"
#include "Shape2D.h"
#include "mesh/Mesh3D.h"
#include <vector>

namespace toxi
{
	namespace geom
	{
		class Vec2D;
		class Vec3D;
		class Line2D;
		class Polygon2D : public Shape2D
		{
		public:
			Polygon2D(void);
			Polygon2D( std::vector< Vec2D > points );
			Polygon2D( Vec2D baseA, Vec2D baseB, int res );
			Polygon2D( Vec2D v1, Vec2D v2 );
			Polygon2D( const Polygon2D & poly );
			~Polygon2D(void);

			std::vector< Vec2D > vertices;

			static float getRadiusForEdgeLength( float len, int res );
			static Polygon2D fromEdgeLength( float len, int res );

			Polygon2D * add( float x, float y );
			Polygon2D * add( toxi::geom::Vec2D v );
			std::vector< Line2D * > getEdges();
			Polygon2D * center();
			Polygon2D * center( Vec2D origin );
			bool containsPoint( Vec2D * p );
			bool containsPolygon( Polygon2D * p );
			Polygon2D * flipVertexOrder();
			Vec2D get( int i );
			float getApothem();
			float getArea();
			toxi::geom::Circle * getBoundingCircle();
			toxi::geom::Rect * getBounds();
			Vec2D getCentroid();
			float getCircumference();
			Vec2D getClosestPointTo( Vec2D p );
			Vec2D getClosestVertexTo( Vec2D p );
			int getNumPoints();
			int getNumVertices();
			Vec2D * getRandomPoint();
			Polygon2D * increaseVertexCount( int count );
			bool intersectsPolygon( Polygon2D * p );
			bool isClockwise();
			bool isConvex();
			Polygon2D * offsetShape( float distance );
			Polygon2D * reduceVertices( float minEdgeLength );
			Polygon2D * removeDuplicates( float tolerance );
			Polygon2D * rotate( float theta );
			Polygon2D * scale( float scale );
			Polygon2D * scale( float x, float y );
			Polygon2D * scale( Vec2D v );
			Polygon2D * scaleSize( float scale );
			Polygon2D * scaleSize( float x, float y );
			Polygon2D * scaleSize( Vec2D p );
			Polygon2D * smooth( float amount, float baseWeight );
			toxi::geom::mesh::Mesh3D * toMesh(toxi::geom::mesh::Mesh3D * mesh );
			toxi::geom::mesh::Mesh3D * toMesh( toxi::geom::mesh::Mesh3D * mesh, Vec2D * centroid2D, float extrude );
			bool toOutLine();
			Polygon2D * toPolygon2D();
			std::string toString();
			Polygon2D * translate( float x, float y);
			Polygon2D * translate( Vec2D v );
			
		protected:
			void offsetCorner( float x1, float y1, float x2, float y2, float x3, float y3, float distance, Vec2D * out );

		};

	}
}

#endif