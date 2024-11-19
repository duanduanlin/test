/*
 * @Author: hanson
 * @Date: 2024-10-08 14:17:24
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-09 11:03:25
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\include\common\RingBuffer.hpp
 */
#ifndef APPS_UCANBUS_INCLUDE_COMMON_RINGBUFFER_HPP_
#define APPS_UCANBUS_INCLUDE_COMMON_RINGBUFFER_HPP_
#include "ringbuffer.h"

template <typename T>
class RingBuffer
{
private:
    /* data */
    ring_buffer_t _ring_buffer = {0};
    char *_buf;

public:
    RingBuffer() : _buf(nullptr)
    {
    }

    RingBuffer(size_t size) : _ring_buffer(0), _buf(nullptr)
    {
        SetUp(size);
    }

    virtual ~RingBuffer()
    {
        Destroy();
    }

    int SetUp(size_t size)
    {
        _buf = (char *)malloc(size * sizeof(T));
        ring_buffer_init(&_ring_buffer, _buf, size * sizeof(T));

        return (_buf == nullptr) ? 0 : 1;
    }

    void Destroy()
    {
        if (_buf)
        {
            free(_buf);
            _buf = nullptr;
        }
    }

    bool IsEmpty()
    {
        return ring_buffer_is_empty(&_ring_buffer);
    }

    bool IsFull()
    {
        return ring_buffer_is_full(&_ring_buffer);
    }

    void Push(T &value)
    {
        ring_buffer_queue_arr(&_ring_buffer, (char *)&value, sizeof(T));
    }

    T Pop()
    {
        T value;
        ring_buffer_dequeue_arr(&_ring_buffer, (char *)&value, sizeof(T));
        return value;
    }

    void Push(const T *values, size_t size)
    {
        ring_buffer_queue_arr(&_ring_buffer, (char *)values, size * sizeof(T));
    }

    size_t Pop(T *values, size_t size)
    {
        return ring_buffer_dequeue_arr(&_ring_buffer, (char *)values, size * sizeof(T)) / sizeof(T);
    }
};

#endif // APPS_UCANBUS_INCLUDE_COMMON_RINGBUFFER_HPP_
