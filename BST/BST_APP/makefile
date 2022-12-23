all : link clean
link : main.o BST.o 
	gcc -o BST BST.o main.o
main.o : main.c
	gcc -Wall -c main.c
BST.o : BST.c
	gcc -Wall -c BST.c
clean:
	rm *.o
