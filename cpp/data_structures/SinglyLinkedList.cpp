#include <cstddef>
#include <functional>
#include <initializer_list>
#include <cassert>

template <typename T>
class SinglyLinkedList
{
public:
    struct Node
    {
        T value;
        Node *next;
    };

public:
    SinglyLinkedList()
        : _head(nullptr), _tail(nullptr), _count(0)
    {
    }

    SinglyLinkedList(std::initializer_list<T> list)
        : _head(nullptr), _tail(nullptr), _count(0)
    {
        Append(list);
    }

    SinglyLinkedList(const SinglyLinkedList &rhs) = delete;

    SinglyLinkedList(SinglyLinkedList &&rhs) = delete;

    SinglyLinkedList &operator=(const SinglyLinkedList &rhs) = delete;

    SinglyLinkedList &operator=(SinglyLinkedList &&rhs) = delete;

    ~SinglyLinkedList()
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

    bool IsEmpty() const { return _count == 0; }

    size_t GetCount() const { return _count; }

    const Node *GetHead() const { return _head; }

    Node *GetHead() { return _head; }

    void Append(std::initializer_list<T> list)
    {
        for (auto &&item : list)
            Append(item);
    }

    void Append(const T &value)
    {
        AppendNode(new Node{value, nullptr});
    }

    void Append(T &&value)
    {
        AppendNode(new Node{std::move(value), nullptr});
    }

    void RemoveAt(int index)
    {
        assert(index >= 0 && index < _count);

        Node *prev = nullptr;
        Node *curr = _head;
        for (; index > 0; --index)
        {
            prev = curr;
            curr = curr->next;
        }

        Node *next = curr->next;
        if (prev)
            prev->next = next;
        else
            _head = next;

        if (!next)
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
            _tail->next = node;
            _tail = _tail->next;
        }
        else
        {
            _head = _tail = node;
        }
        ++_count;
    }

private:
    Node *_head;
    Node *_tail;
    size_t _count;
};

#include <iostream>
template <typename T>
std::ostream &operator<<(std::ostream &stream, const SinglyLinkedList<T> &list)
{
    if (auto node = list.GetHead())
    {
        stream << node->value;
        node = node->next;
        while (node)
        {
            stream << " " << node->value;
            node = node->next;
        }
    }
    return stream;
}

int main()
{
    SinglyLinkedList<int> list{1, 2, 3, 4, 5, 6, 7, 8};
    std::cout << list << std::endl;

    list.Append(3);
    std::cout << "Append 3 -> " << list << std::endl;

    list.RemoveAt(0);
    std::cout << "Remove At 0 -> " << list << std::endl;

    std::cout << "Index of 2 -> " << list.FindFirst(2) << std::endl;

    while (!list.IsEmpty())
        list.Pop();

    std::cout << "Emptied. Count -> " << list.GetCount() << std::endl;
    return 0;
}
