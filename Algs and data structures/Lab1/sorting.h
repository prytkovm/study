#ifndef SORTING_H
#define SORTING_H

#include <cstddef>
#include <cstdlib>
#include <ctime>

namespace  SortArray{ class Array;}

class Array
{
private:
    size_t size;
    int *copy(int *origin, size_t size)
    {
        if (!origin)
            return nullptr;
        int *destination = new int[size];
        for (size_t i = 0; i < size; i++)
            destination[i] = origin[i];
        return destination;
    }
public:
    Array(size_t array_size)
    {
        size = array_size;
    };
    ~Array();
    int *array, *copied;
    int *generate_array(size_t size)
    {
        array = new int[size];
        std::srand(std::time(nullptr));
        for (size_t i = 0; i < size; i++)
            array[i] = rand();
        return array;
    }
};

#endif // SORTING_H
