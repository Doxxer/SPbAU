#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

struct Abstract {
    virtual void pure() = 0;
    virtual void foo() {
        pure();
    }
    Abstract() {
        foo();
    }
    ~Abstract() {
        foo();
    }
};


struct Person {
    Person(string const &n = "") : name(n)
    {
        
    }

    virtual ~Person() {};

    virtual void f() = 0;

protected:
    string name;
};

void Person::f()
{
    cout << "qqqqqqq";
}

struct Student : Person {
    Student(int a) : Person(""), age(a)
    {
        f();
    }

    int age;

    void f()
    {
        
    }

    virtual ~Student()
    {
        cout << "dd student" << endl;
    }
};

struct Teacher : Person {
    //    Teacher() : Person("")

    int zp;
};

// void f(Person *p)
// {
//     Student *s = (Student *)p;
//     cout << s->age << endl;
// }

void test_inh()
{
    // Person p("------");
    Student s(17);
    //    Teacher t;

    // f(&s);
}
