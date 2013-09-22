APPNAME = main.out
CC = clang++
CFLAGS = -c -Wextra

all: main.o mergesort.o
	$(CC) main.o mergesort.o -o $(APPNAME)
	
main.o: main.cpp mergesort.h
	$(CC) $(CFLAGS) main.cpp -o main.o

mergesort.o: mergesort.cpp mergesort.h
	$(CC) $(CFLAGS) mergesort.cpp -o mergesort.o

clean:
	rm -f *.o *.out *.s $(APPNAME)
	
run:
	./$(APPNAME)