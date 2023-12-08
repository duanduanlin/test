/*
 * @Author: dding3
 * @Date: 2023-12-07 17:56:22
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-07 18:02:49
 * @Description:enum class提供了一种作用域限定的枚举定义(默认是全局的，会有命名冲突)，并且不再可以隐式转换（更安全）
 * @FilePath: /test/commonapi/test/other/project/cpp/src/enum_test.cpp
 */
#include <iostream>

enum OldColor
{
    RED,
    GREEN,
    BLUE
};

enum class NewColor {
   RED,
   GREEN,
   BLUE
};


int main()
{
    OldColor oc = GREEN;
    NewColor nc = NewColor::GREEN;

    if (oc == RED)
    {
        std::cout << "old color is read" << std::endl;
    }
    else if (oc == GREEN)
    {
        std::cout << "old color is green" << std::endl;
    }
    else if (oc == BLUE)
    {
        std::cout << "old color is blue" << std::endl;
    }

    if (nc == NewColor::RED)
    {
        std::cout << "new color is read" << std::endl;
    }
    else if (nc == NewColor::GREEN)
    {
        std::cout << "new color is green" << std::endl;
    }
    else if (nc == NewColor::BLUE)
    {
        std::cout << "new color is blue" << std::endl;
    }

    return 0;
}
