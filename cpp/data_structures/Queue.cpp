#include <cstddef>
#include <vector>
#include <cassert>
#include <functional>

namespace
{
constexpr size_t minSize = 4;
constexpr size_t growFactor = 2;
} // namespace

// didn't use vector as an underlying structure intentionally for practice.
template <typename T>
class Queue
{
public:
    Queue()
        : _data(nullptr), _front(0), _size(0), _capacity(0)
    {
    }

    ~Queue()
    {
        if (_data)
        {
            for (size_t i = 0; i < _size; ++i)
            {
                T *item = static_cast<T *>((void *)(_data + sizeof(T) * ((_front + i) % _size)));
                item->~T();
            }
            delete[] _data;
            _front = 0;
            _size = 0;
            _capacity = 0;
        }
    }

    Queue(const Queue &rhs) = delete;

    Queue(Queue &&rhs) = delete;

    Queue &operator=(const Queue &rhs) = delete;

    Queue &operator=(Queue &&rhs) = delete;

    size_t GetCount() const
    {
        return _size;
    }

    bool IsEmpty() const
    {
        return _size == 0;
    }

    void Push(const T &value)
    {
        if (_size >= _capacity)
            Grow();

        new (_data + sizeof(T) * ((_front + _size++) % _capacity)) T{value};
    }

    void Push(T &&value)
    {
        if (_size >= _capacity)
            Grow();

        new (_data + sizeof(T) * ((_front + _size++) % _capacity)) T{std::move(value)};
    }

    const T &Front() const
    {
        assert(_size > 0);
        return *static_cast<const T *>(_data + sizeof(T) * _front);
    }

    T &Front()
    {
        assert(_size > 0);
        return *static_cast<T *>((void *)(_data + sizeof(T) * _front));
    }

    void Pop()
    {
        assert(_size > 0);
        T *item = static_cast<T *>((void *)(_data + sizeof(T) * _front));
        _front = (_front + 1) % _capacity;
        item->~T();
        --_size;
    }

private:
    void Grow()
    {
        _capacity = std::max(minSize, _capacity * growFactor);
        std::byte *newData = new std::byte[_capacity];

        for (size_t i = 0; i < _size; ++i)
        {
            T *oldItem = static_cast<T *>((void *)(_data + sizeof(T) * ((_front + i) % _size)));
            new (newData + sizeof(T) * i) T{std::move(*oldItem)};

            // not necessary for objects that properly implement move semantics, but calling it
            //  should be trivial for those. Destruct it explicitly for objects that aren't trivial
            //  and yet that don't implement move semantics.
            oldItem->~T();
        }

        delete[] _data;
        _data = newData;
        _front = 0;
    }

private:
    std::byte *_data;
    size_t _front;
    size_t _size;
    size_t _capacity;
};

#include <iostream>
int main()
{
    Queue<int> a;

    a.Push(3);
    a.Push(1);
    a.Push(7);
    a.Push(5);
    a.Push(6);

    while (!a.IsEmpty())
    {
        std::cout << a.Front() << std::endl;
        a.Pop();
    }
    return 0;
}
