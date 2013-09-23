#include "GPDriver.h"

GPData CreateGPData()
{
	GPData gpd;
	gpd.gp = popen("gnuplot", "w");
	gpd.xmin = gpd.ymin = -2;
	gpd.xmax = gpd.ymax = 2;
	gpd.x = gpd.y = 0;
	gpd.width = 480;
	gpd.height = 480;
	gpd.flags = (withLine);
	return gpd;
}

void SetWindow(GPData *gpd, int x, int y, int width, int height)
{
	gpd->x = x;
	gpd->y = y;
	gpd->width = width;
	gpd->height = height;
}

void SetRange(GPData *gpd, double xmin, double xmax, double ymin, double ymax)
{
	gpd->xmin = xmin;
	gpd->xmax = xmax;
	gpd->ymin = ymin;
	gpd->ymax = ymax;
}

void InitializeGP(GPData *gpd)
{
	fprintf(gpd->gp, "set terminal x11 position %d,%d size %d,%d\n", gpd->x, gpd->y, gpd->width, gpd->height);
}

void Plot(GPData *gpd, double *data, unsigned int len)
{
	fprintf(gpd->gp, "set xrange[%f:%f]\n", gpd->xmin, gpd->xmax);
	fprintf(gpd->gp, "set yrange[%f:%f]\n", gpd->ymin, gpd->ymax);
	fprintf(gpd->gp, "plot '-' %s %s%s\n", (((withLine | withPoint) & gpd->flags)?("w"):("")), ((withLine & gpd->flags)?("l"):("")), ((withPoint & gpd->flags)?("p"):("")));
	for(unsigned int i = 0; i < len; ++i)
		fprintf(gpd->gp, "%f %f\n", data[2*i], data[2*i + 1]);
	fprintf(gpd->gp, "e\n");
	fflush(gpd->gp);
}

void Begin(GPData *gpd)
{
	
	fprintf(gpd->gp, "'-'");
}

void DeleteGPData(GPData *gpd)
{
	fclose(gpd->gp);
}

#ifdef __cplusplus

std::ostream &operator<<(std::ostream &dest, GPData &gpd)
{
	dest << "(x, y) = (" << gpd.x << ", " << gpd.y << ")\n";
	dest << "(width, height) = (" << gpd.width << ", " << gpd.height << ")\n";
	dest << "xrange[" << gpd.xmin << ", " << gpd.xmax << "]\n";
	dest << "yrange[" << gpd.ymin << ", " << gpd.ymax << "]\n";
}

#endif
