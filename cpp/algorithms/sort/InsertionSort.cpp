#include <functional>

template <typename T, typename COMP>
void insert_sort(T *array, size_t size, COMP comp)
{
    for (int i = 1; i < size; ++i)
    {
        T target = std::move(array[i]);
        int j = i - 1;
        while (j >= 0 && comp(target, array[j]))
        {
            array[j + 1] = std::move(array[j]);
            --j;
        }
        array[j + 1] = std::move(target);
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
    insert_sort(a.data(), a.size(), [](const auto &l, const auto &r) { return l < r; });
    std::cout << " -> ";
    print_array(a.data(), a.size());
    return 0;
}
