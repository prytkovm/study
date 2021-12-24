#include <cstdlib>
#include <ctime>
#include <cstring>

#define SEARCH_CYCLES 1000000

class BinarySearch
{
public:
    int *data, size;
    BinarySearch()
    {
        data = nullptr;
        search_time = 0;
    }
    ~BinarySearch()
    {
        if (data)
            delete data;
    }
    void generate_set(int size, int min, int max)
    {
        this->size = size;
        data = new int[size];
        std::srand(std::time(nullptr));
        for (int i = 0; i < size; i++)
            data[i] = min + rand() % (max - min + 1);
        sort(data);
    }
    int find(int key)
    {
        int right = size - 1, left = 0;
        int central = (right + left) / 2;
        bool found = false;
        cached_key = key;
        while (!found && right >= left)
        {

            if (data[central] == key)
            {
                found = true;
                break;
            }
            else if (data[central] > key)
                right = central - 1;
            else
                left = central + 1;
            central = (right + left) / 2;
        }
      return found ? central : -1;
    }
    double get_search_time()
    {
        return searchTime();
    }
private:
    int cached_key;
    double search_time;
    void sort(int *array)
    {
        int tmp;
        for (int i = 1; i < size; i++)
        {
            for (int j = i ; j > 0 && array[j - 1] > array[j]; j--)
            {
                tmp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = tmp;
            }
        }
    }
    double searchTime()
    {
        int *copied;
        search_time = 0;
        clock_t start_time, end_time;
        for (int iterator = 0; iterator < SEARCH_CYCLES; iterator++)
        {
            copied = copy();
            start_time = clock();
            find(cached_key);
            end_time = clock();
            search_time += (double)(end_time - start_time);
            delete[] copied;
        }
        return search_time /= (double)(CLOCKS_PER_SEC);
    }
    int *copy()
    {
        int *destination = new int [size];
        std::memcpy(destination, data, size * sizeof (int));
        return destination;
    }
};
