#include <time.h>
#include <unistd.h>
#include <math.h>
#include "GPDriver.h"

int main()
{
	double min = -1, max = 1;
	int dim = 10;
	double xy[3*dim*dim], x, y;
	for(int i = 0; i < dim; ++i)
	for(int j = 0; j < dim; ++j)
		xy[3*(j*dim + i)] = x = i*(max - min)/(dim - 1) + min, xy[3*(j*dim + i) + 1] = y = j*(max - min)/(dim - 1) + min, xy[3*(j*dim + i) + 2] = 4*sin(1/(1 + sqrt(x * x + y * y))) - 2.5 ;
	GPData gpd = CreateGPData();
	for(int i = 0; i < 3; ++i)
		SetRange(&gpd, min, max, i);
	SetWindow(&gpd, 0, 0, 800, 600);
	ClearFlags(&gpd, withPoint | withLine);
	SetFlags(&gpd, withLine);
	InitializeGP(&gpd);
	while(1)
	{
		SPlot(&gpd, xy, dim, dim);
		sleep(1);
	}
	DeleteGPData(&gpd);
	return 0;
}
