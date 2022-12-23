all: link clean
link: main.o SERIALIZE.o
	gcc main.o SERIALIZE.o -o SERIALIZE
main.o: main.c
	gcc -Wall -c main.c 
	
SERIALIZE.o: SERIALIZE.c
	gcc -Wall -c SERIALIZE.c
clean:
	rm *.o
