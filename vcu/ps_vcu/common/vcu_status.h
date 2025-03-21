#ifndef COMMON_VCU_STATUS_H_
#define COMMON_VCU_STATUS_H_

#include <stdint.h>

// state
typedef enum driving_mode
{
    Driving_Mode_Standby = 0x0,      // 待机模式
    Driving_Mode_Auto = 0x1,         // 自动驾驶模式
    Driving_Mode_Remote_Cloud = 0x2, // 远程模式
    Driving_Mode_Remote = 0x3,       // 遥控模式
    Driving_Mode_SoftEStop = 0x4,    // 软急停模式
    Driving_Mode_HardEStop = 0x5,    // 硬急停模式
    Driving_Mode_Charging = 0x6,     // 充电模式
    Driving_Mode_OTA = 0x7,          // 升级模式
    Driving_Mode_INVALID = 0xff,     // 无效模式
} DrivingMode;                       // 驾驶模式

typedef enum gear
{
    Gear_N = 0x0, // 空挡
    Gear_P = 0x1, // 驻车
    Gear_D = 0x2, // 前进
    Gear_R = 0x3, // 后退
} Gear;

typedef enum mcu_mode
{
    McuMode_Torque = 0x0,   // 扭矩
    McuMode_Speed = 0x1,    // 速度
    McuMode_Pedal = 0x2,    // 踏板
    McuMode_Reserved = 0x3, // 保留
} McuMode;                  // 轮毂电机模式

typedef enum estop_reason
{
    EStopReason_None = 0x0,     // 未急停
    EStopReason_Key = 0x1,      // 按键
    EStopReason_FtCrash = 0x2,  // 前触边
    EStopReason_RrCrash = 0x3,  // 后触边
    EStopReason_VehFault = 0x4, // 整车故障
    EStopReason_Rmt = 0x5,      // 遥控急停
    EStopReason_Cloud = 0x6,    // 远程急停
    EStopReason_Soft = 0x7,     // 软件逻辑导致急停
} EStopReason;                  // 急停原因

typedef enum err_lvl
{
    ErrLvlNone = 0x0, // 无故障
    ErrLvl1 = 0x1,    // 一级故障
    ErrLvl2 = 0x2,    // 二级故障
    ErrLvl3 = 0x3,    // 三级故障
} ErrLvl;             // 故障等级

typedef enum pwr_mode
{
    PwrMode_Keep = 0x0,     // 保持
    PwrMode_Up = 0x1,       // 上电
    PwrMode_Shutdown = 0x2, // 下电
    PwrMode_Restart = 0x3,  // 重启
} PwrMode;                  // 电源模式
// recv
typedef struct body_cmd
{
    uint8_t warning_lamp;   // 警示灯
    uint8_t head_lamp;      // 大灯
    uint8_t dbl_flash_lamp; // 双闪
    uint8_t turn_l_lamp;    // 左转向灯
    uint8_t turn_r_lamp;    // 右转向
    uint8_t back_lamp;      // 倒车灯
    uint8_t buzzer;         // 蜂鸣器
    uint8_t horn;           // 喇叭
    uint8_t brk_lamp;       // 制动灯
    uint8_t fog_lamp;       // 雾灯
    uint8_t width_lamp;     // 视廓灯
    uint8_t wiper;          // 雨刷
} BodyCmd;                  // 车身控制

typedef struct drv_cmd
{
    uint8_t driving_mode;   // 驱动模式 0 待机，1，自动驾驶，2，远程驾驶
    uint8_t ctrl_mode;      // 控制模式：0 踏板，1 速度
    uint8_t tgt_gear;       // 目标挡位
    double tgt_pedpos;      // 目标油门大小 0-100%
    double tgt_veh_spd;     // 目标速度
    double tgt_veh_acc_spd; // 目标加速度
    double veh_spd_limit;   // 限速
} DrvCmd;                   // 驱动控制

// send
typedef struct steer_cmd
{
    uint8_t work_mode;   // 工作模式 0 助力，1线控
    double target_angle; // 目标角度（-80°到80°）
    double angle_speed;  // 角速度 （50 到 450）
    uint8_t center;      // 请求对中
} SteerCmd;              // 转向指令

typedef struct brake_cmd
{
    uint8_t park_enable;     // 1 驻车使能
    uint8_t work_mode;       // 工作模式 0踏板，1压力
    double target_brake_val; // 目标制动量 （0 到 100 %）
    uint8_t target_pressure; // 目标制动压力(0-80)
} BrakeCmd;                  // 刹车指令

typedef struct rcu_cmd
{
    uint8_t ctrl_mod;           // 控制模式 0 手动，1自动
    double target_angle;        // 目标角度（-80°到80°）
    double tgt_pedpos;          // 目标油门大小 0-100%
    uint8_t tgt_gear;           // 目标挡位
    uint8_t park_enable;        // 1 驻车使能
    uint8_t one_clk_clean_ctrl; // 一键清扫 0 无效，1 开启，2 复位，3 关闭
    uint8_t one_clk_dump_ctrl;  // 一键倒垃圾 0 无效，1 开启，2 复位，3 关闭
} RcuCmd;                       // 遥控指令

typedef struct sweep_cmd
{
    uint8_t fender_ctrl;            // 挡板控制 0 无效，1 提起，2 关闭
    uint8_t one_clk_clean_ctrl;     // 一键清扫 0 无效，1 开启，2 复位，3 关闭
    uint8_t one_clk_dump_ctrl;      // 一键倒垃圾 0 无效，1 开启，2 复位，3 关闭
    uint8_t water_pump_ctrl;        // 水泵 0 无效，1 开启，2 关闭
    uint8_t vbr_ctrl;               // 震尘 0 无效，1 开启，2 关闭
    uint8_t water_add_ctrl;         // 加水 0 无效，1 开启，2 关闭
    uint8_t sweeping_ctrl;          // 清扫请求 0 无效，1 开启，2 关闭
    uint8_t side_brush_lift_ctrl;   // 边刷升降 0 无效，1 上升，2 下降
    uint8_t side_brush_extend_ctrl; // 边刷伸缩 0 无效，1 伸出，2 缩回
    uint8_t main_brush_lift_ctrl;   // 主刷升降 0 无效，1 上升，2 下降
    uint8_t dust_bin_lift_ctrl;     // 垃圾桶升降 0 无效，1 上升，2 下降
    uint8_t dust_bin_dump_ctrl;     // 垃圾桶倾倒 0 无效，1 倾倒，2 复位
    uint8_t dust_bin_open_ctrl;     // 垃圾桶开启 0 无效，1 开启，2 关闭
    uint8_t main_brush_ctrl;        // 主刷电机开启 0 无效，1 开启，2 关闭
    uint8_t side_brush_ctrl;        // 边刷电机开启 0 无效，1 开启，2 关闭
    uint8_t blower_ctrl;            // 风机开启 0 无效，1 开启，2 关闭
    uint8_t high_water_pump_ctrl;   // 高压水泵开启 0 无效，1 开启，2 关闭
    uint8_t vacuum_ctrl;            // 吸尘开启 0 无效，1 开启，2 关闭
    uint8_t dust_bin_compress_ctrl; // 垃圾压缩开启 0 无效，1 开启，2 关闭
    uint8_t wash_valve_ctrl;        // 清洗电磁阀 0 无效，1 开启，2 关闭
    uint8_t clean_valve_ctrl;       // 喷水电磁阀 0 无效，1 开启，2 关闭
    uint8_t high_pump_adjust_ctrl;  // 高压水泵调节 0 无效，1 开启，2 复位 3 停止
    uint8_t wash_probe_adjust_ctrl; // 清洗探头调节 0 无效，1 开启，2 复位 3 停止
} SweepCmd;                         // 清扫指令

typedef struct power_cmd
{
    uint8_t veh_pwrup;        // 整车电源指令，0 keep,1 power up 2 shutdown 3 restart
    uint8_t wl_chg_wake_up;   // 无线充电唤醒 0 false 1 true
    uint8_t emg_brk_req;      // 硬急停请求
    uint8_t soft_emg_brk_req; // 软急停请求
    uint8_t rmt_pwr_on_req;   // 远程上电
    uint8_t crash_free;       // 清除碰撞
    uint8_t apv_pwr_off;      // 同意下电
    uint8_t end_chg_req;      // 结束充电
    uint8_t adcu_pwr_on_req;  // adcu上电
    uint8_t mcu_pwr_on_req;   // mcu上电
    uint8_t led_pwrup;        // led上电
    uint8_t eps_pwrup;        // eps上电
    uint8_t ccu_pwrup;        // ccu上电
    uint8_t obd_pwrup;        // obd上电
    uint8_t wfc_pwrup;        // 无线充电上电
    uint8_t dchager_pwrup;    // 直流充电上电
    uint8_t park_enable;      // 驻车使能
} PowerCmd;

typedef struct veh_info
{
    uint8_t software_ver_num; // 软件版本号
    uint8_t hardware_ver_num; // 硬件版本号
    uint8_t bat_soc;          // 电量
    uint8_t remain_water;     // 剩余水量
    uint8_t remain_trash_bin; // 剩余垃圾仓余量
} VehInfo;

typedef struct veh_state
{
    uint8_t driving_mode;              // 驾驶模式
    uint8_t veh_run_lock_rsn;          // 车辆锁定原因
    uint8_t veh_err_level;             // 整车故障等级
    uint8_t ft_crash_st;               // 前触边状态
    uint8_t rr_crash_st;               // 后触边状态
    uint8_t veh_emgcy_swh_st;          // 急停开关
    uint8_t lv_bat_low_volt;           // vcu供电欠压
    uint8_t bat_low_soc;               // 电量过低
    uint8_t bms_err_level;             // bms故障等级
    uint8_t mcu_err_level;             // mcu故障等级
    uint8_t ehb_err_level;             // ehb故障等级
    uint8_t eps_err_level;             // eps故障等级
    uint8_t epb_err_level;             // epb故障等级
    uint8_t ccu_err_level;             // ccu故障等级
    uint8_t dump_sys_err_lvl;          // 倾倒系统故障等级
    uint8_t clean_sys_err_lvl;         // 清扫系统故障等级
    uint8_t can_bus_off_st;            // bus off
    uint8_t seg_code_disp_offline_err; // 断码屏离线
    uint8_t led_disp_offline_err;      // led点阵屏离线
    uint8_t chg_inhibit_flt;           // 禁止充电
    uint8_t pwr_up_inhibit_flt;        // 禁止上电
    uint8_t ad_emgcy_stop_st;          // 远程状态急停
    uint8_t veh_emgcy_stop_reason;     // 急停原因
    uint8_t veh_err_code;              // 整车故障码
    uint8_t rcu_err_level;             // rcu故障等级
    uint8_t pmu_err_level;             // pmu故障等级
} VehState;                            // 整车状态

typedef struct mcu_state
{
    uint8_t ready;        // 就绪
    uint8_t gear;         // 挡位
    uint16_t motor_speed; // 电机转速
    uint32_t fault_code;  // 故障码
} McuState;               // 轮毂状态

typedef struct sweep_status
{
    uint8_t fender_sts;            // 挡板控制 0 无效，1 提起，2 关闭
    uint8_t one_clk_clean_sts;     // 一键清扫 0 无效，1 开启，2 复位，3 关闭
    uint8_t one_clk_dump_sts;      // 一键倒垃圾 0 无效，1 开启，2 复位，3 关闭
    uint8_t water_pump_sts;        // 水泵 0 无效，1 开启，2 关闭
    uint8_t vbr_sts;               // 震尘 0 无效，1 开启，2 关闭
    uint8_t water_add_sts;         // 加水 0 无效，1 开启，2 关闭
    uint8_t sweeping_sts;          // 清扫请求 0 无效，1 开启，2 关闭
    uint8_t side_brush_lift_sts;   // 边刷升降 0 无效，1 上升，2 下降
    uint8_t side_brush_extend_sts; // 边刷伸缩 0 无效，1 伸出，2 缩回
    uint8_t main_brush_lift_sts;   // 主刷升降 0 无效，1 上升，2 下降
    uint8_t dust_bin_lift_sts;     // 垃圾桶升降 0 无效，1 上升，2 下降
    uint8_t dust_bin_dump_sts;     // 垃圾桶倾倒 0 无效，1 倾倒，2 复位
    uint8_t dust_bin_open_sts;     // 垃圾桶开启 0 无效，1 开启，2 关闭
    uint8_t main_brush_sts;        // 主刷电机开启 0 无效，1 开启，2 关闭
    uint8_t side_brush_sts;        // 边刷电机开启 0 无效，1 开启，2 关闭
    uint8_t blower_sts;            // 风机开启 0 无效，1 开启，2 关闭
    uint8_t high_water_pump_sts;   // 高压水泵开启 0 无效，1 开启，2 关闭
    uint8_t vacuum_sts;            // 吸尘开启 0 无效，1 开启，2 关闭
    uint8_t dust_bin_compress_sts; // 垃圾压缩开启 0 无效，1 开启，2 关闭
    uint8_t wash_valve_sts;        // 清洗电磁阀 0 无效，1 开启，2 关闭
    uint8_t clean_valve_sts;       // 喷水电磁阀 0 无效，1 开启，2 关闭
    uint8_t high_pump_adjust_sts;  // 高压水泵调节 0 无效，1 开启，2 复位 3 停止
    uint8_t wash_probe_adjust_sts; // 清洗探头调节 0 无效，1 开启，2 复位 3 停止
    uint8_t dustbin_full_st;       // 垃圾桶满溢
    uint8_t remain_water;          // 剩余水量
    uint8_t side_brush_extend_pos; // 边刷伸缩位置
    uint8_t side_brush_lift_pos;   // 边刷升降位置
    uint8_t main_brush_pos;        // 主刷位置
    uint8_t high_pump_angle;       // 高压水枪角度
} SweepStatus;

typedef struct drv_state
{
    uint8_t park_st; // 1 驻车状态
    // 刹车状态
    uint8_t brk_work_mode; // 刹车工作模式 0踏板，1压力
    double brk_brake_val;  // 刹车踏板制动量 （0 到 100 %）
    uint8_t brk_pressure;  // 刹车制动压力(0-80)
    // 驱动状态
    uint8_t drv_ctrl_mode;  // 控制模式：0 踏板，1 速度
    uint8_t drv_gear;       // 挡位
    double drv_pedpos;      // 油门大小 0-100%
    double drv_veh_spd;     // 速度
    double drv_veh_acc_spd; // 加速度
    double drv_spd_limit;   // 限速

    // 转向状态
    uint8_t str_work_mode;  // 工作模式 0 助力，1线控
    double str_angle;       // 目标角度（-80°到80°）
    double str_angle_speed; // 角速度 （50 到 450）
    uint8_t str_center_st;  // 请求对中
    // 轮毂状态
    McuState mcu_state_l; // 左轮毂
    McuState mcu_state_r; // 左轮毂
} DrvState;               // 底盘控制状态

typedef struct pwr_state
{
    uint8_t veh_pwrup;       // 整车电源指令，0 keep,1 power up 2 shutdown 3 restart
    uint8_t wl_chg_wake_up;  // 无线充电唤醒 0 false 1 true
    uint8_t adcu_pwrup;      // adcu电源状态
    uint8_t mcu_pwrup;       // mcu电源状态
    uint8_t led_pwrup;       // 灯光电源状态
    uint8_t eps_pwrup;       // eps电源状态
    uint8_t ccu_pwrup;       // ccu电源状态
    uint8_t obd_pwrup;       // obd电源状态
    uint8_t wfc_pwrup;       // 无线充电状态
    uint8_t dchager_pwrup;   // 直流充电状态
    uint8_t power_off_req;   // 下电请求
    uint8_t estop_sts;       // 急停状态
    uint8_t park_enable_sts; // 驻车使能
} PwrState;                  // 电源状态

typedef struct body_state
{
    uint8_t warning_lamp;   // 警示灯
    uint8_t head_lamp;      // 大灯
    uint8_t dbl_flash_lamp; // 双闪
    uint8_t turn_l_lamp;    // 左转向灯
    uint8_t turn_r_lamp;    // 右转向
    uint8_t back_lamp;      // 倒车灯
    uint8_t buzzer;         // 蜂鸣器
    uint8_t horn;           // 喇叭
    uint8_t brk_lamp;       // 制动灯
    uint8_t fog_lamp;       // 雾灯
    uint8_t width_lamp;     // 视廓灯
    uint8_t wiper;          // 雨刷
} BodyState;                // 车身状态

typedef struct chassis_control
{
    BodyCmd body;   // 车身
    BrakeCmd brake; // 刹车
    DrvCmd drv;     // 驱动
    SteerCmd steer; // 转向
    PowerCmd power; // 电源
    SweepCmd sweep; // 清扫
    RcuCmd rcu;     // 遥控指令
} ChassisCmd;       // 底盘控制

typedef struct chassis_status
{
    VehInfo veh_info; // 整车信息
    // 底盘控制状态
    DrvState drv_state;
    // 车身状态
    BodyState body_state;
    // 电源状态
    PwrState pwr_state;
    // 清扫状态
    SweepStatus sweep; // 清扫状态
    // 整车状态
    VehState veh_state;
} ChassisStatus; // 底盘状态
#endif           // COMMON_VCU_STATUS_H_
