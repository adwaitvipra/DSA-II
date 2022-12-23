all : link clean

link : main.o AVL.o
	gcc -o AVL AVL.o main.o

AVL.o : AVL.c 
	gcc -Wall -c AVL.c

main.o : main.c
	gcc -Wall -c main.c

clean :
	rm *.o
