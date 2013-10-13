#include "file.hpp"
#include <cstdio>
#include <iostream>

void print_file_info(File const &f)
{
    printf("FILEINFO-- Filename: %s, OPENED? - %s (Mode = %d), ERROR=%d, EOF=%d\n",
           f.name().c_str(), f.opened() ? "True" : "False", f.mode(), f.error(),
           f.eof());
}

int main()
{
    File f0;
    File f1("1.txt");
    print_file_info(f1);
    print_file_info(f0);
    return 0;
}
