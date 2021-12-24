#include <cstdlib>
#include <ctime>


class Summator
{
public:
    int *array;
    Summator()
    {
        array = nullptr;
    }
    ~Summator()
    {
        if (array)
            delete[] array;
    }
    long long iterative_sum(size_t id)
    {
        long long sum = 0;
        for (size_t i = 0; i <= id; i++)
            sum += i;
        return sum;
    }
    void recursive_sum(long long &x, size_t size)
    {
        if (size == 0)
            return;
        x+=size;
        recursive_sum(x, size - 1);
    }
};
