app: link clean

link : main.o graph.o
	gcc -o graph graph.o main.o

main.o : main.c
	gcc -Wall -c main.c

graph.o : graph.c
	gcc -Wall -c graph.c

clean :
	rm *.o
