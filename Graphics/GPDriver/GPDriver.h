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
				FILE *tp3d;
				char tpf[32];
				double min[3], max[3];
				int x, y, width, height;
				int flags;
			}GPData;

			enum GPFlags
			{
				ploted = 0x01,
				withLine = 0x02,
				withPoint = 0x04,
			};

			GPData CreateGPData();
			void SetWindow(GPData *gpd, int x, int y, int width, int height);
			void SetRange(GPData *gpd, double min, double max, unsigned int dim);
			void SetFlags(GPData *gpd, int flags);
			void ClearFlags(GPData *gpd, int flags);
			void InitializeGP(GPData *gpd);
			void Plot(GPData *gpd, double *data, unsigned int len);
			void rePlot(GPData *gpd, double *data, unsigned int len);
			void SPlot(GPData *gpd, double *data, unsigned int xlen, unsigned int ylen);
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
