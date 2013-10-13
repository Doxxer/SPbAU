APPNAME = main.out
CC = clang++
CFLAGS = -c -Weffc++ -Wextra -Wall -Werror -pedantic

all: main.o
	$(CC) main.o -o $(APPNAME)
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

clean:
	rm -f *.o *.out *.s $(APPNAME)
	
run:
	./$(APPNAME)

.PHONY: clean