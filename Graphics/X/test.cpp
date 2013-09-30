#include <iostream>
#include <ctime>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include "Graph2D.h"

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

	while(1)
	{
	}

	XCloseDisplay(dsp);
	return 0;
}
