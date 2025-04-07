/*
 * @Author: hanson
 * @Date: 2024-08-27 10:15:09
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 11:28:17
 * @Description:
 * @FilePath: \autocity_uros_apps\common\include\cancard\BaseCancard.hpp
 */
#ifndef INCLUDE_CANCARD_BASECANCARD_HPP_
#define INCLUDE_CANCARD_BASECANCARD_HPP_

#include <string>
#include <vector>
#include <mutex>

#include "common/can_support.hpp"

namespace auto_city
{
    class BaseCancard
    {
    protected:
        std::mutex _mux;
        bool _save_can_data;

    private:
        /* data */
        int _fd;
        std::string _dev_name;

    public:
        BaseCancard(const std::string name) : _fd(-1)
        {
            _dev_name = name;
            _save_can_data = false;
        }
        virtual ~BaseCancard()
        {
            CanClose();
        }

        virtual int CanOpen()
        {
            if (_fd > 0)
            {
                printf("can:%s is already open\r\n", _dev_name.c_str());
                return -1;
            }
            if ((_fd = socket_can_open(_dev_name.c_str())) < 0)
            {
                printf("CanOpen failed\r\n");
                return -1;
            }

            return _fd;
        }

        virtual int CanClose()
        {
            if (_fd <= 0)
            {
                printf("can:%s is already close\r\n", _dev_name.c_str());
                return -1;
            }

            socket_can_close(_fd);
            _fd = -1;
            return 0;
        }

        virtual int CanRecv(can_frame &aframe)
        {
            if (_fd < 0)
            {
                printf("can:%s is not open\r\n", _dev_name.c_str());
                return -1;
            }
            std::lock_guard<std::mutex> lock(_mux);
            return socket_can_recv(_fd, &aframe);
        }

        virtual int CanSend(std::vector<can_frame> &frames)
        {
            if (_fd < 0)
            {
                printf("can:%s is not open\r\n", _dev_name.c_str());
                return -1;
            }

            for (auto i : frames)
            {
                std::lock_guard<std::mutex> lock(_mux);
                if (socket_can_send(_fd, &i) < 0)
                {
                    printf("can_id:%04x send failed\r\n", i.can_id);
                }
            }

            return 0;
        }

        virtual int CanSend(can_frame &frame)
        {
            if (_fd < 0)
            {
                // LOG_ERRO("can:%s is not open\r\n", _dev_name.c_str());
                return -1;
            }
            std::lock_guard<std::mutex> lock(_mux);
            return socket_can_send(_fd, &frame);
        }

        virtual int SetFilter(const std::vector<uint32_t> &can_ids)
        {
            can_filter filters[can_ids.size()];

            for (size_t i = 0; i < can_ids.size(); i++)
            {
                printf("set filter id:0x%04X\r\n", can_ids[i]);
                filters[i].can_id = can_ids[i];
            }
            int ret = socket_can_set_filter(_fd, filters, can_ids.size());

            return ret;
        }
    };
}
#endif // INCLUDE_CANCARD_BASECANCARD_HPP_
