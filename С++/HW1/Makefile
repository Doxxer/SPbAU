APPNAME = main.out
CC = clang++
CFLAGS = -std=c++0x -c -Wextra

all: clean main.o
	$(CC) main.o -o $(APPNAME)
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

clean:
	rm -f *.o *.out *.s $(APPNAME)
	
run:
	./$(APPNAME)