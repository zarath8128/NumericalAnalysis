#include <time.h>
#include <unistd.h>
#include <math.h>
#include "GPDriver.h"

int main()
{
	double min = -1, max = 1;
	int dim = 10;
	double xy[2*dim], x, y;
	for(int i = 0; i < dim; ++i)
		xy[2*i] = x = i*(max - min)/(dim - 1) + min, xy[2*i + 1] = sin(x) ;
	GPData gpd = CreateGPData();
	for(int i = 0; i < 3; ++i)
		SetRange(&gpd, min, max, i);
	SetWindow(&gpd, 0, 0, 800, 600);
	//InitializeGP(&gpd);
	while(1)
	{
		Plot(&gpd, xy, dim);
		sleep(1);
	}
	DeleteGPData(&gpd);
	return 0;
}
