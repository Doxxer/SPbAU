#include <iostream>

using namespace std;

class noncopyable {
public:
    noncopyable()
    {
    }

private:
    noncopyable(noncopyable const &noncopyable);
    noncopyable operator=(noncopyable &noncopyable);
};

class Foo : public noncopyable {
public:
    Foo()
    {
        cout << "Foo ctor" << endl;
    }
};

int main()
{
    Foo a;

    // Foo b = a; // error!!
    // Foo b(a);  // error!!

    return 0;
}
