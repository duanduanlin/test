/*
 * @Author: hanson
 * @Date: 2024-08-23 17:27:19
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-12 16:55:52
 * @Description:
 * @FilePath: \ucanbus\src\msg_wrap\ControlMsgWrap.cpp
 */
#include <sstream>
#include "msg_wrap/ControlMsgWrap.hpp"

ControlMsgWrap::ControlMsgWrap(/* args */) : BaseMsgWrap(ControlCmdMsgType)
{
    Setup();
}

ControlMsgWrap::~ControlMsgWrap()
{
}

void ControlMsgWrap::Setup()
{
}

void ControlMsgWrap::Update()
{
    ControlCmdMsg *control_msgs = GetMsg();
    memcpy(&_chassis_cmd, &control_msgs->chassis_cmd, sizeof(ChassisCmdMsg));
    memcpy(&_sweeper_cmd, &control_msgs->sweeper_cmd, sizeof(SweeperCmdMsg));
    memcpy(&_light_cmd, &control_msgs->light_cmd, sizeof(LightCmdMsg));
    memcpy(&_audio_cmd, &control_msgs->audio_cmd, sizeof(AudioCmdMsg));
}

void ControlMsgWrap::Reset()
{
    ControlCmdMsg *control_msgs = GetMsg();
    Lock();
    memset(control_msgs, 0, sizeof(ControlCmdMsg));
    Unlock();
}

std::string ControlMsgWrap::GetPrintableStr()
{
    std::stringstream ss;
    ControlCmdMsg *control_msgs = GetMsg();
    // ss << "f_id:" << control_msgs->ros_header.frame_id << " | ";
    ss << "di_mod:" << control_msgs->chassis_cmd.drivingmode << " ";
    ss << "c_mod:" << control_msgs->chassis_cmd.controlmode << " ";
    ss << "dr_mod:" << control_msgs->chassis_cmd.drivemode << " ";
    ss << "g_cmd:" << control_msgs->chassis_cmd.gear_cmd << " ";
    ss << "fa_rad:" << control_msgs->chassis_cmd.front_angle_rad << " ";
    ss << "ra_rad:" << control_msgs->chassis_cmd.rear_angle_rad << " ";
    ss << "lv_mps:" << control_msgs->chassis_cmd.linear_v_mps << " ";
    ss << "gp_cmd:" << control_msgs->chassis_cmd.gas_pedal_cmd << " ";
    ss << "bp_cmd:" << control_msgs->chassis_cmd.brake_pedal_cmd << " | ";
    ss << "swp:" << control_msgs->sweeper_cmd.sweeping << " ";
    ss << "bm_cmd:" << control_msgs->sweeper_cmd.blow_motor_cmd << " ";
    ss << "sb_cmd:" << control_msgs->sweeper_cmd.sweep_brush_cmd << " ";
    ss << "wp_cmd:" << control_msgs->sweeper_cmd.water_pump_cmd << " ";
    ss << "bwp_cmd:" << control_msgs->sweeper_cmd.blow_water_pump_cmd << " ";
    ss << "swp_cmd:" << control_msgs->sweeper_cmd.suction_water_pump_cmd << " ";
    ss << "jp_cmd:" << control_msgs->sweeper_cmd.jaw_plate_cmd << " ";
    ss << "lfbtad_mm:" << control_msgs->sweeper_cmd.left_front_brush_tgt_abd_dist_mm << " ";
    ss << "rfbtad_mm:" << control_msgs->sweeper_cmd.right_front_brush_tgt_abd_dist_mm << " | ";
    ss << "hl_cmd:" << control_msgs->light_cmd.head_lamp_cmd << " ";
    ss << "fl_cmd:" << control_msgs->light_cmd.fog_lamp_cmd << " ";
    ss << "cl_cmd:" << control_msgs->light_cmd.caution_lamp_cmd << " ";
    ss << "tl_cmd:" << control_msgs->light_cmd.turn_light_cmd << " | ";
    ss << "ad_cmd:" << control_msgs->audio_cmd.audio_cmd << " | ";
    ss << "ho_cmd:" << control_msgs->audio_cmd.horn_cmd << " | ";
    return ss.str();
}
