#include <functional>

template <typename T, typename COMP>
void merge_sort(T *array, int begin, int end, COMP comp, T *buffer)
{
    if (begin < end)
    {
        const int mid = (begin + end) / 2;
        int rbegin = mid + 1;
        merge_sort(array, begin, mid, comp, buffer);
        merge_sort(array, rbegin, end, comp, buffer);
        for (int i = begin; i <= end; ++i)
            buffer[i] = std::move(array[i]);

        int current = begin;
        while (begin <= mid && rbegin <= end)
        {
            if (comp(buffer[begin], buffer[rbegin]))
                array[current] = std::move(buffer[begin++]);
            else
                array[current] = std::move(buffer[rbegin++]);
            ++current;
        }
        while (begin <= mid)
            array[current++] = std::move(buffer[begin++]);
        while (rbegin <= end)
            array[current++] = std::move(buffer[rbegin++]);
    }
}

template <typename T, typename COMP>
void merge_sort(T *array, int size, COMP comp)
{
    T *buffer = new T[size];
    merge_sort(array, 0, size - 1, comp, buffer);
    delete[] buffer;
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
    merge_sort(a.data(), a.size(), [](const auto &l, const auto &r) { return l < r; });
    std::cout << " -> ";
    print_array(a.data(), a.size());
    return 0;
}
