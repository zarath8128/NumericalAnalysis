CXXFLAGS=-std=c++0x ${INCLUDEPATH} -O3
CFLAGS=-std=c99 ${INCLUDEPATH}

INCLUDEPATH=-I${HOME}/NumericalAnalysis
LIBRARY=${HOME}/NumericalAnalysis/ODE/RKMethod/libRKMethod.a ${HOME}/NumericalAnalysis/Graphics/GPDriver/libGPDriver.a

all:test diffusion
clean:
	rm -f *.[ao] test diffusion

test:${LIBRARY}

diffusion:${LIBRARY}

${LIBRARY}:
	

