FLAGS=-W -Wall -O3
CFLAGS=${FLAGS} -lstdc++ -std=c99
CXXFLAGS=${FLAGS} -std=c++0x -lpthread
OBJECT=InnerProduct.o CGMethod.o
EXEC=test
ALL=${EXEC} ${OBJECT}
all:${ALL}
clean:
	rm -f ${ALL}
${EXEC}:${OBJECT}
CGMethod.o:InnerProduct.o
