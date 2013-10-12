CXXFLAGS=${INCLUDEPATH} -W -Wall -fp-model precise -xHOST
CFLAGS=-std=c99 ${INCLUDEPATH}

INCLUDEPATH=-I${HOME}/NumericalAnalysis -L/opt/X11/lib -I/opt/X11/include
LIBRARY=${HOME}/NumericalAnalysis/ODE/RKMethod/libRKMethod.a ${HOME}/NumericalAnalysis/Graphics/GPDriver/libGPDriver.a -lglsc -lX11 ${HOME}/NumericalAnalysis/Utility/Error/libError.a

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

