#ifndef ZARATH_PDE_GPDRIVER_H
#define ZARATH_PDE_GDDRIVER_H

#ifdef __cplusplus
#include <iostream>
#include <cstdio>
#else
#include <stdio.h>
#include <stdint.h>
#endif

#ifdef __cplusplus
namespace zarath
{
	namespace GPDriver
	{
		extern "C"
		{
#endif
			typedef struct tag_GPData
			{
				FILE *gp;
				double xmin, xmax, ymin, ymax;
				int x, y, width, height;
				int flags;
			}GPData;

			enum GPFlags
			{
				withLine = 0x01,
				withPoint = 0x02,
			};

			GPData CreateGPData();
			void SetWindow(GPData *gpd, int x, int y, int width, int height);
			void SetRange(GPData *gpd, double xmin, double xmax, double ymin, double ymax);
			void InitializeGP(GPData *gpd);
			void Plot(GPData *gpd, double *data, unsigned int len);
			vois SPlot(GPData *gpd, double *data, unsigned int xlen, unsigned int ylen);
			void DeleteGPData(GPData *gpd);

#ifdef __cplusplus
		}
		std::ostream &operator<<(std::ostream &dest, GPData &gpd);
#endif

#ifdef __cplusplus
	}
}
#endif

#endif
