#pragma onces

namespace toxi
{
	namespace geom
	{
		class Ray3D;
		class IsectData3D;
		class Intersector3D
		{
		public:
			Intersector3D(void);
			~Intersector3D(void);

			virtual IsectData3D getIntersectionData() = 0;
			virtual bool intersectsRay( Ray3D ray ) = 0;
		};
	}
}


