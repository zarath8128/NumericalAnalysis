
ALL=test libCPU.a 

all:${ALL}
clean:
	rm -rf ${ALL} *.o

test:libCPU.a

libCPU.a:CPU.o
	ar r $@ $^
