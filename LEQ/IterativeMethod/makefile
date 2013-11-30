FLAGS=-W -Wall -O2
CFLAGS=-lstdc++
CXXFLAGS=-std=c++0x
OBJECT=InnerProduct.o CGMethod.o
EXEC=test
ALL=${EXEC} ${OBJECT}
all:${ALL}
clean:
	rm -f ${ALL}
${EXEC}:${OBJECT}
CGMethod.o:InnerProduct.o
