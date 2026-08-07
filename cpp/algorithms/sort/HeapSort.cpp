#include <cassert>
#include <algorithm>

namespace helper
{

template <typename T, typename COMP>
void BubbleDown(T *array, int i, size_t size, COMP comp)
{
    while (i < size / 2)
    {
        int j = i * 2 + 1;
        if (j + 1 < size && comp(array[j + 1], array[j]))
            ++j;
        if (comp(array[j], array[i]))
            std::swap(array[j], array[i]), i = j;
        else
            break;
    }
}

template <typename T, typename COMP>
void BubbleUp(T *array, int i, COMP comp)
{
    int parent = (i - 1) / 2;
    while (parent >= 0 && comp(array[i], array[parent]))
    {
        std::swap(array[parent], array[i]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

template <typename T, typename COMP>
void Heapify(T *array, size_t size, COMP comp)
{
    for (int i = size / 2 - 1; i >= 0; --i)
        BubbleDown(array, i, size, comp);
}

} // namespace helper

template <typename T, typename COMP>
void MakeHeap(T *array, size_t size, COMP comp)
{
    helper::Heapify(array, size, comp);
}

template <typename T, typename COMP>
void PushHeap(T *array, size_t size, COMP comp)
{
    helper::BubbleUp(array, size - 1, comp);
}

template <typename T, typename COMP>
void PopHeap(T *array, size_t size, COMP comp)
{
    assert(size > 0);
    std::swap(array[0], array[size - 1]);
    helper::BubbleDown(array, 0, size - 1, comp);
}

template <typename T, typename COMP>
bool IsHeap(T *array, size_t size, COMP comp)
{
    for (int i = 0; i < size / 2; ++i)
    {
        int j = i * 2 + 1;
        if (j + 1 < size && comp(array[j + 1], array[j]))
            ++j;
        if (comp(array[j], array[i]))
            return false;
    }
    return true;
}

template <typename T, typename COMP>
void HeapSort(T *array, size_t size, COMP comp)
{
    auto inverse = [comp](const auto &a, const auto &b) { return comp(b, a); };
    MakeHeap(array, size, inverse);
    while (size > 0)
        PopHeap(array, size--, inverse);
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
    std::vector<int> a = {2, 9, 0, 6, 5, 7, 4};
    auto less = [](const auto &l, const auto &r) { return l < r; };

    std::cout << "original: ";
    print_array(a.data(), a.size());
    std::cout << " (" << IsHeap(a.data(), a.size(), less) << ")" << std::endl;

    MakeHeap(a.data(), a.size(), less);
    std::cout << "heapified: ";
    print_array(a.data(), a.size());
    std::cout << " (" << IsHeap(a.data(), a.size(), less) << ")" << std::endl;

    a.push_back(3);
    PushHeap(a.data(), a.size(), less);
    std::cout << "push 3: ";
    print_array(a.data(), a.size());
    std::cout << " (" << IsHeap(a.data(), a.size(), less) << ")" << std::endl;

    a.push_back(1);
    PushHeap(a.data(), a.size(), less);
    std::cout << "push 1: ";
    print_array(a.data(), a.size());
    std::cout << " (" << IsHeap(a.data(), a.size(), less) << ")" << std::endl;

    a.push_back(8);
    PushHeap(a.data(), a.size(), less);
    std::cout << "push 8: ";
    print_array(a.data(), a.size());
    std::cout << " (" << IsHeap(a.data(), a.size(), less) << ")" << std::endl;

    a.push_back(8);
    PushHeap(a.data(), a.size(), less);
    std::cout << "push 8: ";
    print_array(a.data(), a.size());
    std::cout << " (" << IsHeap(a.data(), a.size(), less) << ")" << std::endl;

    HeapSort(a.data(), a.size(), less);
    std::cout << "heap sorted: ";
    print_array(a.data(), a.size());
    std::cout << " (" << IsHeap(a.data(), a.size(), less) << ")" << std::endl;

    a[3] = 100;
    std::cout << "randomly modified: ";
    print_array(a.data(), a.size());
    std::cout << " (" << IsHeap(a.data(), a.size(), less) << ")" << std::endl;

    return 0;
}
