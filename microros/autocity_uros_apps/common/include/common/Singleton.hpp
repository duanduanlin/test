/*
 * @Author: hanson
 * @Date: 2024-08-23 16:53:57
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-23 16:54:13
 * @Description:
 * @FilePath: \ucanbus\include\common\Singleton.hpp
 */
#ifndef INCLUDE_COMMON_SINGLETON_HPP_
#define INCLUDE_COMMON_SINGLETON_HPP_

namespace auto_city
{
    template <typename T>
    class Singleton
    {
    public:
        static T &Instance()
        {
            static T instance;
            return instance;
        }

        Singleton(T &&) = delete;
        Singleton(const T &) = delete;
        void operator=(const T &) = delete;

    protected:
        Singleton() = default;
        virtual ~Singleton() = default;
    };
}
#endif // INCLUDE_COMMON_SINGLETON_HPP_
