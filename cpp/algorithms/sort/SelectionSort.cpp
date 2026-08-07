#include <cstddef>
#include <algorithm>

template <typename T, typename COMP>
void select_sort(T *array, size_t size, COMP comp)
{
    for (size_t i = 0; i < size; ++i)
    {
        size_t best = i;
        for (int j = i + 1; j < size; ++j)
        {
            if (comp(array[j], array[best]))
                best = j;
        }
        if (i != best)
            std::swap(array[i], array[best]);
    }
}

#include <iostream>
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

#include <vector>
int main()
{
    std::vector<int> a = {2, 9, 3, 0, 6, 1, 5, 7, 4, 8};

    print_array(a.data(), a.size());
    select_sort(a.data(), a.size(), [](const auto &l, const auto &r) { return l < r; });
    std::cout << " -> ";
    print_array(a.data(), a.size());
    return 0;
}
