#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

int main()
{
    std::string number;
    int left = 0;
    std::cin >> number >> left;
    std::vector<char> digit_stack;

    for (int i = 0; i < (int)number.length(); ++i) {
        while (!digit_stack.empty() && digit_stack.back() < number[i] && left != 0) {
            digit_stack.pop_back();
            --left;
        }
        digit_stack.push_back(number[i]);
    }

    for (size_t i = 0; i + left < digit_stack.size(); ++i)
        printf("%c", digit_stack[i]);
    printf("\n");
    return 0;
}
