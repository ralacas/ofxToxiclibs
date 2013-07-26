#include "AABB.h"


toxi::geom::AABB::AABB(void)
{
}

toxi::geom::AABB::AABB( AABB& aabb )
{
	AABB( aabb, aabb.getExtend() );
}

toxi::geom::AABB::AABB( double extend )
{
	AABB( Vec3D(), extend );
}

toxi::geom::AABB::AABB( Vec3D point, double extend )
{
	AABB( point, extend );
}

toxi::geom::AABB::AABB( Vec3D point, Vec3D extend )
{
	AABB( point );
	setExtend( extend );
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

bool toxi::geom::AABB::containsPoint( Vec3D point )
{
	return point.isInAABB( *this );
}

toxi::geom::Vec3D toxi::geom::AABB::getExtend()
{
	return extent;
}

toxi::geom::Vec3D toxi::geom::AABB::getNormalForPoint( Vec3D p )
{
	p = p.sub(*this);
	Vec3D pabs = extent.sub(p.getAbs());
	Vec3D psign = p.getSignum();
	Vec3D normal = Vec3D::X_AXIS().scale(psign.x);
	float minDist = pabs.x;
	if (pabs.y < minDist) {
		minDist = pabs.y;
		normal = Vec3D::Y_AXIS().scale(psign.y);
	}
	if (pabs.z < minDist) {
		normal = Vec3D::Z_AXIS().scale(psign.z);
	}
	return normal;
}

toxi::geom::AABB toxi::geom::AABB::growToContainPoint( Vec3D p )
{
	min.minSelf(p);
	max.maxSelf(p);
	set(min.interpolateTo(max, 0.5f));
	extent.set(max.sub(min).scaleSelf(0.5f));
	return *this;
}

bool toxi::geom::AABB::intersectsBox( AABB box )
{
	Vec3D t = box.sub(*this);
	return toxi::math::MathUtils::abs( t.x ) <= ( extent.x + box.extent.x )
		&& toxi::math::MathUtils::abs( t.y ) <= ( extent.y + box.extent.y )
		&& toxi::math::MathUtils::abs( t.z ) <= ( extent.z + box.extent.z );
}

toxi::geom::Vec3D toxi::geom::AABB::intersectsRay( Ray3D ray, float minDist, float maxDist )
{
	Vec3D invDir = ray.getDirection().getReciprocal();
	bool signDirX = invDir.x < 0;
	bool signDirY = invDir.y < 0;
	bool signDirZ = invDir.z < 0;
	Vec3D bbox = signDirX ? max : min;
	float tmin = (bbox.x - ray.x) * invDir.x;
	bbox = signDirX ? min : max;
	float tmax = (bbox.x - ray.x) * invDir.x;
	bbox = signDirY ? max : min;
	float tymin = (bbox.y - ray.y) * invDir.y;
	bbox = signDirY ? min : max;
	float tymax = (bbox.y - ray.y) * invDir.y;
	if ((tmin > tymax) || (tymin > tmax)) {
		return Vec3D();
	}
	if (tymin > tmin) {
		tmin = tymin;
	}
	if (tymax < tmax) {
		tmax = tymax;
	}
	bbox = signDirZ ? max : min;
	float tzmin = (bbox.z - ray.z) * invDir.z;
	bbox = signDirZ ? min : max;
	float tzmax = (bbox.z - ray.z) * invDir.z;
	if ((tmin > tzmax) || (tzmin > tmax)) {
		return Vec3D();
	}
	if (tzmin > tmin) {
		tmin = tzmin;
	}
	if (tzmax < tmax) {
		tmax = tzmax;
	}
	if ((tmin < maxDist) && (tmax > minDist)) {
		return ray.getPointAtDistance(tmin);
	}
	return Vec3D();
}

bool toxi::geom::AABB::intersectsSphere( Vec3D c, float r )
{
	float s, d = 0;
	// find the square of the distance
	// from the sphere to the box
	if (c.x < min.x) {
		s = c.x - min.x;
		d = s * s;
	} else if (c.x > max.x) {
		s = c.x - max.x;
		d += s * s;
	}

	if (c.y < min.y) {
		s = c.y - min.y;
		d += s * s;
	} else if (c.y > max.y) {
		s = c.y - max.y;
		d += s * s;
	}

	if (c.z < min.z) {
		s = c.z - min.z;
		d += s * s;
	} else if (c.z > max.z) {
		s = c.z - max.z;
		d += s * s;
	}

	return d <= r * r;
}

bool toxi::geom::AABB::planeBoxOverlap( Vec3D normal, float d, Vec3D maxBox )
{
	Vec3D vmin = Vec3D();
	Vec3D vmax = Vec3D();

	if (normal.x > 0.0f) {
		vmin.x = -maxBox.x;
		vmax.x = maxBox.x;
	} else {
		vmin.x = maxBox.x;
		vmax.x = -maxBox.x;
	}

	if (normal.y > 0.0f) {
		vmin.y = -maxBox.y;
		vmax.y = maxBox.y;
	} else {
		vmin.y = maxBox.y;
		vmax.y = -maxBox.y;
	}

	if (normal.z > 0.0f) {
		vmin.z = -maxBox.z;
		vmax.z = maxBox.z;
	} else {
		vmin.z = maxBox.z;
		vmax.z = -maxBox.z;
	}
	if (normal.dot(vmin) + d > 0.0f) {
		return false;
	}
	if (normal.dot(vmax) + d >= 0.0f) {
		return true;
	}
	return false;
}

toxi::geom::AABB toxi::geom::AABB::set( AABB box )
{
	extent.set( box.extent );
}

toxi::geom::Vec3D toxi::geom::AABB::set( float a, float b, float c )
{
	this->x = a;
	this->y = b;
	this->z = c;
	updateBound();
	return *this;
}

toxi::geom::AABB toxi::geom::AABB::set( Vec3D v )
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	updateBound();
	return *this;
}

toxi::geom::AABB toxi::geom::AABB::setExtend( Vec3D extend )
{
	this->extent = extend;
	return updateBound();
}

bool toxi::geom::AABB::testAxis( float a, float b, float fa, float fb, float va, float vb, float wa, float wb, float ea, float eb )
{
	float p0 = a * va + b * vb;
	float p2 = a * wa + b * wb;
	float min, max;
	if (p0 < p2) {
		min = p0;
		max = p2;
	} else {
		min = p2;
		max = p0;
	}
	float rad = fa * ea + fb * eb;
	return (min > rad || max < -rad);
}

Mesh3D toxi::geom::AABB::toMesh( Mesh3D mesh )
{
	//if (mesh == null) {
	//	mesh = TriangleMesh("aabb", 8, 12);
	//}
	Vec3D a = min;
	Vec3D g = max;
	Vec3D b = Vec3D(a.x, a.y, g.z);
	Vec3D c = Vec3D(g.x, a.y, g.z);
	Vec3D d = Vec3D(g.x, a.y, a.z);
	Vec3D e = Vec3D(a.x, g.y, a.z);
	Vec3D f = Vec3D(a.x, g.y, g.z);
	Vec3D h = Vec3D(g.x, g.y, a.z);
	Vec2D ua = Vec2D(0, 0);
	Vec2D ub = Vec2D(1, 0);
	Vec2D uc = Vec2D(1, 1);
	Vec2D ud = Vec2D(0, 1);
	// left
	mesh.addFace(a, b, f, ud, uc, ub);
	mesh.addFace(a, f, e, ud, ub, ua);
	// front
	mesh.addFace(b, c, g, ud, uc, ub);
	mesh.addFace(b, g, f, ud, ub, ua);
	// right
	mesh.addFace(c, d, h, ud, uc, ub);
	mesh.addFace(c, h, g, ud, ub, ua);
	// back
	mesh.addFace(d, a, e, ud, uc, ub);
	mesh.addFace(d, e, h, ud, ub, ua);
	// top
	mesh.addFace(e, f, h, ua, ud, ub);
	mesh.addFace(f, g, h, ud, uc, ub);
	// bottom
	mesh.addFace(a, d, b, ud, uc, ua);
	mesh.addFace(b, d, c, ua, uc, ub);
	return mesh;
}

Mesh3D toxi::geom::AABB::toMesh( void )
{
	return toMesh( Mesh3D() );
}

std::string toxi::geom::AABB::toString( void )
{
	std::stringstream ss;
	ss << "<aabb> pos: " << Vec3D::toString() << " ext: " << extent.toString() ;
	return ss.str( );
}

toxi::geom::AABB toxi::geom::AABB::updateBound( void )
{
	this->min = this->sub(extent);
	this->max = this->add(extent);
	return *this;
}
