// Time Complexity: O(log min(m, n))
// Idea: Find a boundary in a shorter list, which can be used to deduce 
//       the other boundary in the other list.
//       Check if the left parts of boundaries are smaller than/equal to
//       the right parts.

#include <vector>
#include <limits>
// index calc test
//   0, 1, 2, 3 (len: 4)
//   -> (0 + 4) / 2 = 2
//   0, 1, 2 (len: 3)
//   -> (0 + 3) / 2 = 1

// calculate the boundary of the other one
// if m == 2, n == 3, m + n == odd
//   b1 = 1
//   b2 = (m + n) / 2 - b1 = 1
//   median = min(n1[b1], n2[b2])
// if m == 3, n == 3, m + n == even
//   b1 = 1
//   b2 = (m + n) / 2 - b1 = 2
//   median = max(n1[b1-1], n2[b2-1]) + min(n1[b1], n2[b2])
double findMedianSortedArrays(const std::vector<int> &n1, const std::vector<int> &n2)
{
    const int c1 = n1.size();
    const int c2 = n2.size();
    if (c1 > c2)
        return findMedianSortedArrays(n2, n1);

    const int c3 = c1 + c2;
    const bool odd = c3 % 2;
    int start = 0;
    int end = c1 + 1; // inc a boundary to represent a case where everything is on the left side.
    while (start < end)
    {
        const int b1 = (start + end) / 2;
        const int b2 = c3 / 2 - b1;
        const int n1lmax = b1 > 0 ? n1[b1 - 1] : std::numeric_limits<int>::min();
        const int n1rmin = b1 < c1 ? n1[b1] : std::numeric_limits<int>::max();
        const int n2lmax = b2 > 0 ? n2[b2 - 1] : std::numeric_limits<int>::min();
        const int n2rmin = b2 < c2 ? n2[b2] : std::numeric_limits<int>::max();
        if (n1lmax > n2rmin)
            end = b1;
        else if (n2lmax > n1rmin)
            start = b1;
        else if (odd)
            return std::min(n1rmin, n2rmin);
        else
            return (std::max(n1lmax, n2lmax) + std::min(n1rmin, n2rmin)) * 0.5;
    }
    return 0.0;
}

#include <iostream>
int main()
{
    std::cout << findMedianSortedArrays({0, 1}, {2, 3}) << std::endl;
    return 0;
}