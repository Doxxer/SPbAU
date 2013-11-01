CXX = clang++
CXXFLAGS = -Wextra -Wall -pedantic # -Werror
APPNAME = main

all: main.o
	$(CXX) main.o -o $(APPNAME)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(APPNAME)
	
run:
	./$(APPNAME)

.PHONY: clean