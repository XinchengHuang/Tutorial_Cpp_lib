#include "bubble.hpp"

void swap(int& front, int& back)
{
    int i = front;
    front = back;
    back = i;
}