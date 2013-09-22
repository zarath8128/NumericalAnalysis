
CC=gcc
CXX=g++

CFALGS = -O0
CXXFLAGS = -O0 -lMath -L./
OBJECTS=Math.o

all:test

test:libMath.a Math.h

libMath.a:${OBJECTS}
	ar -r $@ $^
