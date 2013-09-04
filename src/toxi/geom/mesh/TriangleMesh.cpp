#include "TriangleMesh.h"

int toxi::geom::mesh::TriangleMesh::DEFAULT_STRIDE = 0; // TODO
int toxi::geom::mesh::TriangleMesh::DEFAULT_NUM_VERTICES = 1000;
int toxi::geom::mesh::TriangleMesh::DEFAULT_NUN_FACES = 1000;

toxi::geom::mesh::TriangleMesh::TriangleMesh(void)
{
	toxi::geom::mesh::TriangleMesh( "untitled");
}

toxi::geom::mesh::TriangleMesh::TriangleMesh( std::string name )
{
	toxi::geom::mesh::TriangleMesh( name, DEFAULT_NUM_VERTICES, DEFAULT_NUN_FACES );
}

toxi::geom::mesh::TriangleMesh::TriangleMesh( std::string name, int numV, int numF )
{
	this->init( name, numV, numF );
}


toxi::geom::mesh::TriangleMesh::~TriangleMesh(void)
{
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::addFace( toxi::geom::Vec3D * a, toxi::geom::Vec3D * b, toxi::geom::Vec3D * c )
{
	return addFace( a, b, c, nullptr, nullptr, nullptr, nullptr);
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::addFace( toxi::geom::Vec3D * a, toxi::geom::Vec3D  * b, toxi::geom::Vec3D  * c, toxi::geom::Vec2D  * uvA, toxi::geom::Vec2D * uvB, toxi::geom::Vec2D * uvC )
{
	return addFace(a, b, c, nullptr, uvA, uvB, uvC);
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::addFace( toxi::geom::Vec3D * a, toxi::geom::Vec3D *b, toxi::geom::Vec3D * c, toxi::geom::Vec3D * n )
{
	return addFace(a, b, c, n, nullptr, nullptr, nullptr);
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::addFace( toxi::geom::Vec3D * a, toxi::geom::Vec3D * b, toxi::geom::Vec3D * c, toxi::geom::Vec3D * n, toxi::geom::Vec2D * uvA, toxi::geom::Vec2D * uvB, toxi::geom::Vec2D * uvC )
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
		if (n != nullptr) {
			toxi::geom::Vec3D nc = va.sub(&vc).crossSelf(&va.sub(&vb));
			if (n->dot(&nc) < 0) {
				Vertex t = va;
				va = vb;
				vb = t;
			}
		}
		Face f = Face(&va, &vb, &vc, uvA,  uvB, uvC);
		faces.push_back( f );
		numFaces++;
	}
	return this;
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::addMesh( Mesh3D& m )
{
	for (Face f : m.getFaces()) {
		addFace(f.a, f.b, f.c, f.uvA, f.uvB, f.uvC);
	}
	return this;
}

toxi::geom::AABB * toxi::geom::mesh::TriangleMesh::center( toxi::geom::Vec3D * origin )
{
	computeCentroid();
	toxi::geom::Vec3D delta = origin != nullptr ? origin->sub(centroid) : centroid
		->getInverted();

	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		it->second.addSelf( &delta );
	}

	getBoundingBox();
	return bounds;
}

toxi::geom::mesh::Vertex toxi::geom::mesh::TriangleMesh::checkVertex( toxi::geom::Vec3D *v )
{
	Vertex * vertex = &vertices.at( *v );
	if (vertex == nullptr) {
		*vertex = createVertex(*v, uniqueVertexID++);
		//TODO
		//vertices.insert(vertex, vertex);
		numVertices++;
	}
	return *vertex;
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::clear()
{
	vertices.clear();
	faces.clear();
	bounds = new toxi::geom::AABB();
	numVertices = 0;
	numFaces = 0;
	uniqueVertexID = 0;
	return this;
}

toxi::geom::Vec3D toxi::geom::mesh::TriangleMesh::computeCentroid()
{
	centroid->clear();
	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		centroid->addSelf( &it->second );
	}

	return centroid->scaleSelf(1.0 / numVertices).copy();
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
		it->a->addFaceNormal( it->normal );
		it->b->addFaceNormal( it->normal );
		it->c->addFaceNormal( it->normal );
	}

	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		it->second.computeNormal();
	}

	return this;
}

toxi::geom::mesh::Vertex toxi::geom::mesh::TriangleMesh::createVertex( toxi::geom::Vec3D v, int id )
{
	return Vertex( v, id );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::faceOutwards()
{
	computeCentroid();

	for( auto it = faces.begin(); it != faces.end(); ++it )
	{
		toxi::geom::Vec3D n = it->getCentroid()->sub( centroid );
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
		Vertex t = *it->a;
		it->a = it->b;
		it->b = &t;
		toxi::geom::Vec2D tuv = *it->uvA;
		it->uvA = it->uvB;
		it->uvB = &tuv;
		it->normal->invert();
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
		minBounds.minSelf( &it->second );
		maxBounds.maxSelf( &it->second );
	}
	bounds = &toxi::geom::AABB::fromMinMax( &minBounds, &maxBounds );
	return bounds;
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

toxi::geom::mesh::Vertex toxi::geom::mesh::TriangleMesh::getClosestVertexToPoint( toxi::geom::Vec3D p )
{
	Vertex * closest = nullptr;
	float minDist = FLT_MAX;
	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		float d = it->second.distanceToSquared( &p );
		if ( d < minDist )
		{
			closest = new Vertex( p, 1 ); // TODO whats the 1?
			minDist = d;
		}
	}
	return *closest;
}

std::vector< float> * toxi::geom::mesh::TriangleMesh::getFaceNormalsAsArray()
{
	return getFaceNormalsAsArray( 0, DEFAULT_STRIDE );
}

std::vector< float> * toxi::geom::mesh::TriangleMesh::getFaceNormalsAsArray( int offset, int stride )
{
	stride = toxi::math::MathUtils::max( stride, 3 );
	std::vector< float> normals;
	int i = offset;
	for ( auto it = faces.begin(); it != faces.end(); ++it )
	{
		normals[ i ] = it->normal->x;
		normals[ i + 1 ] = it->normal->y;
		normals[ i + 2 ] = it->normal->z;
		i += stride;
		normals[ i ] = it->normal->x;
		normals[ i + 1 ] = it->normal->y;
		normals[ i + 2 ] = it->normal->z;
		i += stride;
		normals[ i ] = it->normal->x;
		normals[ i + 1 ] = it->normal->y;
		normals[ i + 2 ] = it->normal->z;
		i += stride;
	}
	return &normals;
}

std::vector< toxi::geom::mesh::Face > toxi::geom::mesh::TriangleMesh::getFaces()
{
	return faces;
}

toxi::geom::IsectData3D toxi::geom::mesh::TriangleMesh::getIntersectionData()
{
	return intersector->getIntersectionData();
}

std::vector< float> * toxi::geom::mesh::TriangleMesh::getMeshAsVertexArray()
{
	return getMeshAsVertexArray( 0, DEFAULT_STRIDE );
}

std::vector< float> * toxi::geom::mesh::TriangleMesh::getMeshAsVertexArray( int offset, int stride )
{
	stride = toxi::math::MathUtils::max( stride, 3 );
	std::vector< float> normals;
	int i = offset;
	for ( auto it = faces.begin(); it != faces.end(); ++it )
	{
		normals[ i ] = it->a->x;
		normals[ i + 1 ] = it->a->y;
		normals[ i + 2 ] = it->a->z;
		i += stride;
		normals[ i ] = it->b->x;
		normals[ i + 1 ] = it->b->y;
		normals[ i + 2 ] = it->b->z;
		i += stride;
		normals[ i ] = it->c->x;
		normals[ i + 1 ] = it->c->y;
		normals[ i + 2 ] = it->c->z;
		i += stride;
	}
	return &normals;
}

std::vector< float> * toxi::geom::mesh::TriangleMesh::getNormalsForUniqueVerticesArray()
{
	std::vector< float > normals;
	int i = 0;
	for ( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		normals[ i++ ] = it->second.normal->x;
		normals[ i++ ] = it->second.normal->y;
		normals[ i++ ] = it->second.normal->z;
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

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getRotatedAroundAxis( toxi::geom::Vec3D axis, float theta )
{
	TriangleMesh tri = TriangleMesh( *this );
	return tri.rotateAroundAxis( axis, theta );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getRotatedX( float theta )
{
	return TriangleMesh( *this ).rotateX( theta );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getRotatedY( float theta )
{
	return TriangleMesh( *this ).rotateY( theta );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getRotatedZ( float theta )
{
	return TriangleMesh( *this ).rotateZ( theta );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getScaled( float factor )
{
	return TriangleMesh( *this ).scale( factor, factor, factor );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getScaled( toxi::geom::Vec3D scale )
{
	return TriangleMesh( *this ).scale( scale.x, scale.y, scale.z );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::getTranslated( toxi::geom::Vec3D trans )
{
	return TriangleMesh( *this ).translate( trans );
}

std::vector< float> * toxi::geom::mesh::TriangleMesh::getUniqueVerticesAsArray()
{
	std::vector< float> * verts;
	verts->reserve( numVertices * 3 );

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

toxi::geom::mesh::Vertex toxi::geom::mesh::TriangleMesh::getVertexAtPoint( toxi::geom::Vec3D v )
{
	return vertices.at( v );
}

toxi::geom::mesh::Vertex toxi::geom::mesh::TriangleMesh::getVertexForID( int id )
{
	Vertex * vertex = nullptr;
	for( auto it = vertices.begin(); it != vertices.end(); ++it )
	{
		if( it->second.id == id )
		{
			vertex = &it->second;
			break;
		}
	}
	return *vertex;
}

std::vector< float> * toxi::geom::mesh::TriangleMesh::getVertexNormalsAsArray()
{
	return getVertexNormalsAsArray( 0, DEFAULT_STRIDE );
}

std::vector< float> * toxi::geom::mesh::TriangleMesh::getVertexNormalsAsArray( int offset, int stride )
{
	stride = toxi::math::MathUtils::max( stride, 3 );

	std::vector< float> * normals;
	normals->reserve( numVertices * 3 );

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

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::init( std::string name, int numV, int numF )
{
	setName( name );
	faces.reserve( numF );
	return this;
}

bool toxi::geom::mesh::TriangleMesh::intersectsRay( toxi::geom::Ray3D ray )
{
	toxi::geom::Triangle3D tri = intersector->getTriangle();
	for( auto it = faces.begin(); it != faces.end(); ++it )
	{
		tri.set( it->a, it->b, it->c );
		if( intersector->intersectsRay( ray ) )
		{
			return true;
		}
	}

	return false;
}

toxi::geom::Triangle3D toxi::geom::mesh::TriangleMesh::perforateFace( Face f, float size )
{
	toxi::geom::Vec3D centroid = *f.getCentroid();
	float d = 1 - size;
	toxi::geom::Vec3D a2 = f.a->interpolateTo( &centroid, d );
	toxi::geom::Vec3D b2 = f.b->interpolateTo( &centroid, d );
	toxi::geom::Vec3D c2 = f.c->interpolateTo( &centroid, d );
	remove( f );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::pointTowards( toxi::geom::Vec3D dir )
{
	return transform( toxi::geom::Quaternion::getAlignmentQuat( dir, toxi::geom::Vec3D::Z_AXIS() ).toMatrix4x4( ), true );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::pointTowards( toxi::geom::Vec3D dir, toxi::geom::Vec3D forward )
{
	return transform( toxi::geom::Quaternion::getAlignmentQuat( dir, forward ).toMatrix4x4(), true );
}

void toxi::geom::mesh::TriangleMesh::remove( Face f )
{
	// TODO implement
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::rotateAroundAxis( toxi::geom::Vec3D axis, float theta )
{
	return transform( matrix->identity().rotateAroundAxis( axis, theta ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::rotateX( float theta )
{
	return transform( matrix->identity().rotateX( theta ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::rotateY( float theta )
{
	return transform( matrix->identity().rotateY( theta ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::rotateZ( float theta )
{
	return transform( matrix->identity().rotateZ( theta ) );
}

void toxi::geom::mesh::TriangleMesh::saveAsOBJ( OBJWriter * obj )
{
	saveAsOBJ( obj, true );
}

void toxi::geom::mesh::TriangleMesh::saveAsOBJ( OBJWriter * obj, bool saveNormals )
{
	// TODO: CHECK THIS FUNCTION
	int vOffset = obj->getCurrVertexOffset() + 1;
	int nOffset = obj->getCurrNormalOffset() + 1;
	obj->newObject( name );
	for( auto &v : vertices )
	{
		obj->vertex( &v.second );
	}

	if( saveNormals )
	{
		for( auto &v : vertices )
		{
			obj->normal( v.second.normal );
		}

		for( auto &f : faces )
		{
			obj->faceWithNormals( f.b->id + vOffset, f.a->id + vOffset, f.c->id + vOffset, f.b->id + nOffset, f.a->id + nOffset, f.c->id + nOffset );
		}
	}
	else 
	{
		for ( auto &f : faces )
		{
			obj->face( f.b->id + vOffset, f.a->id + vOffset, f.c->id + vOffset );
		}
	}
}

void toxi::geom::mesh::TriangleMesh::saveAsOBJ( std::string path )
{
	saveAsOBJ( path, true );
}

void toxi::geom::mesh::TriangleMesh::saveAsOBJ( std::string path, bool useFlippedY )
{
	OBJWriter * obj = new OBJWriter();
	obj->beginSave( path );
	saveAsOBJ( obj, useFlippedY );
	obj->endSave();
	delete obj;
}

void toxi::geom::mesh::TriangleMesh::saveAsSTL( std::string path )
{
	saveAsSTL( path, true );
}

void toxi::geom::mesh::TriangleMesh::saveAsSTL( std::string path, bool useFlippedY )
{
	toxi::geom::mesh::STLWriter * stl = new toxi::geom::mesh::STLWriter();
	stl->beginSave( path, numFaces );
	handleSaveAsStl(*stl, useFlippedY );
	stl->endSave();
	delete stl;
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::scale( float scale )
{
	return transform( matrix->identity().scaleSelf( scale ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::scale( float _x, float _y, float _z )
{
	return transform( matrix->identity().scaleSelf( _x, _y, _z ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::setName( std::string name )
{
	this->name = name;
}

std::string toxi::geom::mesh::TriangleMesh::toString()
{
	std::stringstream ss;
	ss << "TriangleMesh: " << name << " vertices: " << getNumVertices() << " faces: " << getNumFaces();
	return ss.str();
}

toxi::geom::mesh::WETriangleMesh toxi::geom::mesh::TriangleMesh::toWEMesh()
{
	//TODO CHECK THIS
	//return toxi::geom::mesh::WETriangleMesh( name, vertices.size(), faces.size() ).addMesh( this );
	return WETriangleMesh();
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::transform( toxi::geom::Matrix4x4 mat )
{
	return transform( mat, true );	
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::transform( toxi::geom::Matrix4x4 mat, bool updateNormals )
{
	for( auto &v : vertices )
	{
		v.second.set( &mat.applyTo( v.second ) );
	}

	if( updateNormals )
	{
		computeFaceNormals();
	}

	return this;
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::translate( float _x, float _y, float _z )
{
	return transform( matrix->identity().translateSelf( _x, _y, _z ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::translate( toxi::geom::Vec3D trans )
{
	return transform( matrix->identity().translateSelf( trans.x, trans.y, trans.z ) );
}

toxi::geom::mesh::TriangleMesh* toxi::geom::mesh::TriangleMesh::updateVertex( toxi::geom::Vec3D orig, toxi::geom::Vec3D newPos )
{
	Vertex * v = &vertices.at( orig );
	if( v == nullptr )
	{
		//TODO implement this
	}
	return this;
}

void toxi::geom::mesh::TriangleMesh::handleSaveAsStl( STLWriter stl, bool useFlippedY )
{
	//TODO CHECK THIS
	if( useFlippedY )
	{
		stl.setScale( new toxi::geom::Vec3D( 1, -1, 1 ) );
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
