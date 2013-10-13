#include "file.hpp"
#include <cstdio>
#include <iostream>

#define my_file "1.txt"

void print_file_info(File const &f)
{
    printf("-- Filename: %s, OPENED? - %s (Mode = %d), ERROR=%d, EOF=%d\n\n",
           f.name().c_str(), f.opened() ? "True" : "False", f.mode(), f.error(),
           f.eof());
}

void readlines(size_t count)
{
    std::cout << "====== Read " << count << " lines." << std::endl;
    File f(my_file, File::Read);

    std::string s = "";
    for (size_t i = 0; i < count; ++i) {
        std::cout << "Read: " << f.readline(s) << " elements"
                  << ". Value = <" << s << ">" << std::endl;
        print_file_info(f);
    }
    f.close();
}

void readint(size_t count)
{
    std::cout << "====== Read " << count << " int-values." << std::endl;
    File f(my_file, File::Read);

    int l = 0;
    for (size_t i = 0; i < count; ++i) {
        std::cout << "Read: " << f.read(l) << " elements"
                  << ". Value = <" << l << ">" << std::endl;
        print_file_info(f);
    }
    f.close();
}

void readstring(size_t count)
{
    std::cout << "====== Read " << count << " strings." << std::endl;

    File f(my_file, File::Read);

    std::string s = "";
    for (size_t i = 0; i < count; ++i) {
        std::cout << "Read: " << f.read(s) << " elements"
                  << ". Value = <" << s << ">" << std::endl;
        print_file_info(f);
    }
    f.close();
}

void write()
{
    File f("2.txt", File::Rewrite);
    long k = 1234567890;
    int i = -20;
    double d = 3.141592;
    char a = 65;
    std::string s = "this is the string";

    f.write(k);
    f.write(' ');
    f.write(i);
    f.newline();

    f.write(d);
    f.write(' ');
    f.write(a);
    f.newline();

    f.write(s);
    f.newline();

    print_file_info(f);
    f.close();
}

int main()
{
    write();

    readlines(5);
    readint(3);
    readstring(8);
    return 0;
}
