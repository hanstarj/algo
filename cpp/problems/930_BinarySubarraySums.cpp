// https://leetcode.com/problems/binary-subarrays-with-sum/

#include <vector>

int Find(std::vector<int> a, int i, int v)
{
    while (i < a.size() && a[i] != v)
        ++i;
    return i;
}

int SubarraySums(const std::vector<int> &a, int s)
{
    const int size = a.size();
    if (s == 0)
    {
        int sum = 0;
        int l = Find(a, 0, 0);
        while (l < size)
        {
            int r = Find(a, l + 1, 1);
            int zeros = r - l;
            sum += zeros * (zeros + 1) / 2;
            l = Find(a, r, 0);
        }
        return sum;
    }

    int t = 0;
    int r = Find(a, 0, 1);
    while (r < size && ++t < s)
        r = Find(a, r + 1, 1);

    int sum = 0;
    int l = -1;
    while (r < size)
    {
        int nl = Find(a, l + 1, 1);
        int nr = Find(a, r + 1, 1);
        if (nr > size)
            break;
        sum += (nl - l) * (nr - r);
        l = nl;
        r = nr;
    }
    return sum;
}

#include <iostream>
int main()
{
    int s = 9309;
    std::vector<int> a{};
    std::cout << SubarraySums(a, s) << std::endl;
}