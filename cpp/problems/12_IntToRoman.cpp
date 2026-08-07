#include <string>

int digitToRoman(int digit, char one, char five, char ten, int i, char buffer[])
{
    // 9 = ten - one
    // 8,7,6,5 = five + (d - 5)one
    // 4 = five - one
    // 3,2,1,0 = d(one)
    if (digit == 9)
    {
        buffer[i++] = one;
        buffer[i++] = ten;
        digit = 0;
    }
    else if (digit == 4)
    {
        buffer[i++] = one;
        buffer[i++] = five;
        digit = 0;
    }
    else if (digit >= 5)
    {
        buffer[i++] = five;
        digit -= 5;
    }
    while (digit-- > 0)
        buffer[i++] = one;
    return i;
}
std::string intToRoman(int num)
{
    char buffer[4 * 4] = {
        0,
    };
    int i = digitToRoman(num / 1000, 'M', ' ', ' ', 0, buffer);
    num %= 1000;
    i = digitToRoman(num / 100, 'C', 'D', 'M', i, buffer);
    num %= 100;
    i = digitToRoman(num / 10, 'X', 'L', 'C', i, buffer);
    i = digitToRoman(num % 10, 'I', 'V', 'X', i, buffer);
    return buffer;
}

#include <iostream>
int main()
{
    std::cout << intToRoman(3) << std::endl;
    return 0;
}