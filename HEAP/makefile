all : link clean
link : HEAP.o main.o 
	gcc -o HEAP HEAP.o main.o
main.o: main.c
	gcc -Wall -c main.c
HEAP.o: HEAP.c
	gcc -Wall -c HEAP.c
clean :
	rm *.o
