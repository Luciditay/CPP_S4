#include <iostream>

template<typename T>
T get_input_from_user()
{
    T input_awaited;
    std::cin >> input_awaited;
    return input_awaited;
}