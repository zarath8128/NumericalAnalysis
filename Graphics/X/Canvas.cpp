#include "Canvas.h"
#include <iostream>

namespace zarath
{
	namespace Graphics
	{
		Canvas::Canvas(Display *display, Window parent, int x, int y, unsigned int width, unsigned height)
			:display(display), parent(parent), x(x), y(y), width(width), height(height), wnd(0),
			left(-1), top(1), right(1), bottom(-1)
		{
			XColor white, black;
			white.red = white.green = white.blue = 65535;
			black.red = black.green = black.blue = 0;

			XAllocColor(display, DefaultColormap(display, 0), &white);
			XAllocColor(display, DefaultColormap(display, 0), &black);

			XSetWindowAttributes attributes;
			unsigned long valuemask = CWWinGravity | CWBackPixel;
			attributes.win_gravity = CenterGravity;
			attributes.background_pixel = white.pixel;
			wnd = XCreateWindow(display, parent, x, y, width, height, 0, 
						CopyFromParent, InputOutput, CopyFromParent, valuemask, &attributes);

			valuemask = GCForeground;
			XGCValues values;

			values.foreground = white.pixel;
			
			gc = XCreateGC(display, wnd, valuemask, &values);

			XWindowAttributes wnd_attr;

			XGetWindowAttributes(display, wnd, &wnd_attr);

			buf = XCreatePixmap(display, wnd, width, height, wnd_attr.depth);
			cls = XCreatePixmap(display, wnd, width, height, wnd_attr.depth);

			XFillRectangle(display, buf, gc, 0, 0, width, height);

			XSync(display, False);

			XSetForeground(display, gc, black.pixel);

			XSelectInput(display, wnd, ExposureMask);

			XSync(display, False);
			current = conv(0, 0);
		}

		Canvas::~Canvas()
		{
			XFreePixmap(display, buf);
			XFreePixmap(display, cls);
			XFreeGC(display, gc);
			XDestroyWindow(display, wnd);
		}

		Canvas::operator Window(){return wnd;}

		void Canvas::clear()
		{
			XCopyArea(display, cls, buf, gc, 0, 0, width, height, 0, 0);
			XFlush(display);
		}

		void Canvas::move(double x, double y){current = conv(x, y);}

		void Canvas::plot(double x, double y)
		{
			std::cout << current.x << std::endl;
			XPoint c = current;
			current = conv(x, y);
			std::cout << current.x << std::endl;
			XDrawLine(display, buf, gc, c.x, c.y, current.x, current.y);
		}

		void Canvas::flush()
		{
			XEvent e;
			XMapRaised(display, wnd);
			XWindowEvent(display, wnd, ExposureMask, &e);
			plot(-1, -1);
			XCopyArea(display, buf, wnd, gc, 0, 0, width, height, 0, 0);
			XFlush(display);
		}

		XPoint Canvas::conv(double x, double y)
		{
			XPoint ret;
			ret.x = (int16_t)((x - left)/(right - left)*width);
			ret.y = (int16_t)((y - bottom)/(bottom - top)*height);
			return ret;
		}
	}
}
