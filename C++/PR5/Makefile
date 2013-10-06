APPNAME = main.out
CC = clang++
CFLAGS = -c -Wextra -Wall -Werror -pedantic

all: main.o vector.o
	$(CC) main.o vector.o -o $(APPNAME)
	
main.o: main.cpp vector.hpp
	$(CC) $(CFLAGS) main.cpp -o main.o

vector.o: vector.cpp vector.hpp
	$(CC) $(CFLAGS) vector.cpp -o vector.o

clean:
	rm -f *.o *.out *.s $(APPNAME)
	
run:
	./$(APPNAME)

.PHONY: clean