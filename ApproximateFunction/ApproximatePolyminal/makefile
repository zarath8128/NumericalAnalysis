FLAGS=-W -Wall -lm
CFLAGS=${FLAGS} -std=c99 -lstdc++
CXXFLAGS=${FLAGS} -std=c++0x
HEADER=ApproximatePolyminal.h
OBJECT=Lagrange.o Newton.o
LIBRARY=
EXEC=test
ALL=${OBJECT} ${LIBRARY} ${EXEC}
all:${ALL}
clean:
	rm -f ${ALL}
${OBJECT}:${HEADER}
${LIBRARY}:${OBJECT} ${HEADER}
${EXEC}:${LIBRARY} ${OBJECT} ${HEADER}
