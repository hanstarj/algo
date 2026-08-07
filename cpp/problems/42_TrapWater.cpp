// https://leetcode.com/problems/add-to-array-form-of-integer/

#include <vector>

int Trap(const std::vector<int> &A, int from, int peak)
{
    const int dir = from < peak ? 1 : -1;
    int water = 0;
    while (from < peak)
    {
        int next = from + dir;
        while (next < peak)
        {
            if (A[from] > A[next])
                water += A[from] - A[next];
            else
                break;
            next += dir;
        }
        from = next;
    }
    return water;
}

int TrappedWater2(const std::vector<int> &A)
{
    if (A.size() < 3)
        return 0;

    int peak = 0;
    for (int i = 1; i < A.size(); ++i)
    {
        if (A[i] >= A[peak])
            peak = i;
    }

    return Trap(A, 0, peak) + Trap(A, A.size() - 1, peak);
}

int TrappedWater(const std::vector<int> &A)
{
    if (A.size() < 3)
        return 0;

    int water = 0;
    int l = 0, r = A.size() - 1;
    int maxl = A[l], maxr = A[r];
    while (l < r)
    {
        if (maxl < maxr)
        {
            ++l;
            if (maxl < A[l])
                maxl = A[l];
            else
                water += maxl - A[l];
        }
        else
        {
            --r;
            if (maxr < A[r])
                maxr = A[r];
            else
                water += maxr - A[r];
        }
    }
    return water;
}

#include <iostream>
int main()
{
    std::cout << TrappedWater(std::vector{0, 1, 0, 2, 1, 3, 2, 1, 2, 1}) << std::endl;
}