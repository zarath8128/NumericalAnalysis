CXXFLAGS=-std=c++0x ${INCLUDEPATH}
CFLAGS=-std=c99 ${INCLUDEPATH}

INCLUDEPATH=-I${HOME}/NumericalAnalysis
LIBRARY=${HOME}/NumericalAnalysis/ODE/RKMethod/libRKMethod.a

all:test diffusion
clean:
	rm -f *.[ao] test diffusion

test:libGPDriver.a

diffusion:${LIBRARY} libGPDriver.a

${LIBRARY}:
	

libGPDriver.a:GPDriver.o
	ar r $@ $^
