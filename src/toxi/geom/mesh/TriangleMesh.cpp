#include "TriangleMesh.h"
#include "../AABB.h"
#include "Vertex.h"
#include "Face.h"
#include "../Quaternion.h"
#include "OBJWriter.h"
#include "STLWriter.h"
#include "WETriangleMesh.h"

int toxi::geom::mesh::TriangleMesh::DEFAULT_STRIDE = 0; // TODO
int toxi::geom::mesh::TriangleMesh::DEFAULT_NUM_VERTICES = 1000;
int toxi::geom::mesh::TriangleMesh::DEFAULT_NUN_FACES = 1000;

toxi::geom::mesh::TriangleMesh::TriangleMesh(void) :
	name("untitled")
{
	//toxi::geom::mesh::TriangleMesh( "untitled");
}

toxi::geom::mesh::TriangleMesh::TriangleMesh( const std::string & name )
{
	//toxi::geom::mesh::TriangleMesh( name, DEFAULT_NUM_VERTICES, DEFAULT_NUN_FACES );
	this->init(name, DEFAULT_NUM_VERTICES, DEFAULT_NUN_FACES );
}

toxi::geom::mesh::TriangleMesh::TriangleMesh( const std::string & name, const int & numV, const int & numF )
{
	this->init( name, numV, numF );
}


toxi::geom::mesh::TriangleMesh::~TriangleMesh(void)
{
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::addFace(const toxi::geom::Vec3D & a,const toxi::geom::Vec3D & b,const toxi::geom::Vec3D & c )
{
	return addFace( a, b, c, toxi::geom::Vec3D(), toxi::geom::Vec2D(), toxi::geom::Vec2D(), toxi::geom::Vec2D());
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::addFace(const toxi::geom::Vec3D & a,const toxi::geom::Vec3D & b,const toxi::geom::Vec3D & c,const toxi::geom::Vec2D & uvA,const toxi::geom::Vec2D & uvB,const toxi::geom::Vec2D & uvC )
{
	return addFace(a, b, c, toxi::geom::Vec3D(), uvA, uvB, uvC);
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::addFace(const toxi::geom::Vec3D & a,const toxi::geom::Vec3D &b,const toxi::geom::Vec3D & c,const toxi::geom::Vec3D & n )
{
	return addFace(a, b, c, n, toxi::geom::Vec2D(), toxi::geom::Vec2D(), toxi::geom::Vec2D());
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::addFace(const toxi::geom::Vec3D & a,const toxi::geom::Vec3D & b,const toxi::geom::Vec3D & c,const toxi::geom::Vec3D & n,const toxi::geom::Vec2D & uvA,const toxi::geom::Vec2D & uvB,const toxi::geom::Vec2D & uvC )
{
	Vertex va = checkVertex(a);
	Vertex vb = checkVertex(b);
	Vertex vc = checkVertex(c);
	if (va.id == vb.id || va.id == vc.id || vb.id == vc.id) {
		// 		if (logger.isLoggable(Level.FINE)) {
		// 			logger.fine("ignorning invalid face: " + a + "," + b + "," + c);
		// 		}
		// TODO ADD logger
	} else {
		if (n.isZeroVector()) {
			toxi::geom::Vec3D nc = va.sub(vc).crossSelf(va.sub(vb));
			if (n.dot(nc) < 0) {
				Vertex t = va;
				va = vb;
				vb = t;
			}
		}
		Face f = Face(va, vb, vc, uvA,  uvB, uvC);
		faces.push_back( f );
		numFaces++;
	}
	return this;
}

toxi::geom::mesh::Mesh3D* toxi::geom::mesh::TriangleMesh::addMesh( Mesh3D * m )
{
	for (Face f : m->getFaces()) {
		addFace(f.a, f.b, f.c, f.uvA, f.uvB, f.uvC);
	}
	return this;
}

toxi::geom::AABB toxi::geom::mesh::TriangleMesh::center( toxi::geom::Vec3D & origin )
{
	computeCentroid();
	toxi::geom::Vec3D delta = !origin.isZeroVector() ? origin.sub(centroid) : centroid
		.getInverted();

	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		it->second.addSelf( delta );
	}

	getBoundingBox();
	return bounds;
}

toxi::geom::mesh::Vertex toxi::geom::mesh::TriangleMesh::checkVertex(const toxi::geom::Vec3D &v )
{
	Vertex vertex = vertices.at( v );
	if (vertex.isZeroVector()) {
		vertex = createVertex(v, uniqueVertexID++);
		//TODO
		//vertices.insert(vertex, vertex);
		numVertices++;
	}
	return vertex;
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::clear()
{
	vertices.clear();
	faces.clear();
	bounds = toxi::geom::AABB();
	numVertices = 0;
	numFaces = 0;
	uniqueVertexID = 0;
	return this;
}

toxi::geom::Vec3D * toxi::geom::mesh::TriangleMesh::computeCentroid()
{
	centroid.clear();
	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		centroid.addSelf( it->second );
	}

	return &centroid.scaleSelf(1.0f / numVertices);
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::computeFaceNormals()
{
	for( auto it = faces.begin(); it != faces.end(); ++it ) 
	{
		it->computeNormal();
	}
	return this;
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::computeVertexNormals()
{
	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		it->second.clearNormal();
	}

	for( auto it = faces.begin(); it != faces.end(); ++it )
	{
		it->a.addFaceNormal( it->normal );
		it->b.addFaceNormal( it->normal );
		it->c.addFaceNormal( it->normal );
	}

	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		it->second.computeNormal();
	}

	return this;
}

toxi::geom::mesh::Vertex toxi::geom::mesh::TriangleMesh::createVertex( const toxi::geom::Vec3D & v, const int & id )
{
	return Vertex( v, id );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::faceOutwards()
{
	computeCentroid();

	for( auto it = faces.begin(); it != faces.end(); ++it )
	{
		toxi::geom::Vec3D n = it->getCentroid().sub( centroid );
		float dot = n.dot( it->normal );
		if( dot < 0 )
		{
			it->flipVertexOrder();
		}
	}
	return this;
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::flipVertexOrder()
{
	for( auto it = faces.begin(); it != faces.end(); ++it )
	{
		Vertex t = it->a;
		it->a = it->b;
		it->b = t;
		toxi::geom::Vec2D tuv = it->uvA;
		it->uvA = it->uvB;
		it->uvB = tuv;
		it->normal.invert();
	}

	return this;
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::flipYAxis()
{
	transform( toxi::geom::Matrix4x4().scaleSelf( 1, -1, 1) );
	flipVertexOrder();
	return this;
}

toxi::geom::AABB * toxi::geom::mesh::TriangleMesh::getBoundingBox()
{
	toxi::geom::Vec3D minBounds = toxi::geom::Vec3D::max_value();
	toxi::geom::Vec3D maxBounds = toxi::geom::Vec3D::min_value();
	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		minBounds.minSelf( it->second );
		maxBounds.maxSelf( it->second );
	}
	bounds = toxi::geom::AABB::fromMinMax( minBounds, maxBounds );
	return &bounds;
}

/*toxi::geom::Sphere * toxi::geom::mesh::TriangleMesh::getBoundingSphere()
{

	float radius = 0.0;
	computeCentroid();
	for ( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		radius = toxi::math::MathUtils::max( radius, it->second.distanceToSquared( centroid ) );
	}
	return new toxi::geom::Sphere( *centroid, toxi::math::MathUtils::sqrt( radius ) );
}*/

toxi::geom::mesh::Vertex * toxi::geom::mesh::TriangleMesh::getClosestVertexToPoint(const toxi::geom::Vec3D & p )
{
	Vertex * closest = new Vertex();
	float minDist = FLT_MAX;
	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		float d = static_cast< float > ( it->second.distanceToSquared( p ) );
		if ( d < minDist )
		{
			closest = new Vertex( p, 1 ); // TODO whats the 1?
			minDist = d;
		}
	}
	return closest;
}

std::vector< double > toxi::geom::mesh::TriangleMesh::getFaceNormalsAsArray()
{
	return getFaceNormalsAsArray( 0, DEFAULT_STRIDE );
}

std::vector< double> toxi::geom::mesh::TriangleMesh::getFaceNormalsAsArray( const int & offset, int & stride )
{
	stride = toxi::math::MathUtils::max( stride, 3 );
	std::vector< double> normals;
	int i = offset;
	for ( auto it = faces.begin(); it != faces.end(); ++it )
	{
		normals[ i ] = it->normal.getX();
		normals[ i + 1 ] = it->normal.getY();
		normals[ i + 2 ] = it->normal.getZ();
		i += stride;
		normals[ i ] = it->normal.getX();
		normals[ i + 1 ] = it->normal.getY();
		normals[ i + 2 ] = it->normal.getZ();
		i += stride;
		normals[ i ] = it->normal.getX();
		normals[ i + 1 ] = it->normal.getY();
		normals[ i + 2 ] = it->normal.getZ();
		i += stride;
	}
	return normals;
}

std::vector< toxi::geom::mesh::Face > toxi::geom::mesh::TriangleMesh::getFaces()
{
	return faces;
}

toxi::geom::IsectData3D toxi::geom::mesh::TriangleMesh::getIntersectionData()
{
	return intersector.getIntersectionData();
}

std::vector< double> toxi::geom::mesh::TriangleMesh::getMeshAsVertexArray()
{
	return getMeshAsVertexArray( 0, DEFAULT_STRIDE );
}

std::vector< double> toxi::geom::mesh::TriangleMesh::getMeshAsVertexArray( const int & offset, int & stride )
{
	stride = toxi::math::MathUtils::max( stride, 3 );
	std::vector< double> normals;
	int i = offset;
	for ( auto it = faces.begin(); it != faces.end(); ++it )
	{
		normals[ i ] = it->a.getX();
		normals[ i + 1 ] = it->a.getY();
		normals[ i + 2 ] = it->a.getZ();
		i += stride;
		normals[ i ] = it->b.getX();
		normals[ i + 1 ] = it->b.getY();
		normals[ i + 2 ] = it->b.getZ();
		i += stride;
		normals[ i ] = it->c.getX();
		normals[ i + 1 ] = it->c.getY();
		normals[ i + 2 ] = it->c.getZ();
		i += stride;
	}
	return normals;
}

std::vector< double> toxi::geom::mesh::TriangleMesh::getNormalsForUniqueVerticesArray()
{
	std::vector< double > normals;
	int i = 0;
	for ( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		normals[ i++ ] = it->second.normal.getX();
		normals[ i++ ] = it->second.normal.getY();
		normals[ i++ ] = it->second.normal.getZ();
	}
}

int toxi::geom::mesh::TriangleMesh::getNumFaces()
{
	return numFaces;
}

int toxi::geom::mesh::TriangleMesh::getNumVertices()
{
	return numVertices;
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getRotatedAroundAxis( const toxi::geom::Vec3D & axis, const float & theta )
{
	TriangleMesh tri = TriangleMesh( *this );
	return tri.rotateAroundAxis( axis, theta );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getRotatedX( const float & theta )
{
	return TriangleMesh( *this ).rotateX( theta );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getRotatedY( const float & theta  )
{
	return TriangleMesh( *this ).rotateY( theta );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getRotatedZ( const float & theta  )
{
	return TriangleMesh( *this ).rotateZ( theta );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getScaled(const float & factor  )
{
	return toxi::geom::mesh::TriangleMesh( *this ).scale( factor, factor, factor );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getScaled( const toxi::geom::Vec3D & scale )
{
	return TriangleMesh( *this ).scale( static_cast< float > ( scale.getX() ) , static_cast< float > ( scale.getY() ) , static_cast< float > (  scale.getZ() ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getTranslated( const toxi::geom::Vec3D & trans )
{
	return TriangleMesh( *this ).translate( trans );
}

std::vector< float> toxi::geom::mesh::TriangleMesh::getUniqueVerticesAsArray()
{
	std::vector< float> verts;
	verts.reserve( numVertices * 3 );

	int i = 0;

	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		//verts->assign(i++, it->second.x );
		//verts->assign(i++, it->second.y );
		//verts->assign(i++, it->second.z );
		/*verts[ i++ ] = it->second.x;
		verts[ i++ ] = it->second.y;
		verts[ i++ ] = it->second.z;*/
	}

	return verts;
}

toxi::geom::mesh::Vertex toxi::geom::mesh::TriangleMesh::getVertexAtPoint( const toxi::geom::Vec3D & v )
{
	return vertices.at( v );
}

toxi::geom::mesh::Vertex toxi::geom::mesh::TriangleMesh::getVertexForID( const int & id )
{
	Vertex vertex = Vertex();
	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		if( it->second.id == id )
		{
			vertex = it->second;
			break;
		}
	}
	return vertex;
}

std::vector< float> toxi::geom::mesh::TriangleMesh::getVertexNormalsAsArray()
{
	return getVertexNormalsAsArray( 0, DEFAULT_STRIDE );
}

std::vector< float> toxi::geom::mesh::TriangleMesh::getVertexNormalsAsArray( const int & offset, int & stride )
{
	stride = toxi::math::MathUtils::max( stride, 3 );

	std::vector< float> normals;
	normals.reserve( numVertices * 3 );

	int i = offset;

	for( auto it = faces.begin(); it != faces.end(); ++it )
	{
		//normals->assign(i, it->a->normal->x);
		//normals->assign(i+ 1, it->a->normal->x);
		//normals->assign(i+2, it->a->normal->x);
		/*normals[ i ] = it->a->normal->x;
		normals[ i + 1 ] = it->a.normal.y;
		normals[ i + 2 ] = it->a.normal.z;*/
		i += stride;
		//normals->assign(i, it->b->normal->x);
		//normals->assign(i+ 1, it->b->normal->x);
		//normals->assign(i+2, it->b->normal->x);
		/*
		normals[ i ] = it->b.normal.x;
		normals[ i + 1 ] = it->b.normal.y;
		normals[ i + 2 ] = it->b.normal.z;*/
		i += stride;
		//normals->assign(i, it->c->normal->x);
		//normals->assign(i+ 1, it->c->normal->x);
		//normals->assign(i+2, it->c->normal->x);
		/*
		normals[ i ] = it->c.normal.x;
		normals[ i + 1 ] = it->c.normal.y;
		normals[ i + 2 ] = it->c.normal.z;*/
		i += stride;
	}

	return normals;
}

std::vector< toxi::geom::mesh::Vertex > toxi::geom::mesh::TriangleMesh::getVertices()
{
	std::vector< Vertex > verts;
	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		verts.push_back( it->second );
	}

	return verts;
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::init( const std::string & name, const int & numV, const int & numF )
{
	setName( name );
	faces.reserve( numF );
	return this;
}

bool toxi::geom::mesh::TriangleMesh::intersectsRay( toxi::geom::Ray3D & ray )
{
	toxi::geom::Triangle3D tri = intersector.getTriangle();
	for( auto it = faces.begin(); it != faces.end(); ++it )
	{
		tri.set( it->a, it->b, it->c );
		if( intersector.intersectsRay( ray ) )
		{
			return true;
		}
	}

	return false;
}

toxi::geom::Triangle3D toxi::geom::mesh::TriangleMesh::perforateFace( Face & f, const float & size )
{
	toxi::geom::Vec3D centroid = f.getCentroid();
	float d = 1 - size;
	toxi::geom::Vec3D a2 = f.a.interpolateTo( centroid, d );
	toxi::geom::Vec3D b2 = f.b.interpolateTo( centroid, d );
	toxi::geom::Vec3D c2 = f.c.interpolateTo( centroid, d );
	remove( f );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::pointTowards( toxi::geom::Vec3D & dir )
{
	return transform( toxi::geom::Quaternion::getAlignmentQuat( dir, toxi::geom::Vec3D::Z_AXIS() ).toMatrix4x4( ), true );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::pointTowards( toxi::geom::Vec3D & dir, toxi::geom::Vec3D & forward )
{
	return transform( toxi::geom::Quaternion::getAlignmentQuat( dir, forward ).toMatrix4x4(), true );
}

void toxi::geom::mesh::TriangleMesh::remove( const Face & f )
{
	// TODO implement
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::rotateAroundAxis( const toxi::geom::Vec3D & axis, const float & theta )
{
	return transform( matrix.identity().rotateAroundAxis( axis, theta ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::rotateX( const float & theta )
{
	return transform( matrix.identity().rotateX( theta ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::rotateY(  const float & theta)
{
	return transform( matrix.identity().rotateY( theta ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::rotateZ(  const float & theta )
{
	return transform( matrix.identity().rotateZ( theta ) );
}

void toxi::geom::mesh::TriangleMesh::saveAsOBJ( OBJWriter & obj )
{
	saveAsOBJ( obj, true );
}

void toxi::geom::mesh::TriangleMesh::saveAsOBJ( OBJWriter & obj, const bool & saveNormals )
{
	// TODO: CHECK THIS FUNCTION
	int vOffset = obj.getCurrVertexOffset() + 1;
	int nOffset = obj.getCurrNormalOffset() + 1;
	obj.newObject( name );
	for( auto v : vertices )
	{
		obj.vertex( v.second );
	}

	if( saveNormals )
	{
		for( auto v : vertices )
		{
			obj.normal( v.second.normal );
		}

		for( auto f : faces )
		{
			obj.faceWithNormals( f.b.id + vOffset, f.a.id + vOffset, f.c.id + vOffset, f.b.id + nOffset, f.a.id + nOffset, f.c.id + nOffset );
		}
	}
	else 
	{
		for ( auto &f : faces )
		{
			obj.face( f.b.id + vOffset, f.a.id + vOffset, f.c.id + vOffset );
		}
	}
}

void toxi::geom::mesh::TriangleMesh::saveAsOBJ( const std::string & path )
{
	saveAsOBJ( path, true );
}

void toxi::geom::mesh::TriangleMesh::saveAsOBJ( const std::string & path, const bool & useFlippedY )
{
	OBJWriter obj = OBJWriter();
	obj.beginSave( path );
	saveAsOBJ( obj, useFlippedY );
	obj.endSave();
	//delete obj;
}

void toxi::geom::mesh::TriangleMesh::saveAsSTL( const std::string & path )
{
	saveAsSTL( path, true );
}

void toxi::geom::mesh::TriangleMesh::saveAsSTL( const std::string & path, const bool & useFlippedY )
{
	toxi::geom::mesh::STLWriter stl = toxi::geom::mesh::STLWriter();
	stl.beginSave( path, numFaces );
	handleSaveAsStl(stl, useFlippedY );
	stl.endSave();
	//delete stl;
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::scale( const float & scale )
{
	return transform( matrix.identity().scaleSelf( scale ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::scale( const float & _x, const float & _y, const float & _z )
{
	return transform( matrix.identity().scaleSelf( _x, _y, _z ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::setName( const std::string & name )
{
	this->name = name;
	return this;
}

std::string toxi::geom::mesh::TriangleMesh::toString()
{
	std::stringstream ss;
	ss << "TriangleMesh: " << name << " vertices: " << getNumVertices() << " faces: " << getNumFaces();
	return ss.str();
}

toxi::geom::mesh::WETriangleMesh * toxi::geom::mesh::TriangleMesh::toWEMesh()
{
	//TODO CHECK THIS
	//return toxi::geom::mesh::WETriangleMesh( name, vertices.size(), faces.size() ).addMesh( this );
	return new WETriangleMesh();
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::transform( toxi::geom::Matrix4x4 & mat )
{
	return transform( mat, true );	
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::transform( toxi::geom::Matrix4x4 & mat, const bool & updateNormals )
{
	for( auto &v : vertices )
	{
		v.second.set( mat.applyTo( v.second ) );
	}

	if( updateNormals )
	{
		computeFaceNormals();
	}

	return this;
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::translate( const float & _x, const float & _y, const float & _z )
{
	return transform( matrix.identity().translateSelf( _x, _y, _z ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::translate( const toxi::geom::Vec3D & trans )
{
	return transform( matrix.identity().translateSelf( trans.getX(), trans.getY(), trans.getZ() ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::updateVertex( const toxi::geom::Vec3D & orig, const toxi::geom::Vec3D & newPos )
{
	Vertex v = vertices.at( orig );
	if( v.isZeroVector() )
	{
		//TODO implement this
	}
	return this;
}

void toxi::geom::mesh::TriangleMesh::handleSaveAsStl( STLWriter & stl, const bool & useFlippedY )
{
	//TODO CHECK THIS
	if( useFlippedY )
	{
		stl.setScale( toxi::geom::Vec3D( 1, -1, 1 ) );
		for( auto &f : faces )
		{
			stl.face( f.a, f.b, f.c, f.normal, STLWriter::DEFAULT_RGB );
		}
	} 
	else 
	{
		for( auto &f : faces )
		{
			stl.face( f.a, f.b, f.c, f.normal, STLWriter::DEFAULT_RGB );
		}
	}
}
