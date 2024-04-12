#include <iostream>
#include "bubble.hpp"

int main()
{
    int array[] = {5, 2, 7, 6, 4, 3, 1};
    int length = sizeof(array) / sizeof(int);
    bubbleSort(array, length);
    for (int i = 0; i < length; i++)
    {
        i == (length - 1) ? std::cout << array[i] << std::endl : std::cout << array[i] << ", ";
    }

    return 0;
}