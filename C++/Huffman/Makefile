CXX = clang++
CXXFLAGS = -std=c++0x -Wall -Wextra -Werror -pedantic
APPNAME = arj
srcdir = src
builddir = ./bin
in = 1.dat
out = 2.dat
ar = ar.txt

all: createdir $(builddir)/main.o $(builddir)/EncodeUtilities.o $(builddir)/huffmanDecode.o $(builddir)/huffmanEncode.o $(builddir)/BitFile.o
	$(CXX) $(builddir)/main.o $(builddir)/EncodeUtilities.o $(builddir)/huffmanDecode.o $(builddir)/huffmanEncode.o $(builddir)/BitFile.o -o $(builddir)/$(APPNAME)

createdir:
	mkdir -p $(builddir)

$(builddir)/main.o: $(srcdir)/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(builddir)/EncodeUtilities.o: $(srcdir)/EncodeUtilities.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(builddir)/BitFile.o: $(srcdir)/BitFile.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(builddir)/huffmanDecode.o: $(srcdir)/huffmanDecode.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(builddir)/huffmanEncode.o: $(srcdir)/huffmanEncode.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(builddir)
	
run:
	time $(builddir)/$(APPNAME) -c -i $(in) -o $(ar) && $(builddir)/$(APPNAME) -d -i $(ar) -o $(out) && diff $(in) $(out)

.PHONY: clean