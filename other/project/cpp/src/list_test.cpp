/*
 * @Author: dding3
 * @Date: 2023-12-07 22:20:49
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-07 22:41:37
 * @Description:双向链表基本功能测试
 * @FilePath: /test/commonapi/test/other/project/cpp/src/list_test.cpp
 */
#include <iostream>
#include <list>

// insert
void test_case_14()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 insert() 函数在指定位置插入元素
    std::list<int>::iterator iter = myList.insert(myList.begin(), 0); // 在第一个元素前插入0

    std::cout << "insert begin(0):";
    // 输出列表中的元素
    for (int num : myList)
    {
        std::cout << num << " ";
    }

    std::cout << std::endl;
}

// erase
void test_case_13()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 erase() 函数删除列表中的指定元素
    std::list<int>::iterator iter = myList.erase(myList.begin()); // 删除第一个元素

    std::cout << "erase begin:";
    // 输出列表中的元素
    for (int num : myList)
    {
        std::cout << num << " ";
    }

    std::cout << std::endl;
}

// clear
void test_case_12()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 clear() 函数清空列表
    myList.clear();

    std::cout << "clear:";
    // 输出列表中的元素（为空）
    for (int num : myList)
    {
        std::cout << num << " ";
    }

    std::cout << std::endl;
}

// pop_front
void test_case_11()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 pop_front() 函数删除列表开头的元素
    myList.pop_front();

    std::cout << "pop_front:";
    // 输出列表中的元素
    for (int num : myList)
    {
        std::cout << num << " ";
    }

    std::cout << std::endl;
}

// pop_back
void test_case_10()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 pop_back() 函数删除列表末尾的元素
    myList.pop_back();

    std::cout << "pop_back:";
    // 输出列表中的元素
    for (int num : myList)
    {
        std::cout << num << " ";
    }

    std::cout << std::endl;
}

// push_front
void test_case_9()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 push_front() 函数在列表开头插入元素
    myList.push_front(0);

    std::cout << "push_front(0):";
    // 输出列表中的元素
    for (int num : myList)
    {
        std::cout << num << " ";
    }

    std::cout << std::endl;
}

// push_back
void test_case_8()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 push_back() 函数在列表末尾插入元素
    myList.push_back(6);

    std::cout << "push_back(6):";
    // 输出列表中的元素
    for (int num : myList)
    {
        std::cout << num << " ";
    }

    std::cout << std::endl;
}

// back
void test_case_7()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 back() 函数获取列表的最后一个元素
    int lastElement = myList.back();

    std::cout << "Last element of list: " << lastElement << std::endl;
}

// front
void test_case_6()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 front() 函数获取列表的第一个元素
    int firstElement = myList.front();

    std::cout << "First element of list: " << firstElement << std::endl;
}

// max_size
void test_case_5()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 max_size() 函数获取列表的最大容量
    std::cout << "Max size of list: " << myList.max_size() << std::endl;
}

// size
void test_case_4()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 size() 函数获取列表的元素个数
    std::cout << "Size of list: " << myList.size() << std::endl;
}

// empty
void test_case_3()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 empty() 函数判断列表是否为空
    if (myList.empty())
    {
        std::cout << "List is empty" << std::endl;
    }
    else
    {
        std::cout << "List is not empty" << std::endl;
    }
}

// 反向迭代器
void test_case_2()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 rbegin() 函数获取列表的最后一个元素的反向迭代器
    std::list<int>::reverse_iterator iterStart = myList.rbegin();

    // 使用 rend() 函数获取列表的第一个元素的反向迭代器
    std::list<int>::reverse_iterator iterEnd = myList.rend();

    std::cout << "reverse_iterator:";
    // 遍历列表
    for (std::list<int>::reverse_iterator iter = iterStart; iter != iterEnd; ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

// 迭代器
void test_case_1()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 使用 begin() 函数获取列表的第一个元素的迭代器
    std::list<int>::iterator iterStart = myList.begin();

    // 使用 end() 函数获取列表的最后一个元素的迭代器
    std::list<int>::iterator iterEnd = myList.end();

    std::cout << "iterator:";
    // 遍历列表
    for (std::list<int>::iterator iter = iterStart; iter != iterEnd; ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

int main()
{
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    test_case_6();
    test_case_7();
    test_case_8();
    test_case_9();
    test_case_10();
    test_case_11();
    test_case_12();
    test_case_13();
    test_case_14();
    return 0;
}
