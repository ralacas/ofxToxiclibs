#pragma once

#ifndef __RECT_H__
#define __RECT_H__

namespace toxi
{
	namespace geom
	{
		class Rect
		{
		public:
			Rect(void);
			~Rect(void);

			double x, y, width, height;
		};
	}
}

#endif