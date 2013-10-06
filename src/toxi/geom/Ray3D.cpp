#include "Ray3D.h"
#include "Line3D.h"


toxi::geom::Ray3D::Ray3D(void)
{
	//TODO 
}

toxi::geom::Ray3D::Ray3D( const float & x, const float & y, const float & z, const toxi::geom::Vec3D & d )
{
	//TODO
}

toxi::geom::Ray3D::Ray3D( const toxi::geom::Vec3D & o, const toxi::geom::Vec3D & d )
{
	//TODO
}


toxi::geom::Ray3D::~Ray3D(void)
{
}

toxi::geom::Vec3D toxi::geom::Ray3D::getDirection()
{
	return dir;
}

toxi::geom::Vec3D toxi::geom::Ray3D::getPointAtDistance( const float & d )
{
	Vec3D v = Vec3D();
	return v;
}

float toxi::geom::Ray3D::getDistanceToPoint( const toxi::geom::Vec3D & v )
{
	return 0.0f;
}

toxi::geom::Ray3D toxi::geom::Ray3D::setDirection( const toxi::geom::Vec3D & v )
{
	
}

toxi::geom::Line3D toxi::geom::Ray3D::toLine3DWithPointAtDistance( const float & dist )
{

}

std::string toxi::geom::Ray3D::toString()
{

}
