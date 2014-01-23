#include <iostream>
#include <string>
#include "any.hpp"
#include "bind2.hpp"
#include "comma.hpp"
#include "sng.hpp"

using std::cout;
using std::endl;
using std::string;

extern void test_inh();

int sum(int a, int b)
{
    return a + b;
}

int main()
{
    cout << My::Instance().x;
    
    void p;
    
    return 0;
}

// class A {
//     friend class B;
//     int a;
// };
//
// class B {
//     friend class C;
// };
// class C {
//     void f(A *p)
//     {
//         p->a++; // error:CisnotafriendofA
//                 // despite being a friend of a friend
//     }
// };

// class D : public B {
//     void bbb(A *p)
//     {
//         b(p);
//     }
//
//     void f(A *p)
//     {
//         p->a++; // error:DisnotafriendofA
//                 // despite being derived from a friend
//     }
// };

// class A {
// public:
//     A() : data(146)
//     {
//         cout << "ctor" << endl;
//     }
//
//     A(A const &other) : data(other.data)
//     {
//         cout << "ccopy" << endl;
//     }
//
//     virtual ~A()
//     {
//         cout << "A" << endl;
//     }
//
// private:
//     int const data;
// };
//
// A foo()
// {
//     return A();
// }

// class B : public A {
// public:
//     virtual ~B()
//     {
//         cout << "B" << endl;
//     }
// };

// template <typename T, template <typename> class Cont> void print(Cont<T> &a);
//

// namespace ru{
//     int f(int i){return 2;}
//
//     namespace spb{
//         int f(int i){return 1;}
//     }
//
//     namespace msk{
//         using namespace spb;
//
//         //int f(double i){return 2;}
//
//         int global = f(5);
//     }
// }
