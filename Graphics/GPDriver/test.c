#include "GPDriver.h"
#include <unistd.h>

int main()
{
	double min = -1, max = 1;
	int dim = 400;
	double xy[2*dim];
	for(int i = 0; i < dim; ++i)
		xy[2*i] = i*(max - min)/(dim - 1) + min, xy[2*i + 1] = xy[2*i]*xy[2*i];
	GPData gpd = CreateGPData();
	SetRange(&gpd, min, max, -0.2, 3);
	InitializeGP(&gpd);
	Plot(&gpd, xy, dim);
	sleep(10);
	DeleteGPData(&gpd);
	return 0;
}
