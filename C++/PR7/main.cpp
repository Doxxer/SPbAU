#include "my_string.hpp"
#include <cstdio>

void print(my_string const &s)
{
    printf("|%s| = %ld\n", s.c_str(), s.length());
}

int main()
{
    my_string s0;
    print(s0);

    my_string s("123");
    print(s);

    my_string s1("asd");
    print(s1);

    my_string s2 = "hell";
    s2.at(0) = 'H';
    print(s2.append("o").append("!!!"));

    s1.append(s);
    s1.at(4) = '!';
    print(s1);

    print(s2.append(s1));

    return 0;
}
