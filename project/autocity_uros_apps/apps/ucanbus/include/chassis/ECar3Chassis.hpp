/*
 * @Author: hanson
 * @Date: 2024-08-27 16:16:07
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-30 15:23:37
 * @Description:
 * @FilePath: \ucanbus\include\chassis\ECar3Chassis.hpp
 */
#ifndef INCLUDE_CHASSIS_ECAR3CHASSIS_HPP_
#define INCLUDE_CHASSIS_ECAR3CHASSIS_HPP_

#include <stdint.h>
#include <string>

class ECar3Chassis
{
public:
    enum ControlDriveSelection
    {
        CONTROL_DRIVE_SELECTION_PEDAL = 0,
        CONTROL_DRIVE_SELECTION_SPEED = 1,
    };
    enum ControlGear
    {
        CONTROL_GEAR_DISABLE = 0,
        CONTROL_GEAR_P = 1,
        CONTROL_GEAR_R = 2,
        CONTROL_GEAR_N = 3,
        CONTROL_GEAR_D = 4,
    };
    enum BodyControlType
    {
        BODY_CONTROL_OFF = 0,
        BODY_CONTROL_ON = 1,
        BODY_CONTROL_AUTO = 2,
    };

    enum ChargingStatus
    {
        UNCHARGED = 0,
        CHARGING = 1,
    };
    enum CurrentMode
    {
        CURRENT_MODE_STANDBY = 0,
        CURRENT_MODE_INVALID = 1,
        CURRENT_MODE_REMOTE = 2,
        CURRENT_MODE_AUTO = 3,
        CURRENT_MODE_EMERGENCY = 4,
        CURRENT_MODE_CLOUD = 5,
    };
    enum ParkingStatus
    {
        PARKING_STATUS_RELEASED = 0,
        PARKING_STATUS_PARK = 1,
        PARKING_STATUS_EMERGENCY = 2,
    };
    enum VehicleRunDir
    {
        VEHICLE_RUN_DIR_STOP = 0,
        VEHICLE_RUN_DIR_FORWARD = 1,
        VEHICLE_RUN_DIR_BACK = 2,
    };

    enum CurrentSweepMode
    {
        CURRENT_SWEEP_MODE_DRIVE = 0,
        CURRENT_SWEEP_MODE_SWEEP = 1,
    };

    enum WirelessChargeStatusType
    {
        WIRELESS_UNCHARGED = 0,
        WIRELESS_CHARGING = 1,
    };

    enum DstbLiftDropSt
    {
        Dropped = 0,
        Lifted = 1,
    };

    enum Gear
    {
        N = 0,
        D = 1,
        R = 2,
    };

    enum MotorError
    {
        Normal = 0,
        Overload = 1,
        OpenCircuit = 2,
    };

    enum State
    {
        OFF = 0,
        ON = 1,
    };

    struct CCU211_A
    {
        uint8_t brake_work_mode;   // 制动系统工作模式
        uint8_t brake_mode;        // 制动类型
        double brake_pressure_bar; // 当前实际制动压力
        double brake_pedal_pos;    // 实际制动踏板开度
        uint8_t err_level;         // EHB故障等级
    };
    struct CCU222_A
    {
        double ccu_lvbat_volt;        // 12V小电池电压
        double ccu_bms_vehbatsoc;     // 整车动力电池总SOC
        double ccu_bms_batsoh;        // 当前工作电池SOH
        double ccu_bms_batvolt;       // 当前工作电池电压
        double ccu_bms_batcurt;       // 当前工作电池电流
        double ccu_bms_battemp;       // 当前工作电池温度
        uint8_t ccu_bms_chgst;        // 当前工作电池充电状态
        uint8_t ccu_bms_dischgst;     // 当前工作电池放电状态
        uint8_t ccu_bms_feedbackst;   // 当前工作电池电流回馈状态
        uint8_t ccu_bms_chgconnectst; // 充电枪连接状态
    };

    struct CCU223_A
    {
        uint8_t ccu_bmsmsgperd_err;           // BMS报文周期异常
        uint8_t ccu_bmsmsgdrop_err;           // BMS报文丢帧异常
        uint8_t ccu_bmsmsgchksum_err;         // BMS报文校验和异常
        uint8_t ccu_bmsmsgoffline_err;        // BMS报文掉线
        uint8_t ccu_bmslowsoc_alarm;          // 电量过低提醒
        uint8_t ccu_bmslowsoc_err;            // 电量过低故障
        uint8_t ccu_bmsovervolt_err;          // 过压故障
        uint8_t ccu_bmsundervolt_err;         // 欠压故障
        uint8_t ccu_bmsovercurt_err;          // 过流故障
        uint8_t ccu_bmsovertemp_err;          // 过温故障
        uint8_t ccu_bmsunitundervolt_err;     // 单元欠压故障
        uint8_t ccu_bmsunitovervolt_err;      // 单元过压故障
        uint8_t ccu_bmsunitovercurt_err;      // 单元过流故障
        uint8_t ccu_bmsunitovertemp_err;      // 单元过温故障
        uint8_t ccu_bmslvbatundervolt_alarm;  // 12V小电池欠压提醒
        uint8_t ccu_bmslvbatundervolt_err;    // 12V小电池欠压故障
        uint8_t ccu_bmslvbatovervolt_alarm;   // 12V小电池过压故障
        uint8_t ccu_obchardware_err;          // 充电机硬件故障
        uint8_t ccu_obcovertemp_err;          // 充电机过温
        uint8_t ccu_obcvoltinput_err;         // 充电机输入电压异常
        uint8_t ccu_bmsmsgofflinefromobc_err; // 充电机检测BMS通讯超时
        uint8_t ccu_obcmsgofflinefrombms_err; // BMS检测充电机通讯超时
        uint8_t ccu_bms_errcode;              // 故障码
    };

    struct CCU224_A
    {
        uint8_t ccu_psu_pollingbatnum;   // 动力电池包编号（轮询显示）
        uint8_t ccu_psu_pollingbatst;    // 动力电池在仓状态（根据电池包编号轮询显示）
        uint8_t ccu_psu_runbatnum;       // 当前放电电池包编号
        double ccu_psu_pollingbatsoc;    // 动力电池SOC（根据电池包编号轮询显示）
        double ccu_psu_pollingbatvolt;   // 动力电池电压（根据电池包编号轮询显示）
        double ccu_psu_pollingbattemp;   // 动力电池温度（根据电池包编号轮询显示）
        double ccu_psu_batdumpenergy;    // 动力电池包剩余电量（根据电池包编号轮询显示）
        uint8_t ccu_psu_vehpowerdownerr; // 动力电池包整车下电故障（根据电池包编号轮询显示）
        uint8_t ccu_psu_errlevel;        // 动力电池包故障等级（根据电池包编号轮询显示）
    };

    struct CCU260_A
    {
        uint8_t ccu_vehpwrsupply_st;    // 总电源供电状态
        uint8_t ccu_chaspwrsupply_st;   // 底盘供电状态
        uint8_t ccu_12vmcpwrsupply_st;  // 自动驾驶12v供电状态(自动驾驶主路)
        uint8_t ccu_12vrcpwrsupply_st;  // 自动驾驶12v供电状态(预留)
        uint8_t ccu_24vmcpwrsupply_st;  // 自动驾驶24v供电状态
        uint8_t ccu_pa12vpwrsupply_st;  // 自动驾驶警务12v供电状态(预留)
        uint8_t ccu_pa24vpwrsupply_st;  // 自动驾驶警务24v供电状态(预留)
        uint8_t ccu_vehpwrswh_st;       // 总电源开关状态
        uint8_t ccu_chaspwrswh_st;      // 底盘供电开关状态
        uint8_t ccu_12vmcpwrswh_st;     // 自动驾驶12v供电开关状态(自动驾驶主路)
        uint8_t ccu_12vrcpwrswh_st;     // 自动驾驶12v供电开关状态(预留)
        uint8_t ccu_24vmcpwrswh_st;     // 自动驾驶24v开关状态
        uint8_t ccu_powerstate;         // 电源管理进程
        uint8_t ccu_pwr_prechgst;       // 预充完成
        uint8_t ccu_pwr_batchgst;       // 电池组充电状态
        uint8_t ccu_pwr_batlackst;      // 电池组亏电状态
        uint8_t ccu_pwr_batreadyst;     // 电池组就绪状态
        uint8_t ccu_pwr_dischgrlyst;    // 放电接触器状态
        uint8_t ccu_pwr_chgrlyst;       // 充电接触器状态
        uint8_t ccu_pwr_prechgrlyst;    // 预充接触器状态
        uint8_t ccu_pwr_shutdowncmd;    // 底盘上下电指令
        uint8_t ccu_12vcs1pwrsupply_st; // 自动驾驶支路12V_1供电状态
        uint8_t ccu_12vcs2pwrsupply_st; // 自动驾驶支路12V_2供电状态
        uint8_t ccu_12vcs3pwrsupply_st; // 自动驾驶支路12V_3供电状态
        uint8_t ccu_12vcs4pwrsupply_st; // 自动驾驶支路12V_4供电状态
        uint8_t ccu_12vcs5pwrsupply_st; // 自动驾驶支路12V_5供电状态
        uint8_t ccu_12vcs6pwrsupply_st; // 自动驾驶支路12V_6供电状态
        uint8_t ccu_pa12vpwrswh_st;     // 自动驾驶警务12v开关状态(预留)
        uint8_t ccu_pa24vpwrswh_st;     // 自动驾驶警务24v开关状态(预留)
        uint8_t ccu_12vmcpwrdown_req;   // 自动驾驶12V供电关闭请求(自动驾驶主路)
        uint8_t ccu_12vrcpwrdown_req;   // 自动驾驶12V供电关闭请求(预留)
        uint8_t ccu_24vmcpwrdown_req;   // 自动驾驶24V供电关闭请求(预留)
        uint8_t ccu_pa12vpwrdown_req;   // 自动驾驶警务12v供电关闭请求(预留)
        uint8_t ccu_pa24vpwrdown_req;   // 自动驾驶警务24v供电关闭请求(预留)
        uint8_t ccu_pwrdowntime_chn;    // 自动驾驶供电关闭剩余时间对应通道
        uint8_t ccu_pwrdown_time;       // 自动驾驶供电关闭剩余时间
    };

    struct CCU261_A
    {
        uint8_t ccu_powercmdperd_err;      // 供电控制指令报文周期异常
        uint8_t ccu_powercmddrop_err;      // 供电控制指令报文丢帧异常
        uint8_t ccu_powercmdchksum_err;    // 供电控制指令报文校验和异常
        uint8_t ccu_powercmdoffline_err;   // 供电控制指令报文掉线
        uint8_t ccu_pdumsgperd_err;        // PDU报文周期异常
        uint8_t ccu_pdumsgdrop_err;        // PDU报文丢帧异常
        uint8_t ccu_pdumsgchksum_err;      // PDU报文校验和异常
        uint8_t ccu_pdumsgoffline_err;     // PDU报文掉线
        uint8_t ccu_chas12v_err;           // 底盘12V输出故障
        uint8_t ccu_ad12v1_err;            // 自动驾驶12V1输出故障
        uint8_t ccu_ad12v2_err;            // 自动驾驶12V2输出故障
        uint8_t ccu_ad24v_err;             // 自动驾驶24V输出故障
        uint8_t ccu_ccupwrsupply_err;      // CCU供电输出故障
        uint8_t ccu_bmspwrsupply_err;      // BMS供电输出故障
        uint8_t ccu_ehbpwrsupply_err;      // EHB供电输出故障
        uint8_t ccu_epspwrsupply_err;      // EPS供电输出故障
        uint8_t ccu_siupwrsupply_err;      // SIU供电输出故障
        uint8_t ccu_epbpwrsupply_err;      // 电磁刹(EPB)供电输出故障
        uint8_t ccu_tpmspwrsupply_err;     // 胎压接收机供电输出故障
        uint8_t ccu_datarecpwrsupply_err;  // CAN记录仪供电输出故障
        uint8_t ccu_emgcyrmtpwrsupply_err; // 急停遥控供电输出故障
        uint8_t ccu_mcuwakeup_err;         // MCU唤醒信号输出故障
        uint8_t ccu_bmswakeup_err;         // BMS唤醒信号输出故障
        uint8_t ccu_ehbwakeup_err;         // EHB唤醒信号输出故障
        uint8_t ccu_epswakeup_err;         // EPS唤醒信号输出故障
        uint8_t ccu_epbwakeup_err;         // EPB唤醒信号输出故障
        uint8_t ccu_rsrvdwakeup1_err;      // 预留设备1唤醒信号输出故障
        uint8_t ccu_rsrvdwakeup2_err;      // 预留设备2唤醒信号输出故障
        uint8_t ccu_rsrvdwakeup3_err;      // 预留设备3唤醒信号输出故障
        uint8_t ccu_rsrvdwakeup4_err;      // 预留设备4唤醒信号输出故障
    };

    struct CCU212_A
    {
        uint8_t ccu_brkcmdperd_err;        // 行车制动控制指令报文周期异常
        uint8_t ccu_brkcmddrop_err;        // 行车制动控制指令报文丢帧异常
        uint8_t ccu_brkcmdchksum_err;      // 行车制动控制指令报文校验和异常
        uint8_t ccu_brkcmdoffline_err;     // 行车制动控制指令报文掉线
        uint8_t ccu_brkcmdoverrge_err;     // 行车制动控制指令值越界
        uint8_t ccu_ehbmsgperd_err;        // EHB报文周期异常
        uint8_t ccu_ehbmsgdrop_err;        // EHB报文丢帧异常
        uint8_t ccu_ehbmsgchksum_err;      // EHB报文校验和异常
        uint8_t ccu_ehbmsgoffline_err;     // EHB报文掉线
        uint8_t ccu_brkfldlack_err;        // 制动液不足警告
        uint8_t ccu_ehbcurtsenor_err;      // 电流传感器故障
        uint8_t ccu_ehbtempsenor_err;      // 温度传感器故障
        uint8_t ccu_ehbovertemp_err;       // 制动系统过温异常
        uint8_t ccu_brkpwrsupply_err;      // 制动系统供电异常
        uint8_t ccu_brkpresrsenor_err;     // 液压力传感器故障
        uint8_t ccu_ehbpwrsupply_err;      // EHB供电故障
        uint8_t ccu_ecupwrsupply_err;      // ECU供电故障
        uint8_t ccu_drvbridge_err;         // 驱动桥故障
        uint8_t ccu_drvmtr_err;            // 电机故障
        uint8_t ccu_ehbcan_err;            // CAN节点丢失
        uint8_t ccu_ehbpwrswh_err;         // 功率开关故障
        uint8_t ccu_ehbweeping_err;        // 漏液故障
        uint8_t ccu_ehbpresfolw_alarm;     // EHB液压力跟随异常
        uint8_t ccu_ehbpresctrlvib_alarm;  // EHB液压力轻微震荡
        uint8_t ccu_ehbtempsenor_alarm;    // 温度传感器异常
        uint8_t ccu_ehbworkmode_err;       // EHB工作模式异常故障
        uint8_t ccu_ehbbrkpres_err;        // EHB目标指令响应异常故障
        uint8_t ccu_ehbpresfolw_err;       // EHB液压力跟随故障
        uint8_t ccu_ehbpresctrlvib_err;    // EHB液压力严重震荡
        uint8_t ccu_ehbloadmismatch_err;   // 负载失配故障
        uint8_t ccu_ehbovercurt_err;       // EHB过流故障
        uint8_t ccu_ehbbrkcmdabnormal_err; // 制动指令异常警告
    };

    struct CCU213_A
    {
        uint8_t park_work_mode;          // 驻车制动工作模式
        uint8_t park_status;             // 驻车状态
        uint8_t park_release_swh_status; // 解驻车开关状态
        uint8_t err_level;               // 故障等级
    };

    struct CCU214_A
    {
        uint8_t ccu_prkcmdperd_err;            // 驻车控制指令报文周期异常
        uint8_t ccu_prkcmddrop_err;            // 驻车控制指令报文丢帧异常
        uint8_t ccu_prkcmdchksum_err;          // 驻车控制指令报文校验和异常
        uint8_t ccu_prkcmdoffline_err;         // 驻车控制指令报文掉线
        uint8_t ccu_prkcmdoverrge_err;         // 驻车控制指令值越界
        uint8_t ccu_epbmsgperd_err;            // EPB报文周期异常
        uint8_t ccu_epbmsgdrop_err;            // EPB报文丢帧异常
        uint8_t ccu_epbmsgchksum_err;          // EPB报文校验和异常
        uint8_t ccu_epbmsgoffline_err;         // EPB报文掉线
        uint8_t ccu_epbparkinvalid_err;        // 驻车失效故障
        uint8_t ccu_epbenablefeedback_err;     // EPB使能反馈异常
        uint8_t ccu_epbovervolt_err;           // EPB控制器过压故障
        uint8_t ccu_epbundervolt_err;          // EPB控制器欠压故障
        uint8_t ccu_epbrelay_err;              // EPB继电器故障
        uint8_t ccu_epbcancom_err;             // EPB诊断CAN通讯故障
        uint8_t ccu_epbleftlockingact_err;     // EPB左驻车电流异常
        uint8_t ccu_epbrightlockingact_err;    // EPB右驻车电流异常
        uint8_t ccu_epbleftunlockingact_err;   // EPB左解驻电流异常
        uint8_t ccu_epbrightunlockingact_err;  // EPB右解驻电流异常
        uint8_t ccu_epbfallback_warning;       // EPB溜坡报警
        uint8_t ccu_epbprotectoff_active;      // EPB控制器强制保护激活
        uint8_t ccu_epbmtroffcurt_err;         // EPB电机静态电流异常
        uint8_t ccu_epbtempsenor_err;          // EPB温度传感器故障
        uint8_t ccu_epbovertemplevel1_warning; // EPB控制器过温一级报警
        uint8_t ccu_epbovertemplevel2_warning; // EPB控制器过温二级报警
        uint8_t ccu_epbwakeuphw_err;           // EPB控制器硬线唤醒异常
    };

    struct CCU217_A
    {
        uint8_t mcu_work_mode;  // 驱动系统工作模式
        uint8_t gear;           // 实际档位
        uint8_t run_direction;  // 电机运转方向
        double throttle;        // 实际油门
        double mcu_current;     // 电机电流
        double motor_speed_rpm; // 电机实际转速
        uint8_t err_level;      // MCU故障等级
    };

    struct CCU218_A
    {
        uint8_t ccu_drvcmdperd_err;      // 驱动控制指令报文周期异常
        uint8_t ccu_drvcmddrop_err;      // 驱动控制指令报文丢帧异常
        uint8_t ccu_drvcmdchksum_err;    // 驱动控制指令报文校验和异常
        uint8_t ccu_drvcmdoffline_err;   // 驱动控制指令报文掉线
        uint8_t ccu_drvcmdoverrge_err;   // 驱动控制指令值越界
        uint8_t ccu_mcumsgperd_err;      // MCU报文周期异常
        uint8_t ccu_mcumsgdrop_err;      // MCU报文丢帧异常
        uint8_t ccu_mcumsgchksum_err;    // MCU报文校验和异常
        uint8_t ccu_mcumsgoffline_err;   // MCU报文掉线
        uint8_t ccu_mcumainpwrcur_err;   // MCU主回路断电
        uint8_t ccu_mcucurtsensor_err;   // 电流采样电路故障
        uint8_t ccu_mcuprechg_err;       // MCU预充故障
        uint8_t ccu_mcupwrovervolt_err;  // MCU供电过压
        uint8_t ccu_mcupwrundervolt_err; // MCU供电欠压
        uint8_t ccu_mcupwrovercurt_err;  // MCU供电过流
        uint8_t ccu_mcuovertemp_err;     // MCU过温
        uint8_t ccu_mcucancom_err;       // MCU通信异常
        uint8_t ccu_mcumtrovertemp_err;  // 电机过温
        uint8_t ccu_mcumtrphase_err;     // 电机相序异常
        uint8_t ccu_mcuencoder_err;      // 电机编码器故障
        uint8_t ccu_mcumtrblock_err;     // 堵转保护
        uint8_t ccu_mcuenable_err;       // MCU使能状态异常故障
        uint8_t ccu_mcuthortact_err;     // MCU目标油门指令响应异常故障
        uint8_t ccu_mcumtrspdact_err;    // MCU目标转速指令响应异常故障
        uint8_t ccu_mcu_errcode;         // 故障码
    };

    struct CCU225_A
    {
        double ccu_drv_force; // 当前驱动力
    };

    struct CCU215_A
    {
        uint8_t eps_work_mode;           // 转向工作模式
        double steering_wheel_torque_nm; // 转向盘手力矩
        double front_whl_angle_deg;      // 实际前轮转角
        double angular_velocity_degps;   // 实际车轮转向角速度
        uint8_t err_level;               // EPS故障等级
    };

    struct CCU216_A
    {
        uint8_t ccu_strcmdperd_err;    // 转向控制指令报文周期异常
        uint8_t ccu_strcmddrop_err;    // 转向控制指令报文丢帧异常
        uint8_t ccu_strcmdchksum_err;  // 转向控制指令报文校验和异常
        uint8_t ccu_strcmdoffline_err; // 转向控制指令报文掉线
        uint8_t ccu_strcmdoverrge_err; // 转向控制指令值越界
        uint8_t ccu_epsmsgperd_err;    // EPS报文周期异常
        uint8_t ccu_epsmsgdrop_err;    // EPS报文丢帧异常
        uint8_t ccu_epsmsgchksum_err;  // EPS报文校验和异常
        uint8_t ccu_epsmsgoffline_err; // EPS报文掉线
        uint8_t ccu_epsworkmode_err;   // EPS工作模式异常故障
        uint8_t ccu_epsstrangle_err;   // EPS目标指令响应异常故障
        uint8_t eps_ecuovervolt_err;   // 控制器过压
        uint8_t eps_ecuundervolt_err;  // 控制器欠压
        uint8_t eps_mtrovercurt_err;   // 转向电机过流
        uint8_t eps_ecuovertemp_err;   // 控制器过温
        uint8_t eps_mtrovertemp_err;   // 电机过温
        uint8_t eps_anglesensor_err;   // 角度传感器故障
        uint8_t eps_anglealignm_err;   // 未对中故障
        uint8_t eps_strmtr_err;        // 电机故障
        uint8_t eps_cancom_err;        // CAN通讯故障
    };

    struct CCU221_A
    {
        uint8_t ccu_ftcrashcontact_st;      // 前触边接触状态
        uint8_t ccu_rrcrashcontact_st;      // 后触边接触状态
        uint8_t ccu_ftcrashtrg_st;          // 前触边触发状态
        uint8_t ccu_rrcrashtrg_st;          // 后触边触发状态
        uint8_t ccu_ftcrashopencircuit_err; // 前触边开路故障
        uint8_t ccu_rrcrashopencircuit_err; // 后触边开路故障
        uint8_t ccu_emgcypark_st;           // 紧急驻车状态
        uint8_t ccu_crashcheck_st;          // 触边碰撞检测功能状态
        double ccu_onlinetrip_meter;        // 当次上电小计里程
    };

    struct CCU6F1_A
    {
        uint8_t ap_working_mode;      // 当前工作模式
        uint8_t ap_playing_mode;      // 当前播放模式
        uint8_t ap_playing_num;       // 正在播放音频的编号
        uint8_t ap_playing_errorcode; // 故障码
    };

    struct CCU240_A
    {
        uint8_t vehicle_run_mode;           // 车辆工作模式
        uint8_t ccu_veh_runlockrsn;         // 车辆行驶控制锁定原因
        uint8_t err_level;                  // 整车故障等级
        uint8_t ccu_ftcrash_st;             // 前触边碰撞状态
        uint8_t ccu_rrcrash_st;             // 后触边碰撞状态
        uint8_t ccu_vehemgcyswh_st;         // 急停开关状态
        uint8_t ccu_lvbat_lowvolt;          // CCU供电欠压
        uint8_t ccu_bat_lowsoc;             // 动力电池电量过低
        uint8_t ccu_bms_errlevel;           // 动力电池故障等级
        uint8_t ccu_mcu_errlevel;           // MCU故障等级
        uint8_t ccu_ehb_errlevel;           // EHB故障等级
        uint8_t ccu_eps_errlevel;           // EPS故障等级
        uint8_t ccu_epb_errlevel;           // EPB故障等级
        uint8_t ccu_siu_errlevel;           // SIU故障等级
        uint8_t ccu_lpdu_errlevel;          // LPDU故障等级
        uint8_t ccu_tirepresralarm_st;      // 胎压报警状态
        uint8_t ccu_canbusoff_st;           // CAN总线故障状态
        uint8_t ccu_segcodedispoffline_err; // 段码屏离线故障
        uint8_t ccu_leddispofflie_err;      // LED点阵屏离线故障
        uint8_t ccu_chginhibit_flt;         // 三级故障禁止充电标志位
        uint8_t ccu_pwrupinhibit_flt;       // 三级故障禁止上电标志位
        uint8_t ccu_ademgcystop_st;         // 远程车辆急停状态
        uint8_t ccu_vehemgcystop_reason;    // 车辆急停原因
        uint8_t ccu_hpdu_errlevel;          // HPDU故障等级
        uint8_t ccu_cbcu_errlevel;          // CBCU故障等级
        uint8_t ccu_veh_errcode;            // 整车故障码
    };

    struct CCU153_A
    {
        uint8_t ccu_cbcu_veh_runmode;      // 车辆工作模式
        uint8_t ccu_cbcu_chaspwrsupply_st; // 底盘供电状态
        uint8_t ccu_cbcu_bms_chgconnectst; // 充电枪连接状态
        uint8_t ccu_cbcu_bms_chgst;        // 电池充电状态
        double ccu_cbcu_bms_vehbatsoc;     // 整车动力电池总SOC
        double ccu_cbcu_veh_longtdnalspd;  // 纵向车速
        uint8_t ccu_cbcu_veh_errlevel;     // 整车故障等级
    };

    struct CCU219_A
    {
        uint8_t acostoptic_work_mode; // 声光系统工作模式
        uint8_t head_lamp;            // 前大灯开启状态
        uint8_t double_flash;         // 双闪开启状态
        uint8_t left_turn_light;      // 左转灯开启状态
        uint8_t right_turn_light;     // 右转灯开启状态
        uint8_t back_lamp;            // 倒车灯开启状态
        uint8_t buzzer;               // 警示蜂鸣器开启状态
        uint8_t horn;                 // 喇叭开启状态
        uint8_t run_lamp;             // 日行灯开启状态
        uint8_t brake_lamp;           // 制动灯状态
        uint8_t fog_lamp;             // 雾灯状态
        uint8_t width_lamp;           // 示廓灯开启状态
        uint8_t wiper;                // 雨刷开启状态
        uint8_t warn_lamp;            // 警灯开启状态
        uint8_t flood_light;          // 强光灯开启状态
        uint8_t siren;                // 警笛开启状态
    };

    struct CCU220_A
    {
        uint8_t ccu_bodycmdperd_err;    // 声光控制指令报文周期异常
        uint8_t ccu_bodycmddrop_err;    // 声光控制指令报文丢帧异常
        uint8_t ccu_bodycmdchksum_err;  // 声光控制指令报文校验和异常
        uint8_t ccu_bodycmdoffline_err; // 声光控制指令报文掉线
        uint8_t ccu_headlamp_err;       // 前大灯故障
        uint8_t ccu_turnllamp_err;      // 左转灯故障
        uint8_t ccu_turnrlamp_err;      // 右转灯故障
        uint8_t ccu_backlamp_err;       // 倒车灯故障
        uint8_t ccu_buzzer_err;         // 警示蜂鸣器故障
        uint8_t ccu_runlamp_err;        // 日行灯故障
        uint8_t ccu_brklamp_err;        // 制动灯故障
        uint8_t ccu_foglamp_err;        // 雾灯故障
        uint8_t ccu_horn_err;           // 喇叭故障
        uint8_t ccu_widthlamp_err;      // 示廓灯故障
    };

    struct CCU250_A
    {
        double speed_kmph;       // 纵向车速
        double a_mpps;           // 车辆纵向加速度
        double motion_curvature; // 车辆运动曲率
        uint8_t run_direction;   // 车辆行驶方向
    };

    struct CCU251_A
    {
        double left_front_whl_speed_kmph;  // 左前轮速
        double right_front_whl_speed_kmph; // 右前轮速
        uint8_t left_front_whl_validity;   // 左前轮速有效性
        uint8_t right_front_whl_validity;  // 右前轮速有效性
    };

    struct CCU252_A
    {
        double left_rear_whl_speed_kmph;  // 左后轮速
        double right_rear_whl_speed_kmph; // 右后轮速
        uint8_t left_rear_whl_validity;   // 左后轮速有效性
        uint8_t right_rear_whl_validity;  // 右后轮速有效性
    };

    struct CCU270_A
    {
        double ccu_rmtchn1_freq; // 遥控器通道1（转向）频率
        double ccu_rmtchn1_duty; // 遥控器通道1（转向）占空比
        double ccu_rmtchn2_freq; // 遥控器通道2（制动）频率
        double ccu_rmtchn2_duty; // 遥控器通道2（制动）占空比
    };

    struct CCU271_A
    {
        double ccu_rmtchn3_freq; // 遥控器通道3（油门）频率
        double ccu_rmtchn3_duty; // 遥控器通道3（油门）占空比
        double ccu_rmtchn4_freq; // 遥控器通道4（大灯控制）频率
        double ccu_rmtchn4_duty; // 遥控器通道4（大灯控制）占空比
    };

    struct CCU272_A
    {
        double ccu_rmtchn5_freq; // 遥控器通道5（模式切换）频率
        double ccu_rmtchn5_duty; // 遥控器通道5（模式切换）占空比
        double ccu_rmtchn6_freq; // 遥控器通道6（预留三档开关）频率
        double ccu_rmtchn6_duty; // 遥控器通道6（预留三档开关）占空比
    };

    struct CCU277_A
    {
        double ccu_rmtchn7_freq; // 遥控器通道7频率
        double ccu_rmtchn7_duty; // 遥控器通道7占空比
        double ccu_rmtchn8_freq; // 遥控器通道8频率
        double ccu_rmtchn8_duty; // 遥控器通道8占空比
    };

    struct CCU276_A
    {
        uint8_t ccu_siumsgperd_err;    // SIU报文周期异常
        uint8_t ccu_siumsgdrop_err;    // SIU报文丢帧异常
        uint8_t ccu_siumsgchksum_err;  // SIU报文校验和异常
        uint8_t ccu_siumsgoffline_err; // SIU报文掉线
        uint8_t ccu_rmtchn1freq_err;   // 遥控器通道1（转向）频率异常故障
        uint8_t ccu_rmtchn1duty_err;   // 遥控器通道1（转向）占空比异常故障
        uint8_t ccu_rmtchn2freq_err;   // 遥控器通道2（制动）频率异常故障
        uint8_t ccu_rmtchn2duty_err;   // 遥控器通道2（制动）占空比异常故障
        uint8_t ccu_rmtchn3freq_err;   // 遥控器通道3（油门）频率异常故障
        uint8_t ccu_rmtchn3duty_err;   // 遥控器通道3（油门）占空比异常故障
        uint8_t ccu_rmtchn4freq_err;   // 遥控器通道4（大灯控制）频率异常故障
        uint8_t ccu_rmtchn4duty_err;   // 遥控器通道4（大灯控制）占空比异常故障
        uint8_t ccu_rmtchn5freq_err;   // 遥控器通道5（模式切换）频率异常故障
        uint8_t ccu_rmtchn5duty_err;   // 遥控器通道5（模式切换）占空比异常故障
    };

    struct CCU254_A
    {
        double ccu_totaltrip_meter; // 总小计里程
        double ccu_remain_mileage;  // 剩余里程（参考值）
        double ccu_totalodo_meter;  // 运行总里程
    };

    struct CCU255_A
    {
        double ccu_rmtdrvtrip_meter; // 遥控模式小计里程
        double ccu_rmtdrvodo_meter;  // 遥控模式运行总里程
    };

    struct CCU256_A
    {
        double ccu_autodrvtrip_meter; // 自动驾驶模式小计里程
        double ccu_autodrvodo_meter;  // 自动驾驶模式运行总里程
    };

    struct CCU257_A
    {
        double ccu_clddrvtrip_meter; // 远程驾驶模式小计里程
        double ccu_clddrvodo_meter;  // 远程驾驶模式运行总里程
    };

    struct CCU2A0_A
    {
        double ccu_veh_vin;    // 车型VIN
        double ccu_hw_version; // 硬件版本
        double ccu_sw_version; // 软件版本
    };

    struct CCU2A5_A
    {
        uint8_t ccu_vehvin_c1; // 车型VIN第1位（ASCII码）
        uint8_t ccu_vehvin_c2; // 车型VIN第2位（ASCII码）
        uint8_t ccu_vehvin_c3; // 车型VIN第3位（ASCII码）
        uint8_t ccu_vehvin_c4; // 车型VIN第4位（ASCII码）
        uint8_t ccu_vehvin_c5; // 车型VIN第5位（ASCII码）
        uint8_t ccu_vehvin_c6; // 车型VIN第6位（ASCII码）
        uint8_t ccu_vehvin_c7; // 车型VIN第7位（ASCII码）
    };

    struct CCU2A6_A
    {
        uint8_t ccu_vehvin_c8;    // 车型VIN第8位（ASCII码）
        uint8_t ccu_vehvin_c9;    // 车型VIN第9位（ASCII码）
        uint8_t ccu_vehvin_c10;   // 车型VIN第10位（ASCII码）
        uint8_t ccu_vehvin_c11;   // 车型VIN第11位（ASCII码）
        double ccu_vehvin_d12_17; // 车型VIN第12-17位
    };

    struct CBCU534_A
    {
        uint8_t sweep_mode;                       // 当前清扫模式
        uint8_t sweep_sys_status;                 // 清扫系统工作状态
        uint8_t sweep_estop_status;               // 清扫系统急停状态
        uint8_t shake_dust_status;                // 震尘状态
        uint8_t left_front_brush_stretch_status;  // 左前边刷伸缩状态
        uint8_t right_front_brush_stretch_status; // 右前边刷伸缩状态
        uint8_t left_front_brush_drop_status;     // 左前边刷升降状态
        uint8_t right_front_brush_drop_status;    // 右前边刷升降状态
        uint8_t rear_brush_drop_status;           // 后边刷升降状态
        uint8_t main_brush_drop_status;           // 滚刷升降状态
        uint8_t suction_drop_status;              // 吸口升降状态
        uint8_t left_front_brush_motor_status;    // 左前边刷电机状态
        uint8_t right_front_brush_motor_status;   // 右前边刷电机状态
        uint8_t left_rear_brush_motor_status;     // 左后边刷电机状态
        uint8_t right_rear_brush_motor_status;    // 右后边刷电机状态
        uint8_t main_brush_motor_status;          // 滚刷电机状态
        double left_front_brush_expand_dist_mm;   // 左前置边刷实际外展距离
        double right_front_brush_expand_dist_mm;  // 右前置边刷实际外展距离
        uint8_t ctfg_fan1_status;                 // 离心风机1状态
        uint8_t ctfg_fan2_status;                 // 离心风机2状态
        uint8_t front_fender_status;              // 前挡板状态
        uint8_t water_pump_status;                // 水泵状态
        uint8_t brush_water_valve_status;         // 边刷水阀状态
        uint8_t fan_dust_fall_valve_status;       // 风机降尘水阀状态
        uint8_t suction_dust_fall_valve_status;   // 吸口降尘水阀状态
        uint8_t dustbin_dust_fall_valve_status;   // 垃圾箱降尘水阀状态
        uint8_t roll_swp_water_valve_status;      // 滚扫降尘水阀状态
        uint8_t dustbin_clean_water_valve_status; // 垃圾箱自洁水阀状态
        uint8_t water_boxlid_status;              // 加水盖开关状态
        uint8_t water_drain_valve_status;         // 放水阀状态
    };

    struct CBCU537_A
    {
        double remain_water;                    // 水箱剩余水量
        uint8_t dustbin_pose_status;            // 垃圾箱位置状态
        uint8_t dustbin_lock_status;            // 垃圾箱舱门锁紧状态
        uint8_t dustbin_door_status;            // 垃圾箱舱门开闭状态
        uint8_t dustbin_lift_pose_status;       // 垃圾箱举升位置状态
        uint8_t dustbin_overturn_pose_status;   // 垃圾箱翻转位置状态
        uint8_t dustbin_lift_angle_gear_status; // 垃圾箱举升角度挡位状态
        uint8_t dustbin_full_status;            // 垃圾箱满载状态
        uint8_t sweep_lamp_status;              // 清扫警示灯状态
        uint8_t dustbin_sater_lvl_status;       // 垃圾箱水位状态
        uint8_t dump_status;                    // 自驾一键倒垃圾执行状态
        double brush_motor1_speed_rpm;          // 边刷电机1转速
        double brush_motor2_speed_rpm;          // 边刷电机2转速
    };

    struct CBCU535_A
    {
        uint8_t left_front_brush_stretch_mtr_err;     // 左前边刷伸缩杆电机故障
        uint8_t right_front_brush_stretch_mtr_err;    // 右前边刷伸缩杆电机故障
        uint8_t left_front_brush_drop_mtr_fault_err;  // 左前边刷升降杆电机故障
        uint8_t right_front_brush_drop_mtr_err;       // 右前边刷升降杆电机故障
        uint8_t rear_brush_drop_mtr_err;              // 后置边刷升降电机故障
        uint8_t main_brush_drop_mtr_err;              // 滚刷升降电机故障
        uint8_t suction_drop_mtr_err;                 // 吸口升降电机故障
        uint8_t front_fender_mtr_err;                 // 前挡板电机故障
        uint8_t dustbin_door_openclose_mtr_err;       // 垃圾箱舱门开关电机故障
        uint8_t dustbin_door_lock_mtr_err;            // 垃圾箱舱门锁紧电机故障
        uint8_t main_brush_mtr_err;                   // 滚刷电机故障
        uint8_t left_front_brush_mtr_err;             // 左前边刷电机故障
        uint8_t right_front_brush_mtr_err;            // 右前边刷电机故障
        uint8_t left_rear_brush_mtr_err;              // 左后边刷电机故障
        uint8_t right_rear_brush_mtr_err;             // 右后边刷电机故障
        uint8_t ctfgal_mtr1_err;                      // 离心风机1故障
        uint8_t ctfgal_mtr2_err;                      // 离心风机2故障
        uint8_t shake_dust_mtr_err;                   // 震尘电机故障
        uint8_t water_pump_err;                       // 水泵故障
        uint8_t brush_water_valve_err;                // 边刷降尘水阀故障
        uint8_t fan_dust_fall_valve_err;              // 风机降尘水阀故障
        uint8_t suction_dust_fall_valve_err;          // 吸口降尘水阀故障
        uint8_t dustbin_dust_fall_valve_err;          // 垃圾箱降尘水阀故障
        uint8_t roll_swp_water_valve_err;             // 滚扫降尘水阀故障
        uint8_t dustbin_selfcleaning_water_valve_err; // 垃圾箱自洁水阀故障
        uint8_t water_drain_valve_err;                // 放水阀故障
        uint8_t low_water_level_alarm;                // 水箱水位不足报警
        uint8_t dustbin_overflow_alarm;               // 垃圾箱满载报警
        uint8_t water_pump_pressure_err;              // 洒水水泵压力异常
        uint8_t dustbin_fall_pose_alram;              // 垃圾箱未下降到位报警
        uint8_t adcu_msg_offline_err;                 // ADCU报文离线故障
        uint8_t water_boxlid_mtr_err;                 // 加水口推杆电机故障
    };

    struct CBCU538_A
    {
        uint8_t cbcu_errlevel; // 故障等级
        uint8_t cbcu_errcode;  // 故障码
    };

    struct CBCU300_A
    {
        double cbcu_syserrcode; // CBCU系统故障码
    };

    struct CBCU536_A
    {
        double cbcu_supplier_code;    // CBCU供应商代码
        double cbcu_sw_version;       // CBCU软件版本号
        double cbcu_hw_version;       // CBCU硬件版本号
        double cbcu_production_batch; // CBCU生产批次
    };

    struct CDCU227_A
    {
        uint8_t wireless_chg_coupling_status; // 无线充电线圈耦合状态
        uint8_t wireless_charging_status;     // 无线充电状态
    };

    struct GYLGZ0_B
    {
        double rainfall;                      // 雨量
        std::string rainfall_status = "none"; // 雨量状态
        double light_intensity;               // 光照强度
    };

private:
    /* data */
public:
    ECar3Chassis(/* args */) = default;
    ~ECar3Chassis() = default;
    CCU222_A ccu222_a_;
    CCU223_A ccu223_a_;
    CCU224_A ccu224_a_;
    CCU260_A ccu260_a_;
    CCU261_A ccu261_a_;
    CCU211_A ccu211_a_;
    CCU212_A ccu212_a_;
    CCU213_A ccu213_a_;
    CCU214_A ccu214_a_;
    CCU217_A ccu217_a_;
    CCU218_A ccu218_a_;
    CCU225_A ccu225_a_;
    CCU215_A ccu215_a_;
    CCU216_A ccu216_a_;
    CCU221_A ccu221_a_;
    CCU6F1_A ccu6f1_a_;
    CCU240_A ccu240_a_;
    CCU153_A ccu153_a_;
    CCU219_A ccu219_a_;
    CCU220_A ccu220_a_;
    CCU250_A ccu250_a_;
    CCU251_A ccu251_a_;
    CCU252_A ccu252_a_;
    CCU270_A ccu270_a_;
    CCU271_A ccu271_a_;
    CCU272_A ccu272_a_;
    CCU277_A ccu277_a_;
    CCU276_A ccu276_a_;
    CCU254_A ccu254_a_;
    CCU255_A ccu255_a_;
    CCU256_A ccu256_a_;
    CCU257_A ccu257_a_;
    CCU2A0_A ccu2a0_a_;
    CCU2A5_A ccu2a5_a_;
    CCU2A6_A ccu2a6_a_;
    CBCU534_A cbcu534_a_;
    CBCU537_A cbcu537_a_;
    CBCU535_A cbcu535_a_;
    CBCU538_A cbcu538_a_;
    CBCU300_A cbcu300_a_;
    CBCU536_A cbcu536_a_;
    CDCU227_A cdcu227_a_;
    GYLGZ0_B gylgz0_b_;
};

#endif // INCLUDE_CHASSIS_ECAR3CHASSIS_HPP_
