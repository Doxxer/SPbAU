default: all

main.o: main.cpp sort.h
	g++ -c main.cpp -o main.o

sort.o: sort.cpp sort.h
	g++ -c sort.cpp -o sort.o

all: main.o sort.o
	g++ main.o sort.o -o sort
	
clean:
	rm -f *.o *.s sort
	
run: clean all
	./sort