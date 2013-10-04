#ifndef ZARATH_GRAPHICS_X_GRAPH_2D_H
#define ZARATH_GRAPHICS_X_GRAPH_2D_H

#include <X11/Xlib.h>

namespace zarath
{
	namespace X
	{
		class Graph2D
		{
		public:
			Graph2D(Display *disp, Window &parent, short x, short y, unsigned short width, unsigned short height, unsigned long black, unsigned long white);
			~Graph2D();
			void Show();
			void Flush();
			void Plot(double *data, unsigned int len);
			void Update();

			operator Window();
		private:
			Display *disp;
			Window parent, self;
			short x, y;
			unsigned short width, height;

			GC buf;

			short ox, oy;
			double upx, upy;//unit_per_x, unit_oer_y;

			void draw();
			void map(double x, double y, short &X, short &Y);
			void coordinate();
		};
	}	
}

#endif
