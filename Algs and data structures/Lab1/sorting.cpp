#include <cstring>
#include <cstdlib>
#include <ctime>

#define SORT_CYCLES 1000000

class Array
{
public:
    int size;
    int *array;
    Array(int array_size)
    {
        size = array_size;
        array = nullptr;
    };
    ~Array()
    {
        if (array)
            delete[] array;
    };
    void generate_array(int min_val, int max_val)
    {
        array = new int [size];
        std::srand(std::time(nullptr));
        for (int i = 0; i < size; i++)
            array[i] = rand() % (max_val - min_val + 1) + min_val;
    }
    void sort(int *sort_array)
    {
        int tmp;
        for (int i = 1; i < size; i++)
        {
            for (int j = i ; j > 0 && sort_array[j - 1] > sort_array[j]; j--)
            {
                tmp = sort_array[j - 1];
                sort_array[j - 1] = sort_array[j];
                sort_array[j] = tmp;
            }
        }
    }
    double get_sortTime()
    {
        sort_time = 0;
        return sortTime();
    }
private:
    double sort_time;
    double sortTime()
    {
        int *copied;
        clock_t start_time, end_time;
        for (int iterator = 0; iterator < SORT_CYCLES; iterator++)
        {
            copied = copy();
            start_time = clock();
            sort(copied);
            end_time = clock();
            sort_time += (double)(end_time - start_time);
            delete[] copied;
        }
        return sort_time /= (double)(CLOCKS_PER_SEC);
    }
    int *copy()
    {
        int *destination = new int [size];
        std::memcpy(destination, array, size * sizeof (int));
        return destination;
    }
};
