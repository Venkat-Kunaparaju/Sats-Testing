CCo = gcc -o
CCc = gcc -c

all: main


buffering.o: ../src/buffering.c ../include/buffering.h
		$(CCc) ../src/buffering.c

packet.o: ../src/packet.c ../include/packet.h
		$(CCc) ../src/packet.c

dummyDriver.o: ../src/dummyDriver.c ../include/dummyDriver.h
		$(CCc) ../src/dummyDriver.c

main: buffering.o packet.o dummyDriver.o
		$(CCo) main ../src/main.c buffering.o packet.o dummyDriver.o

clean:
	rm -f main
	rm -f buffering.o
	rm -f packet.o
	rm -f dummyDriver.o