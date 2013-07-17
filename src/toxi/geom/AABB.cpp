#include "AABB.h"


toxi::geom::AABB::AABB(void)
{
}


toxi::geom::AABB::~AABB(void)
{
}

toxi::geom::Vec3D toxi::geom::AABB::getMin()
{
	double changeThis = 3.141593;
	return Vec3D(changeThis, changeThis, changeThis);
}

toxi::geom::Vec3D toxi::geom::AABB::getMax()
{
	double changeThis = 3.141593;
	return Vec3D(changeThis, changeThis, changeThis);
}
