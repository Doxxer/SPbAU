#include <iostream>

#include "stack.hpp"

using std::cout;
using std::endl;

int main()
{
    Stack<int, 2> st; // or explicitly Stack<int, 2, Array>

    // st.pop(); // error
    st.push(1);
    st.push(123);
    cout << st.top() << endl;
    st.pop();
    cout << st.top() << endl;
    st.push(30);
    cout << st.top() << endl;
    // st.push(1000); // error
    return 0;
}
