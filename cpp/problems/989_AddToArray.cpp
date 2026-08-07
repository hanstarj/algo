// https://leetcode.com/problems/add-to-array-form-of-integer/

#include <vector>
int CountDigits(int n)
{
    int c = 0;
    while (n > 0)
    {
        n /= 10;
        ++c;
    }
    return c;
}

std::vector<int> AddToArrayForm(std::vector<int> &A, int K)
{
    const int size = A.size();
    for (int i = size - 1; K > 0 && i >= 0; --i)
    {
        A[i] += K;
        K = A[i] / 10;
        A[i] %= 10;
    }

    int extra = CountDigits(K);
    if (extra == 0)
        return std::move(A);

    std::vector<int> B(size + extra);
    B.reserve(size + extra);
    B.resize(extra);
    while (K > 0)
    {
        B[--extra] = K % 10;
        K /= 10;
    }
    B.insert(B.end(), A.begin(), A.end());
    return B;
}

#include <iostream>
int main()
{
    std::vector<int> a = {0};
    auto result = AddToArrayForm(a, 10000);
    for (auto &a : result)
    {
        std::cout << a << " ";
    }
    std::cout << std::endl;
    return 0;
}