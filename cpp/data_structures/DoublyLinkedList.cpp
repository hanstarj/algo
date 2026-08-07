#include <cstddef>
#include <functional>
#include <initializer_list>
#include <cassert>

template <typename T>
class DoublyLinkedList
{
    using ValueType = T;

public:
    struct Node
    {
        ValueType value;
        Node *prev = nullptr;
        Node *next = nullptr;
    };

    template <typename PT>
    class Iterator
    {
        using PointerType = PT;

    public:
        Iterator(Node *node)
            : _node(node)
        {
        }

        Iterator(const Iterator &rhs) = default;

        Iterator(Iterator &&rhs) = default;

        Iterator &operator=(const Iterator &rhs) = default;

        Iterator &operator=(Iterator &&rhs) = default;

        bool operator!=(const Iterator &rhs) const
        {
            return _node != rhs._node;
        }

        bool operator==(const Iterator &rhs) const
        {
            return _node == rhs._node;
        }

        Iterator &operator++()
        {
            assert(_node);
            _node = _node->next;
            return *this;
        }

        Iterator operator++(int)
        {
            assert(_node);
            Iterator copy = *this;
            ++(*this);
            return copy;
        }

        Iterator &operator--()
        {
            assert(_node);
            _node = _node->prev;
            return *this;
        }

        Iterator &operator+=(int value)
        {
            assert(_node);
            if (value < 0)
                return (*this) -= -value;

            while (value-- > 0)
                ++*this;
            return *this;
        }

        Iterator &operator-=(int value)
        {
            assert(_node);
            if (value < 0)
                return (*this) += -value;

            while (value-- > 0)
                --*this;
            return *this;
        }

        PointerType &operator*() { return _node->value; }

        PointerType *operator->() { return &_node->value; }

        operator bool() const { return _node != nullptr; }

    private:
        Node *_node;
    };

    using IteratorType = Iterator<ValueType>;
    using ConstIteratorType = Iterator<const ValueType>;

public:
    DoublyLinkedList()
        : _head(nullptr), _tail(nullptr), _count(0)
    {
    }

    DoublyLinkedList(std::initializer_list<ValueType> list)
        : _head(nullptr), _tail(nullptr), _count(0)
    {
        Append(list);
    }

    DoublyLinkedList(const DoublyLinkedList<ValueType> &rhs)
        : _head(nullptr), _tail(nullptr), _count(0)
    {
        for (const Node *curr = rhs._head; curr; curr = curr->next)
            Append(curr->value);
    }

    DoublyLinkedList(DoublyLinkedList<ValueType> &&rhs)
        : _head(rhs._head), _tail(rhs._tail), _count(rhs._count)
    {
        rhs._head = nullptr;
        rhs._tail = nullptr;
        rhs._count = 0;
    }

    DoublyLinkedList &operator=(const DoublyLinkedList &rhs)
    {
        if (this != &rhs)
        {
            Clear();
            for (const Node *curr = _head; curr; curr = curr->next)
                Append(curr->value);
        }
        return *this;
    }

    DoublyLinkedList &operator=(DoublyLinkedList &&rhs)
    {
        if (this != &rhs)
        {
            Clear();
            _head = rhs._head;
            _tail = rhs._tail;
            _count = rhs._count;
            rhs._head = nullptr;
            rhs._tail = nullptr;
            rhs._count = 0;
        }
        return *this;
    }

    ~DoublyLinkedList()
    {
        Clear();
    }

    bool IsEmpty() const { return _count == 0; }

    size_t GetCount() const { return _count; }

    IteratorType Begin() { return IteratorType(_head); }

    ConstIteratorType Begin() const { return ConstIteratorType(_head); }

    IteratorType End() { return IteratorType(nullptr); }

    ConstIteratorType End() const { return ConstIteratorType(nullptr); }

    void Clear()
    {
        while (_head)
        {
            Node *next = _head->next;
            delete _head;
            _head = next;
        }
        _head = _tail = nullptr;
        _count = 0;
    }

    void Append(std::initializer_list<ValueType> list)
    {
        for (auto &&item : list)
            Append(item);
    }

    void Append(const T &value)
    {
        AppendNode(new Node{value});
    }

    void Append(T &&value)
    {
        AppendNode(new Node{std::move(value)});
    }

    void RemoveAt(int index)
    {
        assert(index >= 0 && index < _count);
        Node *curr = _head;
        for (; index > 0; --index)
            curr = curr->next;

        Node *prev = curr->prev;
        Node *next = curr->next;

        if (prev)
            prev->next = next;
        else
            _head = next;

        if (next)
            next->prev = prev;
        else
            _tail = prev;

        delete curr;
        --_count;
    }

    void Pop()
    {
        assert(_count > 0);
        RemoveAt(_count - 1);
    }

    int FindFirst(const T &value)
    {
        Node *curr = _head;
        for (int i = 0; curr; curr = curr->next, ++i)
        {
            if (curr->value == value)
                return i;
        }
        return -1;
    }

private:
    void AppendNode(Node *node)
    {
        if (_tail)
        {
            node->prev = _tail;
            _tail->next = node;
            _tail = _tail->next;
        }
        else
        {
            _head = _tail = node;
        }
        ++_count;
    }

    Node *GetNode(int index)
    {
        if (index < _count / 2)
        {
            Node *curr = _head;
            for (; index > 0; --index)
                curr = curr->next;
            return curr;
        }
        else
        {
            Node *curr = _tail;
            for (; index < _count - 1; ++index)
                curr = curr->prev;
            return curr;
        }
    }

private:
    Node *_head;
    Node *_tail;
    size_t _count;
};

#include <iostream>
template <typename T>
std::ostream &operator<<(std::ostream &stream, const DoublyLinkedList<T> &list)
{
    if (auto iter = list.Begin())
    {
        stream << *iter;
        for (++iter; iter != list.End(); ++iter)
            stream << " " << *iter;
    }
    return stream;
}

int main()
{
    DoublyLinkedList<int> list{1, 2, 3, 4, 5, 6, 7, 8};
    std::cout << list << std::endl;

    list.Append(3);
    std::cout << "Append 3 -> " << list << std::endl;

    list.RemoveAt(0);
    std::cout << "Remove At 0 -> " << list << std::endl;

    std::cout << "Index of 2 -> " << list.FindFirst(2) << std::endl;

    auto list2 = list;
    std::cout << "Copied: " << list2 << std::endl;

    while (!list.IsEmpty())
        list.Pop();
    return 0;
}
