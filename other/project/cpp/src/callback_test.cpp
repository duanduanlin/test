/*
 * @Author: dding3
 * @Date: 2023-12-07 17:35:28
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-07 18:04:19
 * @Description:回调函数有三种形式，typedef，using，以及std::function
 * @FilePath: /test/commonapi/test/other/project/cpp/src/callback_test.cpp
 */
#include <iostream>
#include <functional>
void test(int a){
  printf("xxx---------->%s(), line = %d, a = %d\n",__FUNCTION__,__LINE__,a);
}

int main(){
  //使用std::function定义回调函数
  //v1.0: 未使用typedef和using关键字定义
  std::function<void(int)> Callback = test;
  (Callback)(100);


  //v2.0 :typedef
  typedef std::function<void(int)> Callback1;
  Callback1 c1 = test;
  c1(200);

  //v3.0
  using Callback2 = std::function<void(int)>;
  Callback2 c2 = test;
  c2(300);
}
