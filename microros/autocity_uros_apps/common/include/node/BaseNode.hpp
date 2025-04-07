/*
 * @Author: hanson hanson@citygo.com.cn
 * @Date: 2024-08-20 16:00:08
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-29 15:27:23
 * @FilePath: \autocity_uros_apps\apps\ucanbus\include\node\BaseNode.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#ifndef __UCANBUS_INCLUDE_NODE_BASENODE__H_
#define __UCANBUS_INCLUDE_NODE_BASENODE__H_

#include <string>
#include <functional>
#include <memory>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <rmw_microros/rmw_microros.h>
#include <microros_transports.h>

namespace auto_city
{
#define RCCHECK(fn)                                                                                        \
    {                                                                                                      \
        rcl_ret_t temp_rc = fn;                                                                            \
        if ((temp_rc != RCL_RET_OK))                                                                       \
        {                                                                                                  \
            printf("[%s]Failed status on line %d: %d. Aborting.\n", __FUNCTION__, __LINE__, (int)temp_rc); \
            return;                                                                                        \
        }                                                                                                  \
    }
#define RCCHECKR(fn)                                                                                       \
    {                                                                                                      \
        rcl_ret_t temp_rc = fn;                                                                            \
        if ((temp_rc != RCL_RET_OK))                                                                       \
        {                                                                                                  \
            printf("[%s]Failed status on line %d: %d. Aborting.\n", __FUNCTION__, __LINE__, (int)temp_rc); \
            return 1;                                                                                      \
        }                                                                                                  \
    }
#define RCSOFTCHECK(fn)                                                                                      \
    {                                                                                                        \
        rcl_ret_t temp_rc = fn;                                                                              \
        if ((temp_rc != RCL_RET_OK))                                                                         \
        {                                                                                                    \
            printf("[%s]Failed status on line %d: %d. Continuing.\n", __FUNCTION__, __LINE__, (int)temp_rc); \
        }                                                                                                    \
    }

    typedef void (*timer_callback)(rcl_timer_t *timer, int64_t last_call_time);
    typedef void (*subscribe_callback)(const void *msgin);

    class BaseNode
    {
    public:
        template <typename MessageT>
        class Subscriber
        {
        private:
            static MessageT _msg;
            static void (*_onRecv)(MessageT &msg);
            rcl_subscription_t _sub;
            BaseNode *_node;
            std::string _topic_name;

        public:
            Subscriber(BaseNode *node, const std::string &topic_name)
            {
                _node = node;
                _topic_name = topic_name;
            }
            ~Subscriber()
            {
                Destory();
            }

            int Create(void (*cb)(MessageT &msg))
            {
                if (RCL_RET_OK != rclc_subscription_init_best_effort(&_sub, &_node->_node, _msg.GetType(), _topic_name.c_str()))
                {
                    return -1;
                }

                if (RCL_RET_OK != rclc_executor_add_subscription(&_node->_executor, &_sub, _msg.GetMsg(), _callback, ON_NEW_DATA))
                {
                    return -1;
                }

                _onRecv = cb;

                return 0;
            }

            int Destory()
            {
                if (RCL_RET_OK != rcl_subscription_fini(&_sub, &_node->_node))
                {
                    return -1;
                }

                return 0;
            }

            MessageT *GetMsg()
            {
                return &_msg;
            }

        private:
            static void _callback(const void *msgin)
            {
                // printf("got some data since %f ms ago\r\n", _msg.Elapsed());
                if (_onRecv != nullptr)
                {
                    _onRecv(_msg);
                }
                // printf("got msg len %d \r\n", _msg.GetMsgLen());
            }
        };

        class Timer
        {
        private:
            rcl_timer_t _timer;
            BaseNode *_node;

        public:
            Timer(BaseNode *node, int duration, timer_callback cb)
            {
                _node = node;
                RCCHECK(rclc_timer_init_default(&_timer, &_node->_support, RCL_MS_TO_NS(duration), cb));
                RCCHECK(rclc_executor_add_timer(&_node->_executor, &_timer));
            }

            ~Timer()
            {
                RCCHECK(rcl_timer_fini(&_timer));
            }
        };

        template <typename MessageT>
        class Publisher
        {
        private:
            rcl_publisher_t _pub;
            BaseNode *_node;
            std::string _topic_name;
            MessageT _msg;

        public:
            Publisher(BaseNode *node, const std::string &topic_name) : _node(nullptr)
            {
                _node = node;
                _topic_name = topic_name;
            }
            ~Publisher()
            {
                Destory();
            }

            int Create()
            {
                if (RCL_RET_OK != rclc_publisher_init_best_effort(&_pub, &_node->_node, _msg.GetType(), _topic_name.c_str()))
                {
                    return -1;
                }

                return 0;
            }

            int Destory()
            {
                if (RCL_RET_OK != rcl_publisher_fini(&_pub, &_node->_node))
                {
                    return -1;
                }

                return 0;
            }

            int Publish(MessageT &msg)
            {
                return rcl_publish(&_pub, (const void *)msg.GetMsg(), NULL);
            }
        };

    public:
        BaseNode(const std::string &node_name) : _init_ok(false)
        {
            // Set custom transports
            RCCHECK(rmw_uros_set_custom_transport(
                MICRO_ROS_FRAMING_REQUIRED,
                (void *)&default_params,
                zephyr_transport_open,
                zephyr_transport_close,
                zephyr_transport_write,
                zephyr_transport_read));
            // Init micro-ROS
            _allocator = rcl_get_default_allocator();
            // create init_options
            RCCHECK(rclc_support_init(&_support, 0, NULL, &_allocator));
            // create node
            RCCHECK(rclc_node_init_default(&_node, node_name.c_str(), "", &_support));
            RCCHECK(rclc_executor_init(&_executor, &_support.context, 3, &_allocator));
            _init_ok = true;
        }
        virtual ~BaseNode()
        {
            _init_ok = false;
            RCCHECK(rcl_node_fini(&_node));
            RCCHECK(rclc_executor_fini(&_executor));
            RCCHECK(rclc_support_fini(&_support));
        }

        /**
         * @description:spin some ms
         * @param {int} ms
         * @return {*}
         */
        void Spin(int ms)
        {
            rclc_executor_spin_some(&_executor, RCL_MS_TO_NS(ms));
        }

        /**
         * @description:spin forever
         * @param {int} ms
         * @return {*}
         */
        void Spin()
        {
            rclc_executor_spin(&_executor);
        }

        bool IsOk()
        {
            return _init_ok;
        }

        /**
         * @description: create sub
         * @param {string} topic_name
         * @param {type_support} type
         * @param {subscribe_callback} cb
         * @return {*}
         */
        template <typename MessageT>
        std::shared_ptr<Publisher<MessageT>> CreatePublisher(const std::string &topic_name)
        {
            auto pub = std::make_shared<Publisher<MessageT>>(this, topic_name);
            if (pub->Create() != 0)
            {
                return nullptr;
            }
            return pub;
        }

        template <typename MessageT>
        std::shared_ptr<Subscriber<MessageT>> CreateSubscription(const std::string &topic_name, void (*cb)(MessageT &msg))
        {
            auto sub = std::make_shared<Subscriber<MessageT>>(this, topic_name);
            if (sub->Create(cb) != 0)
            {
                return nullptr;
            }
            return sub;
        }

        /**
         * @description: init a timer
         * @param {int} duration_ms
         * @param {timer_callback} cb
         * @return {*}
         */
        std::shared_ptr<Timer> CreateTimer(int duration_ms, timer_callback cb)
        {
            return std::make_shared<Timer>(this, duration_ms, cb);
        }

    private:
        /* rcl */
        rcl_allocator_t _allocator;
        rclc_support_t _support;
        rcl_node_t _node;
        rclc_executor_t _executor;
        /*status*/
        bool _init_ok;
    };
}
#endif //__UCANBUS_INCLUDE_NODE_BASENODE__H_
