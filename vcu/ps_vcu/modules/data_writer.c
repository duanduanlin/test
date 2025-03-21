/*
 * @Author: hanson
 * @Date: 2025-02-21 15:34:08
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-15 14:28:25
 * @Description:
 * @FilePath: \ps_vcu\modules\data_writer.c
 */
#include "fdcan.h"
#include "common/error_code.h"
#include "protocol/psa_can.h"
#include "modules/data_writer.h"
#include "modules/crc.h"
#include "modules/log.h"

#define CAN_SYNC_INTERNAL (10u)
#define DEFAULT_CYCLE_TIME_MS (100u)

// 消息打包函数指针
typedef int (*msg_pack)(CanMsg *msg);

// 发送数据信息结构
struct msg_send_info
{
    CanMsg msg;      // 消息
    msg_pack pack;   // 消息打包函数
    CanNet net;      // can网络
    int cycle_count; // 发送周期，即每间隔几次循环发送一次数据
};

// 发送数据缓存
static struct
{
    // 状态
    struct psa_can_vcu_info_t vcu_info;             // 整车信息
    struct psa_can_vcu_brake_status_t vcu_brk_st;   // 刹车状态
    struct psa_can_vcu_drive_status_t vcu_drv_st;   // 驱动状态
    struct psa_can_vcu_lamp_status_t vcu_lmp_st;    // 车身状态
    struct psa_can_vcu_power_sts_t vcu_pwr_st;      // 电源状态
    struct psa_can_vcu_steer_status_t vcu_str_st;   // 转向状态
    struct psa_can_vcu_sweep_status_t vcu_swp_st;   // 清扫状态
    struct psa_can_vcu_sweep_status1_t vcu_swp_st1; // 清扫状态1
    struct psa_can_vcu_veh_state_t veh_state;       // vcu状态

    // 指令
    struct psa_can_ccu_cmd_t ccu_cmd;
    struct psa_can_eps_cmd_t eps_cmd;
    struct psa_can_pmu_cmd_t pmu_cmd;
    struct psa_can_mcu_cmdl_t mcu_cmd_l;
    struct psa_can_mcu_cmdr_t mcu_cmd_r;
} s_send_data_cache;

// 发送消息处理函数声明
static int vcu_info_pack(CanMsg *msg);
static int vcu_brake_status_pack(CanMsg *msg);
static int vcu_drive_status_pack(CanMsg *msg);
static int vcu_lamp_status_pack(CanMsg *msg);
static int vcu_power_status_pack(CanMsg *msg);
static int vcu_steer_status_pack(CanMsg *msg);
static int vcu_sweep_status_pack(CanMsg *msg);
static int vcu_sweep_status1_pack(CanMsg *msg);
static int vcu_veh_state_pack(CanMsg *msg);
static int ccu_cmd_pack(CanMsg *msg);
static int eps_cmd_pack(CanMsg *msg);
static int pmu_cmd_pack(CanMsg *msg);
static int mcu_cmd_l_pack(CanMsg *msg);
static int mcu_cmd_r_pack(CanMsg *msg);

// 发送消息信息表
static struct msg_send_info s_msg_send_map[] = {
    {.msg = {.id = PSA_CAN_VCU_INFO_FRAME_ID,
             .len = PSA_CAN_VCU_INFO_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = vcu_info_pack,
     .net = CanNetA,
     .cycle_count = (PSA_CAN_VCU_INFO_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
    {.msg = {.id = PSA_CAN_VCU_BRAKE_STATUS_FRAME_ID,
             .len = PSA_CAN_VCU_BRAKE_STATUS_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = vcu_brake_status_pack,
     .net = CanNetA,
     .cycle_count = (PSA_CAN_VCU_BRAKE_STATUS_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
    {.msg = {.id = PSA_CAN_VCU_DRIVE_STATUS_FRAME_ID,
             .len = PSA_CAN_VCU_DRIVE_STATUS_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = vcu_drive_status_pack,
     .net = CanNetA,
     .cycle_count = (PSA_CAN_VCU_DRIVE_STATUS_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
    {.msg = {.id = PSA_CAN_VCU_LAMP_STATUS_FRAME_ID,
             .len = PSA_CAN_VCU_LAMP_STATUS_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = vcu_lamp_status_pack,
     .net = CanNetA,
     .cycle_count = (PSA_CAN_VCU_LAMP_STATUS_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
    {.msg = {.id = PSA_CAN_VCU_POWER_STS_FRAME_ID,
             .len = PSA_CAN_VCU_POWER_STS_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = vcu_power_status_pack,
     .net = CanNetA,
     .cycle_count = (PSA_CAN_VCU_POWER_STS_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
    {.msg = {.id = PSA_CAN_VCU_STEER_STATUS_FRAME_ID,
             .len = PSA_CAN_VCU_STEER_STATUS_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = vcu_steer_status_pack,
     .net = CanNetA,
     .cycle_count = (PSA_CAN_VCU_STEER_STATUS_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
    {.msg = {.id = PSA_CAN_VCU_SWEEP_STATUS_FRAME_ID,
             .len = PSA_CAN_VCU_SWEEP_STATUS_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = vcu_sweep_status_pack,
     .net = CanNetA,
     .cycle_count = (PSA_CAN_VCU_SWEEP_STATUS_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
    {.msg = {.id = PSA_CAN_VCU_SWEEP_STATUS1_FRAME_ID,
             .len = PSA_CAN_VCU_SWEEP_STATUS1_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = vcu_sweep_status1_pack,
     .net = CanNetA,
     .cycle_count = (PSA_CAN_VCU_SWEEP_STATUS1_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
    {.msg = {.id = PSA_CAN_VCU_VEH_STATE_FRAME_ID,
             .len = PSA_CAN_VCU_VEH_STATE_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = vcu_veh_state_pack,
     .cycle_count = (PSA_CAN_VCU_VEH_STATE_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
    {.msg = {.id = PSA_CAN_CCU_CMD_FRAME_ID,
             .len = PSA_CAN_CCU_CMD_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = ccu_cmd_pack,
     .net = CanNetC,
     .cycle_count = (PSA_CAN_CCU_CMD_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
    {.msg = {.id = PSA_CAN_EPS_CMD_FRAME_ID,
             .len = PSA_CAN_EPS_CMD_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = eps_cmd_pack,
     .net = CanNetC,
     .cycle_count = (PSA_CAN_EPS_CMD_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
    {.msg = {.id = PSA_CAN_MCU_CMDL_FRAME_ID,
             .len = PSA_CAN_MCU_CMDL_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = mcu_cmd_l_pack,
     .net = CanNetC,
     .cycle_count = (PSA_CAN_MCU_CMDL_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
    {.msg = {.id = PSA_CAN_MCU_CMDR_FRAME_ID,
             .len = PSA_CAN_MCU_CMDR_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = mcu_cmd_r_pack,
     .net = CanNetC,
     .cycle_count = (PSA_CAN_MCU_CMDR_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
    {.msg = {.id = PSA_CAN_PMU_CMD_FRAME_ID,
             .len = PSA_CAN_PMU_CMD_LENGTH,
             .rtr = FRAME_TYPE_DATA},
     .pack = pmu_cmd_pack,
     .net = CanNetC,
     .cycle_count = (PSA_CAN_PMU_CMD_CYCLE_TIME_MS / CAN_SYNC_INTERNAL)},
};

// 发送消息信息表大小
static int s_msg_send_map_size = sizeof(s_msg_send_map) / sizeof(struct msg_send_info);

/**
 * @brief pmu 命令打包
 *
 * @param msg
 * @return int
 */
static int pmu_cmd_pack(CanMsg *msg)
{
    int ret = 0;
    s_send_data_cache.pmu_cmd.cu_pwr_cmd_roll_cnt++;
    s_send_data_cache.pmu_cmd.cu_pwr_cmd_roll_cnt %= 0xF;
    ret = psa_can_pmu_cmd_pack(msg->buffer, &s_send_data_cache.pmu_cmd, msg->len);
    msg->buffer[msg->len - 1] = Calculate_Crc(msg->buffer, msg->len - 1);
    return ret;
}

/**
 * @brief mcu 命令打包
 *
 * @param msg
 * @return int
 */
static int mcu_cmd_l_pack(CanMsg *msg)
{
    int ret = 0;
    s_send_data_cache.mcu_cmd_l.mcu_cmd_roll_cnt++;
    s_send_data_cache.mcu_cmd_l.mcu_cmd_roll_cnt %= 0xF;
    ret = psa_can_mcu_cmdl_pack(msg->buffer, &s_send_data_cache.mcu_cmd_l, msg->len);
    msg->buffer[msg->len - 1] = Calculate_Crc(msg->buffer, msg->len - 1);
    return ret;
}

/**
 * @brief mcu 命令打包
 *
 * @param msg
 * @return int
 */
static int mcu_cmd_r_pack(CanMsg *msg)
{
    int ret = 0;
    s_send_data_cache.mcu_cmd_r.mcu_cmd_roll_cnt++;
    s_send_data_cache.mcu_cmd_r.mcu_cmd_roll_cnt %= 0xF;
    ret = psa_can_mcu_cmdr_pack(msg->buffer, &s_send_data_cache.mcu_cmd_r, msg->len);
    msg->buffer[msg->len - 1] = Calculate_Crc(msg->buffer, msg->len - 1);
    return ret;
}

/**
 * @brief eps 命令打包
 *
 * @param msg
 * @return int
 */
static int eps_cmd_pack(CanMsg *msg)
{
    return psa_can_eps_cmd_pack(msg->buffer, &s_send_data_cache.eps_cmd, msg->len);
}

/**
 * @brief ccu命令打包
 *
 * @param msg
 * @return int
 */
static int ccu_cmd_pack(CanMsg *msg)
{
    int ret = 0;
    s_send_data_cache.ccu_cmd.ccu_cmd_roll_cnt++;
    s_send_data_cache.ccu_cmd.ccu_cmd_roll_cnt %= 0xF;
    ret = psa_can_ccu_cmd_pack(msg->buffer, &s_send_data_cache.ccu_cmd, msg->len);
    msg->buffer[msg->len - 1] = Calculate_Crc(msg->buffer, msg->len - 1);
    return ret;
}

/**
 * @brief vcu vhe状态打包
 *
 * @param msg
 * @return int
 */
static int vcu_veh_state_pack(CanMsg *msg)
{
    int ret = 0;
    ret = psa_can_vcu_veh_state_pack(msg->buffer, &s_send_data_cache.veh_state, msg->len);
    msg->buffer[msg->len - 1] = Calculate_Crc(msg->buffer, msg->len - 1);
    return ret;
}

/**
 * @brief vcu清扫状态打包
 *
 * @param msg
 * @return int
 */
static int vcu_info_pack(CanMsg *msg)
{
    int ret = 0;
    s_send_data_cache.vcu_info.vcu_info_roll_cnt++;
    s_send_data_cache.vcu_info.vcu_info_roll_cnt %= 0xF;
    ret = psa_can_vcu_info_pack(msg->buffer, &s_send_data_cache.vcu_info, msg->len);
    msg->buffer[msg->len - 1] = Calculate_Crc(msg->buffer, msg->len - 1);
    return ret;
}

/**
 * @brief vcu刹车状态打包
 *
 * @param msg
 * @return int
 */
static int vcu_brake_status_pack(CanMsg *msg)
{
    int ret = 0;
    s_send_data_cache.vcu_brk_st.vcu_brk_status_roll_cnt++;
    s_send_data_cache.vcu_brk_st.vcu_brk_status_roll_cnt %= 0xF;
    ret = psa_can_vcu_brake_status_pack(msg->buffer, &s_send_data_cache.vcu_brk_st, msg->len);
    msg->buffer[msg->len - 1] = Calculate_Crc(msg->buffer, msg->len - 1);
    return ret;
}

/**
 * @brief vcu驱动状态打包
 *
 * @param msg
 * @return int
 */
static int vcu_drive_status_pack(CanMsg *msg)
{
    int ret = 0;
    s_send_data_cache.vcu_drv_st.vcu_drv_status_roll_cnt++;
    s_send_data_cache.vcu_drv_st.vcu_drv_status_roll_cnt %= 0xF;
    ret = psa_can_vcu_drive_status_pack(msg->buffer, &s_send_data_cache.vcu_drv_st, msg->len);
    msg->buffer[msg->len - 1] = Calculate_Crc(msg->buffer, msg->len - 1);
    return ret;
}

/**
 * @brief vcu车身状态打包
 *
 * @param msg
 * @return int
 */
static int vcu_lamp_status_pack(CanMsg *msg)
{
    int ret = 0;
    s_send_data_cache.vcu_lmp_st.vcu_lamp_status_roll_cnt++;
    s_send_data_cache.vcu_lmp_st.vcu_lamp_status_roll_cnt %= 0xF;
    ret = psa_can_vcu_lamp_status_pack(msg->buffer, &s_send_data_cache.vcu_lmp_st, msg->len);
    msg->buffer[msg->len - 1] = Calculate_Crc(msg->buffer, msg->len - 1);
    return ret;
}

/**
 * @brief vcu电源状态打包
 *
 * @param msg
 * @return int
 */
static int vcu_power_status_pack(CanMsg *msg)
{
    int ret = 0;
    s_send_data_cache.vcu_pwr_st.vcu_pwr_cmd_roll_cnt++;
    s_send_data_cache.vcu_pwr_st.vcu_pwr_cmd_roll_cnt %= 0xF;
    ret = psa_can_vcu_power_sts_pack(msg->buffer, &s_send_data_cache.vcu_pwr_st, msg->len);
    msg->buffer[msg->len - 1] = Calculate_Crc(msg->buffer, msg->len - 1);
    return ret;
}

/**
 * @brief vcu转向状态打包
 *
 * @param msg
 * @return int
 */
static int vcu_steer_status_pack(CanMsg *msg)
{
    int ret = 0;
    s_send_data_cache.vcu_str_st.vcu_str_status_roll_cnt++;
    s_send_data_cache.vcu_str_st.vcu_str_status_roll_cnt %= 0xF;
    ret = psa_can_vcu_steer_status_pack(msg->buffer, &s_send_data_cache.vcu_str_st, msg->len);
    msg->buffer[msg->len - 1] = Calculate_Crc(msg->buffer, msg->len - 1);
    return ret;
}

/**
 * @brief vcu清扫状态打包
 *
 * @param msg
 * @return int
 */
static int vcu_sweep_status_pack(CanMsg *msg)
{
    int ret = 0;
    s_send_data_cache.vcu_swp_st.vcu_sweeper_sts_roll_cnt++;
    s_send_data_cache.vcu_swp_st.vcu_sweeper_sts_roll_cnt %= 0xF;
    ret = psa_can_vcu_sweep_status_pack(msg->buffer, &s_send_data_cache.vcu_swp_st, msg->len);
    msg->buffer[msg->len - 1] = Calculate_Crc(msg->buffer, msg->len - 1);
    return ret;
}

/**
 * @brief vcu清扫状态1打包
 *
 * @param msg
 * @return int
 */
static int vcu_sweep_status1_pack(CanMsg *msg)
{
    int ret = 0;
    s_send_data_cache.vcu_swp_st1.vcu_sweep_status2_roll_cnt++;
    s_send_data_cache.vcu_swp_st1.vcu_sweep_status2_roll_cnt %= 0xF;
    ret = psa_can_vcu_sweep_status1_pack(msg->buffer, &s_send_data_cache.vcu_swp_st1, msg->len);
    msg->buffer[msg->len - 1] = Calculate_Crc(msg->buffer, msg->len - 1);
    return ret;
}

/**
 * @brief 更新整车信息到canmsg
 *
 */
static void update_veh_info(const ChassisStatus *status)
{
    if (status != NULL)
    {
        s_send_data_cache.vcu_info.vcu_software_ver_num = psa_can_vcu_info_vcu_software_ver_num_encode(status->veh_info.software_ver_num);
        s_send_data_cache.vcu_info.vcu_hardware_ver_num = psa_can_vcu_info_vcu_software_ver_num_encode(status->veh_info.software_ver_num);
        s_send_data_cache.vcu_info.vcu_bat_soc = psa_can_vcu_info_vcu_bat_soc_encode(status->veh_info.bat_soc);
        s_send_data_cache.vcu_info.vcu_remain_water = psa_can_vcu_info_vcu_remain_water_encode(status->veh_info.remain_water);
        s_send_data_cache.vcu_info.vcu_remain_trash_bin = psa_can_vcu_info_vcu_remain_trash_bin_encode(status->veh_info.remain_trash_bin);
    }
}

/**
 * @brief 更新整车刹车到canmsg
 *
 */
static void update_brake_status(const ChassisStatus *status)
{
    if (status != NULL)
    {
        s_send_data_cache.vcu_brk_st.vcu_brk_ctrl_mode_sts = psa_can_vcu_brake_status_vcu_brk_ctrl_mode_sts_encode(status->drv_state.brk_work_mode);
        s_send_data_cache.vcu_brk_st.vcu_brk_park_enable_sts = psa_can_vcu_brake_status_vcu_brk_ctrl_mode_sts_encode(status->drv_state.park_st);
        s_send_data_cache.vcu_brk_st.vcu_brk_act_pedpos = psa_can_vcu_brake_status_vcu_brk_ctrl_mode_sts_encode(status->drv_state.brk_brake_val);
        s_send_data_cache.vcu_brk_st.vcu_brk_act_press = psa_can_vcu_brake_status_vcu_brk_ctrl_mode_sts_encode(status->drv_state.brk_pressure);
    }
}

/**
 * @brief 更新驱动信息到canmsg
 *
 */
static void update_drive_status(const ChassisStatus *status)
{
    if (status != NULL)
    {
        s_send_data_cache.vcu_drv_st.vcu_drving_mode = psa_can_vcu_drive_status_vcu_drving_mode_encode(status->veh_state.driving_mode);
        s_send_data_cache.vcu_drv_st.vcu_drv_ctrl_mode = psa_can_vcu_drive_status_vcu_drv_ctrl_mode_encode(status->drv_state.drv_ctrl_mode);
        s_send_data_cache.vcu_drv_st.vcu_drv_gear = psa_can_vcu_drive_status_vcu_drv_gear_encode(status->drv_state.drv_gear);
        s_send_data_cache.vcu_drv_st.vcu_drv_act_pedpos = psa_can_vcu_drive_status_vcu_drv_act_pedpos_encode(status->drv_state.drv_pedpos);
        s_send_data_cache.vcu_drv_st.vcu_drv_act_veh_spd = psa_can_vcu_drive_status_vcu_drv_act_pedpos_encode(status->drv_state.drv_veh_spd);
        s_send_data_cache.vcu_drv_st.vcu_drv_act_veh_acc = psa_can_vcu_drive_status_vcu_drv_act_pedpos_encode(status->drv_state.drv_veh_acc_spd);
        s_send_data_cache.vcu_drv_st.vcu_drv_veh_spd_limit = psa_can_vcu_drive_status_vcu_drv_act_pedpos_encode(status->drv_state.drv_spd_limit);
    }
}

/**
 * @brief 更新车身信息到canmsg
 *
 */
static void update_lamp_status(const ChassisStatus *status)
{
    if (status != NULL)
    {
        s_send_data_cache.vcu_lmp_st.vcu_head_lamp_sts = psa_can_vcu_lamp_status_vcu_head_lamp_sts_encode(status->body_state.head_lamp);
        s_send_data_cache.vcu_lmp_st.vcu_dbl_flash_lamp_sts = psa_can_vcu_lamp_status_vcu_dbl_flash_lamp_sts_encode(status->body_state.dbl_flash_lamp);
        s_send_data_cache.vcu_lmp_st.vcu_turn_l_lamp_sts = psa_can_vcu_lamp_status_vcu_turn_l_lamp_sts_encode(status->body_state.turn_l_lamp);
        s_send_data_cache.vcu_lmp_st.vcu_turn_r_lamp_sts = psa_can_vcu_lamp_status_vcu_turn_r_lamp_sts_encode(status->body_state.turn_r_lamp);
        s_send_data_cache.vcu_lmp_st.vcu_reverse_lamp_sts = psa_can_vcu_lamp_status_vcu_reverse_lamp_sts_encode(status->body_state.back_lamp);
        s_send_data_cache.vcu_lmp_st.vcu_buzzer_sts = psa_can_vcu_lamp_status_vcu_buzzer_sts_encode(status->body_state.buzzer);
        s_send_data_cache.vcu_lmp_st.vcu_horn_sts = psa_can_vcu_lamp_status_vcu_horn_sts_encode(status->body_state.horn);
        s_send_data_cache.vcu_lmp_st.vcu_warning_lamp_sts = psa_can_vcu_lamp_status_vcu_warning_lamp_sts_encode(status->body_state.warning_lamp);
        s_send_data_cache.vcu_lmp_st.vcu_brake_lamp_sts = psa_can_vcu_lamp_status_vcu_brake_lamp_sts_encode(status->body_state.brk_lamp);
        s_send_data_cache.vcu_lmp_st.vcu_fog_lamp_sts = psa_can_vcu_lamp_status_vcu_fog_lamp_sts_encode(status->body_state.fog_lamp);
        s_send_data_cache.vcu_lmp_st.vcu_width_lamp_sts = psa_can_vcu_lamp_status_vcu_width_lamp_sts_encode(status->body_state.width_lamp);
        s_send_data_cache.vcu_lmp_st.vcu_wiper_sts = psa_can_vcu_lamp_status_vcu_wiper_sts_encode(status->body_state.wiper);
    }
}

/**
 * @brief 更新电源信息到canmsg
 *
 */
static void update_power_status(const ChassisStatus *status)
{
    if (status != NULL)
    {
        s_send_data_cache.vcu_pwr_st.vcu_veh_pwrup_sts = psa_can_vcu_power_sts_vcu_veh_pwrup_sts_encode(status->pwr_state.veh_pwrup);
        s_send_data_cache.vcu_pwr_st.vcu_wl_chg_wake_up_sts = psa_can_vcu_power_sts_vcu_wl_chg_wake_up_sts_encode(status->pwr_state.wl_chg_wake_up);
    }
}

/**
 * @brief 更新转向信息到canmsg
 *
 */
static void update_steer_status(const ChassisStatus *status)
{
    if (status != NULL)
    {
        s_send_data_cache.vcu_str_st.vcu_str_work_mode = psa_can_vcu_steer_status_vcu_str_work_mode_encode(status->drv_state.str_work_mode);
        s_send_data_cache.vcu_str_st.vcu_str_angle = psa_can_vcu_steer_status_vcu_str_angle_encode(status->drv_state.str_angle);
        s_send_data_cache.vcu_str_st.vcu_str_angle_spd = psa_can_vcu_steer_status_vcu_str_angle_spd_encode(status->drv_state.str_angle_speed);
        s_send_data_cache.vcu_str_st.vcu_str_centering_sts = psa_can_vcu_steer_status_vcu_str_centering_sts_encode(status->drv_state.str_center_st);
    }
}

/**
 * @brief 更新清扫信息到canmsg
 *
 */
static void update_sweep_status(const ChassisStatus *status)
{
    if (status != NULL)
    {
        s_send_data_cache.vcu_swp_st.vcu_fender_sts = psa_can_vcu_sweep_status_vcu_fender_sts_encode(status->sweep.fender_sts);
        s_send_data_cache.vcu_swp_st.vcu_water_pump_sts = psa_can_vcu_sweep_status_vcu_water_pump_sts_encode(status->sweep.water_pump_sts);
        s_send_data_cache.vcu_swp_st.vcu_one_clk_dump_sts = psa_can_vcu_sweep_status_vcu_one_clk_dump_sts_encode(status->sweep.one_clk_dump_sts);
        s_send_data_cache.vcu_swp_st.vcu_one_clk_clean_sts = psa_can_vcu_sweep_status_vcu_one_clk_clean_sts_encode(status->sweep.one_clk_clean_sts);
        s_send_data_cache.vcu_swp_st.vcu_sweeping_sts = psa_can_vcu_sweep_status_vcu_sweeping_sts_encode(status->sweep.sweeping_sts);
        s_send_data_cache.vcu_swp_st.vcu_water_add_sts = psa_can_vcu_sweep_status_vcu_water_add_sts_encode(status->sweep.water_add_sts);
        s_send_data_cache.vcu_swp_st.vcu_vbr_sts = psa_can_vcu_sweep_status_vcu_vbr_sts_encode(status->sweep.vbr_sts);
        s_send_data_cache.vcu_swp_st.vcu_dust_bin_lift_sts = psa_can_vcu_sweep_status_vcu_dust_bin_lift_sts_encode(status->sweep.dust_bin_lift_sts);
        s_send_data_cache.vcu_swp_st.vcu_main_brush_lift_sts = psa_can_vcu_sweep_status_vcu_main_brush_lift_sts_encode(status->sweep.main_brush_lift_sts);
        s_send_data_cache.vcu_swp_st.vcu_side_brush_extend_sts = psa_can_vcu_sweep_status_vcu_side_brush_extend_sts_encode(status->sweep.side_brush_extend_sts);
        s_send_data_cache.vcu_swp_st.vcu_side_brush_lift_sts = psa_can_vcu_sweep_status_vcu_side_brush_lift_sts_encode(status->sweep.side_brush_lift_sts);
        s_send_data_cache.vcu_swp_st.vcu_side_brush_sts = psa_can_vcu_sweep_status_vcu_side_brush_sts_encode(status->sweep.side_brush_sts);
        s_send_data_cache.vcu_swp_st.vcu_main_brush_sts = psa_can_vcu_sweep_status_vcu_main_brush_sts_encode(status->sweep.main_brush_sts);
        s_send_data_cache.vcu_swp_st.vcu_dust_bin_open_sts = psa_can_vcu_sweep_status_vcu_dust_bin_open_sts_encode(status->sweep.dust_bin_open_sts);
        s_send_data_cache.vcu_swp_st.vcu_dust_bin_dump_sts = psa_can_vcu_sweep_status_vcu_dust_bin_dump_sts_encode(status->sweep.dust_bin_dump_sts);
        s_send_data_cache.vcu_swp_st.vcu_dust_bin_compress_sts = psa_can_vcu_sweep_status_vcu_dust_bin_compress_sts_encode(status->sweep.dust_bin_compress_sts);
        s_send_data_cache.vcu_swp_st.vcu_vacuum_sts = psa_can_vcu_sweep_status_vcu_vacuum_sts_encode(status->sweep.vacuum_sts);
        s_send_data_cache.vcu_swp_st.vcu_high_water_pump_sts = psa_can_vcu_sweep_status_vcu_high_water_pump_sts_encode(status->sweep.high_water_pump_sts);
        s_send_data_cache.vcu_swp_st.vcu_blower_sts = psa_can_vcu_sweep_status_vcu_blower_sts_encode(status->sweep.blower_sts);
        s_send_data_cache.vcu_swp_st.vcu_wash_probe_adjust_sts = psa_can_vcu_sweep_status_vcu_wash_probe_adjust_sts_encode(status->sweep.wash_probe_adjust_sts);
        s_send_data_cache.vcu_swp_st.vcu_high_pump_adjust_sts = psa_can_vcu_sweep_status_vcu_high_pump_adjust_sts_encode(status->sweep.high_pump_adjust_sts);
        s_send_data_cache.vcu_swp_st.vcu_wash_vale_sts = psa_can_vcu_sweep_status_vcu_wash_vale_sts_encode(status->sweep.wash_valve_sts);
        s_send_data_cache.vcu_swp_st.vcu_clean_vale_sts = psa_can_vcu_sweep_status_vcu_clean_vale_sts_encode(status->sweep.clean_valve_sts);
    }
}

/**
 * @brief 更新清扫信息1到canmsg
 *
 */
static void update_sweep_status1(const ChassisStatus *status)
{
    if (status != NULL)
    {
        s_send_data_cache.vcu_swp_st1.vcu_dustbin_full_st = psa_can_vcu_sweep_status1_vcu_dustbin_full_st_encode(status->sweep.dustbin_full_st);
        s_send_data_cache.vcu_swp_st1.vcu_remain_water = psa_can_vcu_sweep_status1_vcu_remain_water_encode(status->sweep.remain_water);
        s_send_data_cache.vcu_swp_st1.vcu_side_brush_extend_pos_st = psa_can_vcu_sweep_status1_vcu_side_brush_extend_pos_st_encode(status->sweep.side_brush_extend_pos);
        s_send_data_cache.vcu_swp_st1.vcu_side_brush_lift_pos_st = psa_can_vcu_sweep_status1_vcu_side_brush_lift_pos_st_encode(status->sweep.side_brush_lift_pos);
        s_send_data_cache.vcu_swp_st1.vcu_main_brush_pos_st = psa_can_vcu_sweep_status1_vcu_main_brush_pos_st_encode(status->sweep.main_brush_pos);
        s_send_data_cache.vcu_swp_st1.vcu_high_pump_angle_st = psa_can_vcu_sweep_status1_vcu_high_pump_angle_st_encode(status->sweep.high_pump_angle);
        // s_send_data_cache.vcu_swp_st1.vcu_wash_probe_adjust_st = psa_can_vcu_sweep_status1_vcu_wash_probe_adjust_st_encode(status->sweep.high_pump_angle);
    }
}

/**
 * @brief 更新整车状态到canmsg
 *
 */
static void update_veh_state(const ChassisStatus *status)
{
    if (status != NULL)
    {
        s_send_data_cache.veh_state.vcu_veh_run_mode = psa_can_vcu_veh_state_vcu_veh_run_mode_encode(status->veh_state.driving_mode);
        s_send_data_cache.veh_state.vcu_veh_run_lock_rsn = psa_can_vcu_veh_state_vcu_veh_run_lock_rsn_encode(status->veh_state.veh_run_lock_rsn);
        s_send_data_cache.veh_state.vcu_veh_err_level = psa_can_vcu_veh_state_vcu_veh_err_level_encode(status->veh_state.veh_err_level);
        s_send_data_cache.veh_state.vcu_ft_crash_st = psa_can_vcu_veh_state_vcu_ft_crash_st_encode(status->veh_state.ft_crash_st);
        s_send_data_cache.veh_state.vcu_rr_crash_st = psa_can_vcu_veh_state_vcu_rr_crash_st_encode(status->veh_state.rr_crash_st);
        s_send_data_cache.veh_state.vcu_veh_emgcy_swh_st = psa_can_vcu_veh_state_vcu_veh_emgcy_swh_st_encode(status->veh_state.veh_emgcy_swh_st);
        s_send_data_cache.veh_state.vcu_lv_bat_low_volt = psa_can_vcu_veh_state_vcu_lv_bat_low_volt_encode(status->veh_state.lv_bat_low_volt);
        s_send_data_cache.veh_state.vcu_bat_low_soc = psa_can_vcu_veh_state_vcu_bat_low_soc_encode(status->veh_state.bat_low_soc);
        s_send_data_cache.veh_state.vcu_bms_err_level = psa_can_vcu_veh_state_vcu_bms_err_level_encode(status->veh_state.bms_err_level);
        s_send_data_cache.veh_state.vcu_mcu_err_level = psa_can_vcu_veh_state_vcu_mcu_err_level_encode(status->veh_state.mcu_err_level);
        s_send_data_cache.veh_state.vcu_ehb_err_level = psa_can_vcu_veh_state_vcu_ehb_err_level_encode(status->veh_state.ehb_err_level);
        s_send_data_cache.veh_state.vcu_eps_err_level = psa_can_vcu_veh_state_vcu_eps_err_level_encode(status->veh_state.eps_err_level);
        s_send_data_cache.veh_state.vcu_epb_err_level = psa_can_vcu_veh_state_vcu_epb_err_level_encode(status->veh_state.epb_err_level);
        s_send_data_cache.veh_state.vcu_ccu_err_level = psa_can_vcu_veh_state_vcu_ccu_err_level_encode(status->veh_state.ccu_err_level);
        s_send_data_cache.veh_state.vcu_dump_sys_err_lvl = psa_can_vcu_veh_state_vcu_dump_sys_err_lvl_encode(status->veh_state.dump_sys_err_lvl);
        s_send_data_cache.veh_state.vcu_clean_sys_err_lvl = psa_can_vcu_veh_state_vcu_clean_sys_err_lvl_encode(status->veh_state.clean_sys_err_lvl);
        s_send_data_cache.veh_state.vcu_can_bus_off_st = psa_can_vcu_veh_state_vcu_can_bus_off_st_encode(status->veh_state.can_bus_off_st);
        s_send_data_cache.veh_state.vcu_seg_code_disp_offline_err = psa_can_vcu_veh_state_vcu_seg_code_disp_offline_err_encode(status->veh_state.seg_code_disp_offline_err);
        s_send_data_cache.veh_state.vcu_led_disp_offline_err = psa_can_vcu_veh_state_vcu_led_disp_offline_err_encode(status->veh_state.led_disp_offline_err);
        s_send_data_cache.veh_state.vcu_chg_inhibit_flt = psa_can_vcu_veh_state_vcu_chg_inhibit_flt_encode(status->veh_state.chg_inhibit_flt);
        s_send_data_cache.veh_state.vcu_pwr_up_inhibit_flt = psa_can_vcu_veh_state_vcu_pwr_up_inhibit_flt_encode(status->veh_state.pwr_up_inhibit_flt);
        s_send_data_cache.veh_state.vcu_ad_emgcy_stop_st = psa_can_vcu_veh_state_vcu_ad_emgcy_stop_st_encode(status->veh_state.ad_emgcy_stop_st);
        s_send_data_cache.veh_state.vcu_veh_emgcy_stop_reason = psa_can_vcu_veh_state_vcu_veh_emgcy_stop_reason_encode(status->veh_state.veh_emgcy_stop_reason);
        s_send_data_cache.veh_state.vcu_veh_err_code = psa_can_vcu_veh_state_vcu_veh_err_code_encode(status->veh_state.veh_err_code);
        s_send_data_cache.veh_state.vcu_rcu_err_level = psa_can_vcu_veh_state_vcu_rcu_err_level_encode(status->veh_state.rcu_err_level);
        s_send_data_cache.veh_state.vcu_pmu_err_level = psa_can_vcu_veh_state_vcu_pmu_err_level_encode(status->veh_state.pmu_err_level);
    }
}

void Sync_Chassis_Status(const ChassisStatus *status)
{
    update_veh_info(status);
    update_brake_status(status);
    update_drive_status(status);
    update_lamp_status(status);
    update_power_status(status);
    update_steer_status(status);
    update_sweep_status(status);
    update_sweep_status1(status);
    update_veh_state(status);
}

void Sync_Drv_Cmd(const DrvCmd *drv, const SteerCmd *steer)
{
    if (steer != NULL)
    {
        s_send_data_cache.eps_cmd.eps_angle_calibrate = psa_can_eps_cmd_eps_angle_calibrate_encode(steer->center);
        s_send_data_cache.eps_cmd.eps_ctrl_enable = psa_can_eps_cmd_eps_ctrl_enable_encode(steer->work_mode);
        s_send_data_cache.eps_cmd.eps_target_angle = psa_can_eps_cmd_eps_target_angle_encode(steer->target_angle);
        s_send_data_cache.eps_cmd.eps_angle_speed = psa_can_eps_cmd_eps_angle_speed_encode(steer->angle_speed);
    }

    if (drv != NULL)
    {
        // left
        s_send_data_cache.mcu_cmd_l.working_mode = psa_can_mcu_cmdl_working_mode_encode(drv->ctrl_mode);
        s_send_data_cache.mcu_cmd_l.gear_setting = psa_can_mcu_cmdl_gear_setting_encode(drv->tgt_gear);
        s_send_data_cache.mcu_cmd_l.target_torque = psa_can_mcu_cmdl_target_torque_encode(drv->tgt_pedpos);
        // s_send_data_cache.mcu_cmd_l.target_speed = psa_can_mcu_cmdl_target_speed_encode(cmd->drv.tgt_veh_spd);

        // right
        s_send_data_cache.mcu_cmd_r.working_mode = psa_can_mcu_cmdr_working_mode_encode(drv->ctrl_mode);
        s_send_data_cache.mcu_cmd_r.gear_setting = psa_can_mcu_cmdr_gear_setting_encode(drv->tgt_gear);
        s_send_data_cache.mcu_cmd_r.target_torque = psa_can_mcu_cmdr_target_torque_encode(drv->tgt_pedpos);
        // s_send_data_cache.mcu_cmd_r.target_speed = psa_can_mcu_cmdl_target_speed_encode(cmd->drv.tgt_veh_spd);
    }
}

void Sync_Power_Cmd(const PowerCmd *cmd)
{
    if (cmd != NULL)
    {
        s_send_data_cache.pmu_cmd.vcu_veh_pwrup_cmd = psa_can_pmu_cmd_vcu_veh_pwrup_cmd_encode(cmd->veh_pwrup);
        s_send_data_cache.pmu_cmd.vcu_adcu_pwrup_cmd = psa_can_pmu_cmd_vcu_adcu_pwrup_cmd_encode(cmd->adcu_pwr_on_req);
        s_send_data_cache.pmu_cmd.vcu_mcu_pwrup_cmd = psa_can_pmu_cmd_vcu_mcu_pwrup_cmd_encode(cmd->mcu_pwr_on_req);
        s_send_data_cache.pmu_cmd.vcu_led_pwrup_cmd = psa_can_pmu_cmd_vcu_led_pwrup_cmd_encode(cmd->led_pwrup);
        s_send_data_cache.pmu_cmd.vcu_eps_pwrup_cmd = psa_can_pmu_cmd_vcu_eps_pwrup_cmd_encode(cmd->eps_pwrup);
        s_send_data_cache.pmu_cmd.vcu_ccu_pwrup_cmd = psa_can_pmu_cmd_vcu_ccu_pwrup_cmd_encode(cmd->ccu_pwrup);
        s_send_data_cache.pmu_cmd.vcu_obd_pwrup_cmd = psa_can_pmu_cmd_vcu_obd_pwrup_cmd_encode(cmd->obd_pwrup);
        s_send_data_cache.pmu_cmd.vcu_wfc_pwrup_cmd = psa_can_pmu_cmd_vcu_wfc_pwrup_cmd_encode(cmd->wfc_pwrup);
        s_send_data_cache.pmu_cmd.vcu_dchager_pwrup_cmd = psa_can_pmu_cmd_vcu_dchager_pwrup_cmd_encode(cmd->dchager_pwrup);
        s_send_data_cache.pmu_cmd.vcu_park_enable_cmd = psa_can_pmu_cmd_vcu_park_enable_cmd_encode(cmd->park_enable);
    }
}

void Sync_Sweep_Cmd(const SweepCmd *cmd)
{
    if (cmd != NULL)
    {
        s_send_data_cache.ccu_cmd.ccu_fender_ctrl = psa_can_ccu_cmd_ccu_fender_ctrl_encode(cmd->fender_ctrl);
        s_send_data_cache.ccu_cmd.ccu_water_pump_ctrl = psa_can_ccu_cmd_ccu_water_pump_ctrl_encode(cmd->water_pump_ctrl);
        s_send_data_cache.ccu_cmd.ccu_one_clk_dump_ctrl = psa_can_ccu_cmd_ccu_one_clk_dump_ctrl_encode(cmd->one_clk_dump_ctrl);
        s_send_data_cache.ccu_cmd.ccu_one_clk_clean_ctrl = psa_can_ccu_cmd_ccu_one_clk_clean_ctrl_encode(cmd->one_clk_clean_ctrl);
        s_send_data_cache.ccu_cmd.ccu_sweeping_ctrl = psa_can_ccu_cmd_ccu_sweeping_ctrl_encode(cmd->sweeping_ctrl);
        // s_send_data_cache.ccu_cmd.ccu_wpt_wakeup_ctrl = psa_can_ccu_cmd_ccu_wpt_wakeup_ctrl_encode(cmd->sweep.wpt_wakeup_ctrl);
        s_send_data_cache.ccu_cmd.ccu_water_add_ctrl = psa_can_ccu_cmd_ccu_water_add_ctrl_encode(cmd->water_add_ctrl);
        s_send_data_cache.ccu_cmd.ccu_vbr_ctrl = psa_can_ccu_cmd_ccu_vbr_ctrl_encode(cmd->vbr_ctrl);
        s_send_data_cache.ccu_cmd.ccu_dust_bin_lift_ctrl = psa_can_ccu_cmd_ccu_dust_bin_lift_ctrl_encode(cmd->dust_bin_lift_ctrl);
        s_send_data_cache.ccu_cmd.ccu_main_brush_lift_ctrl = psa_can_ccu_cmd_ccu_main_brush_lift_ctrl_encode(cmd->main_brush_lift_ctrl);
        s_send_data_cache.ccu_cmd.ccu_side_brush_extend_ctrl = psa_can_ccu_cmd_ccu_side_brush_extend_ctrl_encode(cmd->side_brush_extend_ctrl);
        s_send_data_cache.ccu_cmd.ccu_side_brush_lift_ctrl = psa_can_ccu_cmd_ccu_side_brush_lift_ctrl_encode(cmd->side_brush_lift_ctrl);
        s_send_data_cache.ccu_cmd.ccu_side_brush_ctrl = psa_can_ccu_cmd_ccu_side_brush_ctrl_encode(cmd->side_brush_ctrl);
        s_send_data_cache.ccu_cmd.ccu_main_brush_ctrl = psa_can_ccu_cmd_ccu_main_brush_ctrl_encode(cmd->main_brush_ctrl);
        s_send_data_cache.ccu_cmd.ccu_dust_bin_open_ctrl = psa_can_ccu_cmd_ccu_dust_bin_open_ctrl_encode(cmd->dust_bin_open_ctrl);
        s_send_data_cache.ccu_cmd.ccu_dust_bin_dump_ctrl = psa_can_ccu_cmd_ccu_dust_bin_dump_ctrl_encode(cmd->dust_bin_dump_ctrl);
        s_send_data_cache.ccu_cmd.ccu_dust_bin_compress_ctrl = psa_can_ccu_cmd_ccu_dust_bin_compress_ctrl_encode(cmd->dust_bin_compress_ctrl);
        s_send_data_cache.ccu_cmd.ccu_vacuum_ctrl = psa_can_ccu_cmd_ccu_vacuum_ctrl_encode(cmd->vacuum_ctrl);
        s_send_data_cache.ccu_cmd.ccu_high_water_pump_ctrl = psa_can_ccu_cmd_ccu_high_water_pump_ctrl_encode(cmd->high_water_pump_ctrl);
        s_send_data_cache.ccu_cmd.ccu_blower_ctrl = psa_can_ccu_cmd_ccu_blower_ctrl_encode(cmd->blower_ctrl);
        s_send_data_cache.ccu_cmd.ccu_wash_probe_adjust_ctrl = psa_can_ccu_cmd_ccu_wash_probe_adjust_ctrl_encode(cmd->wash_probe_adjust_ctrl);
        s_send_data_cache.ccu_cmd.ccu_high_pump_adjust_ctrl = psa_can_ccu_cmd_ccu_high_pump_adjust_ctrl_encode(cmd->high_pump_adjust_ctrl);
        s_send_data_cache.ccu_cmd.ccu_wash_valve_ctrl = psa_can_ccu_cmd_ccu_wash_valve_ctrl_encode(cmd->wash_valve_ctrl);
        s_send_data_cache.ccu_cmd.ccu_clean_valve_ctrl = psa_can_ccu_cmd_ccu_clean_valve_ctrl_encode(cmd->clean_valve_ctrl);
    }
}

void Can_Msg_Write()
{
    static int count = 0;

    // 同步状态到can总线
    for (int i = 0; i < s_msg_send_map_size; i++)
    {
        if ((count % s_msg_send_map[i].cycle_count) == 0)
        {
            CanMsg *msg = &s_msg_send_map[i].msg;
            s_msg_send_map[i].pack(msg);
            if (s_msg_send_map[i].net == CanNetA)
            {
                // LOG_INFO("T[A]:%x-%d:%x %x %x %x %x %x %x %x\r\n", msg->id, msg->len, msg->buffer[0], msg->buffer[1], msg->buffer[2], msg->buffer[3], msg->buffer[4], msg->buffer[5], msg->buffer[6], msg->buffer[7]);
                FDCAN1_Send_Msg(&s_msg_send_map[i].msg);
            }
            else
            {
                // LOG_INFO("T[C]:%x-%d:%x %x %x %x %x %x %x %x\r\n", msg->id, msg->len, msg->buffer[0], msg->buffer[1], msg->buffer[2], msg->buffer[3], msg->buffer[4], msg->buffer[5], msg->buffer[6], msg->buffer[7]);
                FDCAN2_Send_Msg(&s_msg_send_map[i].msg);
            }
        }
    }
    count++;
}
