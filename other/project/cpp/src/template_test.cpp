/*
 * @Author: dding3
 * @Date: 2023-12-07 17:45:04
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-07 18:05:03
 * @Description:参数模板可以用于函数或者类可变参数的场景
 * @FilePath: /test/commonapi/test/other/project/cpp/src/template_test.cpp
 */
#include <iostream>

class TEST {
public:
  void print_test(int a, float b) {
    std::cout << "a: " << a << ", b: " << b << std::endl;
  }
};


//v1.0: 不使用template模板和Args
void call0(TEST* obj, void (TEST::*member)(int a, float b), int x , int y) {
  (obj->*member)(std::forward<int>(x), std::forward<int>(y));
}

//v2.0: 使用template模板,但是不使用Args
template <typename... Args>
void call(TEST* obj, void (TEST::*member)(int a, float b), Args... args) {
  (obj->*member)(std::forward<Args>(args)...);
}

//v3.0 使用Args变长参数
//obj:表示TEST对象;
//TEST::*member:表示TEST类成员函数
//Args... args: 表示成员函数参数
template <typename... Args>
void call1(TEST* obj, void (TEST::*member)(Args...), Args... args) {
  (obj->*member)(std::forward<Args>(args)...);
}



int main() {
  /*
    obj:表示TEST对象,对应真正的对象:&obj0.
    TEST::*member:表示TEST类成员函数,对应真正的函数&TEST::print_test()
    Args... args: 表示成员函数参数 ,对应真正的参数11, 0.34.
  */
  //v1.0
  TEST obj0;
  call(&obj0, &TEST::print_test, 11, 0.34);

  //v2.0
  TEST obj;
  call(&obj, &TEST::print_test, 23, 0.11);


  //v3.0
  TEST obj1;
  call1(&obj, &TEST::print_test, 133, 3.14f);

  //v4.0
  TEST obj2;
  void (TEST::*print)(int, float) = &TEST::print_test;
  (obj.*print)(100, 4.34);

  return 0;
}
