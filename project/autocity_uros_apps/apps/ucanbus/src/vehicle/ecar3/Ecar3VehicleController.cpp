/*
 * @Author: hanson
 * @Date: 2024-08-28 15:59:38
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-20 17:50:40
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\src\vehicle\ecar3\Ecar3VehicleController.cpp
 */
#include "vehicle/ecar3/Ecar3VehicleController.hpp"
#include "trace/LogTrace.hpp"
#include "param/ParamHelper.hpp"

int Ecar3VehicleController::Setup(std::unordered_map<uint32_t, BaseProtocol *> &protocol_map, ControlMsgWrap *msg, ChassisDetail *chassis)
{
    LOG_INFO("setup vehicle controller\r\n");
    if (msg == nullptr || chassis == nullptr)
    {
        LOG_ERRO("invalid param\r\n");
        return -1;
    }
    _control_cmd_msg = msg;
    _chassis_detail = chassis;

    _dump_time_threshold_s = GetParamWithDefault<double>("dump_time_threshold_s", 10.0);
    _control_timeout_ms = GetParamWithDefault<double>("control_timeout_ms", 500.0);

    _drive_118 = static_cast<RDCU118 *>(protocol_map[0x118]);
    _body_119 = static_cast<RDCU119 *>(protocol_map[0x119]);
    _sweep_154 = static_cast<RDCU154 *>(protocol_map[0x154]);
    _sweep2_155 = static_cast<RDCU155 *>(protocol_map[0x155]);
    _audio_6f0 = static_cast<RDCU6F0 *>(protocol_map[0x6f0]);

    if (!_drive_118 || !_body_119 || !_sweep_154 || !_sweep2_155 || !_audio_6f0)
    {
        LOG_ERRO("setup vehicle controller failed\r\n");
        return -1;
    }
    return 0;
}

int Ecar3VehicleController::UpdateControlCmd()
{
    _control_cmd_msg->Update();

    _update_chassis();
    _update_mode();
    _update_light();
    _update_gear();
    _update_steer();
    _update_drive_select();
    _update_sweep();
    _update_audio();
    _update_vertical();
    _update_dump_task();
    return 0;
}

void Ecar3VehicleController::_update_chassis()
{
    auto ecar3_chassis = _chassis_detail->GetEcar3Chassis();
    _current_mode = ecar3_chassis->ccu240_a_.vehicle_run_mode;
    _current_drive_direction = ecar3_chassis->ccu250_a_.run_direction;
    _current_acc_mpps = ecar3_chassis->ccu250_a_.a_mpps;
    _dustbin_overturn_pose_status = ecar3_chassis->cbcu537_a_.dustbin_overturn_pose_status;
    _dustbin_lift_pose_status = ecar3_chassis->cbcu537_a_.dustbin_lift_pose_status;
}

void Ecar3VehicleController::_update_mode()
{
    bool is_drive_cloud = false;
    auto chassis_cmd = _control_cmd_msg->GetChassisCmd();
    LOG_INFO_EVERY_SECOND("request mode:%d\r\n", chassis_cmd.drivingmode);
    if (chassis_cmd.drivingmode == ECar3Chassis::CurrentMode::CURRENT_MODE_CLOUD)
    {
        is_drive_cloud = true;
    }

    if ((_current_mode == ECar3Chassis::CurrentMode::CURRENT_MODE_CLOUD) &&
        (_control_cmd_msg->Elapsed() > _control_timeout_ms))
    {
        LOG_INFO_EVERY_SECOND("control msg timeout,elapsed:%f\r\n", _control_cmd_msg->Elapsed());
        _control_cmd_msg->Reset();
        is_drive_cloud = false;
    }

    std::string current_mode_s;
    switch (_current_mode)
    {
    case ECar3Chassis::CurrentMode::CURRENT_MODE_STANDBY:
        current_mode_s = "Standby";
        break;
    case ECar3Chassis::CurrentMode::CURRENT_MODE_REMOTE:
        current_mode_s = "Remote";
        break;
    case ECar3Chassis::CurrentMode::CURRENT_MODE_AUTO:
        current_mode_s = "Auto";
        break;
    case ECar3Chassis::CurrentMode::CURRENT_MODE_EMERGENCY:
        current_mode_s = "Emergency";
        break;
    case ECar3Chassis::CurrentMode::CURRENT_MODE_CLOUD:
        current_mode_s = "Cloud";
        break;
    default:
        break;
    }
    LOG_INFO_EVERY_SECOND("current mode:%s\r\n", current_mode_s.c_str());
    static bool run_once_flag = true;

    // 第一次开机处于待机模式，等待控制节点请求进入远程模式
    if (_current_mode == ECar3Chassis::CurrentMode::CURRENT_MODE_STANDBY)
    {
        if (is_drive_cloud)
        {
            if (run_once_flag)
            {
                // 第一次进入待机模式的时候，重置信号
                run_once_flag = false;
                _drive_118->SetActive(RDCU118::Active::ACTIVE_DISABLE);
                LOG_INFO("first request to cloud,reset signal\r\n");
            }
            else
            {
                _drive_118->SetActive(RDCU118::Active::ACTIVE_ENABLE);
                LOG_INFO_EVERY_SECOND("request enter cloud from standby\r\n");
            }
        }
        else
        {
            _drive_118->SetActive(RDCU118::Active::ACTIVE_DISABLE);
            LOG_INFO_EVERY_SECOND("now we at standby\r\n");
        }
    }
    else if (_current_mode == ECar3Chassis::CurrentMode::CURRENT_MODE_AUTO)
    {
        if (is_drive_cloud)
        {
            _drive_118->SetActive(RDCU118::Active::ACTIVE_ENABLE);
            LOG_INFO_EVERY_SECOND("request enter cloud from auto\r\n");
        }
        else
        {
            _drive_118->SetActive(RDCU118::Active::ACTIVE_DISABLE);
            LOG_INFO_EVERY_SECOND("now we at auto\r\n");
        }
    }
    else if (_current_mode == ECar3Chassis::CurrentMode::CURRENT_MODE_CLOUD)
    {
        if (is_drive_cloud)
        {
            _drive_118->SetActive(RDCU118::Active::ACTIVE_ENABLE);
            LOG_INFO_EVERY_SECOND("already enter cloud\r\n");
        }
        else
        {
            _drive_118->SetActive(RDCU118::Active::ACTIVE_DISABLE);
            LOG_INFO_EVERY_SECOND("try to leave cloud\r\n");
        }
    }
    else if (_current_mode == ECar3Chassis::CurrentMode::CURRENT_MODE_REMOTE)
    {
        _drive_118->SetActive(RDCU118::Active::ACTIVE_DISABLE);
        LOG_INFO_EVERY_SECOND("now we at remote\r\n");
    }

    if (_current_mode != ECar3Chassis::CurrentMode::CURRENT_MODE_STANDBY)
    {
        run_once_flag = true;
    }
}

void Ecar3VehicleController::_update_light()
{
    // LightCMD
    auto light_cmd = _control_cmd_msg->GetLightCmd();
    auto chassis_cmd = _control_cmd_msg->GetChassisCmd();

    // 转向指示灯
    if (light_cmd.turn_light_cmd == ucontrol_msgs__msg__LightCMD__TURN_LEFT)
    {
        _body_119->SetLeftTurnLampCmd(1);
        _body_119->SetRightTurnLampCmd(0);
        _body_119->SetDoubleFlashLampCmd(0);
    }
    else if (light_cmd.turn_light_cmd == ucontrol_msgs__msg__LightCMD__TURN_RIGHT)
    {
        _body_119->SetLeftTurnLampCmd(0);
        _body_119->SetRightTurnLampCmd(1);
        _body_119->SetDoubleFlashLampCmd(0);
    }
    else if (light_cmd.turn_light_cmd == ucontrol_msgs__msg__LightCMD__EMERGENCY_LIGHT)
    {
        _body_119->SetLeftTurnLampCmd(0);
        _body_119->SetRightTurnLampCmd(0);
        _body_119->SetDoubleFlashLampCmd(1);
    }
    else if (light_cmd.turn_light_cmd == ucontrol_msgs__msg__LightCMD__AUTO)
    {
        LOG_INFO_EVERY_SECOND("auto light:on\r\n");
        if (chassis_cmd.front_angle_rad > 0)
        {
            _body_119->SetLeftTurnLampCmd(1);
            _body_119->SetRightTurnLampCmd(0);
            _body_119->SetDoubleFlashLampCmd(0);
        }
        else if (chassis_cmd.front_angle_rad < 0)
        {
            _body_119->SetLeftTurnLampCmd(0);
            _body_119->SetRightTurnLampCmd(1);
            _body_119->SetDoubleFlashLampCmd(0);
        }
        else
        {
            _body_119->SetLeftTurnLampCmd(0);
            _body_119->SetRightTurnLampCmd(0);
            _body_119->SetDoubleFlashLampCmd(0);
        }
    }
    else
    {
        _body_119->SetLeftTurnLampCmd(0);
        _body_119->SetRightTurnLampCmd(0);
        _body_119->SetDoubleFlashLampCmd(0);
    }

    // 倒车灯
    if (light_cmd.back_light_cmd == ECar3Chassis::BodyControlType::BODY_CONTROL_AUTO)
    {
        if (_current_drive_direction == ECar3Chassis::VehicleRunDir::VEHICLE_RUN_DIR_BACK)
        {
            LOG_INFO_EVERY_SECOND("Astern please pay attention\r\n");
            _body_119->SetBackLampCmd(ECar3Chassis::BodyControlType::BODY_CONTROL_ON);
        }
        else
        {
            _body_119->SetBackLampCmd(ECar3Chassis::BodyControlType::BODY_CONTROL_OFF);
        }
    }
    else
    {
        _body_119->SetBackLampCmd(light_cmd.back_light_cmd);
    }

    // 制动灯
    if (_current_acc_mpps < 0)
    {
        _body_119->SetBrakeLampCmd(ECar3Chassis::BodyControlType::BODY_CONTROL_ON);
    }
    else
    {
        _body_119->SetBrakeLampCmd(ECar3Chassis::BodyControlType::BODY_CONTROL_OFF);
    }

    // 前大灯
    if (light_cmd.head_lamp_cmd == ECar3Chassis::BodyControlType::BODY_CONTROL_AUTO)
    {
        // todo
    }
    else
    {
        _body_119->SetHeadLampCmd(light_cmd.head_lamp_cmd);
    }
    // 雾灯
    _body_119->SetFogLampCmd(light_cmd.fog_lamp_cmd);
}

void Ecar3VehicleController::_update_vertical()
{
    auto chassis_cmd = _control_cmd_msg->GetChassisCmd();
    _drive_118->SetTgtBrk(chassis_cmd.brake_pedal_cmd);
    if (chassis_cmd.drivemode == ECar3Chassis::ControlDriveSelection::CONTROL_DRIVE_SELECTION_PEDAL)
    {
        _drive_118->SetTgtThrottle(chassis_cmd.gas_pedal_cmd);
        LOG_INFO_EVERY_SECOND("tgt_throttle[pedal]:%f,tgt_brk:%f\r\n", chassis_cmd.gas_pedal_cmd, chassis_cmd.brake_pedal_cmd);
    }
    else
    {
        _drive_118->SetTgtThrottle((chassis_cmd.linear_v_mps * 3.6) / 30);
        LOG_INFO_EVERY_SECOND("tgt_throttle[speed]:%f,tgt_brk:%f\r\n", (chassis_cmd.linear_v_mps * 3.6) / 30, chassis_cmd.brake_pedal_cmd);
    }
}

void Ecar3VehicleController::_update_gear()
{
    auto chassis_cmd = _control_cmd_msg->GetChassisCmd();
    LOG_INFO_EVERY_SECOND("gear:%d\r\n", chassis_cmd.gear_cmd);
    switch (chassis_cmd.gear_cmd)
    {
    case ECar3Chassis::ControlGear::CONTROL_GEAR_P:
        _drive_118->SetTgtThrottle(0);
        _drive_118->SetTgtGear(RDCU118::RdcuTargetGear::RDCU_TARGET_GEAR_N);
        _drive_118->SetParkEnable(1);
        break;
    case ECar3Chassis::ControlGear::CONTROL_GEAR_R:
        _drive_118->SetParkEnable(0);
        _drive_118->SetTgtGear(RDCU118::RdcuTargetGear::RDCU_TARGET_GEAR_R);
        break;
    case ECar3Chassis::ControlGear::CONTROL_GEAR_N:
        _drive_118->SetParkEnable(0);
        _drive_118->SetTgtGear(RDCU118::RdcuTargetGear::RDCU_TARGET_GEAR_N);
        break;
    case ECar3Chassis::ControlGear::CONTROL_GEAR_D:
        _drive_118->SetParkEnable(0);
        _drive_118->SetTgtGear(RDCU118::RdcuTargetGear::RDCU_TARGET_GEAR_D);
        break;
    default:
        _drive_118->SetTgtGear(RDCU118::RdcuTargetGear::RDCU_TARGET_GEAR_N);
        break;
    }
}

void Ecar3VehicleController::_update_steer()
{
    auto chassis_cmd = _control_cmd_msg->GetChassisCmd();
    double str_angle = chassis_cmd.front_angle_rad / 3.141592 * 180.0;
    LOG_INFO_EVERY_SECOND("str_angle:%f\r\n", str_angle);
    _drive_118->SetTgtStrAngle(str_angle);
}

void Ecar3VehicleController::_update_drive_select()
{
    auto chassis_cmd = _control_cmd_msg->GetChassisCmd();
    _drive_118->SetDriveCtrlMode(chassis_cmd.drivemode);
    LOG_INFO_EVERY_SECOND("drivemode:%d\r\n", chassis_cmd.drivemode);
}

void Ecar3VehicleController::_update_sweep()
{
    auto sweeper_cmd = _control_cmd_msg->GetSweeperCmd();
    // 是否清扫
    if (sweeper_cmd.sweeping)
    {
        _sweep_154->SetTgtSweepMode(RDCU154::RdcuTargetSweepMode::RDCU_TGT_SWEEP_MODE_SWEEP);
        _sweep_154->SetSweepCmd(RDCU154::RdcuSweepCommand::RDCU_SWEEP_CMD_ON);
        _sweep2_155->SetLeftFrontBrushMotorCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdON);
        _sweep2_155->SetRightFrontBrushMotorCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdON);
        _sweep2_155->SetLeftRearBrushMotorCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdON);
        _sweep2_155->SetRightRearBrushMotorCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdON);
        _sweep2_155->SetLeftFrontBrushMotorModeCmd(RDCU154::FanCtrlModeSel::GearCtrlMode);
        _sweep2_155->SetRightFrontBrushMotorModeCmd(RDCU154::FanCtrlModeSel::GearCtrlMode);
        _sweep2_155->SetLeftFrontBrushMotorGearCmd(RDCU154::FanSpdGearSel::Medium_Speed_Gear);
        _sweep2_155->SetRightFrontBrushMotorGearCmd(RDCU154::FanSpdGearSel::Medium_Speed_Gear);
    }
    else
    {
        _sweep_154->SetTgtSweepMode(RDCU154::RdcuTargetSweepMode::RDCU_TGT_SWEEP_MODE_DRIVE);
        _sweep_154->SetSweepCmd(RDCU154::RdcuSweepCommand::RDCU_SWEEP_CMD_OFF);
        _sweep2_155->SetLeftFrontBrushMotorCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdOFF);
        _sweep2_155->SetRightFrontBrushMotorCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdOFF);
        _sweep2_155->SetLeftRearBrushMotorCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdOFF);
        _sweep2_155->SetRightRearBrushMotorCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdOFF);
        _sweep2_155->SetLeftFrontBrushMotorModeCmd(RDCU154::FanCtrlModeSel::GearCtrlMode);
        _sweep2_155->SetRightFrontBrushMotorModeCmd(RDCU154::FanCtrlModeSel::GearCtrlMode);
        _sweep2_155->SetLeftFrontBrushMotorGearCmd(RDCU154::FanSpdGearSel::Disable);
        _sweep2_155->SetRightFrontBrushMotorGearCmd(RDCU154::FanSpdGearSel::Disable);
    }

    // 风机控制
    if (sweeper_cmd.blow_motor_cmd == ucontrol_msgs__msg__SweeperCMD__TURN_OFF)
    {
        _sweep2_155->SetFanCmd(ECar3Chassis::State::OFF);
        _sweep2_155->SetFanModeCmd(RDCU154::FanCtrlModeSel::GearCtrlMode);
        _sweep2_155->SetFanGearCmd(RDCU154::FanSpdGearSel::Disable);
    }
    else if (sweeper_cmd.blow_motor_cmd == ucontrol_msgs__msg__SweeperCMD__TURN_ON)
    {
        _sweep2_155->SetFanCmd(ECar3Chassis::State::ON);
        _sweep2_155->SetFanModeCmd(RDCU154::FanCtrlModeSel::GearCtrlMode);
        _sweep2_155->SetFanGearCmd(RDCU154::FanSpdGearSel::Low_Speed_Gear);
    }
    else if (sweeper_cmd.blow_motor_cmd == ucontrol_msgs__msg__SweeperCMD__LOW_SPEED)
    {
        _sweep2_155->SetFanCmd(ECar3Chassis::State::ON);
        _sweep2_155->SetFanModeCmd(RDCU154::FanCtrlModeSel::GearCtrlMode);
        _sweep2_155->SetFanGearCmd(RDCU154::FanSpdGearSel::Low_Speed_Gear);
    }
    else if (sweeper_cmd.blow_motor_cmd == ucontrol_msgs__msg__SweeperCMD__MEDIUM_SPEED)
    {
        _sweep2_155->SetFanCmd(ECar3Chassis::State::ON);
        _sweep2_155->SetFanModeCmd(RDCU154::FanCtrlModeSel::GearCtrlMode);
        _sweep2_155->SetFanGearCmd(RDCU154::FanSpdGearSel::Medium_Speed_Gear);
    }
    else if (sweeper_cmd.blow_motor_cmd == ucontrol_msgs__msg__SweeperCMD__HIGH_SPEED)
    {
        _sweep2_155->SetFanCmd(ECar3Chassis::State::ON);
        _sweep2_155->SetFanModeCmd(RDCU154::FanCtrlModeSel::GearCtrlMode);
        _sweep2_155->SetFanGearCmd(RDCU154::FanSpdGearSel::High_Speed_Gear);
    }

    // 扫刷控制 //没有

    // 喷水控制
    if (sweeper_cmd.water_pump_cmd == 0)
        _sweep_154->SetBrushWaterValveCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdOFF);
    else
        _sweep_154->SetBrushWaterValveCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdON);
    // 垃圾箱喷水控制
    if (sweeper_cmd.blow_water_pump_cmd == 0)
        _sweep_154->SetDustbinDustFallValveCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdOFF);
    else
        _sweep_154->SetDustbinDustFallValveCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdON);
    // 吸盘喷水控制
    if (sweeper_cmd.suction_water_pump_cmd == 0)
        _sweep_154->SetSuctionDustFallValveCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdOFF);
    else
        _sweep_154->SetSuctionDustFallValveCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdON);
    // 鄂板开启控制
    if (sweeper_cmd.jaw_plate_cmd == 0)
        _sweep_154->SetFrontFenderCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdOFF);
    else
        _sweep_154->SetFrontFenderCmd(RDCU154::RdcuSwitchCmd::RDCU_SwitchCmdON);
    // 左扫刷伸出距离
    // 右扫刷伸出距离
    double left_front_brush_tgt_abd_dist_mm = sweeper_cmd.left_front_brush_tgt_abd_dist_mm < 10 ? 0 : sweeper_cmd.left_front_brush_tgt_abd_dist_mm;
    double right_front_brush_tgt_abd_dist_mm = sweeper_cmd.right_front_brush_tgt_abd_dist_mm < 10 ? 0 : sweeper_cmd.right_front_brush_tgt_abd_dist_mm;
    _sweep_154->SetLeftFrontBrushAbdDist(left_front_brush_tgt_abd_dist_mm);
    _sweep_154->SetRightFrontBrushAbdDist(right_front_brush_tgt_abd_dist_mm);
    // L
    if (left_front_brush_tgt_abd_dist_mm < 10)
    {
        // LOG_WARN("左伸展指令<10mm,执行回缩!");
        _sweep_154->SetLeftFrontBrushExtensionRodCmd(RDCU154::RdcuBrushAbdCmdType::RDCU_BRUSH_ABD_CMD_RETRACT);
    }
    else
        _sweep_154->SetLeftFrontBrushExtensionRodCmd(RDCU154::RdcuBrushAbdCmdType::RDCU_BRUSH_ABD_CMD_STRETCH);
    // R
    if (right_front_brush_tgt_abd_dist_mm < 10)
    {
        // LOG_WARN("右伸展指令<10mm,执行回缩!");
        _sweep_154->SetRightFrontBrushExtensionRodCmd(RDCU154::RdcuBrushAbdCmdType::RDCU_BRUSH_ABD_CMD_RETRACT);
    }
    else
        _sweep_154->SetRightFrontBrushExtensionRodCmd(RDCU154::RdcuBrushAbdCmdType::RDCU_BRUSH_ABD_CMD_STRETCH);
}

void Ecar3VehicleController::_update_audio()
{
    auto audio_cmd = _control_cmd_msg->GetAudioCmd();
    LOG_INFO_EVERY_SECOND("audio_cmd:%d,audio_num:%d,horn_cmd:%d\r\n", audio_cmd.audio_cmd, audio_cmd.audio_num, audio_cmd.horn_cmd);

    // 音频
    if (audio_cmd.audio_cmd == ucontrol_msgs__msg__AudioCMD__AUDIO_CMD_PAUSE)
    {
        LOG_INFO_EVERY_SECOND("audio pause\r\n");
        _audio_6f0->SetPlayAudioPause(RDCU6F0::AudioControlCmd::AUDIO_CMD_STOP);
        _audio_6f0->SetPlayAudioMode(RDCU6F0::AudioControlMode::AUDIO_MODE_DISABLE);
    }
    else if (audio_cmd.audio_cmd == ucontrol_msgs__msg__AudioCMD__AUDIO_CMD_PLAY)
    {
        LOG_INFO_EVERY_SECOND("audio play,num:%d,volume:%d \r\n", audio_cmd.audio_num, audio_cmd.audio_volume);
        _audio_6f0->SetPlayAudioPause(RDCU6F0::AudioControlCmd::AUDIO_CMD_PLAY);
        _audio_6f0->SetPlayAudioMode(RDCU6F0::AudioControlMode::AUDIO_MODE_SINGLE);
        _audio_6f0->SetPlayAudioNum(audio_cmd.audio_num);
        _audio_6f0->SetPlayAudioVolume(audio_cmd.audio_volume);
    }
    // 喇叭
    _body_119->SetHornCmd(audio_cmd.horn_cmd);
}

void Ecar3VehicleController::_update_dump_task()
{
    auto sweeper_cmd = _control_cmd_msg->GetSweeperCmd();
    const int16_t task_request = sweeper_cmd.task_request;
    std::string task_request_s = "";

    _sweep_154->SetDustbinCleanWaterValveCmd(RDCU154::RdcuWaterValveControlType::RDCU_WATER_VALVE_CTRL_CLOSE);
    _sweep_154->SetDustbinDustFallValveCmd(RDCU154::RdcuWaterValveControlType::RDCU_WATER_VALVE_CTRL_CLOSE);
    if (task_request != ucontrol_msgs__msg__SweeperCMD__DUSTBIN_DUMPING_CLEANING_TASK)
    {
        _dump_finished = false;
        _dump_time.Reset(); // 重新记录倒垃圾时间
        GetTaskRequestStatusBridge()->set_dustbin_dumping_cleaning_task_status(0);
    }
    if (task_request == ucontrol_msgs__msg__SweeperCMD__NONE)
    {
        _dump_task_none();
        task_request_s = "None";
        GetTaskRequestStatusBridge()->set_dustbin_dumping_cleaning_task_status(0);
    }
    else if (task_request == ucontrol_msgs__msg__SweeperCMD__DUSTBIN_LIFTING_TASK)
    {
        _dump_task_lift();
        task_request_s = "Lifting";
        GetTaskRequestStatusBridge()->set_dustbin_dumping_cleaning_task_status(0);
    }
    else if (task_request == ucontrol_msgs__msg__SweeperCMD__DUSTBIN_DUMPING_CLEANING_TASK)
    {
        _dump_task_dumping_and_cleaning();
        task_request_s = "Dumping_Cleaning";
    }
    else if (task_request == ucontrol_msgs__msg__SweeperCMD__DUSTBIN_RESET_TASK)
    {
        _dump_task_reset();
        task_request_s = "Reset";
        GetTaskRequestStatusBridge()->set_dustbin_dumping_cleaning_task_status(0);
    }
    LOG_INFO_EVERY_SECOND("dump task:%s lift pose status:%d dustbin overturn pose status:%d\r\n", task_request_s.c_str(), _dustbin_lift_pose_status, _dustbin_overturn_pose_status);
}

void Ecar3VehicleController::_dump_task_none()
{
    _sweep2_155->SetDustbinLiftdropCmd(RDCU155::RdcuDustbinLiftDropCmdType::RDCU_DUSTBIN_LIFTDROP_CMD_INVALID);
    _sweep2_155->SetDustbinOverturnCmd(RDCU155::RdcuDustbinOverTurnCmdType::RDCU_DUSTBIN_OVERTURN_CMD_INVALID);
}

void Ecar3VehicleController::_dump_task_lift()
{
    _sweep2_155->SetDustbinLiftdropCmd(RDCU155::RdcuDustbinLiftDropCmdType::RDCU_DUSTBIN_LIFTDROP_CMD_LIFT);
    _sweep2_155->SetDustbinOverturnCmd(RDCU155::RdcuDustbinOverTurnCmdType::RDCU_DUSTBIN_OVERTURN_CMD_INVALID);
}

void Ecar3VehicleController::_dump_task_dumping_and_cleaning()
{
    // 举升无效
    _sweep2_155->SetDustbinLiftdropCmd(RDCU155::RdcuDustbinLiftDropCmdType::RDCU_DUSTBIN_LIFTDROP_CMD_INVALID);
    if (_current_mode != ECar3Chassis::CurrentMode::CURRENT_MODE_AUTO)
    {
        _dump_time.Reset(); // 重新记录倒垃圾时间
        GetTaskRequestStatusBridge()->set_dustbin_dumping_cleaning_task_status(0);
    }
    if (!_dump_finished)
    {
        _sweep2_155->SetDustbinOverturnCmd(RDCU155::RdcuDustbinOverTurnCmdType::RDCU_DUSTBIN_OVERTURN_CMD_DUMP);
        if (_dustbin_overturn_pose_status)
        {
            // 翻转到位清0
            _sweep2_155->SetDustbinOverturnCmd(RDCU155::RdcuDustbinOverTurnCmdType::RDCU_DUSTBIN_OVERTURN_CMD_INVALID);
            // 翻转到位打开喷水
            _sweep_154->SetDustbinCleanWaterValveCmd(RDCU154::RdcuWaterValveControlType::RDCU_WATER_VALVE_CTRL_OPEN);
            _sweep_154->SetDustbinDustFallValveCmd(RDCU154::RdcuWaterValveControlType::RDCU_WATER_VALVE_CTRL_OPEN);
            // 翻转到位开始计时
            if (!_dump_time.IsActive())
            {
                _dump_time.Set();
            }
            double dump_duration = _dump_time.Duration();
            if (dump_duration > _dump_time_threshold_s)
            {
                _dump_finished = true;
                GetTaskRequestStatusBridge()->set_dustbin_dumping_cleaning_task_status(1);
            }
            LOG_INFO("dustbin overturn done,dumping duration:%.1f(s)\r\n", dump_duration);
        }
        else
        {
            LOG_INFO("dustbin overturn...\r\n");
        }
    }
    else
    {
        _sweep2_155->SetDustbinOverturnCmd(RDCU155::RdcuDustbinOverTurnCmdType::RDCU_DUSTBIN_OVERTURN_CMD_RETRACT);
        if (_dustbin_overturn_pose_status)
        {
            LOG_INFO("dumping finish,retract dustbin\r\n");
        }
    }
}

void Ecar3VehicleController::_dump_task_reset()
{
    if (_dustbin_overturn_pose_status)
    {
        _sweep2_155->SetDustbinLiftdropCmd(RDCU155::RdcuDustbinLiftDropCmdType::RDCU_DUSTBIN_LIFTDROP_CMD_INVALID);
        _sweep2_155->SetDustbinOverturnCmd(RDCU155::RdcuDustbinOverTurnCmdType::RDCU_DUSTBIN_OVERTURN_CMD_RETRACT);
        LOG_INFO("overturn not finish,run retract\r\n");
    }
    else
    {
        _sweep2_155->SetDustbinLiftdropCmd(RDCU155::RdcuDustbinLiftDropCmdType::RDCU_DUSTBIN_LIFTDROP_CMD_DROP);
        _sweep2_155->SetDustbinOverturnCmd(RDCU155::RdcuDustbinOverTurnCmdType::RDCU_DUSTBIN_OVERTURN_CMD_INVALID);
        LOG_INFO("overturn set done,run lift reset\r\n");
    }
}
