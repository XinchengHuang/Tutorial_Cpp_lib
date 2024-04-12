#include "bubble.hpp"


void bubbleSort(int a[], int& size)
{   
    int count = size;
    for (bool sorted = false; !sorted; count--)
    {
        sorted = true;
        for (int i = 1; i < size; i++)
        {
            if (a[i-1] > a[i])
            {
                swap(a[i-1], a[i]);
                sorted = false;
            }
        }
    }
}

