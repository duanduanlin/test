/*
 * @Author: dding3
 * @Date: 2023-12-14 18:11:16
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-14 18:12:51
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/macro_test.cpp
 */
#include <stdio.h>

#define To_String(x) #x
#define Binder(X, Y) X##Y

#define ANY_TO_STR(X, Y) To_String(Binder(X, Y))
/*
#: 将宏参数转化为字符串.
##: 将两个标识符拼接成一个标识符.
*/

int main()
{
    // 1.Binder将两个标识符合成一个
    printf("Binder = %d\n", Binder(55, 44));

    // 2.To_String实现将任意类型宏参数转化为字符串。
    printf("To_String(123) = %s\n", To_String(123));

    // 3.将合并的任意类型的标识符转换为字符串.
    printf("Binder = %s\n", To_String(Binder("0000", 88888)));

    // 4.将合并的任意类型的标识符转换为字符串.
    printf("Binder = %s\n", ANY_TO_STR(123, 456));
    return 0;
}
