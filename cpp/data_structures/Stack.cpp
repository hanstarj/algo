#include <vector>

template <typename T>
class Stack
{
public:
    size_t GetCount() const
    {
        return array.size();
    }

    bool IsEmpty() const
    {
        return array.empty();
    }

    void Push(const T &value)
    {
        array.push_back(value);
    }

    void Push(T &&value)
    {
        array.push_back(value);
    }

    const T &Top() const
    {
        return array.back();
    }

    T &Top()
    {
        return array.back();
    }

    void Pop()
    {
        array.pop_back();
    }

private:
    std::vector<T> array;
};

#include <iostream>
int main()
{
    Stack<int> a;

    a.Push(3);
    a.Push(1);
    a.Push(7);
    a.Push(5);
    a.Push(6);

    while (!a.IsEmpty())
    {
        std::cout << a.Top() << std::endl;
        a.Pop();
    }
    return 0;
}