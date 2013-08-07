#include "SurfaceFunction.h"


toxi::geom::mesh::SurfaceFunction::SurfaceFunction(void)
{
	// TODO: is this a good substitution for the SphereFunction interface?
	// declaring interfaces in c++ looks spooky to me.
}


toxi::geom::mesh::SurfaceFunction::~SurfaceFunction(void)
{
}

toxi::geom::Vec3D toxi::geom::mesh::SurfaceFunction::computeVertexFor( Vec3D p, float phi, float theta )
{
	return Vec3D();
}

float toxi::geom::mesh::SurfaceFunction::getPhiRange()
{
	return 0.0;
}

int toxi::geom::mesh::SurfaceFunction::getPhiResolutionLimit( int res )
{
	return 0;
}

float toxi::geom::mesh::SurfaceFunction::getThetaRange()
{
	return 0.0;
}

int toxi::geom::mesh::SurfaceFunction::getThetaResolutionLimit( int res )
{
	return 0;
}
