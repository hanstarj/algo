#include <algorithm>

template <typename T, typename COMP, typename PIVOT>
int partition(T *array, int p, int r, COMP comp, PIVOT pivot)
{
    int q = pivot(p, r);
    if (q < r)
        std::swap(array[q], array[r]);

    for (q = p; p < r; ++p)
    {
        if (comp(array[p], array[r]))
        {
            if (p > q)
                std::swap(array[q], array[p]);
            ++q;
        }
    }
    return q;
}

template <typename T, typename COMP, typename PIVOT>
void quick_sort(T *array, int p, int r, COMP comp, PIVOT pivot)
{
    if (p < r)
    {
        int q = partition(array, p, r, comp, pivot);
        quick_sort(array, p, q - 1, comp, pivot);
        quick_sort(array, q, r, comp, pivot);
    }
}

template <typename T, typename COMP, typename PIVOT>
void quick_sort(T *array, int size, COMP comp, PIVOT pivot)
{
    quick_sort(array, 0, size - 1, comp, pivot);
}

#include <iostream>
#include <vector>
#include <random>

template <typename T>
void print_array(const T *array, size_t size)
{
    if (size > 0)
    {
        std::cout << array[0];
        for (size_t i = 1; i < size; ++i)
            std::cout << " " << array[i];
    }
}

int PivotRandom(int begin, int end)
{
    static std::random_device randomDevice;
    static std::mt19937 randomGenerator(randomDevice());
    std::uniform_int_distribution<int> random{begin, end};
    return random(randomGenerator);
}

int PivotFirst(int begin, int end)
{
    return begin;
}

int PivotLast(int begin, int end)
{
    return end;
}

int main()
{
    std::vector<int> a = {2, 9, 3, 0, 6, 1, 5, 7, 4, 8};

    print_array(a.data(), a.size());
    quick_sort(a.data(), a.size(), [](const auto &l, const auto &r) { return l < r; }, &PivotRandom);
    std::cout << " -> ";
    print_array(a.data(), a.size());

    return 0;
}
