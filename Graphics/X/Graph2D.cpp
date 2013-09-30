#include "Graph2D.h"
#include <iostream>

using namespace zarath::X;

Graph2D::Graph2D(Display *disp, Window &parent, short x, short y, unsigned short width, unsigned short height, unsigned long black, unsigned long white)
:disp(disp), parent(parent), x(x), y(y), width(width), height(height)
{
	self = XCreateSimpleWindow(disp, parent, x, y, width, height, 0, black, white);
	buf = XCreateGC(disp, self, 0, 0);
}

Graph2D::~Graph2D()
{
	XDestroyWindow(disp, self);
	XFreeGC(disp, buf);
}

void Graph2D::Show()
{
	XMapWindow(disp, self);
	XSelectInput(disp, self, KeyPressMask);
	XMoveWindow(disp, self, x, y);
}

void Graph2D::Flush()
{
	XFlush(disp);
}

void Graph2D::Plot(double *data, unsigned int len)
{
	
}

void Graph2D::Update()
{
	XEvent e;
	if(XCheckWindowEvent(disp, self, KeyPressMask, &e))
		std::cerr << e.type << std::endl;
}

Graph2D::operator Window()
{
	return self;
}

void Graph2D::map(double x, double y, short &X, short &Y)
{
	X = ox + x*upx;
	Y = oy - y*upy;
}

void Graph2D::coordinate()
{
	
}
