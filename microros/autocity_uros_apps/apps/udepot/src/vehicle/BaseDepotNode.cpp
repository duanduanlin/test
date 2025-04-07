/*
 * @Author: hanson
 * @Date: 2024-08-23 17:24:38
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 11:20:42
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\BaseDepotNode.cpp
 */
#include "vehicle/BaseDepotNode.hpp"

template <typename MessageT>
MessageT auto_city::BaseNode::Subscriber<MessageT>::_msg;

template <typename MessageT>
void (*auto_city::BaseNode::Subscriber<MessageT>::_onRecv)(MessageT &msg) = nullptr;
