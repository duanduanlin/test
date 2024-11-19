/*
 * @Author: hanson
 * @Date: 2024-08-27 17:49:07
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-24 17:35:55
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\src\vehicle\ecar3\Ecar3RecvMsgManager.cpp
 */
#include <sstream>
#include <iomanip>
#include <math.h>
#include <float.h>
#include "vehicle/ecar3/Ecar3RecvMsgManager.hpp"
#include "vehicle/ecar3/protocol/recv/CCU240.hpp"
#include "vehicle/ecar3/protocol/recv/CCU217.hpp"
#include "vehicle/ecar3/protocol/recv/CCU250.hpp"
#include "vehicle/ecar3/protocol/recv/CCU254.hpp"
#include "vehicle/ecar3/protocol/recv/CCU222.hpp"
#include "vehicle/ecar3/protocol/recv/CBCU535.hpp"
#include "vehicle/ecar3/protocol/recv/CBCU537.hpp"
#include "vehicle/ecar3/protocol/recv/CCU211.hpp"
#include "vehicle/ecar3/protocol/recv/CCU215.hpp"
#include "vehicle/ecar3/protocol/recv/CCU213.hpp"
#include "vehicle/ecar3/protocol/recv/CCU212.hpp"
#include "vehicle/ecar3/protocol/recv/CCU214.hpp"
#include "vehicle/ecar3/protocol/recv/CCU216.hpp"
#include "vehicle/ecar3/protocol/recv/CCU218.hpp"
#include "vehicle/ecar3/protocol/recv/CCU220.hpp"
#include "vehicle/ecar3/protocol/recv/CCU261.hpp"
#include "vehicle/ecar3/protocol/recv/CCU219.hpp"
#include "vehicle/ecar3/protocol/recv/CCU252.hpp"
#include "vehicle/ecar3/protocol/recv/CCU251.hpp"
#include "vehicle/ecar3/protocol/recv/CCU2A5.hpp"
#include "vehicle/ecar3/protocol/recv/CCU2A6.hpp"
#include "vehicle/ecar3/protocol/recv/CBCU534.hpp"
#include "vehicle/ecar3/protocol/recv/CDCU227.hpp"

#include "trace/LogTrace.hpp"

int Ecar3RecvMsgManager::Setup()
{
    LOG_INFO("recv manager setup\r\n");
    AddProtocol<CCU240, true>();
    AddProtocol<CCU217, true>();
    AddProtocol<CCU250, true>();
    AddProtocol<CCU254, true>();
    AddProtocol<CCU222, true>();
    AddProtocol<CBCU535, true>();
    AddProtocol<CBCU537, true>();
    AddProtocol<CCU211, true>();
    AddProtocol<CCU215, true>();
    AddProtocol<CCU213, true>();
    AddProtocol<CCU212, true>();
    AddProtocol<CCU214, true>();
    AddProtocol<CCU216, true>();
    AddProtocol<CCU218, true>();
    AddProtocol<CCU220, true>();
    AddProtocol<CCU261, true>();
    AddProtocol<CCU219, true>();
    AddProtocol<CCU252, true>();
    AddProtocol<CCU251, true>();
    AddProtocol<CCU2A5, true>();
    AddProtocol<CCU2A6, true>();
    AddProtocol<CBCU534, true>();
    AddProtocol<CDCU227, true>();
    return 0;
}

void Ecar3RecvMsgManager::UpdateChassis()
{
    auto ecar3_chassis = _chassis_detail.GetEcar3Chassis();
    ChassisMsg *chassis_msgs = _chassis_msg_wrap.GetMsg();

    _chassis_msg_wrap.Lock();
    chassis_msgs->vehicle_info.motor_spd_radps = ecar3_chassis->ccu217_a_.motor_speed_rpm;
    chassis_msgs->vehicle_info.speed_mps = ecar3_chassis->ccu250_a_.speed_kmph / 3.6;
    chassis_msgs->vehicle_info.odometer_m = ecar3_chassis->ccu254_a_.ccu_totalodo_meter * 1000;

    // // 胎压
    // chassis_msgs->tire_pressure.ecar3_ccu_tirepresralarm_st = ecar3_chassis->ccu240_a_.ccu_tirepresralarm_st;

    // 碰撞检测
    chassis_msgs->vehicle_info.front_crash_status = ecar3_chassis->ccu240_a_.ccu_ftcrash_st;
    chassis_msgs->vehicle_info.rear_crash_status = ecar3_chassis->ccu240_a_.ccu_rrcrash_st;

    // // 电池信息
    chassis_msgs->battery_info.range_km = ecar3_chassis->ccu254_a_.ccu_remain_mileage;
    chassis_msgs->battery_info.power_remain = ecar3_chassis->ccu222_a_.ccu_bms_vehbatsoc;
    chassis_msgs->battery_info.battery_temperature = ecar3_chassis->ccu222_a_.ccu_bms_battemp;
    chassis_msgs->battery_info.battery_current = ecar3_chassis->ccu222_a_.ccu_bms_batcurt;
    chassis_msgs->battery_info.battery_voltage = ecar3_chassis->ccu222_a_.ccu_bms_batvolt;
    if (ecar3_chassis->ccu222_a_.ccu_bms_chgst == ECar3Chassis::ChargingStatus::CHARGING)
        chassis_msgs->battery_info.charging_status = uchassis_msgs__msg__BatteryInfo__CHARGING;
    else
        chassis_msgs->battery_info.charging_status = uchassis_msgs__msg__BatteryInfo__NONE;

    // 垃圾箱占用量
    chassis_msgs->rubbish_info.quantity = 0;
    // 垃圾箱剩余量
    chassis_msgs->rubbish_info.box_remain = 0;
    // 垃圾箱举升状态
    chassis_msgs->rubbish_info.lift_status = 0;
    // 垃圾箱举升位置
    chassis_msgs->rubbish_info.lift_position = ecar3_chassis->cbcu535_a_.dustbin_fall_pose_alram;

    // 垃圾箱倾倒状态
    chassis_msgs->rubbish_info.dump_status = 0;
    // 垃圾箱倾倒位置
    chassis_msgs->rubbish_info.dump_position = 0;
    // 垃圾箱门状态
    chassis_msgs->rubbish_info.door_status = 0;
    // 垃圾箱门位置
    chassis_msgs->rubbish_info.door_position = 0;
    // 垃圾箱清洗状态
    chassis_msgs->rubbish_info.dustbin_box_clean_status = 0;

    // 垃圾箱升举状态
    chassis_msgs->rubbish_info.task_request_status.dustbin_lifting_task_status = ecar3_chassis->cbcu537_a_.dustbin_lift_pose_status;
    chassis_msgs->rubbish_info.task_request_status.dustbin_lifting_task_status = ecar3_chassis->cbcu537_a_.dustbin_lift_pose_status;

    // 踏板和方向盘
    chassis_msgs->vehicle_info.throttle_percentage = ecar3_chassis->ccu217_a_.throttle;
    chassis_msgs->vehicle_info.brake_percentage = ecar3_chassis->ccu211_a_.brake_pedal_pos;
    chassis_msgs->vehicle_info.steering_percentage = 0; // unused
    chassis_msgs->vehicle_info.steering_torque_nm = ecar3_chassis->ccu215_a_.steering_wheel_torque_nm;

    // 驻车状态
    if (ecar3_chassis->ccu213_a_.park_status == ECar3Chassis::ParkingStatus::PARKING_STATUS_RELEASED)
        chassis_msgs->vehicle_info.parking_state.value = uchassis_msgs__msg__ParkingState__ELEASE;
    else if (ecar3_chassis->ccu213_a_.park_status == ECar3Chassis::ParkingStatus::PARKING_STATUS_PARK)
        chassis_msgs->vehicle_info.parking_state.value = uchassis_msgs__msg__ParkingState__PARK;
    else if (ecar3_chassis->ccu213_a_.park_status == ECar3Chassis::ParkingStatus::PARKING_STATUS_EMERGENCY)
        chassis_msgs->vehicle_info.parking_state.value = uchassis_msgs__msg__ParkingState__EMERGENCYPARK;
    else
        chassis_msgs->vehicle_info.parking_state.value = uchassis_msgs__msg__ParkingState__EXECUTING;

    // 驾驶模式
    if (ecar3_chassis->ccu240_a_.vehicle_run_mode == ECar3Chassis::CurrentMode::CURRENT_MODE_STANDBY)
        chassis_msgs->vehicle_info.driving_mode.value = uchassis_msgs__msg__DrivingMode__STANDBY;
    else if (ecar3_chassis->ccu240_a_.vehicle_run_mode == ECar3Chassis::CurrentMode::CURRENT_MODE_REMOTE)
        chassis_msgs->vehicle_info.driving_mode.value = uchassis_msgs__msg__DrivingMode__REMOTE;
    else if (ecar3_chassis->ccu240_a_.vehicle_run_mode == ECar3Chassis::CurrentMode::CURRENT_MODE_AUTO)
        chassis_msgs->vehicle_info.driving_mode.value = uchassis_msgs__msg__DrivingMode__AUTO;
    else if (ecar3_chassis->ccu240_a_.vehicle_run_mode == ECar3Chassis::CurrentMode::CURRENT_MODE_EMERGENCY)
        chassis_msgs->vehicle_info.driving_mode.value = uchassis_msgs__msg__DrivingMode__ESTOP;
    else if (ecar3_chassis->ccu240_a_.vehicle_run_mode == ECar3Chassis::CurrentMode::CURRENT_MODE_CLOUD)
        chassis_msgs->vehicle_info.driving_mode.value = uchassis_msgs__msg__DrivingMode__CLOUD;

    // 错误码
    if (ecar3_chassis->ccu212_a_.ccu_brkcmdperd_err || ecar3_chassis->ccu214_a_.ccu_prkcmdperd_err || ecar3_chassis->ccu216_a_.ccu_strcmdperd_err || ecar3_chassis->ccu218_a_.ccu_drvcmdperd_err || ecar3_chassis->ccu220_a_.ccu_bodycmdperd_err)
    {
        chassis_msgs->error_code.value = uchassis_msgs__msg__ErrorCode__CMD_NOT_IN_PERIOD;
    }
    else if (ecar3_chassis->ccu261_a_.ccu_chas12v_err)
    {
        chassis_msgs->error_code.value = uchassis_msgs__msg__ErrorCode__CHASSIS_ERROR;
    }
    else if (false) // 方向盘故障
    {
        chassis_msgs->error_code.value = uchassis_msgs__msg__ErrorCode__CHASSIS_ERROR_ON_STEER;
    }
    else if (ecar3_chassis->ccu212_a_.ccu_ehbovertemp_err || ecar3_chassis->ccu212_a_.ccu_brkpwrsupply_err || ecar3_chassis->ccu212_a_.ccu_ehbbrkcmdabnormal_err)
    {
        chassis_msgs->error_code.value = uchassis_msgs__msg__ErrorCode__CHASSIS_ERROR_ON_BRAKE;
    }
    else if (ecar3_chassis->ccu218_a_.ccu_mcuthortact_err)
    {
        chassis_msgs->error_code.value = uchassis_msgs__msg__ErrorCode__CHASSIS_ERROR_ON_THROTTLE;
    }
    else if (false) // 档位故障
    {
        chassis_msgs->error_code.value = uchassis_msgs__msg__ErrorCode__CHASSIS_ERROR_ON_GEAR;
    }
    else if (ecar3_chassis->ccu212_a_.ccu_ehbcan_err == 0x1 || ecar3_chassis->ccu214_a_.ccu_epbcancom_err == 0x1 || ecar3_chassis->ccu216_a_.eps_cancom_err == 0x1 || ecar3_chassis->ccu240_a_.ccu_canbusoff_st == 0x1)
    {
        chassis_msgs->error_code.value = uchassis_msgs__msg__ErrorCode__CHASSIS_CAN_NOT_IN_PERIOD;
    }
    else
    {
        chassis_msgs->error_code.value = uchassis_msgs__msg__ErrorCode__NO_ERROR;
    }

    // 档位
    if (ecar3_chassis->ccu217_a_.gear == ECar3Chassis::Gear::N && ecar3_chassis->ccu213_a_.park_status == ECar3Chassis::ParkingStatus::PARKING_STATUS_RELEASED)
        chassis_msgs->vehicle_info.gear_location.value = uchassis_msgs__msg__GearPosition__GEAR_NEUTRAL;
    else if (ecar3_chassis->ccu217_a_.gear == ECar3Chassis::Gear::N && ecar3_chassis->ccu213_a_.park_status != ECar3Chassis::ParkingStatus::PARKING_STATUS_RELEASED)
        chassis_msgs->vehicle_info.gear_location.value = uchassis_msgs__msg__GearPosition__GEAR_PARKING;
    else if (ecar3_chassis->ccu217_a_.gear == ECar3Chassis::Gear::D)
        chassis_msgs->vehicle_info.gear_location.value = uchassis_msgs__msg__GearPosition__GEAR_DRIVE;
    else if (ecar3_chassis->ccu217_a_.gear == ECar3Chassis::Gear::R)
        chassis_msgs->vehicle_info.gear_location.value = uchassis_msgs__msg__GearPosition__GEAR_REVERSE;
    else
        chassis_msgs->vehicle_info.gear_location.value = uchassis_msgs__msg__GearPosition__GEAR_INVALID;

    // chassis_msgs->chassis_error_mask = 0; // unused

    // 车辆车灯信号
    if (ecar3_chassis->ccu219_a_.left_turn_light == ECar3Chassis::State::ON)
        chassis_msgs->vehicle_info.signal.turn_signal.value = uchassis_msgs__msg__TurnSignal__TURN_LEFT;
    else if (ecar3_chassis->ccu219_a_.right_turn_light == ECar3Chassis::State::ON)
        chassis_msgs->vehicle_info.signal.turn_signal.value = uchassis_msgs__msg__TurnSignal__TURN_RIGHT;
    else
        chassis_msgs->vehicle_info.signal.turn_signal.value = uchassis_msgs__msg__TurnSignal__TURN_NONE;
    chassis_msgs->vehicle_info.signal.high_beam = static_cast<bool>(ecar3_chassis->ccu219_a_.flood_light);
    chassis_msgs->vehicle_info.signal.low_beam = static_cast<bool>(ecar3_chassis->ccu219_a_.head_lamp);
    chassis_msgs->vehicle_info.signal.horn = static_cast<bool>(ecar3_chassis->ccu219_a_.horn);
    chassis_msgs->vehicle_info.signal.fog_light = static_cast<bool>(ecar3_chassis->ccu219_a_.fog_lamp);
    chassis_msgs->vehicle_info.signal.emergency_light = static_cast<bool>(ecar3_chassis->ccu219_a_.double_flash);

    // 急停原因
    chassis_msgs->vehicle_info.emgcy_stop_reason = ecar3_chassis->ccu240_a_.ccu_vehemgcystop_reason;
    // // 状态建议
    // // chassis_msgs->engage_advice = common_msgs::msg::EngageAdvice(); // unused

    // // 轮速信息 无效
    // chassis_msgs->wheel_speed.is_wheel_spd_rr_valid = static_cast<bool>(ecar3_chassis->ccu252_a_.right_rear_whl_validity);
    // chassis_msgs->wheel_speed.wheel_spd_rr = ecar3_chassis->ccu252_a_.right_rear_whl_speed_kmph / 3.6;
    // chassis_msgs->wheel_speed.is_wheel_spd_rl_valid = static_cast<bool>(ecar3_chassis->ccu252_a_.left_rear_whl_validity);
    // chassis_msgs->wheel_speed.wheel_spd_rl = ecar3_chassis->ccu252_a_.left_rear_whl_speed_kmph / 3.6;
    // chassis_msgs->wheel_speed.is_wheel_spd_fr_valid = static_cast<bool>(ecar3_chassis->ccu251_a_.right_front_whl_validity);
    // chassis_msgs->wheel_speed.wheel_spd_fr = ecar3_chassis->ccu251_a_.right_front_whl_speed_kmph / 3.6;
    // chassis_msgs->wheel_speed.is_wheel_spd_fl_valid = static_cast<bool>(ecar3_chassis->ccu251_a_.left_front_whl_validity);
    // chassis_msgs->wheel_speed.wheel_spd_fl = ecar3_chassis->ccu251_a_.left_front_whl_speed_kmph / 3.6;

    // // 超声波信息
    // // chassis_msgs->ultrasonic_sense = chassis_msgs::msg::UltrasonicSense(); // unused

    // 车辆ID
    std::string vin;
    vin.append({static_cast<char>(ecar3_chassis->ccu2a5_a_.ccu_vehvin_c1)});
    vin.append({static_cast<char>(ecar3_chassis->ccu2a5_a_.ccu_vehvin_c2)});
    vin.append({static_cast<char>(ecar3_chassis->ccu2a5_a_.ccu_vehvin_c3)});
    vin.append({static_cast<char>(ecar3_chassis->ccu2a5_a_.ccu_vehvin_c4)});
    vin.append({static_cast<char>(ecar3_chassis->ccu2a5_a_.ccu_vehvin_c5)});
    vin.append({static_cast<char>(ecar3_chassis->ccu2a5_a_.ccu_vehvin_c6)});
    vin.append({static_cast<char>(ecar3_chassis->ccu2a5_a_.ccu_vehvin_c7)});
    vin.append({static_cast<char>(ecar3_chassis->ccu2a6_a_.ccu_vehvin_c8)});
    vin.append({static_cast<char>(ecar3_chassis->ccu2a6_a_.ccu_vehvin_c9)});
    vin.append({static_cast<char>(ecar3_chassis->ccu2a6_a_.ccu_vehvin_c10)});
    vin.append({static_cast<char>(ecar3_chassis->ccu2a6_a_.ccu_vehvin_c11)});
    std::ostringstream ss;
    ss << std::setw(6) << std::setfill('0') << ecar3_chassis->ccu2a6_a_.ccu_vehvin_d12_17;
    vin.append(ss.str());
    sprintf(chassis_msgs->vehicle_id.vin.data, "%s", vin.c_str());

    // // 纵向加速度
    // chassis_msgs->acceleration_mpss = ecar3_chassis->ccu250_a_.a_mpps;

    // // 车辆转向信息
    // chassis_msgs->wheel_steering.lfwhl_angle_rad = -(ecar3_chassis->ccu215_a_.front_whl_angle_deg * 3.141592 / 180.0);
    // chassis_msgs->wheel_steering.rfwhl_angle_rad = chassis_msgs->wheel_steering.lfwhl_angle_rad;
    // chassis_msgs->wheel_steering.lrwhl_angle_rad = 0;
    // chassis_msgs->wheel_steering.rrwhl_angle_rad = 0;
    // chassis_msgs->wheel_steering.lfwhlspd_radps = ecar3_chassis->ccu215_a_.angular_velocity_degps * 3.141592 / 180.0;
    // chassis_msgs->wheel_steering.rfwhlspd_radps = chassis_msgs->wheel_steering.lfwhlspd_radps;
    // chassis_msgs->wheel_steering.lrwhlspd_radps = 0;
    // chassis_msgs->wheel_steering.rrwhlspd_radps = 0;

    // lift_status
    chassis_msgs->rubbish_info.lift_status = uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    if (std::fabs(chassis_msgs->vehicle_info.speed_mps) < DBL_EPSILON) // 若车辆静止
    {
        if (!ecar3_chassis->cbcu534_a_.left_front_brush_motor_status &&
            !ecar3_chassis->cbcu534_a_.right_front_brush_motor_status &&
            !ecar3_chassis->cbcu534_a_.left_rear_brush_motor_status &&
            !ecar3_chassis->cbcu534_a_.right_rear_brush_motor_status) // 扫刷电机未工作
        {
            if (chassis_msgs->rubbish_info.task_request_status.dustbin_lifting_task_status) // 垃圾箱处于举起状态
            {
                chassis_msgs->rubbish_info.lift_status = uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_COMPLETED;
            }
            else
            {
                chassis_msgs->rubbish_info.lift_status = uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_UNCOMPLETED;
            }
        }
    }
    else // 若车辆未静止
    {
        chassis_msgs->rubbish_info.lift_status = uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    }

    // dump_status
    chassis_msgs->rubbish_info.dump_status = uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    if (std::fabs(chassis_msgs->vehicle_info.speed_mps) < DBL_EPSILON) // 若车辆静止
    {
        if (chassis_msgs->rubbish_info.task_request_status.dustbin_lifting_task_status // 垃圾箱处于举起状态
            && GetTaskRequestStatusBridge()->dustbin_dumping_cleaning_task_status())   // 完成垃圾斗翻转并持续一段时间后
        {
            chassis_msgs->rubbish_info.dump_status = uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_COMPLETED;
        }
        else
        {
            chassis_msgs->rubbish_info.dump_status = uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_UNCOMPLETED;
        }
    }
    else if (chassis_msgs->rubbish_info.task_request_status.dustbin_lifting_task_status == 0)
    {
        chassis_msgs->rubbish_info.dump_status = uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    }
    else // 车辆未静止
    {
        chassis_msgs->rubbish_info.dump_status = uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    }

    // reset_status
    chassis_msgs->rubbish_info.reset_status = uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    if (std::fabs(chassis_msgs->vehicle_info.speed_mps) < DBL_EPSILON) // 若车辆静止
    {
        if (ecar3_chassis->cbcu537_a_.dustbin_lift_pose_status == 0         // 垃圾箱举升位置状态 -- 1:举升
            && ecar3_chassis->cbcu537_a_.dustbin_overturn_pose_status == 0) // 垃圾箱翻转位置状态 -- 1:翻转
        {
            chassis_msgs->rubbish_info.reset_status = uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_COMPLETED;
        }
        else
        {
            chassis_msgs->rubbish_info.reset_status = uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_UNCOMPLETED;
        }
    }
    else // 若车辆未静止
    {
        chassis_msgs->rubbish_info.reset_status = uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    }

    // 清扫状态
    if (ecar3_chassis->cbcu534_a_.left_front_brush_motor_status &&
        ecar3_chassis->cbcu534_a_.right_front_brush_motor_status &&
        ecar3_chassis->cbcu534_a_.left_rear_brush_motor_status &&
        ecar3_chassis->cbcu534_a_.right_rear_brush_motor_status &&
        ecar3_chassis->cbcu534_a_.left_front_brush_drop_status &&
        ecar3_chassis->cbcu534_a_.right_front_brush_drop_status &&
        ecar3_chassis->cbcu534_a_.rear_brush_drop_status &&
        ecar3_chassis->cbcu534_a_.main_brush_drop_status)
    {
        chassis_msgs->sweeper_status.sweeping = true;
    }
    else
    {
        chassis_msgs->sweeper_status.sweeping = false;
    }

    chassis_msgs->sweeper_status.remain_water = ecar3_chassis->cbcu537_a_.remain_water;

    _chassis_msg_wrap.Unlock();
}

void Ecar3RecvMsgManager::UpdateSweeperStatus()
{
    // auto ecar3_chassis = _chassis_detail.GetEcar3Chassis();
    // // SweeperStatusMsg *sweeper_staus_msg = _sweeper_staus_msg_wrap.GetMsg();
    // ChassisMsg *chassis_msgs = _chassis_msg_wrap.GetMsg();

    // auto &ss = sweeper_staus_msg->ecar_threewheel_status;
    // _sweeper_staus_msg_wrap.Lock();

    // ss.left_front_brush_stretch_status = ecar3_chassis->cbcu534_a_.left_front_brush_stretch_status;
    // ss.right_front_brush_stretch_status = ecar3_chassis->cbcu534_a_.right_front_brush_stretch_status;
    // ss.left_front_brush_drop_status = ecar3_chassis->cbcu534_a_.left_front_brush_drop_status;
    // ss.right_front_brush_drop_status = ecar3_chassis->cbcu534_a_.right_front_brush_drop_status;
    // ss.rear_brush_drop_status = ecar3_chassis->cbcu534_a_.rear_brush_drop_status;
    // ss.main_brush_drop_status = ecar3_chassis->cbcu534_a_.main_brush_drop_status;
    // ss.suction_drop_status = ecar3_chassis->cbcu534_a_.suction_drop_status;
    // ss.left_front_brush_motor_status = ecar3_chassis->cbcu534_a_.left_front_brush_motor_status;
    // ss.right_front_brush_motor_status = ecar3_chassis->cbcu534_a_.right_front_brush_motor_status;
    // ss.left_rear_brush_motor_status = ecar3_chassis->cbcu534_a_.left_rear_brush_motor_status;
    // ss.right_rear_brush_motor_status = ecar3_chassis->cbcu534_a_.right_rear_brush_motor_status;
    // ss.main_brush_motor_status = ecar3_chassis->cbcu534_a_.main_brush_motor_status;
    // ss.left_front_brush_expand_dist_mm = ecar3_chassis->cbcu534_a_.left_front_brush_expand_dist_mm;
    // ss.right_front_brush_expand_dist_mm = ecar3_chassis->cbcu534_a_.right_front_brush_expand_dist_mm;
    // ss.dustbin_selfcleaning_water_valve_status = ecar3_chassis->cbcu534_a_.dustbin_clean_water_valve_status;
    // ss.dustbin_pose_status = ecar3_chassis->cbcu537_a_.dustbin_pose_status;
    // ss.dustbin_lock_status = ecar3_chassis->cbcu537_a_.dustbin_lock_status;
    // ss.dustbin_door_status = ecar3_chassis->cbcu537_a_.dustbin_door_status;
    // ss.dustbin_lift_pose_status = ecar3_chassis->cbcu537_a_.dustbin_lift_pose_status;
    // ss.dustbin_overturn_pose_status = ecar3_chassis->cbcu537_a_.dustbin_overturn_pose_status;
    // ss.dustbin_full_status = ecar3_chassis->cbcu537_a_.dustbin_full_status;
    // ss.left_front_brush_stretch_mtr_err = ecar3_chassis->cbcu535_a_.left_front_brush_stretch_mtr_err;
    // ss.right_front_brush_stretch_mtr_err = ecar3_chassis->cbcu535_a_.right_front_brush_stretch_mtr_err;
    // ss.left_front_brush_drop_mtr_fault_err = ecar3_chassis->cbcu535_a_.left_front_brush_drop_mtr_fault_err;
    // ss.right_front_brush_drop_mtr_err = ecar3_chassis->cbcu535_a_.right_front_brush_drop_mtr_err;
    // ss.rear_brush_drop_mtr_err = ecar3_chassis->cbcu535_a_.rear_brush_drop_mtr_err;
    // ss.main_brush_drop_mtr_err = ecar3_chassis->cbcu535_a_.main_brush_drop_mtr_err;
    // ss.suction_drop_mtr_err = ecar3_chassis->cbcu535_a_.suction_drop_mtr_err;
    // ss.front_fender_mtr_err = ecar3_chassis->cbcu535_a_.front_fender_mtr_err;
    // ss.dustbin_door_openclose_mtr_err = ecar3_chassis->cbcu535_a_.dustbin_door_openclose_mtr_err;
    // ss.dustbin_door_lock_mtr_err = ecar3_chassis->cbcu535_a_.dustbin_door_lock_mtr_err;
    // ss.main_brush_mtr_err = ecar3_chassis->cbcu535_a_.main_brush_mtr_err;
    // ss.left_front_brush_mtr_err = ecar3_chassis->cbcu535_a_.left_front_brush_mtr_err;
    // ss.right_front_brush_mtr_err = ecar3_chassis->cbcu535_a_.right_front_brush_mtr_err;
    // ss.left_rear_brush_mtr_err = ecar3_chassis->cbcu535_a_.left_rear_brush_mtr_err;
    // ss.right_rear_brush_mtr_err = ecar3_chassis->cbcu535_a_.right_rear_brush_mtr_err;
    // ss.dustbin_selfcleaning_water_valve_err = ecar3_chassis->cbcu535_a_.dustbin_selfcleaning_water_valve_err;
    // ss.wireless_chg_coupling_status = ecar3_chassis->cdcu227_a_.wireless_chg_coupling_status;
    // ss.wireless_charging_status = ecar3_chassis->cdcu227_a_.wireless_charging_status;
    // ss.brush_water_valve_status = ecar3_chassis->cbcu534_a_.brush_water_valve_status;
    // ss.suction_dust_fall_valve_status = ecar3_chassis->cbcu534_a_.suction_dust_fall_valve_status;
    // ss.dustbin_dust_fall_valve_status = ecar3_chassis->cbcu534_a_.dustbin_dust_fall_valve_status;
    // ss.remain_water = ecar3_chassis->cbcu537_a_.remain_water;

    // // sweeping
    // if (ss.left_front_brush_motor_status && ss.right_front_brush_motor_status && ss.left_rear_brush_motor_status && ss.right_rear_brush_motor_status && ss.left_front_brush_drop_status && ss.right_front_brush_drop_status && ss.rear_brush_drop_status && ss.main_brush_drop_status)
    // {
    //     sweeper_staus_msg->sweeping = true;
    // }
    // else
    // {
    //     sweeper_staus_msg->sweeping = false;
    // }

    // _sweeper_staus_msg_wrap.Unlock();

    // _chassis_msg_wrap.Lock();
    // // lift_status
    // chassis_msgs->rubbish_info.lift_status = chassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    // if (std::fabs(chassis_msgs->speed_mps) < DBL_EPSILON) // 若车辆静止
    // {
    //     // if (!ss.left_front_brush_motor_status && !ss.right_front_brush_motor_status && !ss.left_rear_brush_motor_status && !ss.right_rear_brush_motor_status) // 扫刷电机未工作
    //     {
    //         if (chassis_msgs->rubbish_info.task_request_status.dustbin_lifting_task_status) // 垃圾箱处于举起状态
    //         {
    //             chassis_msgs->rubbish_info.lift_status = chassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_COMPLETED;
    //         }
    //         else
    //         {
    //             chassis_msgs->rubbish_info.lift_status = chassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_UNCOMPLETED;
    //         }
    //     }
    // }
    // else // 若车辆未静止
    // {
    //     chassis_msgs->rubbish_info.lift_status = chassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    // }

    // // dump_status
    // chassis_msgs->rubbish_info.dump_status = chassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    // if (std::fabs(chassis_msgs->speed_mps) < DBL_EPSILON) // 若车辆静止
    // {
    //     if (chassis_msgs->rubbish_info.task_request_status.dustbin_lifting_task_status // 垃圾箱处于举起状态
    //         && GetTaskRequestStatusBridge()->dustbin_dumping_cleaning_task_status())   // 完成垃圾斗翻转并持续一段时间后
    //     {
    //         chassis_msgs->rubbish_info.dump_status = chassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_COMPLETED;
    //     }
    //     else
    //     {
    //         chassis_msgs->rubbish_info.dump_status = chassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_UNCOMPLETED;
    //     }
    // }
    // else if (chassis_msgs->rubbish_info.task_request_status.dustbin_lifting_task_status == 0)
    // {
    //     chassis_msgs->rubbish_info.dump_status = chassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    // }
    // else // 车辆未静止
    // {
    //     chassis_msgs->rubbish_info.dump_status = chassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    // }

    // // reset_status
    // chassis_msgs->rubbish_info.reset_status = chassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    // if (std::fabs(chassis_msgs->speed_mps) < DBL_EPSILON) // 若车辆静止
    // {
    //     if (sweeper_staus_msg->ecar_threewheel_status.dustbin_lift_pose_status == 0         // 垃圾箱举升位置状态 -- 1:举升
    //         && sweeper_staus_msg->ecar_threewheel_status.dustbin_overturn_pose_status == 0) // 垃圾箱翻转位置状态 -- 1:翻转
    //     {
    //         chassis_msgs->rubbish_info.reset_status = chassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_COMPLETED;
    //     }
    //     else
    //     {
    //         chassis_msgs->rubbish_info.reset_status = chassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_UNCOMPLETED;
    //     }
    // }
    // else // 若车辆未静止
    // {
    //     chassis_msgs->rubbish_info.reset_status = chassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED;
    // }

    // _chassis_msg_wrap.Unlock();
}
