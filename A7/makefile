all: app clean
app: main.o SERIALIZE.o
	cc main.o SERIALIZE.o -o app

main.o: main.c
main.c:
	cc -c main.c -o main.o
	
SERIALIZE.o: SERIALIZE.c
SERIALIZE.c:
	cc -c SERIALIZE.c -o SERIALIZE.o
clean:
	rm *.o