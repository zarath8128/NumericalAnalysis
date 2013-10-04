#include "GPDriver.h"

using namespace zarath::GPDriver;

extern "C"
{
	GPData CreateGPData()
	{
		GPData gpd;
		gpd.gp = popen("gnuplot", "w");
		gpd.tp3d = 0;
		sprintf(gpd.tpf, "tp3d%p.tmp\0", &gpd);
		for(int i = 0; i < 3; ++i)
			gpd.min[i] = -(gpd.max[i] = 2);
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

	void SetRange(GPData *gpd, double min, double max, unsigned int dim)
	{
		gpd->min[dim] = min;
		gpd->max[dim] = max;
	}

	void SetFlags(GPData *gpd, int flags)
	{
		gpd->flags |= flags;
	}

	void ClearFlags(GPData *gpd, int flags)
	{
		gpd->flags &= ~flags;
	}

	void InitializeGP(GPData *gpd)
	{
		fprintf(gpd->gp, "set terminal x11 position %d,%d size %d,%d\n", gpd->x, gpd->y, gpd->width, gpd->height);
	}

	void Plot(GPData *gpd, double *data, unsigned int len)
	{
		fprintf(gpd->gp, "set xrange[%f:%f]\n", gpd->min[0], gpd->max[0]);
		fprintf(gpd->gp, "set yrange[%f:%f]\n", gpd->min[1], gpd->max[1]);
		fprintf(gpd->gp, "%s '-' %s %s%s\n", "plot", (((withLine | withPoint) & gpd->flags)?("w"):("")), ((withLine & gpd->flags)?("l"):("")), ((withPoint & gpd->flags)?("p"):("")));
		for(unsigned int i = 0; i < len; ++i)
				fprintf(gpd->gp, "%f %f\n", data[2*i], data[2*i + 1]);
		fprintf(gpd->gp, "e\n");
		fflush(gpd->gp);
	}

	void rePlot(GPData *gpd, double *data, unsigned int len)
	{
		fprintf(gpd->gp, "set xrange[%f:%f]\n", gpd->min[0], gpd->max[0]);
		fprintf(gpd->gp, "set yrange[%f:%f]\n", gpd->min[1], gpd->max[1]);
		fprintf(gpd->gp, "%s\n", "replot");
		for(unsigned int i = 0; i < len; ++i)
				fprintf(gpd->gp, "%f %f\n", data[2*i], data[2*i + 1]);
		fprintf(gpd->gp, "e\n");
		gpd->flags |= ploted;
		fflush(gpd->gp);
	}

	void SPlot(GPData *gpd, double *data, unsigned int xlen, unsigned int ylen)
	{
		if(!gpd->tp3d)
			if(!(gpd->tp3d = fopen(gpd->tpf, "w")))
				return;

		fprintf(gpd->gp, "set xrange[%f:%f]\n", gpd->min[0], gpd->max[0]);
		fprintf(gpd->gp, "set yrange[%f:%f]\n", gpd->min[1], gpd->max[1]);
		fprintf(gpd->gp, "set zrange[%f:%f]\n", gpd->min[2], gpd->max[2]);
		for(unsigned int i = 0; i < xlen; ++i)
		{
			for(unsigned int j = 0; j < ylen; ++j)
				fprintf(gpd->tp3d, "%f %f %f\n", data[3*(j*xlen + i)], data[3*(j*xlen + i) + 1], data[3*(j*xlen + i) + 2]);
			fprintf(gpd->tp3d, "\n");
		}
		fflush(gpd->tp3d);
		fprintf(gpd->gp, "%s '%s' %s %s%s\n", "splot", gpd->tpf, (((withLine | withPoint) & gpd->flags)?("w"):("")), ((withLine & gpd->flags)?("l"):("")), ((withPoint & gpd->flags)?("p"):("")));

		gpd->flags |= ploted;

		fflush(gpd->gp);
	}

	void DeleteGPData(GPData *gpd)
	{
		pclose(gpd->gp);
		if(gpd->tp3d)
			remove(gpd->tpf), fclose(gpd->tp3d);
	}
}

std::ostream &operator<<(std::ostream &dest, GPData &gpd)
{
	dest << "(x, y) = (" << gpd.x << ", " << gpd.y << ")\n";
	dest << "(width, height) = (" << gpd.width << ", " << gpd.height << ")\n";
	dest << "xrange[" << gpd.min[0] << ", " << gpd.max[0] << "]\n";
	dest << "yrange[" << gpd.min[1] << ", " << gpd.max[1] << "]\n";
	return dest;
}

