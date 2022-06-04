#include <iostream>

template<typename T>
T get_input_from_user()
{
    T awaited_input;
    std::cin >> awaited_input;
    return awaited_input;
}