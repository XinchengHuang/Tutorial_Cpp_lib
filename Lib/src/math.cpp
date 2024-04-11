#include <iostream>
#include "../include/demo.hpp"

int Add(int& x, int& y)
{
    return (x + y < 128 ? x + y : 127);
}

int Multiply(int& x, int& y)
{
    return (x * y < 128 ? x * y : 127);
}

int Subtract(int& x, int& y)
{
    return (x - y < 0 ? 0 : x - y);
}

int Divise(int& x, int& y)
{
    return (y == 0 ? y : x / y);
}