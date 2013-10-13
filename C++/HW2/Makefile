APPNAME = main.out
CC = clang++
CFLAGS = -c -Weffc++ -Wextra -Wall -Werror -pedantic

all: main.o file.o
	$(CC) main.o file.o -o $(APPNAME)
	
main.o: main.cpp file.hpp
	$(CC) $(CFLAGS) main.cpp -o main.o

file.o: file.cpp file.hpp
	$(CC) $(CFLAGS) file.cpp -o file.o

clean:
	rm -f *.o *.out *.s $(APPNAME)
	
run:
	./$(APPNAME)

.PHONY: clean