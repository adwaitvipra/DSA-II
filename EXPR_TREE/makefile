all : link clean
link : main.o EXPRTREE.o 
	gcc -o EXPRTREE EXPRTREE.o main.o
main.o : main.c
	gcc -Wall -c main.c
EXPRTREE.o : EXPRTREE.c
	gcc -Wall -c EXPRTREE.c
clean:
	rm *.o
