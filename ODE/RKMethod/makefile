CFLAGS=-std=c99 -O3
CXXFLAGS=-std=c++0x -O3
OBJECTS=EulerMethod.o ERKMethod.o ButcherTable.o

all:test

clean:
	rm -f ${OBJECTS} test libRKMethod.a

test:libRKMethod.a

libRKMethod.a:${OBJECTS}
	ar r $@ $^
