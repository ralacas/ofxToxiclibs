#include "SurfaceMeshBuilder.h"


toxi::geom::mesh::SurfaceMeshBuilder::SurfaceMeshBuilder( SurfaceFunction function  )
{
	this->function = function;
}


toxi::geom::mesh::SurfaceMeshBuilder::~SurfaceMeshBuilder(void)
{
}

toxi::geom::mesh::Mesh3D toxi::geom::mesh::SurfaceMeshBuilder::createMesh( int res )
{
	return createMesh( toxi::geom::mesh::TriangleMesh(), res, 1 );
}

toxi::geom::mesh::Mesh3D toxi::geom::mesh::SurfaceMeshBuilder::createMesh( Mesh3D mesh, int res, float size )
{
	return createMesh( mesh, res, size, true );
}

toxi::geom::mesh::Mesh3D toxi::geom::mesh::SurfaceMeshBuilder::createMesh( Mesh3D mesh, int res, float size, bool isClosed )
{
	Vec3D a = Vec3D();
	Vec3D b = Vec3D();
	Vec3D pa = Vec3D(), pb = Vec3D();
	Vec3D a0 = Vec3D(), b0 = Vec3D();
	int phiRes = function.getPhiResolutionLimit(res);
	float phiRange = function.getPhiRange();
	int thetaRes = function.getThetaResolutionLimit(res);
	float thetaRange = function.getThetaRange();
	float pres = 1.0 / phiRes;
	float tres = 1.0 / thetaRes;
	float ires = 1.0 / res;
	Vec2D pauv = Vec2D();
	Vec2D pbuv = Vec2D();
	Vec2D auv = Vec2D();
	Vec2D buv = Vec2D();
	for (int p = 0; p < phiRes; p++) {
		float phi = p * phiRange * ires;
		float phiNext = (p + 1) * phiRange * ires;
		for (int t = 0; t <= thetaRes; t++) {
			float theta;
			theta = t * thetaRange * ires;
			a = function.computeVertexFor(a, phiNext, theta)
				.scaleSelf(size);
			auv.set(t * tres, 1 - (p + 1) * pres);
			b = function.computeVertexFor(b, phi, theta).scaleSelf(size);
			buv.set(t * tres, 1 - p * pres);
			if (b.equalsWithTolerance(a, 0.0001f)) {
				b.set(a);
			}
			if (t > 0) {
				if (t == thetaRes && isClosed) {
					a.set(a0);
					b.set(b0);
				}
				mesh.addFace(pa, pb, a, Vec2D( pauv ), Vec2D( pbuv ),
					Vec2D( auv );
				mesh.addFace(pb, b, a, Vec2D( pbuv ), Vec2D( buv ), Vec2D( auv ));
			} else {
				a0.set(a);
				b0.set(b);
			}
			pa.set(a);
			pb.set(b);
			pauv.set(auv);
			pbuv.set(buv);
		}
	}
	return mesh;
}

toxi::geom::mesh::SurfaceFunction toxi::geom::mesh::SurfaceMeshBuilder::getFunction()
{
	return function;
}

void toxi::geom::mesh::SurfaceMeshBuilder::setFunction( SurfaceFunction function )
{
	this->function = function;
}
