APPNAME = main.out
CC = clang++
CFLAGS = -Werror -c

all: main.o
	$(CC) main.o -o $(APPNAME)
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

clean:
	rm -f *.o *.out *.s $(APPNAME)
	
run:
	./$(APPNAME) 0