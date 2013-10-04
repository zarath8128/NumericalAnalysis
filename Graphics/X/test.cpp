#include <iostream>
#include <ctime>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include "Graph2D.h"
#include "Canvas.h"

using namespace zarath::Graphics;

int main()
{
	std::cout << "Hello X!" << std::endl;
	Display *dsp = XOpenDisplay(0);
	Window root = DefaultRootWindow(dsp);
	int screen = DefaultScreen(dsp);
	unsigned long black = BlackPixel(dsp, screen);
	unsigned long white = WhitePixel(dsp, screen);
	XEvent e;

	zarath::X::Graph2D g(dsp, root, 100, 100, 480, 480, black, white);
	g.Show();
	g.Flush();

	Canvas c(dsp, root, 0, 0, 100, 100);

	XMapWindow(dsp, c);
	c.clear();
	c.plot(1, 1);
	c.flush();


	while(1)
	{
		XEvent e;
		XNextEvent(dsp, &e);
		if(e.type == Expose)
		{
//	XDrawLine(dsp, c, c.gc, 0, 0, 100, 100);
		std::cout << "check" << std::endl;
		}
	}

	XCloseDisplay(dsp);
	return 0;
}
