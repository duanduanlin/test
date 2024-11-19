#ifndef INCLUDE_COMMON_TASKREQUESTSTATUSBRIDGE_HPP_
#define INCLUDE_COMMON_TASKREQUESTSTATUSBRIDGE_HPP_

#pragma once

#include <atomic>
#include <cstdint>

class TaskRequestStatusBridge
{

public:
    TaskRequestStatusBridge()
    {
    }
    ~TaskRequestStatusBridge()
    {
    }

    void set_sweeping_task_status(uint16_t value)
    {
        sweeping_task_status_.store(value);
    }
    int16_t sweeping_task_status() const
    {
        return sweeping_task_status_.load();
    }

    void set_dustbin_lifting_task_status(uint16_t value)
    {
        dustbin_lifting_task_status_.store(value);
    }
    int16_t dustbin_lifting_task_status() const
    {
        return dustbin_lifting_task_status_.load();
    }

    void set_dustbin_dumping_cleaning_task_status(uint16_t value)
    {
        dustbin_dumping_cleaning_task_status_.store(value);
    }
    int16_t dustbin_dumping_cleaning_task_status() const
    {
        return dustbin_dumping_cleaning_task_status_.load();
    }

    void set_dustbin_reset_task_status(uint16_t value)
    {
        dustbin_reset_task_status_.store(value);
    }
    int16_t dustbin_reset_task_status() const
    {
        return dustbin_reset_task_status_.load();
    }

    void set_wireless_charge_task_status(uint16_t value)
    {
        wireless_charge_task_status_.store(value);
    }
    int16_t wireless_charge_task_status() const
    {
        return wireless_charge_task_status_.load();
    }

    // void set_left_front_brush_tgt_abd_dist_mm(float value)
    // {
    //     left_front_brush_tgt_abd_dist_mm_ = value;
    // }
    // float left_front_brush_tgt_abd_dist_mm() const
    // {
    //     return left_front_brush_tgt_abd_dist_mm_;
    // }

    // void set_right_front_brush_tgt_abd_dist_mm(uint16_t value)
    // {
    //     right_front_brush_tgt_abd_dist_mm_ = value;
    // }
    // int16_t right_front_brush_tgt_abd_dist_mm() const
    // {
    //     return right_front_brush_tgt_abd_dist_mm_;
    // }

private:
    // 清扫状态
    std::atomic<int16_t> sweeping_task_status_;

    // 垃圾箱升举状态
    std::atomic<int16_t> dustbin_lifting_task_status_;

    // 垃圾箱倾倒、清洗状态
    std::atomic<int16_t> dustbin_dumping_cleaning_task_status_;

    // 垃圾桶复位状态
    std::atomic<int16_t> dustbin_reset_task_status_;

    // 充电状态
    std::atomic<int16_t> wireless_charge_task_status_;

    // //左前置边刷目标外展距离
    // float left_front_brush_tgt_abd_dist_mm_;

    // //右前置边刷目标外展距离
    // float right_front_brush_tgt_abd_dist_mm_;
};

#endif // INCLUDE_COMMON_TASKREQUESTSTATUSBRIDGE_HPP_
