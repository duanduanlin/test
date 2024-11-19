/*
 * @Author: hanson
 * @Date: 2024-08-28 15:55:50
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-12 16:41:54
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\Ecar3VehicleController.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_ECAR3VEHICLECONTROLLER_HPP_
#define INCLUDE_VEHICLE_ECAR3_ECAR3VEHICLECONTROLLER_HPP_

#include "vehicle/BaseVehicleController.hpp"
#include "vehicle/ecar3/protocol/send/RDCU118.hpp"
#include "vehicle/ecar3/protocol/send/RDCU119.hpp"
#include "vehicle/ecar3/protocol/send/RDCU154.hpp"
#include "vehicle/ecar3/protocol/send/RDCU155.hpp"
#include "vehicle/ecar3/protocol/send/RDCU6F0.hpp"
#include "common/TimeTools.hpp"

class Ecar3VehicleController : public BaseVehicleController
{
private:
    /* data */
    uint8_t _current_mode;
    uint8_t _current_drive_direction;
    uint8_t _dustbin_overturn_pose_status;
    uint8_t _dustbin_lift_pose_status;
    double _current_acc_mpps;
    bool _dump_finished = false;
    double _dump_time_threshold_s;
    double _control_timeout_ms;
    /*chassis cmd */
    RDCU118 *_drive_118 = nullptr;
    RDCU119 *_body_119 = nullptr;
    RDCU154 *_sweep_154 = nullptr;
    RDCU155 *_sweep2_155 = nullptr;
    RDCU6F0 *_audio_6f0 = nullptr;
    /*task time*/
    TimeTools _dump_time;

public:
    Ecar3VehicleController(/* args */) = default;
    virtual ~Ecar3VehicleController() = default;

    int Setup(std::unordered_map<uint32_t, BaseProtocol *> &protocol_map, ControlMsgWrap *msg, ChassisDetail *chassis) override;
    int UpdateControlCmd() override;

private:
    void _update_chassis();
    void _update_mode();
    void _update_light();
    void _update_vertical();
    void _update_gear();
    void _update_steer();
    void _update_drive_select();
    void _update_sweep();
    void _update_audio();
    void _update_dump_task();

    void _dump_task_none();
    void _dump_task_lift();
    void _dump_task_dumping_and_cleaning();
    void _dump_task_reset();
};

#endif // INCLUDE_VEHICLE_ECAR3_ECAR3VEHICLECONTROLLER_HPP_
