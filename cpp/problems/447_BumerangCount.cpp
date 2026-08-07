// https://leetcode.com/problems/number-of-boomerangs/

#include <vector>
#include <unordered_map>

inline int distSq(const std::vector<int> &a, const std::vector<int> &b)
{
    const int xd = b[0] - a[0];
    const int yd = b[1] - a[1];
    return xd * xd + yd * yd;
}

inline int countBoomerangs(int n)
{
    return n * (n - 1);
}

int numberOfBoomerangs(std::vector<std::vector<int>> &points)
{
    const int size = points.size();
    if (size < 3)
        return 0;

    int boomerangs = 0;
    std::unordered_map<int, int> counter;
    counter.reserve(points.size());
    for (int i = 0; i < points.size(); ++i)
    {
        counter.clear();
        auto &a = points[i];
        for (int j = 0; j < points.size(); ++j)
        {
            if (i == j)
                continue;
            counter[distSq(a, points[j])]++;
        }
        for (auto &count : counter)
            boomerangs += countBoomerangs(count.second);
    }

    return boomerangs;
}

#include <iostream>

int main()
{
    std::vector<std::vector<int>> a = {{0, 0}, {1, 0}, {2, 0}};
    std::cout << numberOfBoomerangs(a) << std::endl;
    return 0;
}