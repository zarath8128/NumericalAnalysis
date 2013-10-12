CFLAGS=-std=c99 -O0 -W -Wall
ALL=test DetectLoss.o libError.a


all:${ALL}
clean:
	rm -rf ${ALL}

test:DetectLoss.o
libError.a:DetectLoss.o
	ar r $@ $^
