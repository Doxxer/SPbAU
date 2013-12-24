CXX = clang++
CXXFLAGS = -std=c++03 -stdlib=libc++ -Wall -Wextra -pedantic
APPNAME = PP
srcdir = src
builddir = ./bin
in = 3.txt

all: createdir $(builddir)/main.o $(builddir)/lexer.o $(builddir)/parser.o $(builddir)/evaluator.o $(builddir)/token.o
	$(CXX) $(builddir)/main.o $(builddir)/lexer.o $(builddir)/parser.o $(builddir)/evaluator.o $(builddir)/token.o -o $(builddir)/$(APPNAME)

createdir:
	mkdir -p $(builddir)

$(builddir)/main.o: $(srcdir)/main.cpp $(srcdir)/lexer.hpp $(srcdir)/token.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(builddir)/lexer.o: $(srcdir)/lexer.cpp $(srcdir)/lexer.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
    
$(builddir)/parser.o: $(srcdir)/parser.cpp $(srcdir)/lexer.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(builddir)/evaluator.o: $(srcdir)/evaluator.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
    
$(builddir)/token.o: $(srcdir)/token.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
    
clean:
	rm -rf $(builddir)
	
run:
	$(builddir)/$(APPNAME) $(in)

.PHONY: clean