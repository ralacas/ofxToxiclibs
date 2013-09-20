#include "Polygon2D.h"
#include <vector>
#include "Line2D.h"
#include "Circle.h"
#include "Rect.h"
#include "LineIntersection.h"
#include "../math/MathUtils.h"
#include "mesh/TriangleMesh.h"
#include "Vec3D.h"


toxi::geom::Polygon2D::Polygon2D(void)
{
}

toxi::geom::Polygon2D::Polygon2D( std::vector< Vec2D > points )
{
	for( auto it = points.begin(); it != points.end(); ++it ) 
	{
		Vec2D v = *it;
		add(v);
	}
}

toxi::geom::Polygon2D::Polygon2D( Vec2D baseA, Vec2D baseB, int res )
{
	float theta = -(toxi::math::MathUtils::PI - (toxi::math::MathUtils::PI * (res - 2) / res));
	Vec2D dir = *baseB.sub( &baseA);
	Vec2D prev = baseB;
	add( baseA );
	add( baseB );
	for (int i = 1; i < res - 1; i++) {
		Vec2D p = *prev.add(dir.getRotated(theta * i));
		add(p);
		prev = p;
	}
}

toxi::geom::Polygon2D::Polygon2D( Vec2D v1, Vec2D v2 )
{
	add( v1 );
	add( v2 );
}

toxi::geom::Polygon2D::Polygon2D( const Polygon2D & poly )
{
	for( auto it = poly.vertices.begin(); it != poly.vertices.end(); ++it )
	{
		Vec2D v = *it;
		this->vertices.push_back( v );
	}
}

toxi::geom::Polygon2D::~Polygon2D(void)
{

}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::add( float x, float y )
{
	return add(Vec2D( x, y ) );
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::add( toxi::geom::Vec2D v )
{
	vertices.push_back( v );
	return this;
}

std::vector< toxi::geom::Line2D * > toxi::geom::Polygon2D::getEdges()
{
	int num = vertices.size();
	std::vector< Line2D * > edges;
	for( int i = 0; i < num; i++ )
	{
		int i2 = std::fmod( ( i + 1 ), num );
		edges.push_back( new Line2D( &vertices[i], &vertices[ i2 ] ) );
	}
}

float toxi::geom::Polygon2D::getRadiusForEdgeLength( float len, int res )
{
	return len / (2 * toxi::math::MathUtils::sin(toxi::math::MathUtils::PI / res));
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::center()
{
	return center( Vec2D( 0, 0 ) );
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::center( Vec2D origin )
{
	Vec2D centroid = getCentroid();
	Vec2D delta = ( !origin.isZeroVector() ) ? *origin.sub( &centroid ) : *centroid.invert();
	for( Vec2D v : vertices )
	{
		v.addSelf( &delta );
	}
	return this;
}

bool toxi::geom::Polygon2D::containsPoint( Vec2D * p )
{
	int num = vertices.size();
	int i, j = num - 1;
	bool oddNodes = false;
	float px = p->getX();
	float py = p->getY();
	for (i = 0; i < num; i++) 
	{
		
		Vec2D vi = vertices.at(i);
		Vec2D vj = vertices.at(j);
		if (vi.getY() < py && vj.getY() >= py || vj.getY() < py && vi.getY() >= py) 
		{
			if (vi.getX() + (py - vi.getY() ) / (vj.getY() - vi.getY()) * (vj.getX() - vi.getX()) < px) 
			{
				oddNodes = !oddNodes;
			}
		}
		j = i;
	}
	return oddNodes;
}

bool toxi::geom::Polygon2D::containsPolygon( Polygon2D * pol )
{
	for (Vec2D p : pol->vertices) 
	{
		if (!containsPoint( &p ) ) 
		{
			return false;
		}
	}
	return true;
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::flipVertexOrder()
{
	//TODO: Collections.reverse( vertices );
	// return this;
	// find a way to reverse the order of a std::vector
}

toxi::geom::Vec2D toxi::geom::Polygon2D::get( int i )
{
	if( i < 0 )
	{
		i += vertices.size();
	}

	return vertices.at( i );
}

float toxi::geom::Polygon2D::getApothem()
{
	return vertices.at( 0 ).interpolateTo( &vertices.at( 1 ), 0.5 )->distanceTo( &getCentroid() );
}

float toxi::geom::Polygon2D::getArea()
{
	float area = 0;
	for (int i = 0, num = vertices.size(); i < num; i++) 
	{
		Vec2D a = vertices.at(i);
		Vec2D b = vertices.at(std::fmod( i + 1, num) );
		area += a.getX() * b.getY();
		area -= a.getY() * b.getX();
	}
	area *= 0.5f;
	return area;
}

toxi::geom::Circle * toxi::geom::Polygon2D::getBoundingCircle()
{
	return toxi::geom::Circle::newBoundingCircle( &vertices );
}

toxi::geom::Rect * toxi::geom::Polygon2D::getBounds()
{
	return toxi::geom::Rect::getBoundingRect( &vertices );
}

toxi::geom::Vec2D toxi::geom::Polygon2D::getCentroid()
{
	Vec2D res = Vec2D();
	for (int i = 0, num = vertices.size(); i < num; i++) 
	{
		Vec2D a = vertices.at(i);
		Vec2D b = vertices.at(std::fmod( i + 1, num ));
		float crossP = a.getX() * b.getY() - b.getX() * a.getY();
		res.set( res.getX() +  (a.getX() + b.getX()) * crossP, res.getY() + (a.getY() + b.getY()) * crossP );
	}
	return *res.scale(1 / (6 * getArea()));
}

float toxi::geom::Polygon2D::getCircumference()
{
	float circ = 0;
	for (int i = 0, num = vertices.size(); i < num; i++)
	{
		circ += vertices.at(i).distanceTo(&vertices.at(std::fmod( i + 1, num ) ) );
	}
	return circ;
}

toxi::geom::Vec2D toxi::geom::Polygon2D::getClosestPointTo( Vec2D p )
{
	float minD = FLT_MAX;
	Vec2D q = Vec2D();
	for (Line2D * l : getEdges()) 
	{
		Vec2D c = *l->closestPointTo(p);
		float d = c.distanceToSquared( &p);
		if (d < minD) 
		{
			q = c;
			minD = d;
		}
	}
	return q;
}

toxi::geom::Vec2D toxi::geom::Polygon2D::getClosestVertexTo( Vec2D p )
{
	float minD = FLT_MAX;
	Vec2D q = Vec2D();
	for (Vec2D v : vertices) 
	{
		float d = v.distanceToSquared( &p );
		if (d < minD) 
		{
			q = v;
			minD = d;
		}
	}
	return q;
}

int toxi::geom::Polygon2D::getNumPoints()
{
	return getNumVertices();
}

int toxi::geom::Polygon2D::getNumVertices()
{
	return vertices.size();
}

toxi::geom::Vec2D * toxi::geom::Polygon2D::getRandomPoint()
{
	std::vector< Line2D *> edges = getEdges();
	int numEdges = edges.size();
	Line2D * ea = edges.at(toxi::math::MathUtils::random(numEdges));
	Line2D * eb = nullptr;
	// and another one, making sure it's different
	while (eb == nullptr || *eb == *ea) 
	{
		eb = edges.at(toxi::math::MathUtils::random(numEdges));
	}
	// pick a random point on edge A
	Vec2D p = *ea->a->interpolateTo(ea->b, toxi::math::MathUtils::random( 1 ) );
	// then randomly interpolate to another random point on edge B
	return p.interpolateToSelf(
		eb->a->interpolateTo(eb->b, toxi::math::MathUtils::random( 1 ) ),
		toxi::math::MathUtils::random( 1 ) );
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::increaseVertexCount( int count )
{
	int num = vertices.size();
	while (num < count) 
	{
		// find longest edge
		int longestID = 0;
		float maxD = 0;
		for (int i = 0; i < num; i++) {
			float d = vertices.at(i).distanceToSquared(
				&vertices.at(std::fmod( i + 1, num ) ) );
			if (d > maxD) 
			{
				longestID = i;
				maxD = d;
			}
		}
		// insert mid point of longest segment in vertex list
		Vec2D m = *vertices.at(longestID)
			.add(&vertices.at(std::fmod( longestID + 1, num ) ) )->scaleSelf(0.5f);
		vertices.assign(longestID + 1, m);
		num++;
	}
	return this;
}

bool toxi::geom::Polygon2D::intersectsPolygon( Polygon2D * p )
{
	for (Line2D * ea : getEdges()) 
	{
		for (Line2D * eb : p->getEdges()) 
		{
			toxi::geom::LineIntersection::Type isec = ea->intersectLine(eb)->getType();
			if (isec == toxi::geom::LineIntersection::Type::INTERSECTING || isec == toxi::geom::LineIntersection::Type::COINCIDENT) 
			{
				return true;
			}
		}
	}
	return false;
}

bool toxi::geom::Polygon2D::isClockwise()
{
	return getArea() > 0;
}

bool toxi::geom::Polygon2D::isConvex()
{
	bool isPositive = false;
	int num = vertices.size();
	for (int i = 0; i < num; i++) 
	{
		int prev = (i == 0) ? num - 1 : i - 1;
		int next = (i == num - 1) ? 0 : i + 1;
		Vec2D d0 = *vertices.at(i).sub( &vertices.at(prev));
		Vec2D d1 = *vertices.at(next).sub(&vertices.at(i));
		bool newIsP = (d0.cross( &d1 ) > 0);
		if (i == 0) 
		{
			isPositive = newIsP;
		} 
		else if (isPositive != newIsP) 
		{
			return false;
		}
	}
	return true;
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::offsetShape( float distance )
{
	int num = vertices.size() - 1;
	if (num > 1) 
	{
		float startX = vertices.at(0).getX();
		float startY = vertices.at(0).getY();
		float c = vertices.at(num).getX();
		float d = vertices.at(num).getY();
		float e = startX;
		float f = startY;
		for (int i = 0; i < num; i++) 
		{
			float a = c;
			float b = d;
			c = e;
			d = f;
			e = vertices.at(i + 1).getX();
			f = vertices.at(i + 1).getY();
			offsetCorner(a, b, c, d, e, f, distance, &vertices.at(i));
		}
		offsetCorner(c, d, e, f, startX, startY, distance,
			&vertices.at(num));
	}
	return this;
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::reduceVertices( float minEdgeLength )
{
	minEdgeLength *= minEdgeLength;
	std::vector<Vec2D> reduced;
	Vec2D prev = vertices.at(0);
	reduced.push_back(prev);
	int num = vertices.size() - 1;
	for (int i = 1; i < num; i++) 
	{
		Vec2D v = vertices.at(i);
		if (prev.distanceToSquared( &v ) >= minEdgeLength) 
		{
			reduced.push_back(v);
			prev = v;
		}
	}
	if (vertices.at(0).distanceToSquared( &vertices.at(num)) >= minEdgeLength) 
	{
		reduced.push_back(vertices.at(num));
	}
	vertices = reduced;
	return this;
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::removeDuplicates( float tolerance )
{
	Vec2D prev;
	for (auto it = vertices.begin(); it != vertices.end(); ++it ) 
	{
		Vec2D p = *it;
		if (p.equalsWithTolerance(&prev, tolerance)) 
		{
			vertices.erase( it );
			//iv.remove();
		} else {
			prev = p;
		}
	}
	int num = vertices.size();
	if (num > 0) {
		Vec2D last = vertices.at(num - 1);
		if (last.equalsWithTolerance(&vertices.at(0), tolerance)) {
			//TODO: how to nicely remove things from a vector ffs?
			//vertices.remove(last);
		}
	}
	return this;
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::rotate( float theta )
{
	for (Vec2D v : vertices) {
		v.rotate(theta);
	}
	return this;
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::scale( float scale )
{
	return this->scale(scale, scale);
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::scale( float x, float y )
{
	for (Vec2D v : vertices) {
		v.scaleSelf(x, y);
	}
	return this;
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::scale( Vec2D v )
{
	return this->scale(v.getX(), v.getY() );
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::scaleSize( float scale )
{
	return scaleSize(scale, scale);
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::scaleSize( float x, float y )
{
	Vec2D centroid = getCentroid();
	for (Vec2D v : vertices) {
		v.subSelf(&centroid)->scaleSelf(x, y)->addSelf( &centroid );
	}
	return this;
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::scaleSize( Vec2D p )
{
	return scaleSize(p.getX(), p.getY());
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::smooth( float amount, float baseWeight )
{
	Vec2D centroid = getCentroid();
	int num = vertices.size();
	std::vector<Vec2D> filtered;
	for (int i = 0, j = num - 1, k = 1; i < num; i++) {
		Vec2D a = vertices.at(i);
		Vec2D dir = *vertices.at(j).sub( &a )->addSelf( vertices.at(k).sub( &a ))
			->addSelf(a.sub(&centroid)->scaleSelf(baseWeight));
		filtered.push_back(*a.add(dir.scaleSelf(amount)));
		j++;
		if (j == num) {
			j = 0;
		}
		k++;
		if (k == num) {
			k = 0;
		}
	}
	vertices.clear();

	for( auto it = filtered.begin(); it != filtered.end(); ++it ) 
	{
		vertices.push_back( *it );
	}

	return this;
}

toxi::geom::mesh::Mesh3D * toxi::geom::Polygon2D::toMesh( toxi::geom::mesh::Mesh3D * mesh  )
{
	return toMesh( mesh, nullptr, 0 );
}

toxi::geom::mesh::Mesh3D * toxi::geom::Polygon2D::toMesh(  toxi::geom::mesh::Mesh3D * mesh, Vec2D * centroid2D, float extrude ) 
{
	if (mesh == nullptr) {
		mesh = new toxi::geom::mesh::TriangleMesh();
	}
	int num = vertices.size();
	if (centroid2D == nullptr) {
		centroid2D = &getCentroid();
	}
	toxi::geom::Vec3D centroid = *centroid2D->to3DXY();
	centroid.z = extrude;
	Rect bounds = *getBounds();
	Vec2D boundScale = Vec2D(1 / bounds.width, 1 / bounds.height);
	Vec2D uvC = *centroid2D->sub( &bounds.getTopLeft())->scaleSelf( &boundScale);
	for (int i = 1; i <= num; i++) {
		Vec2D a = vertices.at(std::fmod( i, num));
		Vec2D b = vertices.at(i - 1);
		Vec2D uvA = *a.sub(&bounds.getTopLeft())->scaleSelf( &boundScale);
		Vec2D uvB = *b.sub(&bounds.getTopLeft())->scaleSelf( &boundScale);
		mesh->addFace( &centroid, a.to3DXY(), b.to3DXY(), &uvC, &uvA, &uvB);
	}
	return mesh;
}

bool toxi::geom::Polygon2D::toOutLine()
{
	int corners = vertices.size();
	int maxSegs = corners * 3;
	std::vector<Vec2D> newVerts;

	Vec2D * segments;
	segments = ( Vec2D* ) malloc( sizeof( Vec2D ) * maxSegs);
	Vec2D * segEnds;
	segEnds = (Vec2D * ) malloc(sizeof( Vec2D ) * maxSegs );
	float * segAngles;
	segAngles = (float * ) malloc( sizeof( float ) * maxSegs );
	//Vec2D[] segments = new Vec2D[maxSegs];
	//Vec2D[] segEnds = new Vec2D[maxSegs];
	//float[] segAngles = new float[maxSegs];
	Vec2D start = vertices.at(0);
	float lastAngle = toxi::math::MathUtils::PI;
	float a, b, c, d, e, f;
	double angleDif, bestAngleDif;
	int i, j = corners - 1, segs = 0;

	if (corners > maxSegs) {
		return false;
	}

	// 1,3. Reformulate the polygon as a set of line segments, and choose a
	// starting point that must be on the perimeter.
	for (i = 0; i < corners; i++) {
		Vec2D pi = vertices.at(i);
		Vec2D pj = vertices.at(j);
		if (!( pi == pj )) {
			segments[segs] = pi;
			segEnds[segs++] = pj;
		}
		j = i;
		if (pi.getY() > start.getY() || (pi.getY() == start.getY() && pi.getX() < start.getX())) {
			start.set( &pi);
		}
	}
	if (segs == 0) {
		return false;
	}

	// 2. Break the segments up at their intersection points.
	for (i = 0; i < segs - 1; i++) {
		for (j = i + 1; j < segs; j++) {
			Line2D li = toxi::geom::Line2D( &segments[i], &segEnds[i]);
			Line2D lj = toxi::geom::Line2D( &segments[j], &segEnds[j]);
			LineIntersection isec = *li.intersectLine( &lj);
			if (isec.getType() == toxi::geom::LineIntersection::Type::INTERSECTING) {
				Vec2D ipos = isec.getPos();
				if (!( ipos == segments[i] ) && !( ipos == segEnds[i])) {
					if (segs == maxSegs) {
						return false;
					}
					segments[segs] = segments[i];
					segEnds[segs++] = ipos;
					segments[i] = ipos;
				}
				if (!( ipos == segments[j] ) && !( ipos ==  segEnds[ j ] ) ) {
					if (segs == maxSegs) {
						return false;
					}
					segments[segs] = segments[j];
					segEnds[segs++] = ipos;
					segments[j] = ipos;
				}
			}
		}
	}

	// Calculate the angle of each segment.
	for (i = 0; i < segs; i++) {
		segAngles[i] = segEnds[i].sub( &segments[i])->positiveHeading();
	}

	// 4. Build the perimeter polygon.
	c = start.getX();
	d = start.getY();
	a = c - 1;
	b = d;
	e = 0;
	f = 0;
	newVerts.push_back(Vec2D(c, d));
	corners = 1;
	while (true) {
		bestAngleDif = toxi::math::MathUtils::TWO_PI;
		for (i = 0; i < segs; i++) {
			if (segments[i].getX() == c && segments[i].getY() == d
				&& (segEnds[i].getX() != a || segEnds[i].getY() != b)) {
					angleDif = lastAngle - segAngles[i];
					while (angleDif >= toxi::math::MathUtils::TWO_PI) {
						angleDif -= toxi::math::MathUtils::TWO_PI;
					}
					while (angleDif < 0) {
						angleDif += toxi::math::MathUtils::TWO_PI;
					}
					if (angleDif < bestAngleDif) {
						bestAngleDif = angleDif;
						e = segEnds[i].getX();
						f = segEnds[i].getY();
					}
			}
			if (segEnds[i].getX() == c && segEnds[i].getY() == d
				&& (segments[i].getX() != a || segments[i].getY() != b)) {
					angleDif = lastAngle - segAngles[i] + toxi::math::MathUtils::PI;
					while (angleDif >= toxi::math::MathUtils::TWO_PI) {
						angleDif -= toxi::math::MathUtils::TWO_PI;
					}
					while (angleDif < 0) {
						angleDif += toxi::math::MathUtils::TWO_PI;
					}
					if (angleDif < bestAngleDif) {
						bestAngleDif = angleDif;
						e = segments[i].getX();
						f = segments[i].getY();
					}
			}
		}
		if (corners > 1 && c == newVerts.at(0).getX() && d == newVerts.at(0).getY()
			&& e == newVerts.at(1).getX() && f == newVerts.at(1).getY()) {
				corners--;
				vertices = newVerts;
				return true;
		}
		if (bestAngleDif == toxi::math::MathUtils::TWO_PI || corners == maxSegs) {
			return false;
		}
		lastAngle -= bestAngleDif + toxi::math::MathUtils::PI;
		newVerts.push_back(Vec2D(e, f));
		corners++;
		a = c;
		b = d;
		c = e;
		d = f;
	}
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::toPolygon2D()
{
	return this;
}

std::string toxi::geom::Polygon2D::toString()
{
	std::stringstream ss;
	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		ss << it->toString() << ", ";
	}
	return ss.str();
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::translate( float x, float y )
{
	for (Vec2D v : vertices) {
		v.addSelf(x, y);
	}
	return this;
}

toxi::geom::Polygon2D * toxi::geom::Polygon2D::translate( Vec2D v )
{
	return translate(v.getX(), v.getY());
}

void toxi::geom::Polygon2D::offsetCorner( float x1, float y1, float x2, float y2, float x3, float y3, float distance, Vec2D * out )
{
	float c1 = x2, d1 = y2, c2 = x2, d2 = y2;
	float dx1, dy1, dist1, dx2, dy2, dist2, insetX, insetY;

	dx1 = x2 - x1;
	dy1 = y2 - y1;
	dist1 = (float) toxi::math::MathUtils::sqrt(dx1 * dx1 + dy1 * dy1);
	dx2 = x3 - x2;
	dy2 = y3 - y2;
	dist2 = (float) toxi::math::MathUtils::sqrt(dx2 * dx2 + dy2 * dy2);

	if (dist1 < toxi::math::MathUtils::EPS || dist2 < toxi::math::MathUtils::EPS) {
		return;
	}
	dist1 = distance / dist1;
	dist2 = distance / dist2;

	insetX = dy1 * dist1;
	insetY = -dx1 * dist1;
	x1 += insetX;
	c1 += insetX;
	y1 += insetY;
	d1 += insetY;
	insetX = dy2 * dist2;
	insetY = -dx2 * dist2;
	x3 += insetX;
	c2 += insetX;
	y3 += insetY;
	d2 += insetY;

	if (c1 == c2 && d1 == d2) {
		out->set(c1, d1);
		return;
	}

	Line2D l1 = toxi::geom::Line2D( new Vec2D(x1, y1), new Vec2D(c1, d1));
	Line2D l2 = toxi::geom::Line2D( new Vec2D(c2, d2), new Vec2D(x3, y3));
	LineIntersection isec = *l1.intersectLine( &l2);
	Vec2D ipos = isec.getPos();
	if (ipos.isZeroVector()) {
		out->set(&ipos);
	}
}

toxi::geom::Polygon2D toxi::geom::Polygon2D::fromEdgeLength( float len, int res )
{
	return *toxi::geom::Circle( getRadiusForEdgeLength( len, res ) ).toPolygon2D();
}
