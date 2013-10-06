CXXFLAGS=-std=c++0x ${INCLUDEPATH} -O3 -W -Wall
CFLAGS=-std=c99 ${INCLUDEPATH}

INCLUDEPATH=-I${HOME}/NumericalAnalysis -L/opt/X11/lib -I/opt/X11/include
LIBRARY=${HOME}/NumericalAnalysis/ODE/RKMethod/libRKMethod.a ${HOME}/NumericalAnalysis/Graphics/GPDriver/libGPDriver.a -lglsc -lX11

TARGET=test diffusion diffusion_glsc diffusion_err driver

all:${TARGET}
clean:
	rm -f *.[ao] ${TARGET}

test:${LIBRARY}

diffusion:${LIBRARY}
diffusion_glsc:${LIBRARY}
diffusion_err:${LIBRARY}
driver:${LIBRARY}

${LIBRARY}:
	

