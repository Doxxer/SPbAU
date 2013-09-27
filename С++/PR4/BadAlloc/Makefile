APPNAME = main.out
CC = g++
CFLAGS = -c

all: main.o
	$(CC) main.o -o $(APPNAME)
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

clean:
	rm -f *.o *.out *.s $(APPNAME)
	
run:
	./$(APPNAME)