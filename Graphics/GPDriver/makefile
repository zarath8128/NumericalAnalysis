CFLAGS=-std=c99
CXXFLAGS=-std=c++0x
PRODUCT=libGPDriver.a


all:test ${PRODUCT}
clean:
	rm -r test ${PRODUCT} *.o

test:${PRODUCT}

libGPDriver.a:GPDriver.o
	ar r $@ $^
	ranlib $@
