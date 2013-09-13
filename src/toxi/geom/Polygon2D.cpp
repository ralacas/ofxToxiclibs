#include "Polygon2D.h"
#include <vector>
#include "Line2D.h"


toxi::geom::Polygon2D::Polygon2D(void)
{
}


toxi::geom::Polygon2D::~Polygon2D(void)
{
}

toxi::geom::Polygon2D toxi::geom::Polygon2D::add( float x, float y )
{
	return *this;
}

toxi::geom::Polygon2D toxi::geom::Polygon2D::add( toxi::geom::Vec2D * v )
{
	return *this;
}

std::vector< toxi::geom::Line2D * > toxi::geom::Polygon2D::getEdges()
{
	int num = vertices.size();
	std::vector< Line2D * > edges;
	for( int i = 0; i < num; i++ )
	{
		int i2 = std::fmod( ( i + 1 ), num );
		edges.push_back( new Line2D( vertices[i], vertices[ i2 ] ) );
	}
}
