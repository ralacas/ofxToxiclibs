#include "Ray3D.h"


toxi::geom::Ray3D::Ray3D(void)
{
	//TODO 
}

toxi::geom::Ray3D::Ray3D( float x, float y, float z, toxi::geom::Vec3D * d )
{
	//TODO
}

toxi::geom::Ray3D::Ray3D( toxi::geom::Vec3D * o, toxi::geom::Vec3D * d )
{
	//TODO
}


toxi::geom::Ray3D::~Ray3D(void)
{
}

toxi::geom::Vec3D * toxi::geom::Ray3D::getDirection()
{
	return dir;
}

toxi::geom::Vec3D * toxi::geom::Ray3D::getPointAtDistance( float d )
{
	Vec3D * v;
	return v;
}

float toxi::geom::Ray3D::getDistanceToPoint( toxi::geom::Vec3D * v )
{

}

toxi::geom::Ray3D toxi::geom::Ray3D::setDirection( toxi::geom::Vec3D * v )
{

}

toxi::geom::Line3D toxi::geom::Ray3D::toLine3DWithPointAtDistance( float dist )
{

}

std::string toxi::geom::Ray3D::toString()
{

}
