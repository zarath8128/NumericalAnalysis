CFLAGS=-std=c99 -O3 -W -Wall ${ICCFLAGS}
CXXFLAGS=-std=c++0x -O3 -W -Wall ${ICCFLAGS}

ICCFLAGS=-fp-model precise -fp-model source

OBJECTS=EulerMethod.o ERKMethod.o ButcherTable.o GillMethod.o

all:test

clean:
	rm -f ${OBJECTS} test libRKMethod.a

test:libRKMethod.a

libRKMethod.a:${OBJECTS}
	ar r $@ $^
