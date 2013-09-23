#ifndef __POLYGON_2D_H__
#define __POLYGON_2D_H__

#pragma once

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
		class Shape2D;
		class Polygon2D : public Shape2D
		{
		public:
			Polygon2D(void);
			Polygon2D( const std::vector< Vec2D > & points );
			Polygon2D( const Vec2D & baseA, const Vec2D & baseB, const int & res );
			Polygon2D( const Vec2D & v1, const Vec2D & v2 );
			Polygon2D( const Polygon2D & poly );
			~Polygon2D(void);

			std::vector< Vec2D > vertices;

			static float getRadiusForEdgeLength( const float & len, const int & res );
			static Polygon2D fromEdgeLength( const float & len, const int & res );

			Polygon2D * add( const float & x, const float & y );
			Polygon2D * add( const toxi::geom::Vec2D & v );
			std::vector< Line2D > getEdges();
			Polygon2D * center();
			Polygon2D * center( Vec2D & origin );
			bool containsPoint( Vec2D & p );
			bool containsPolygon( const Polygon2D & p );
			Polygon2D * flipVertexOrder();
			Vec2D get( const int & i );
			float getApothem();
			float getArea();
			toxi::geom::Circle getBoundingCircle();
			toxi::geom::Rect getBounds();
			Vec2D getCentroid();
			float getCircumference();
			Vec2D getClosestPointTo( Vec2D & p );
			Vec2D getClosestVertexTo( Vec2D & p );
			int getNumPoints();
			int getNumVertices();
			Vec2D getRandomPoint();
			Polygon2D  *increaseVertexCount( const int & count );
			bool intersectsPolygon( Polygon2D & p );
			bool isClockwise();
			bool isConvex();
			Polygon2D * offsetShape( const float & distance );
			Polygon2D * reduceVertices( const float & minEdgeLength );
			Polygon2D * removeDuplicates( const float & tolerance );
			Polygon2D * rotate( const float & theta );
			Polygon2D * scale( const float & scale );
			Polygon2D * scale( const float & x, const float & y );
			Polygon2D * scale( const Vec2D &v );
			Polygon2D * scaleSize( const float & scale );
			Polygon2D * scaleSize( const float & x, const float & y );
			Polygon2D * scaleSize( const Vec2D & p );
			Polygon2D * smooth( const float & amount, const float & baseWeight );
			//toxi::geom::mesh::Mesh3D toMesh( toxi::geom::mesh::Mesh3D * mesh );
			//toxi::geom::mesh::Mesh3D toMesh( toxi::geom::mesh::Mesh3D * mesh, const Vec2D & centroid2D, const float & extrude );
			bool toOutLine();
			Polygon2D toPolygon2D();
			std::string toString();
			Polygon2D * translate( const float & x, const float & y);
			Polygon2D * translate( const Vec2D & v );
			
		protected:
			void offsetCorner( const float & x1, const float & y1, const float & x2, const float & y2, const float & x3, const float & y3, const float & distance, Vec2D * out );

		};

	}
}

#endif