/*
 * @Author: dding3
 * @Date: 2023-12-14 19:28:09
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-14 19:30:36
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/bits_test.cpp
 */
#include <iostream>
using namespace std;

typedef struct Bit
{
    unsigned int a : 1; // 0000 0001 = 1；占1bit,超出的部分为0，没有超出的部分，正常计算即可。
    unsigned int b : 3; // 0000 0111 = 7; 占3bit,没有超出的部分，正常计算即可。
    unsigned int : 0;   // 0   = 0 空域，下一个重新开始
    unsigned int d : 6; // 0011 1111 = 64；占6bit,没有超出的部分，正常计算即可。
} Bit;

int main(int argc, char *argv[])
{
    Bit bit;
    cout << "sizeof(Bit) = " << sizeof(Bit) << endl; // a(bit) + b(3bit) + d(6bit);a+b = 1byte; d = 1byte

    bit.a = 2;             // 10
    cout << bit.a << endl; // 0; 溢出

    bit.b = 7;             // 0000 0111
    cout << bit.b << endl; // 7

    bit.b = 8;             // 1000
    cout << bit.b << endl; // 0: overflow

    bit.d = 86; // 0101 0110 & 0011 1111 = 0001 0110 = 22
    cout << bit.d << endl;

    bit.a = 1;             // 0000 0001
    cout << bit.a << endl; // 1

    return EXIT_SUCCESS;
}
