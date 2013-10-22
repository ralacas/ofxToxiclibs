#include "IsectData3D.h"
#include "Vec3D.h"

toxi::geom::IsectData3D::IsectData3D(void)
{
}


toxi::geom::IsectData3D::~IsectData3D(void)
{
}

void toxi::geom::IsectData3D::clear()
{
	isIntersection = false;
	dist = 0.0;
	pos = toxi::geom::Vec3D( );
	dir = Vec3D( );
	normal = Vec3D( );
}

std::string toxi::geom::IsectData3D::toString()
{
	std::stringstream ss;
	ss << "isec: " << isIntersection;
	if( isIntersection )
	{
		ss << " at: " << pos << " dist: " << dist << " normal: " << normal;
	}
	return ss.str();
}
