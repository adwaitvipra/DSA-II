all : link clean
link : main.o BSTARR.o 
	gcc -o BSTARR BSTARR.o main.o
main.o : main.c
	gcc -Wall -c main.c
BSTARR.o : BSTARR.c
	gcc -Wall -c BSTARR.c
clean:
	rm *.o
