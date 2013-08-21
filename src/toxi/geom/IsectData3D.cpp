#include "IsectData3D.h"


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
	pos = new Vec3D( );
	dir = new Vec3D( );
	normal = new Vec3D( );
}

std::string toxi::geom::IsectData3D::toString()
{
	std::stringstream ss;
	ss << "isec: " << isIntersection;
	if( isIntersection )
	{
		ss << " at: " << pos->toString() << " dist: " << dist << " normal: " << normal->toString();
	}
	return ss.str();
}
