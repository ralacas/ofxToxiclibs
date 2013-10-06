#include "SphereFunction.h"


toxi::geom::mesh::SphereFunction::SphereFunction(void)
{
	SphereFunction( 1 );
}

toxi::geom::mesh::SphereFunction::SphereFunction( float radius )
{
	//SphereFunction( new toxi::geom::Sphere( toxi::geom::Vec3D(), radius ) );
	//TODO: FHIX THIS
}

toxi::geom::mesh::SphereFunction::SphereFunction( const Sphere & s )
{
	this->sphere = sphere;
}


toxi::geom::mesh::SphereFunction::~SphereFunction(void)
{
	//delete sphere;
}

toxi::geom::Vec3D toxi::geom::mesh::SphereFunction::computeVertexFor( toxi::geom::Vec3D p, float phi, float theta )
{
	phi -= static_cast< float > ( toxi::math::MathUtils::HALF_PI );
	float cosPhi = toxi::math::MathUtils::cos(phi);
	float cosTheta = toxi::math::MathUtils::cos(theta);
	float sinPhi = toxi::math::MathUtils::sin(phi);
	float sinTheta = toxi::math::MathUtils::sin(theta);
	float t = toxi::math::MathUtils::sign(cosPhi) * toxi::math::MathUtils::abs(cosPhi);
	p.set(t * toxi::math::MathUtils::sign(cosTheta) * toxi::math::MathUtils::abs(cosTheta), toxi::math::MathUtils::sign(sinPhi) * toxi::math::MathUtils::abs(sinPhi), t * toxi::math::MathUtils::sign(sinTheta) * toxi::math::MathUtils::abs(sinTheta) );

	//return p->scaleSelf(sphere->radius)->addSelf(sphere);
	//TODO
	return toxi::geom::Vec3D();
}

float toxi::geom::mesh::SphereFunction::getPhiRange()
{
	return phiRange;
}

int toxi::geom::mesh::SphereFunction::getPhiResolutionLimit( int res )
{
	return res;
}

float toxi::geom::mesh::SphereFunction::getThetaRange()
{
	return thetaRange;
}

int toxi::geom::mesh::SphereFunction::getThetaResolutionLimit( int res )
{
	return res;
}

void toxi::geom::mesh::SphereFunction::setMaxPhi( float max )
{
	float first = max / 2.0f;
	float second = static_cast< float > ( toxi::math::MathUtils::PI );
	phiRange = static_cast< float > ( toxi::math::MathUtils::min( first,  second) );
}

void toxi::geom::mesh::SphereFunction::setMaxTheta( float max )
{
	float first = max / 2.0f;
	float second = static_cast< float > ( toxi::math::MathUtils::PI );
	thetaRange = static_cast< float > ( toxi::math::MathUtils::min( first, second ) );
}
