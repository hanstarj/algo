// https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/

#include <vector>
#include <limits>

int MinSwap(const std::vector<int> &as, const std::vector<int> &bs)
{
    // answer when i = 0
    int minSwap = 1;
    int minNoswap = 0;

    const int size = as.size();
    for (int i = 1; i < size; ++i)
    {
        const int a = as[i], pa = as[i - 1];
        const int b = bs[i], pb = bs[i - 1];

        // overflow can never happen because swap/noswap has
        //  always a better value than numeric_limits max since
        //  the problem guarantees the existence of solution.
        // Therefore, minSwap/minNoswap is always less than numeric
        //  limits, meaning no overflow.
        int swap = std::numeric_limits<int>::max();
        int noswap = std::numeric_limits<int>::max();
        if (pa < a && pb < b)
        {
            swap = std::min(swap, minSwap + 1);
            noswap = std::min(noswap, minNoswap);
        }
        if (pb < a && pa < b)
        {
            swap = std::min(swap, minNoswap + 1);
            noswap = std::min(noswap, minSwap);
        }

        minNoswap = noswap;
        minSwap = swap;
    }
    return std::min(minNoswap, minSwap);
}

#include <iostream>
int main()
{
    //int a = MinSwap({0,3,5,8,9}, {2,1,4,6,9});
    int a = MinSwap({1, 3, 5, 4, 6}, {1, 2, 3, 7, 8});
    std::cout << a << std::endl;
    return 0;
}