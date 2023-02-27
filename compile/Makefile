CCo = gcc -o
CCc = gcc -c

all: main
	git add --all
	git commit -m "Commit"
	git push


buffering.o: ../src/buffering.c ../include/buffering.h
		$(CCc) ../src/buffering.c

packet.o: ../src/packet.c ../include/packet.h
		$(CCc) ../src/packet.c

main: buffering.o packet.o
		$(CCo) main ../src/main.c buffering.o packet.o

clean:
	rm -f main
	rm -f buffering.o
	rm -f packet.o