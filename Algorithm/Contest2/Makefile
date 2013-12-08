TASK = task5
CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic
APPNAME = main
srcdir = .
builddir = .

all: $(builddir)/main.o
	$(CXX) $(builddir)/main.o -o $(builddir)/$(APPNAME)

$(builddir)/main.o: $(srcdir)/$(TASK).cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
    
clean:
	rm -f *.o $(APPNAME)
	
run:
	$(builddir)/$(APPNAME)

.PHONY: clean