#pragma once

#ifndef __MATRIX4X4_H__
#define __MATRIX4X4_H__

#include < sstream >

//#include "../math/MathUtils.h"
//#include "Vec3D.h"

namespace toxi
{
	namespace geom
	{
		class Vec3D;
		class MathUtils;
		class Matrix4x4
		{
		public:
			Matrix4x4(void);
			Matrix4x4( const double & v11, const double & v12, const double & v13, const double & v14,
				const double & v21, const double & v22, const double & v23, const double & v24, const double & v31,
				const double & v32, const double & v33, const double & v34, const double & v41, const double & v42,
				const double & v43, const double & v44 );
			Matrix4x4( const double* & array, const bool & isLength16 );
			Matrix4x4( Matrix4x4 &m );

			~Matrix4x4(void);

			
			double** matrix;
			int width;
			int height;
			toxi::geom::Matrix4x4 * TEMP;

			static bool LUDecomposition( const double* & matrix0, const int* & row_perm, const int & width );

			Matrix4x4 add( const Matrix4x4 & rhs );
			Matrix4x4 addSelf( const Matrix4x4 & m );
			Vec3D applyTo( const Vec3D & v );
			Vec3D applyToSelf( Vec3D & v );
			Matrix4x4 getInverted();
			Matrix4x4 getRotatedAroundAxis( const Vec3D & axis, const double & theta );
			Matrix4x4 getRotatedX( const double & theta );
			Matrix4x4 getRotatedY( const double & theta );
			Matrix4x4 getRotatedZ( const double & theta );
			Matrix4x4 getTransposed( );
			Matrix4x4 identity( );
			void init();
			Matrix4x4 invert();
			Matrix4x4 lookAt( Vec3D & eye, Vec3D & target, Vec3D & up );
			Matrix4x4 multiply( const double & factor );
			Matrix4x4 multiply( const Matrix4x4 & mat );
			Matrix4x4 multiplySelf( const double & factor );
			Matrix4x4 multiplySelf( const Matrix4x4 & mat );
			Matrix4x4 rotateAroundAxis( const Vec3D & axis, const double & theta );
			Matrix4x4 rotateX( const double & theta );
			Matrix4x4 rotateY( const double & theta );
			Matrix4x4 rotateZ( const double & theta );
			Matrix4x4 scale( const double & scale );
			Matrix4x4 scale( const double & scaleX, const double & scaleY, const double & scaleZ );
			Matrix4x4 scale( const Vec3D & scale );
			Matrix4x4 scaleSelf( const double & scale );
			Matrix4x4 scaleSelf( const double & scaleX, const double & scaleY, const double & scaleZ );
			Matrix4x4 scaleSelf( const Vec3D & scale );
			Matrix4x4 set( const double & a, const double & b, const double & c, const double & d, const double & e,
				const double & f, const double & g, const double & h, const double & i, const double & j, const double & k,
				const double & l, const double & m, const double & n, const double & o, const double & p );
			Matrix4x4 set( const Matrix4x4 & mat );
			Matrix4x4 setFrustum( const double & left, const double & right, const double & top,
				const double & bottom, const double & near, const double & far );
			Matrix4x4 setOrtho( const double & left, const double & right, const double & top,
				const double & bottom, const double & near, const double & far );
			Matrix4x4 setPerspective( const double & fov, const double & aspect, const double & near,
				const double & far );
			Matrix4x4 setPosition( const double & x, const double & y, const double & z );
			Matrix4x4 setScale( const double & scaleX, const double & scaleY, const double & scaleZ );
			Matrix4x4 sub( const Matrix4x4 & mat );
			Matrix4x4 subSelf( const Matrix4x4 & mat );
			double* toArray();
			float* toFloatArra();
			std::string toString();
			float* toTransposedFloatArray();
			Matrix4x4 translate( const double & dx, const double & dy, const double & dz );
			Matrix4x4 translate( const Vec3D & v );
			Matrix4x4 translateSelf( const double & dx, const double & dy, const double & dz );
			Matrix4x4 transpose();


		protected:
			double* temp;
		};
	}
}

#endif