APPNAME = main.out
CC = clang++
CFLAGS = -c -Wextra -Wall -Werror -pedantic

all: main.o my_string.o
	$(CC) main.o my_string.o -o $(APPNAME)
	
main.o: main.cpp my_string.hpp
	$(CC) $(CFLAGS) main.cpp -o main.o

my_string.o: my_string.cpp my_string.hpp
	$(CC) $(CFLAGS) my_string.cpp -o my_string.o

clean:
	rm -f *.o *.out *.s $(APPNAME)
	
run:
	./$(APPNAME)

.PHONY: clean