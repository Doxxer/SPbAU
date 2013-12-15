CXX = clang++
CXXFLAGS = -std=c++03 -Wall -Wextra -pedantic
APPNAME = interpp
srcdir = src
builddir = ./bin
in = 1.txt

all: createdir $(builddir)/main.o $(builddir)/lexer.o $(builddir)/token.o $(builddir)/parser.o
	$(CXX) $(builddir)/main.o $(builddir)/lexer.o $(builddir)/token.o $(builddir)/parser.o -o $(builddir)/$(APPNAME)

createdir:
	mkdir -p $(builddir)

$(builddir)/main.o: $(srcdir)/main.cpp $(srcdir)/lexer.hpp $(srcdir)/token.hpp $(srcdir)/parser.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(builddir)/token.o: $(srcdir)/token.cpp $(srcdir)/token.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(builddir)/lexer.o: $(srcdir)/lexer.cpp $(srcdir)/lexer.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
    
$(builddir)/parser.o: $(srcdir)/parser.cpp $(srcdir)/parser.hpp $(srcdir)/ast.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
    
clean:
	rm -rf $(builddir)
	
run:
	$(builddir)/$(APPNAME) $(in)

.PHONY: clean