#pragma once

#include "ReadonlyVec2D.h"
#include <math.h>
#include "../math/MathUtils.h"
#include "Vec3D.h"

namespace toxi
{
	namespace geom
	{
		class Vec2D :
			public ReadonlyVec2D
		{
		public:
			Vec2D( double _x, double _y );
			~Vec2D(void);

			 Vec2D add( float x, float y );
			 Vec2D add( toxi::geom::Vec2D v );
			 float angleBetween( Vec2D v );
			 float angleBetween( Vec2D v, bool forceNormalize );
			 Vec3D bisect( Vec2D p );
			 int compareTo( Vec2D v );
			 float cross( Vec2D v );
			 float distanceTo( Vec2D v );
			 float distanceToSquared( Vec2D v );
			 float dot( Vec2D v );
			 bool equals( Vec2D v );
			 bool equalsWithTolerance(Vec2D v, float tolerance);
			 Vec2D getCartesian();
			 float getComponent(int id);
			 Vec2D contrain(Rect r);
			 Vec2D getFloored();
			 Vec2D getFrac();
			 Vec2D getInverted();
			 Vec2D getLimited(float lim);
			 Vec2D getMapped(toxi::math::ScaleMap map);
			 Vec2D getNormalized();
			 Vec2D getNormalizedTo(float len);
			 Vec2D getPerpendicular();
			 Vec2D getPolar();
			 Vec2D getReciprocal();
			 Vec2D getReflected(Vec2D normal);
			 Vec2D getRotated(float theta);
			 Vec2D getRoundedTo(float prec);
			 Vec2D getSignum();
			 float heading();
			 Vec2D interpolateTo(Vec2D v, float f);
			 Vec2D interpolateTo(Vec2D v, float f, toxi::math::InterpolateStrategy s);
			 bool isInCircle(Vec2D sO, float sR);
			 bool isInRectangle(Rect r);
			 bool isInTriangle(Vec2D a, Vec2D b, Vec2D c);
			 bool isMajorAxis(float tolerance);
			 bool isZeroVector();
			 float magnitude();
			 float magSquared();
			 Vec2D max(Vec2D v);
			 Vec2D min(Vec2D v);
			 Vec2D scale(float s);
			 Vec2D scale(float a, float b);
			 Vec2D scale(Vec2D s);
			 Vec2D sub(float a, float b);
			 Vec2D sub(Vec2D v);
			 Vec2D tangentNormalOfEllipse(Vec2D eO, Vec2D eR);
			 Vec3D to3DXY();
			 Vec3D to3DXZ();
			 Vec3D to3DYZ();
			 void toArray(float *a);
			 float x( void );
			 float y( void );

			double x;
			double y;
		};
	}
}
