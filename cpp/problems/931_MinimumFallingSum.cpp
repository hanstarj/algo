// https://leetcode.com/problems/minimum-falling-path-sum/

#include <vector>
#include <limits>
#include <algorithm>

int MinFallingSum(std::vector<std::vector<int>> &a)
{
    const int n = a.size();

    const int steps[] = {-1, 0, 1};
    for (int r = 1; r < n; ++r)
    {
        for (int c = 0; c < n; ++c)
        {
            int minFrom = std::numeric_limits<int>::max();
            for (int s = 0; s < 3; ++s)
            {
                if (c + steps[s] >= 0 && c + steps[s] < n)
                    minFrom = std::min(minFrom, a[r - 1][c + steps[s]]);
            }
            a[r][c] += minFrom;
        }
    }
    int min = std::numeric_limits<int>::max();
    for (int c = 0; c < n; ++c)
        min = std::min(min, a[n - 1][c]);
    return min;
}

#include <iostream>
int main()
{
    std::vector<std::vector<int>> a{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::cout << MinFallingSum(a) << std::endl;
}