/*
 * @Author: dding3
 * @Date: 2023-12-13 22:34:17
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-13 22:43:45
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/stringstream_test.cpp
 */
#include <sstream>
#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

// 字符串转数字
void test_case_1()
{
    stringstream stream;
    string buf = "1234";
    int i;

    // 1.字符串转换为整形
    stream << buf; // 插入字符串
    stream >> i;   // 字符串转换成int类型
    cout << "typeinfo(i) = " << typeid(i).name() << ", i = " << i << endl;
    stream.clear();
}

// 数字转字符串
void test_case_2()
{
    stringstream stream;
    string buf = "1234";
    int j = 1000;
    stream << j;   // 将int流输入
    stream >> buf; // 将int类型转为字符串，放入buf
    cout << "typeinfo(buf) = " << typeid(buf).name() << ", buf = " << buf << endl;
}

// 数据拼接
void test_case_3()
{
    stringstream stream;
    int port = 1;

    stream << "/dev/video" << port; //: /dev/video0
    string str(stream.str());
    cout << "stream.str() = " << stream.str() << endl; //: /dev/video0
    cout << "str = " << str << endl;
    cout << "str.c_str() = " << str.c_str() << endl;
}

int main()
{
    test_case_1();
    test_case_2();
    test_case_3();
}
