#include "Matrix4x4.h"

toxi::geom::Matrix4x4 TEMP = toxi::geom::Matrix4x4();
static const int width = 4;
static const int height = 4;

toxi::geom::Matrix4x4::Matrix4x4(void) 
{
	init();
	matrix[ 0 ][ 0 ] = 1;
	matrix[ 1 ][ 1 ] = 1;
	matrix[ 2 ][ 2 ] = 1;
	matrix[ 3 ][ 3 ] = 1;
}

toxi::geom::Matrix4x4::Matrix4x4( double v11, double v12, double v13, double v14,
								 double v21, double v22, double v23, double v24, double v31,
								 double v32, double v33, double v34, double v41, double v42,
								 double v43, double v44 )
{
	init();
	matrix[ 0 ][ 0 ] = v11;
	matrix[ 0 ][ 1 ] = v12;
	matrix[ 0 ][ 2 ] = v13;
	matrix[ 0 ][ 3 ] = v14;
	
	matrix[ 1 ][ 0 ] = v21;
	matrix[ 1 ][ 1 ] = v22;
	matrix[ 1 ][ 2 ] = v23;
	matrix[ 1 ][ 3 ] = v24;

	matrix[ 2 ][ 0 ] = v31;
	matrix[ 2 ][ 1 ] = v32;
	matrix[ 2 ][ 2 ] = v33;
	matrix[ 2 ][ 3 ] = v34;

	matrix[ 3 ][ 0 ] = v41;
	matrix[ 3 ][ 1 ] = v42;
	matrix[ 3 ][ 2 ] = v43;
	matrix[ 3 ][ 3 ] = v44;
}

toxi::geom::Matrix4x4::Matrix4x4( double* array, bool isLength16 )
{
	init();
	if( isLength16 )
	{
		matrix[ 0 ][ 0 ] = array[ 0 ];
		matrix[ 0 ][ 1 ] = array[ 1 ];
		matrix[ 0 ][ 2 ] = array[ 2 ];
		matrix[ 0 ][ 3 ] = array[ 3 ];

		matrix[ 1 ][ 0 ] = array[ 4 ];
		matrix[ 1 ][ 1 ] = array[ 5 ];
		matrix[ 1 ][ 2 ] = array[ 6 ];
		matrix[ 1 ][ 3 ] = array[ 7 ];

		matrix[ 2 ][ 0 ] = array[ 8 ];
		matrix[ 2 ][ 1 ] = array[ 9] ;
		matrix[ 2 ][ 2 ] = array[ 10 ];
		matrix[ 2 ][ 3 ] = array[ 11 ];

		matrix[ 3 ][ 0 ] = array[ 12 ];
		matrix[ 3 ][ 1 ] = array[ 13 ];
		matrix[ 3 ][ 2 ] = array[ 14 ];
		matrix[ 3 ][ 3 ] = array[ 15 ];
	}
	else
	{
		matrix[ 0 ][ 0 ] = array[ 0 ];
		matrix[ 0 ][ 1 ] = array[ 1 ];
		matrix[ 0 ][ 2 ] = array[ 2 ];

		matrix[ 1 ][ 0 ] = array[ 3 ];
		matrix[ 1 ][ 1 ] = array[ 4 ];
		matrix[ 1 ][ 2 ] = array[ 5 ];

		matrix[ 2 ][ 0 ] = array[ 6 ];
		matrix[ 2 ][ 1 ] = array[ 7 ];
		matrix[ 2 ][ 2 ] = array[ 8 ];

		matrix[ 3 ][ 0 ] = array[ 9 ];
		matrix[ 3 ][ 1 ] = array[ 10 ];
		matrix[ 3 ][ 2 ] = array[ 11 ];
		matrix[ 3 ][ 3 ] = 1;
	}
}

toxi::geom::Matrix4x4::Matrix4x4( Matrix4x4 &m )
{
	init();
	for( size_t i = 0; i < 4; i++ )
	{
		matrix[ i ] = m.matrix[ i ];
	}
}

toxi::geom::Matrix4x4::~Matrix4x4(void)
{
}

void toxi::geom::Matrix4x4::init()
{
	this->matrix = new double*[width];
	for( size_t i = 0; i < height; i++ ) 
	{
		matrix[ i ] = new double[ width ];
	}
}

bool toxi::geom::Matrix4x4::LUDecomposition( double* matrix0, int* row_perm, int width )
{
	double row_scale[ 4 ];
	{
		int i, j;
		int ptr, rs;
		double big, temp;

		ptr = 0;
		rs = 0;

		// For each row ...
		i = width;
		while ( i-- != 0 ) 
		{
			big = 0.0;

			// For each column, find the largest element in the row
			j = width;
			while ( j-- != 0 ) 
			{
				temp = matrix0[ ptr++ ];
				temp = toxi::math::MathUtils::abs( temp );
				if ( temp > big ) 
				{
					big = temp;
				}
			}
			// Is the matrix singular?
			if ( big == 0.0 ) 
			{
				return false;
			}
			row_scale[ rs++ ] = 1.0 / big;
		}
	}

	{
		int j;
		int mtx = 0;

		// For all columns, execute Crout's method
		for ( j = 0; j < width; j++ ) 
		{
			int i, imax, k;
			int target, p1, p2;
			double sum, big, temp;

			// Determine elements of upper diagonal matrix U
			for ( i = 0; i < j; i++ ) 
			{
				target = mtx + ( width * i ) + j;
				sum = matrix0[ target ];
				k = i;
				p1 = mtx + ( width * i );
				p2 = mtx + j;
				while ( k-- != 0 ) {
					sum -= matrix0[ p1 ] * matrix0[ p2 ];
					p1++;
					p2 += width;
				}
				matrix0[ target ] = sum;
			}

			// Search for largest pivot element and calculate
			// intermediate elements of lower diagonal matrix L.
			big = 0.0;
			imax = -1;
			for ( i = j; i < width; i++ ) 
			{
				target = mtx + ( width * i ) + j;
				sum = matrix0[ target ];
				k = j;
				p1 = mtx + ( width * i );
				p2 = mtx + j;
				while ( k-- != 0 ) 
				{
					sum -= matrix0[ p1 ] * matrix0[ p2 ];
					p1++;
					p2 += width;
				}
				matrix0[ target ] = sum;

				// Is this the best pivot so far?
				if ( ( temp = row_scale[ i ] * toxi::math::MathUtils::abs( sum ) ) >= big ) 
				{
					big = temp;
					imax = i;
				}
			}

			if ( imax < 0 ) 
			{
				return false;
			}

			// Is a row exchange necessary?
			if ( j != imax ) 
			{
				// Yes: exchange rows
				k = width;
				p1 = mtx + ( width * imax );
				p2 = mtx + ( width * j );
				while ( k-- != 0 ) 
				{
					temp = matrix0[ p1 ];
					matrix0[ p1++ ] = matrix0[ p2 ];
					matrix0[ p2++ ] = temp;
				}

				// Record change in scale factor
				row_scale[ imax ] = row_scale[ j ];
			}

			// Record row permutation
			row_perm[ j ] = imax;

			// Is the matrix singular
			if ( matrix0[ ( mtx + ( width * j ) + j ) ] == 0.0 ) 
			{
				return false;
			}

			// Divide elements of lower diagonal matrix L by pivot
			if ( j != width - 1 ) 
			{
				temp = 1.0 / ( matrix0[ ( mtx + ( width * j ) + j ) ] );
				target = mtx + ( width * ( j + 1 ) ) + j;
				i = ( width - 1 ) - j;
				while ( i-- != 0 ) 
				{
					matrix0[ target ] *= temp;
					target += width;
				}
			}
		}
	}
	return true;
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::add( Matrix4x4 rhs )
{
	Matrix4x4 result = Matrix4x4(*this);
	return result.addSelf( rhs );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::addSelf( Matrix4x4 m )
{
	for( size_t i = 0; i < 4; i++ )
	{
		matrix[ i ] = m.matrix[ i ];
	}
}

toxi::geom::Vec3D toxi::geom::Matrix4x4::applyTo( Vec3D v )
{
	return applyToSelf( Vec3D( v ) );
}

toxi::geom::Vec3D toxi::geom::Matrix4x4::applyToSelf( Vec3D v )
{
	for ( int i = 0; i < 4; i++ ) {
		double* m = matrix[ i ];
		temp[ i ] = v.x * m[ 0 ] + v.y * m[ 1 ] + v.z * m[ 2 ] + m[ 3 ];
	}
	v.set( ( float ) temp[ 0 ], ( float ) temp[ 1 ], ( float ) temp[ 2 ] ).scaleSelf(
		( float ) ( 1.0 / temp[ 3 ] ) );
	return v;
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::getInverted()
{
	return Matrix4x4( *this ).invert();
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::getRotatedAroundAxis( Vec3D axis, double theta )
{
	return Matrix4x4( *this ).rotateAroundAxis( axis, theta );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::getRotatedX( double theta )
{
	return Matrix4x4( *this ).rotateX( theta );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::getRotatedY( double theta )
{
	return Matrix4x4( *this ).rotateY( theta );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::getRotatedZ( double theta )
{
	return Matrix4x4( *this ).rotateZ( theta );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::getTransposed()
{
	return Matrix4x4( *this ).transpose();
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::identity()
{

	for( size_t i = 0; i < width; i++ )
	{
		for( size_t j = 0; j < height; j++ )
		{
			this->matrix[ i ][ j ] = 0;
		}
	}

	matrix[ 0 ][ 0 ] = 1;
	matrix[ 1 ][ 1 ] = 1;
	matrix[ 2 ][ 2 ] = 1;
	matrix[ 3 ][ 3 ] = 1;
	return *this;
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::invert()
{
	double tmp[ 12 ];
	double src[ 16 ];
	double dst[ 16 ];
	double * mat = toArray();

	for (int i = 0; i < 4; i++) {
		int i4 = i << 2;
		src[ i ] = mat[ i4 ];
		src[ i + 4 ] = mat[ i4 + 1 ];
		src[ i + 8 ] = mat[ i4 + 2 ];
		src[ i + 12 ] = mat[ i4 + 3 ];
	}

	// calculate pairs for first 8 elements (cofactors)
	tmp[ 0 ] = src[ 10 ] * src[ 15 ];
	tmp[ 1 ] = src[ 11 ] * src[ 14 ];
	tmp[ 2 ] = src[ 9 ] * src[ 15 ];
	tmp[ 3 ] = src[ 11 ] * src[ 13 ];
	tmp[ 4 ] = src[ 9 ] * src[ 14 ];
	tmp[ 5 ] = src[ 10 ] * src[ 13 ];
	tmp[ 6 ] = src[ 8 ] * src[ 15 ];
	tmp[ 7 ] = src[ 11 ] * src[ 12 ];
	tmp[ 8 ] = src[ 8 ] * src[ 14 ];
	tmp[ 9 ] = src[ 10 ] * src[ 12 ];
	tmp[ 10 ] = src[ 8 ] * src[ 13 ];
	tmp[ 11 ] = src[ 9 ] * src[ 12 ];

	// calculate first 8 elements (cofactors)
	double src0 = src[ 0 ];
	double src1 = src[ 1 ];
	double src2 = src[ 2 ];
	double src3 = src[ 3 ];
	double src4 = src[ 4 ];
	double src5 = src[ 5 ];
	double src6 = src[ 6 ];
	double src7 = src[ 7 ];
	dst[ 0 ] = tmp[ 0 ] * src5 + tmp[ 3 ] * src6 + tmp[ 4 ] * src7;
	dst[ 0 ] -= tmp[ 1 ] * src5 + tmp[ 2 ] * src6 + tmp[ 5 ] * src7;
	dst[ 1 ] = tmp[ 1 ] * src4 + tmp[ 6 ] * src6 + tmp[ 9 ] * src7;
	dst[ 1 ] -= tmp[ 0 ] * src4 + tmp[ 7 ] * src6 + tmp[ 8 ] * src7;
	dst[ 2 ] = tmp[ 2 ] * src4 + tmp[ 7 ] * src5 + tmp[ 10 ] * src7;
	dst[ 2 ] -= tmp[ 3 ] * src4 + tmp[ 6 ] * src5 + tmp[ 11 ] * src7;
	dst[ 3 ] = tmp[ 5 ] * src4 + tmp[ 8 ] * src5 + tmp[ 11 ] * src6;
	dst[ 3 ] -= tmp[ 4 ] * src4 + tmp[ 9 ] * src5 + tmp[ 10 ] * src6;
	dst[ 4 ] = tmp[ 1 ] * src1 + tmp[ 2 ] * src2 + tmp[ 5 ] * src3;
	dst[ 4 ] -= tmp[ 0 ] * src1 + tmp[ 3 ] * src2 + tmp[ 4 ] * src3;
	dst[ 5 ] = tmp[ 0 ] * src0 + tmp[ 7 ] * src2 + tmp[ 8 ] * src3;
	dst[ 5 ] -= tmp[ 1 ] * src0 + tmp[ 6 ] * src2 + tmp[ 9 ] * src3;
	dst[ 6 ] = tmp[ 3 ] * src0 + tmp[ 6 ] * src1 + tmp[ 11 ] * src3;
	dst[ 6 ] -= tmp[ 2 ] * src0 + tmp[ 7 ] * src1 + tmp[ 10 ] * src3;
	dst[ 7 ] = tmp[ 4 ] * src0 + tmp[ 9 ] * src1 + tmp[ 10 ] * src2;
	dst[ 7 ] -= tmp[ 5 ] * src0 + tmp[ 8 ] * src1 + tmp[ 11 ] * src2;

	// calculate pairs for second 8 elements (cofactors)
	tmp[ 0 ] = src2 * src7;
	tmp[ 1 ] = src3 * src6;
	tmp[ 2 ] = src1 * src7;
	tmp[ 3 ] = src3 * src5;
	tmp[ 4 ] = src1 * src6;
	tmp[ 5 ] = src2 * src5;
	tmp[ 6 ] = src0 * src7;
	tmp[ 7 ] = src3 * src4;
	tmp[ 8 ] = src0 * src6;
	tmp[ 9 ] = src2 * src4;
	tmp[ 10 ] = src0 * src5;
	tmp[ 11 ] = src1 * src4;

	// calculate second 8 elements (cofactors)
	src0 = src[ 8 ];
	src1 = src[ 9 ];
	src2 = src[ 10 ];
	src3 = src[ 11 ];
	src4 = src[ 12 ];
	src5 = src[ 13 ];
	src6 = src[ 14 ];
	src7 = src[ 15 ];
	dst[ 8 ] = tmp[ 0 ] * src5 + tmp[ 3 ] * src6 + tmp[ 4 ] * src7;
	dst[ 8 ] -= tmp[ 1 ] * src5 + tmp[ 2 ] * src6 + tmp[ 5 ] * src7;
	dst[ 9 ] = tmp[ 1 ] * src4 + tmp[ 6 ] * src6 + tmp[ 9 ] * src7;
	dst[ 9 ] -= tmp[ 0 ] * src4 + tmp[ 7 ] * src6 + tmp[ 8 ] * src7;
	dst[ 10 ] = tmp[ 2 ] * src4 + tmp[ 7 ] * src5 + tmp[ 10 ] * src7;
	dst[ 10 ] -= tmp[ 3 ] * src4 + tmp[ 6 ] * src5 + tmp[ 11 ] * src7;
	dst[ 11 ] = tmp[ 5 ] * src4 + tmp[ 8 ] * src5 + tmp[ 11 ] * src6;
	dst[ 11 ] -= tmp[ 4 ] * src4 + tmp[ 9 ] * src5 + tmp[ 10 ] * src6;
	dst[ 12 ] = tmp[ 2 ] * src2 + tmp[ 5 ] * src3 + tmp[ 1 ] * src1;
	dst[ 12 ] -= tmp[ 4 ] * src3 + tmp[ 0 ] * src1 + tmp[ 3 ] * src2;
	dst[ 13 ] = tmp[ 8 ] * src3 + tmp[ 0 ] * src0 + tmp[ 7 ] * src2;
	dst[ 13 ] -= tmp[ 6 ] * src2 + tmp[ 9 ] * src3 + tmp[ 1 ] * src0;
	dst[ 14 ] = tmp[ 6 ] * src1 + tmp[ 11 ] * src3 + tmp[ 3 ] * src0;
	dst[ 14 ] -= tmp[ 10 ] * src3 + tmp[ 2 ] * src0 + tmp[ 7 ] * src1;
	dst[ 15 ] = tmp[ 10 ] * src2 + tmp[ 4 ] * src0 + tmp[ 9 ] * src1;
	dst[ 15 ] -= tmp[ 8 ] * src1 + tmp[ 11 ] * src2 + tmp[ 5 ] * src0;

	double det = 1.0 / (src[ 0 ] * dst[ 0 ] + src[ 1 ] * dst[ 1 ] + src[ 2 ] * dst[ 2 ] + src[ 3 ]
	* dst[ 3 ]);

	for (int i = 0, k = 0; i < 4; i++) {
		double* m = matrix[ i ];
		for (int j = 0; j < 4; j++) {
			m[ j ] = dst[ k++ ] * det;
		}
	}
	return *this;
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::lookAt( Vec3D eye, Vec3D target, Vec3D up )
{
	Vec3D f = eye.sub( target ).normalize();
	Vec3D s = up.cross( f ).normalize();
	Vec3D t = f.cross( s ).normalize();
	return set( s.x, s.y, s.z, -s.dot( eye ), t.x, t.y, t.z, -t.dot( eye ), f.x,
		f.y, f.z, -f.dot( eye ), 0, 0, 0, 1 );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::multiply( double factor )
{
	return Matrix4x4( *this ).multiply( factor );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::multiply( Matrix4x4 mat )
{
	return Matrix4x4( *this ).multiplySelf( mat );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::multiplySelf( double factor )
{
	for( size_t i = 0; i < width; i++ )
	{
		for( size_t j = 0; j < height; j++ )
		{
			this->matrix[ i ][ j ] *= factor;
		}
	}

	return *this;
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::multiplySelf( Matrix4x4 mat )
{
	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			temp[ j ] = matrix[ i ][ 0 ] * mat.matrix[ 0 ][ j ] + matrix[ i ][ 1 ] * mat.matrix[ 1 ][ j ] + this->matrix[ i ][ 2 ] * mat.matrix[ 2 ][ j ] + matrix[ i ][ 3 ]
			* mat.matrix[ 3 ][ j ];
		}
		matrix[i][0] = temp[0];
		matrix[i][1] = temp[1];
		matrix[i][2] = temp[2];
		matrix[i][3] = temp[3];
	}
	return *this;
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::rotateAroundAxis( Vec3D axis, double theta )
{
	double x, y, z, s, c, t, tx, ty;
	x = axis.x;
	y = axis.y;
	z = axis.z;
	s = toxi::math::MathUtils::sin( theta );
	c = toxi::math::MathUtils::cos( theta );
	t = 1 - c;
	tx = t * x;
	ty = t * y;
	TEMP.set( tx * x + c, tx * y + s * z, tx * z - s * y, 0, tx * y - s * z,
		ty * y + c, ty * z + s * x, 0, tx * z + s * y, ty * z - s * x,
		t * z * z + c, 0, 0, 0, 0, 1 );
	return this->multiplySelf( TEMP );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::rotateX( double theta )
{
	TEMP.identity();
	TEMP.matrix[1][1] = TEMP.matrix[2][2] = toxi::math::MathUtils::cos(theta);
	TEMP.matrix[2][1] = toxi::math::MathUtils::sin(theta);
	TEMP.matrix[1][2] = -TEMP.matrix[2][1];
	return this->multiplySelf(TEMP);
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::rotateY( double theta )
{
	TEMP.identity();
	TEMP.matrix[0][0] = TEMP.matrix[2][2] = toxi::math::MathUtils::cos(theta);
	TEMP.matrix[0][2] = toxi::math::MathUtils::sin(theta);
	TEMP.matrix[2][0] = -TEMP.matrix[0][2];
	return this->multiplySelf(TEMP);
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::rotateZ( double theta )
{
	TEMP.identity();
	TEMP.matrix[0][0] = TEMP.matrix[1][1] = toxi::math::MathUtils::cos(theta);
	TEMP.matrix[1][0] = toxi::math::MathUtils::sin(theta);
	TEMP.matrix[0][1] = -TEMP.matrix[1][0];
	return this->multiplySelf(TEMP);
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::scale( double scale )
{
	return Matrix4x4( *this ).scaleSelf( scale );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::scale( double scaleX, double scaleY, double scaleZ )
{
	return Matrix4x4( *this ).scaleSelf( scaleX, scaleY, scaleZ );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::scale( Vec3D scale )
{
	return Matrix4x4( *this).scaleSelf( scale.x, scale.y, scale.z );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::scaleSelf( double scale )
{
	return scaleSelf( scale, scale, scale );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::scaleSelf( double scaleX, double scaleY, double scaleZ )
{
	TEMP.identity();
	TEMP.setScale(scaleX, scaleY, scaleZ);
	return this->multiplySelf(TEMP);
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::scaleSelf( Vec3D scale )
{
	return scaleSelf( scale.x, scale.y, scale.z );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::set( double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l, double m, double n, double o, double p )
{
	matrix[ 0 ][ 0 ] = a;
	matrix[ 0 ][ 1 ] = b;
	matrix[ 0 ][ 2 ] = c;
	matrix[ 0 ][ 3 ] = d;

	matrix[ 1 ][ 0 ] = e;
	matrix[ 1 ][ 1 ] = f;
	matrix[ 1 ][ 2 ] = g;
	matrix[ 1 ][ 3 ] = h;

	matrix[ 2 ][ 0 ] = i;
	matrix[ 2 ][ 1 ] = j;
	matrix[ 2 ][ 2 ] = k;
	matrix[ 2 ][ 3 ] = l;

	matrix[ 3 ][ 0 ] = m;
	matrix[ 3 ][ 1 ] = n;
	matrix[ 3 ][ 2 ] = o;
	matrix[ 3 ][ 3 ] = p;

	return *this;
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::set( Matrix4x4 mat )
{
	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			this->matrix[ i ][ j ] = mat.matrix[ i ][ j ];
		}
	}

	return *this;
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::setFrustum( double left, double right, double top, double bottom, double near, double far )
{
	return set( ( 2.0 * near ) / ( right - left ), 0, ( left + right )
		/ ( right - left ), 0, 0, ( 2.0 * near ) / ( top - bottom ),
		( top + bottom ) / ( top - bottom ), 0, 0, 0, -( near + far )
		/ ( far - near ), ( -2 * near * far ) / ( far - near ), 0, 0,
		-1, 0);
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::setOrtho( double left, double right, double top, double bottom, double near, double far )
{
	return set(2.0 / (right - left), 0, 0, (left + right) / (right - left),
		0, 2.0 / (top - bottom), 0, (top + bottom) / (top - bottom), 0,
		0, -2.0 / (far - near), (far + near) / (far - near), 0, 0, 0, 1);
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::setPerspective( double fov, double aspect, double near, double far )
{
	double y = near * std::tan(0.5 * toxi::math::MathUtils::radians(fov));
	double x = aspect * y;
	return setFrustum(-x, x, y, -y, near, far);
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::setPosition( double x, double y, double z )
{
	matrix[ 0 ][ 3 ] = x;
	matrix[ 1 ][ 3 ] = y;
	matrix[ 2 ][ 3 ] = z;
	return *this;
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::setScale( double scaleX, double scaleY, double scaleZ )
{
	matrix[ 0 ][ 0 ] = scaleX;
	matrix[ 1 ][ 1 ] = scaleY;
	matrix[ 2 ][ 2 ] = scaleZ;
	return *this;
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::sub( Matrix4x4 mat )
{
	return Matrix4x4( *this ).subSelf( mat );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::subSelf( Matrix4x4 mat )
{
	for ( int i = 0; i < 4; i++ ) 
	{
		for ( int j = 0; j < 4; j++ ) 
		{
			this->matrix[ i ][ j ] -= mat.matrix[ i ][ j ];
		}
	}

	return *this;
}

double* toxi::geom::Matrix4x4::toArray()
{
	double* result;
	for (int i = 0, k = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[k++] = matrix[ i ][ j ];
		}
	}
	return result;
}

float* toxi::geom::Matrix4x4::toFloatArra()
{
	float* result;
	double* tmp = toArray();
	for (int i = 0; i < 16; i++) {
		result[i] = ( float ) tmp[i];
	}
	return result;
}

std::string toxi::geom::Matrix4x4::toString()
{
	std::stringstream ss;
	ss << "| " << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2]
	<< " " << matrix[0][3] << " |\n" << "| " << matrix[1][0] << " "
		<< matrix[1][1] << " " << matrix[1][2] << " " << matrix[1][3]
	<< " |\n" << "| " << matrix[2][0] << " " << matrix[2][1] << " "
		<< matrix[2][2] << " " << matrix[2][3] << " |\n" << "| "
		<< matrix[3][0] << " " << matrix[3][1] << " " << matrix[3][2] << " "
		<< matrix[3][3] << " |";
}

float* toxi::geom::Matrix4x4::toTransposedFloatArray()
{
	float* result;
	for (int i = 0, k = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[k++] = (float) matrix[j][i];
		}
	}
	return result;
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::translate( double dx, double dy, double dz )
{
	return Matrix4x4( *this ).translateSelf( dx, dy, dz );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::translate( Vec3D v )
{
	return Matrix4x4( *this ).translateSelf( v.x, v.y, v.z );
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::translateSelf( double dx, double dy, double dz )
{
	TEMP.identity();
	TEMP.setPosition(dx, dy, dz);
	return this->multiplySelf(TEMP);
}

toxi::geom::Matrix4x4 toxi::geom::Matrix4x4::transpose()
{
	return set(matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
		matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1],
		matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2],
		matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]);
}
