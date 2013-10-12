CFLAGS=-std=c99
ALL=test libCPU.a 

all:${ALL}
clean:
	rm -rf ${ALL} *.o

test:libCPU.a

libCPU.a:CPU.o
	ar r $@ $^
