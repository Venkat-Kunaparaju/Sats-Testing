CCo = gcc -o
CCc = gcc -c

all: main




buffering.o: ../src/buffering.c ../include/buffering.h
		$(CCc) ../src/buffering.c

packet.o: ../src/packet.c ../include/packet.h
		$(CCc) ../src/packet.c

main: buffering.o packet.o
		$(CCo) main ../src/main.c buffering.o packet.o
		-mv *.o /bin

clean:
	rm -f main
	rm -f buffering.o
	rm -f packet.o