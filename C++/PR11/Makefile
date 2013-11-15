CXX = clang++
CXXFLAGS = -Wall -Wextra -pedantic
APPNAME = main
srcdir = .
builddir = .

all: $(builddir)/main.o $(builddir)/unique_ptr.o
	$(CXX) $(builddir)/main.o $(builddir)/unique_ptr.o -o $(builddir)/$(APPNAME)

$(builddir)/main.o: $(srcdir)/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(builddir)/unique_ptr.o: $(srcdir)/unique_ptr.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(APPNAME)
	
run:
	$(builddir)/$(APPNAME)

.PHONY: clean