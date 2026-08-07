// Time Complexity: O(n^2)
// Idea: Sort, Fix each number, use two pointers in the rest range,
//       narrowing down to the closest approximation.

#include <vector>
#include <algorithm>
#include <cmath>
int threeSumClosest(std::vector<int> &v, int t)
{
    int u = v[0] + v[1] + v[2];
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size() - 2; ++i)
    {
        int l = i + 1;
        int r = v.size() - 1;
        while (l < r)
        {
            const int s = v[i] + v[l] + v[r];
            if (s < t)
                ++l;
            else if (s > t)
                --r;
            else
                return s;
            if (std::abs(s - t) < std::abs(u - t))
                u = s;
        }
    }
    return u;
}

#include <iostream>
int main()
{
    std::vector<int> v = {-1, 2, 1, -4};
    int t = 1;
    std::cout << threeSumClosest(v, t) << std::endl;
    return 0;
}