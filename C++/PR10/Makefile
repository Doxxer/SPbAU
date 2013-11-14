CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -pedantic
APPNAME = main
srcdir = .
builddir = .

all: $(builddir)/main.o $(builddir)/rational.o
	$(CXX) $(builddir)/main.o $(builddir)/rational.o -o $(builddir)/$(APPNAME)

$(builddir)/main.o: $(srcdir)/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(builddir)/rational.o: $(srcdir)/rational.cpp $(srcdir)/rational.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(APPNAME)
	
run:
	time $(builddir)/$(APPNAME)

.PHONY: clean