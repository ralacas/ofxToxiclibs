#pragma once

#ifndef __MATRIX4X4_H__
#define __MATRIX4X4_H__

#include < sstream >
#include "../math/MathUtils.h"
#include "Vec3D.h"

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
			Matrix4x4( double v11, double v12, double v13, double v14,
				double v21, double v22, double v23, double v24, double v31,
				double v32, double v33, double v34, double v41, double v42,
				double v43, double v44 );
			Matrix4x4( double* array, bool isLength16 );
			Matrix4x4( Matrix4x4 &m );

			~Matrix4x4(void);

			double** matrix;
			static const int width;
			static const int height;

			static bool LUDecomposition( double* matrix0, int* row_perm, int width );

			Matrix4x4 add( Matrix4x4 rhs );
			Matrix4x4 addSelf( Matrix4x4 m );
			Vec3D applyTo( Vec3D v );
			Vec3D applyToSelf( Vec3D v );
			Matrix4x4 getInverted();
			Matrix4x4 getRotatedAroundAxis( Vec3D axis, double theta );
			Matrix4x4 getRotatedX( double theta );
			Matrix4x4 getRotatedY( double theta );
			Matrix4x4 getRotatedZ( double theta );
			Matrix4x4 getTransposed( );
			Matrix4x4 identity( );
			void init();
			Matrix4x4 invert();
			Matrix4x4 lookAt( Vec3D eye, Vec3D target, Vec3D up );
			Matrix4x4 multiply( double factor );
			Matrix4x4 multiply( Matrix4x4 mat );
			Matrix4x4 multiplySelf( double factor );
			Matrix4x4 multiplySelf( Matrix4x4 mat );
			Matrix4x4 rotateAroundAxis( Vec3D axis, double theta );
			Matrix4x4 rotateX( double theta );
			Matrix4x4 rotateY( double theta );
			Matrix4x4 rotateZ( double theta );
			Matrix4x4 scale( double scale );
			Matrix4x4 scale( double scaleX, double scaleY, double scaleZ );
			Matrix4x4 scale( Vec3D scale );
			Matrix4x4 scaleSelf( double scale );
			Matrix4x4 scaleSelf( double scaleX, double scaleY, double scaleZ );
			Matrix4x4 scaleSelf( Vec3D scale );
			Matrix4x4 set( double a, double b, double c, double d, double e,
				double f, double g, double h, double i, double j, double k,
				double l, double m, double n, double o, double p );
			Matrix4x4 set( Matrix4x4 mat );
			Matrix4x4 setFrustum( double left, double right, double top,
				double bottom, double near, double far );
			Matrix4x4 setOrtho( double left, double right, double top,
				double bottom, double near, double far );
			Matrix4x4 setPerspective( double fov, double aspect, double near,
				double far );
			Matrix4x4 setPosition( double x, double y, double z );
			Matrix4x4 setScale( double scaleX, double scaleY, double scaleZ );
			Matrix4x4 sub( Matrix4x4 mat );
			Matrix4x4 subSelf( Matrix4x4 mat );
			double* toArray();
			float* toFloatArra();
			std::string toString();
			float* toTransposedFloatArray();
			Matrix4x4 translate( double dx, double dy, double dz );
			Matrix4x4 translate( Vec3D v );
			Matrix4x4 translateSelf( double dx, double dy, double dz );
			Matrix4x4 transpose();

		private:
			static Matrix4x4 TEMP;

		protected:
			double* temp;
		};
	}
}

#endif