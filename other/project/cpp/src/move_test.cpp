/*
 * @Author: dding3
 * @Date: 2023-12-07 01:23:22
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-07 01:24:05
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/move_test.cpp
 */
#include <iostream>
#include <string>

int main() {
    std::string source = "Hello, world!";
    std::string destination = std::move(source);
    std::cout << "source: " << source << std::endl;        // 输出：source:
    std::cout << "destination: " << destination << std::endl;  // 输出：destination: Hello, world!
    return 0;
}
