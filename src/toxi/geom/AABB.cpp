#include "AABB.h"
#include "Vec2D.h"

toxi::geom::AABB::AABB(void)
{
}

toxi::geom::AABB::AABB( AABB& aabb )
{
	AABB( toxi::geom::Vec3D(aabb.getMin().getX(), aabb.getMin().getY(), aabb.getMin().getZ()), aabb.getExtend() );
}

toxi::geom::AABB::AABB( const double & extend )
{
	AABB( Vec3D(), extend );
}

toxi::geom::AABB::AABB( const Vec3D & point, const double & extend )
{
	AABB( point, extend );
}

toxi::geom::AABB::AABB( const Vec3D & point, const Vec3D & extend )
{
	this->x = point.getX();
	this->y = point.getY();
	this->z = point.getZ();
	setExtend( extend );
}


toxi::geom::AABB::~AABB(void)
{
}

toxi::geom::Vec3D toxi::geom::AABB::getMin()
{
	// TODO
	float changeThis = static_cast< float > ( 3.141593 );
	return Vec3D(changeThis, changeThis, changeThis);
}

toxi::geom::Vec3D toxi::geom::AABB::getMax()
{
	float changeThis = static_cast< float > ( 3.141593 );
	return Vec3D(changeThis, changeThis, changeThis);
}

bool toxi::geom::AABB::containsPoint( Vec3D & point )
{
	return point.isInAABB( *this );
}

toxi::geom::Vec3D toxi::geom::AABB::getExtend()
{
	return extent;
}

toxi::geom::Vec3D toxi::geom::AABB::getNormalForPoint( Vec3D & p )
{
	p = p.sub( Vec3D( x, y, z ) );
	Vec3D pabs = extent.sub( p.getAbs() );
	Vec3D psign = p.getSignum();
	Vec3D normal = Vec3D::X_AXIS().scale( static_cast< float > ( psign.getX() ) );
	double minDist = pabs.getX();
	if (pabs.getY() < minDist) {
		minDist = pabs.getY();
		normal = Vec3D::Y_AXIS().scale( static_cast< float > ( psign.getY() ) );
	}
	if (pabs.getZ() < minDist) {
		normal = Vec3D::Z_AXIS().scale( static_cast< float > ( psign.getZ() ) );
	}
	return normal;
}

toxi::geom::AABB * toxi::geom::AABB::growToContainPoint( const Vec3D & p )
{
	min.minSelf( p );
	max.maxSelf( p );
	set( min.interpolateTo( max, 0.5f ) );
	extent.set( max.sub( min ).scaleSelf( 0.5f ) );
	return this;
}

bool toxi::geom::AABB::intersectsBox( AABB & box )
{
	Vec3D t = box.sub(x, y, z);
	return toxi::math::MathUtils::abs( t.getX() ) <= ( extent.getX() + box.extent.getX() )
		&& toxi::math::MathUtils::abs( t.getY() ) <= ( extent.getZ() + box.extent.getY() )
		&& toxi::math::MathUtils::abs( t.getY() ) <= ( extent.getY() + box.extent.getZ() );
}

toxi::geom::Vec3D toxi::geom::AABB::intersectsRay( toxi::geom::Ray3D & ray, const float & minDist, const float & maxDist )
{
	Vec3D invDir = ray.getDirection().getReciprocal();
	bool signDirX = invDir.getX() < 0;
	bool signDirY = invDir.getY() < 0;
	bool signDirZ = invDir.getZ() < 0;
	Vec3D bbox = signDirX ? max : min;
	double tmin = (bbox.getX() - ray.getX()) * invDir.getX();
	bbox = signDirX ? min : max;
	double tmax = (bbox.getX() - ray.getX()) * invDir.getX();
	bbox = signDirY ? max : min;
	double tymin = (bbox.getY() - ray.getY()) * invDir.getY();
	bbox = signDirY ? min : max;
	double tymax = (bbox.getY() - ray.getY()) * invDir.getY();
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
	double tzmin = (bbox.getZ() - ray.getZ()) * invDir.getZ();
	bbox = signDirZ ? min : max;
	double tzmax = (bbox.getZ() - ray.getZ()) * invDir.getZ();
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
		return ray.getPointAtDistance( static_cast < float > ( tmin ) );
	}
	return Vec3D();
}

bool toxi::geom::AABB::intersectsSphere( const Vec3D & c, const float & r )
{
	double s, d = 0;
	// find the square of the distance
	// from the sphere to the box
	if (c.getX() < min.getX()) {
		s = c.getX() - min.getX();
		d = s * s;
	} else if (c.getX() > max.getX()) {
		s = c.getX() - max.getX();
		d += s * s;
	}

	if (c.getY() < min.getY()) {
		s = c.getY() - min.getY();
		d += s * s;
	} else if (c.getY() > max.getY()) {
		s = c.getY() - max.getY();
		d += s * s;
	}

	if (c.getZ() < min.getZ()) {
		s = c.getZ() - min.getZ();
		d += s * s;
	} else if (c.getZ() > max.getZ()) {
		s = c.getZ() - max.getZ();
		d += s * s;
	}

	return d <= r * r;
}

bool toxi::geom::AABB::planeBoxOverlap( Vec3D & normal, const float & d, const Vec3D & maxBox )
{
	Vec3D vmin = Vec3D();
	Vec3D vmax = Vec3D();

	if (normal.getX() > 0.0f) {
		vmin.setX( -maxBox.getX() );
		vmax.setX( maxBox.getX() );
	} else {
		vmin.setX( maxBox.getX() );
		vmax.setX( -maxBox.getX() );
	}

	if (normal.getY() > 0.0f) {
		vmin.setY( -maxBox.getY() );
		vmax.setY( maxBox.getY() );
	} else {
		vmin.setY( maxBox.getY() );
		vmax.setY( -maxBox.getY() );
	}

	if (normal.getZ() > 0.0f) {
		vmin.setZ( -maxBox.getZ() );
		vmax.setZ( maxBox.getZ() );
	} else {
		vmin.setZ( maxBox.getZ() );
		vmax.setZ( -maxBox.getZ() );
	}
	if (normal.dot(vmin) + d > 0.0f) {
		return false;
	}
	if (normal.dot(vmax) + d >= 0.0f) {
		return true;
	}
	return false;
}

toxi::geom::AABB * toxi::geom::AABB::set( const AABB & box )
{
	extent.set( box.extent );
}

toxi::geom::AABB * toxi::geom::AABB::set( const float & a, const float & b, const float & c )
{
	this->x = a;
	this->y = b;
	this->z = c;
	updateBound();
	return this; // TODO
}

toxi::geom::AABB * toxi::geom::AABB::set( const Vec3D & v )
{
	this->x = v.getX();
	this->y = v.getY();
	this->z = v.getZ();
	updateBound();
	return this;
}

toxi::geom::AABB * toxi::geom::AABB::setExtend( const Vec3D & extend )
{
	this->extent = extend;
	return updateBound();
}

bool toxi::geom::AABB::testAxis( const float & a, const float & b, const float & fa, const float & fb, const float & va, const float & vb, const float & wa, const float & wb, const float & ea, const float & eb )
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

/*toxi::geom::mesh::Mesh3D toxi::geom::AABB::toMesh()
{
	//if (mesh == null) {
	//	mesh = TriangleMesh("aabb", 8, 12);
	//}
	toxi::geom::mesh::Mesh3D* mesh;
	Vec3D a = *min;
	Vec3D g = *max;
	Vec3D b = Vec3D(a.getX(), a.getY(), g.getZ());
	Vec3D c = Vec3D(g.getX(), a.getY(), g.getZ());
	Vec3D d = Vec3D(g.getX(), a.getY(), a.getZ());
	Vec3D e = Vec3D(a.getX(), g.getY(), a.getZ());
	Vec3D f = Vec3D(a.getX(), g.getY(), g.getZ());
	Vec3D h = Vec3D(g.getX(), g.getY(), a.getZ());
	Vec2D ua = Vec2D(0, 0);
	Vec2D ub = Vec2D(1, 0);
	Vec2D uc = Vec2D(1, 1);
	Vec2D ud = Vec2D(0, 1);
	// left
	mesh->addFace(&a, &b, &f, &ud, &uc, &ub);
	mesh->addFace(&a, &f, &e, &ud, &ub, &ua);
	// front
	mesh->addFace(&b, &c, &g, &ud, &uc, &ub);
	mesh->addFace(&b, &g, &f, &ud, &ub, &ua);
	// right
	mesh->addFace(&c, &d, &h, &ud, &uc, &ub);
	mesh->addFace(&c, &h, &g, &ud, &ub, &ua);
	// back
	mesh->addFace(&d, &a, &e, &ud, &uc, &ub);
	mesh->addFace(&d, &e, &h, &ud, &ub, &ua);
	// top
	mesh->addFace(&e, &f, &h, &ua, &ud, &ub);
	mesh->addFace(&f, &g, &h, &ud, &uc, &ub);
	// bottom
	mesh->addFace(&a, &d, &b, &ud, &uc, &ua);
	mesh->addFace(&b, &d, &c, &ua, &uc, &ub);
	return mesh;
}
*/

std::string toxi::geom::AABB::toString( void )
{
	std::stringstream ss;
	ss << "<aabb> pos: " << "{x:" << this->x << ", y:" << this->y << ", z:" << this->z << "}" << " ext: " << extent;
	return ss.str( );
}

toxi::geom::AABB * toxi::geom::AABB::updateBound( void )
{
	this->min = sub( extent );
	this->max = add( extent );
	return this;
}

toxi::geom::Vec3D toxi::geom::AABB::sub( const float & a, const float & b, const float & c )
{
	return Vec3D( x-a, y-b, z-c );
}

toxi::geom::Vec3D toxi::geom::AABB::sub( const double & a, const double & b, const double & c )
{
	return Vec3D( x-a, y-b, z-c );
}

toxi::geom::Vec3D toxi::geom::AABB::sub( const toxi::geom::Vec3D & v )
{
	return Vec3D( x - v.getX(), y - v.getY(), z - v.getZ() );
}

toxi::geom::Vec3D toxi::geom::AABB::add( const float & a, const float & b, const float & c )
{
	return Vec3D( x + a, y + b, z + c );
}

toxi::geom::Vec3D toxi::geom::AABB::add( const double & a, const double & b, const double & c )
{
	return Vec3D( x + a, y + b, z + c );
}

toxi::geom::Vec3D toxi::geom::AABB::add( const Vec3D & v )
{
	return Vec3D( x + v.getX(), y + v.getY(), z + v.getZ() );
}
