APPNAME = main1.out
TASK = task5
CC = g++
CFLAGS = -c -Wextra -Wall -pedantic
# CFLAGS = -c -O3

all: main.o
	$(CC) $(TASK).o -o $(APPNAME)
	
main.o: $(TASK).cpp
	$(CC) $(CFLAGS) $(TASK).cpp -o $(TASK).o

clean:
	rm -f *.o *.out *.s $(APPNAME)
	
run:
	./$(APPNAME)

.PHONY: clean