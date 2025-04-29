/*
 * @Author: hanson
 * @Date: 2025-02-17 10:58:12
 * @LastEditors: dding3
 * @LastEditTime: 2025-04-27 14:23:21
 * @Description:
 * 基本的消息处理流程：
 * 1.根据消息id查表
 * 2.调用对应的处理函数
 * @FilePath: \ps_vcu\modules\data_reader.c
 */
#include "modules/crc.h"
#include "modules/data_reader.h"
#include "common/error_code.h"
#include "modules/log.h"
#include "protocol/psa_can.h"
#include "modules/diag.h"
#include "protocol/can_open.h"
#include "modules/ota_app.h"

// 接收数据缓存
static struct
{
    struct psa_can_adcu_lamp_cmd_t adcu_body_cmd;   // ADCU车身控制协议
    struct psa_can_adcu_brake_cmd_t adcu_brake_cmd; // ADCU踏板控制协议
    struct psa_can_adcu_drive_cmd_t adcu_drive_cmd; // ADCU驱动控制协议
    struct psa_can_adcu_power_cmd_t adcu_power_cmd; // ADCU电源控制协议
    struct psa_can_adcu_steer_cmd_t adcu_steer_cmd; // ADCU转向控制协议
    struct psa_can_adcu_sweep_cmd_t adcu_sweep_cmd; // ADCU清扫控制协议
    struct psa_can_adcu_date_time_t adcu_date_time; // ADCU时间同步
    // struct psa_can_tbox_nm_t tbox_nm;               // tobox心跳

    struct psa_can_ccu_status_t ccu_status;
    struct psa_can_ccu_status2_t ccu_status2;
    struct psa_can_ccu_error_code_status_t ccu_err_code;
    struct psa_can_rcu_ctrl_cmd_t rcu_ctrl_cmd;
    struct psa_can_eps_status_t eps_status;
    struct psa_can_bms_fault_t bms_fault;
    struct psa_can_bms_status_1_t bms_status_1;
    struct psa_can_mcu_status_l1_t mcu_status_l1;
    struct psa_can_mcu_status_l2_t mcu_status_l2;
    struct psa_can_mcu_status_l3_t mcu_status_l3;
    struct psa_can_mcu_status_r1_t mcu_status_r1;
    struct psa_can_mcu_status_r2_t mcu_status_r2;
    struct psa_can_mcu_status_r3_t mcu_status_r3;
    struct psa_can_pmu_status_t pmu_status;
} s_recv_data_cache;

// 消息处理函数指针
typedef int (*msg_handle)(const uint8_t *data, uint8_t len, DataReader *reader);

// 消息处理结构
struct msg_handle_info
{
    uint32_t id;       // can id
    CanNet net;        // can网络
    msg_handle handle; // 消息处理函数
};

// 接收消息处理函数声明
static int adcu_body_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int adcu_brake_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int adcu_drive_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int adcu_power_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int adcu_steer_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int adcu_sweep_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int adcu_date_time_handle(const uint8_t *data, uint8_t len, DataReader *reader);

// static int tbox_nm_handle(const uint8_t *data, uint8_t len, DataReader *reader);

static int ccu_status_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int ccu_status2_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int ccu_error_code_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int rcu_ctrl_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int eps_status_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int bms_fault_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int bms_status_1_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int mcu_status_l1_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int mcu_status_l2_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int mcu_status_l3_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int mcu_status_r1_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int mcu_status_r2_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int mcu_status_r3_handle(const uint8_t *data, uint8_t len, DataReader *reader);
static int pmu_status_handle(const uint8_t *data, uint8_t len, DataReader *reader);

static int sdo_server_handler(const uint8_t *data, uint8_t len, DataReader *reader);
static int nmt_boot_up_handler(const uint8_t *data, uint8_t len, DataReader *reader);

static int ota_cmd_209_handler(const uint8_t *data, uint8_t len, DataReader *reader);
static int ota_cmd_211_handler(const uint8_t *data, uint8_t len, DataReader *reader);
static int ota_cmd_200_handler(const uint8_t *data, uint8_t len, DataReader *reader);

// 接收消息处理函数表
static struct msg_handle_info s_recv_msg_handle_map[] = {
    {.id = PSA_CAN_ADCU_LAMP_CMD_FRAME_ID, .net = CanNetA, .handle = adcu_body_cmd_handle},
    {.id = PSA_CAN_ADCU_BRAKE_CMD_FRAME_ID, .net = CanNetA, .handle = adcu_brake_cmd_handle},
    {.id = PSA_CAN_ADCU_DRIVE_CMD_FRAME_ID, .net = CanNetA, .handle = adcu_drive_cmd_handle},
    {.id = PSA_CAN_ADCU_POWER_CMD_FRAME_ID, .net = CanNetA, .handle = adcu_power_cmd_handle},
    {.id = PSA_CAN_ADCU_STEER_CMD_FRAME_ID, .net = CanNetA, .handle = adcu_steer_cmd_handle},
    {.id = PSA_CAN_ADCU_SWEEP_CMD_FRAME_ID, .net = CanNetA, .handle = adcu_sweep_cmd_handle},
    {.id = PSA_CAN_ADCU_DATE_TIME_FRAME_ID, .net = CanNetA, .handle = adcu_date_time_handle},
    // {.id = PSA_CAN_TBOX_NM_FRAME_ID, .net = CanNetA, .handle = tbox_nm_handle},

    {.id = PSA_CAN_CCU_STATUS_FRAME_ID, .net = CanNetC, .handle = ccu_status_handle},
    {.id = PSA_CAN_CCU_STATUS2_FRAME_ID, .net = CanNetC, .handle = ccu_status2_handle},
    {.id = PSA_CAN_CCU_ERROR_CODE_STATUS_FRAME_ID, .net = CanNetC, .handle = ccu_error_code_handle},
    {.id = PSA_CAN_RCU_CTRL_CMD_FRAME_ID, .net = CanNetC, .handle = rcu_ctrl_cmd_handle},
    {.id = PSA_CAN_EPS_STATUS_FRAME_ID, .net = CanNetC, .handle = eps_status_handle},
    {.id = PSA_CAN_BMS_FAULT_FRAME_ID, .net = CanNetC, .handle = bms_fault_handle},
    {.id = PSA_CAN_BMS_STATUS_1_FRAME_ID, .net = CanNetC, .handle = bms_status_1_handle},
    {.id = PSA_CAN_MCU_STATUS_L1_FRAME_ID, .net = CanNetC, .handle = mcu_status_l1_handle},
    {.id = PSA_CAN_MCU_STATUS_L2_FRAME_ID, .net = CanNetC, .handle = mcu_status_l2_handle},
    {.id = PSA_CAN_MCU_STATUS_L3_FRAME_ID, .net = CanNetC, .handle = mcu_status_l3_handle},
    {.id = PSA_CAN_MCU_STATUS_R1_FRAME_ID, .net = CanNetC, .handle = mcu_status_r1_handle},
    {.id = PSA_CAN_MCU_STATUS_R2_FRAME_ID, .net = CanNetC, .handle = mcu_status_r2_handle},
    {.id = PSA_CAN_MCU_STATUS_R3_FRAME_ID, .net = CanNetC, .handle = mcu_status_r3_handle},
    {.id = PSA_CAN_PMU_STATUS_FRAME_ID, .net = CanNetC, .handle = pmu_status_handle},

    //canopen
    {.id = CAN_OPEN_NMT_BOOT_UP_FRAME_ID, .net = CanNetC, .handle = nmt_boot_up_handler},
    {.id = CAN_OPEN_SDO_SERVER_NODE_1_FRAME_ID, .net = CanNetC, .handle = sdo_server_handler},

    //ota
    {.id = OTA_CMD_209, .net = CanNetA, .handle = ota_cmd_209_handler},
    {.id = OTA_CMD_211, .net = CanNetA, .handle = ota_cmd_211_handler},
    {.id = OTA_CMD_200, .net = CanNetA, .handle = ota_cmd_200_handler},
};

// 接收消息处理函数表大小
static int s_recv_msg_handle_map_size = sizeof(s_recv_msg_handle_map) / sizeof(struct msg_handle_info);

static int ota_cmd_200_handler(const uint8_t *data, uint8_t len, DataReader *reader)
{
    msg_packet_200_handler(data);
    return VCU_OK;
}

static int ota_cmd_209_handler(const uint8_t *data, uint8_t len, DataReader *reader)
{
    msg_packet_209_handler(data);
    return VCU_OK;
}

static int ota_cmd_211_handler(const uint8_t *data, uint8_t len, DataReader *reader)
{
    msg_packet_211_handler(data);
    return VCU_OK;
}

static int sdo_server_handler(const uint8_t *data, uint8_t len, DataReader *reader)
{
    return Can_Open_Handle_NMT_BootUp(data);
}

static int nmt_boot_up_handler(const uint8_t *data, uint8_t len, DataReader *reader)
{
    return Can_Open_Handle_SDO_Server(data);
}

/**
 * @brief 处理pmu状态
 *
 * @param data
 * @param len
 * @return int
 */
static int pmu_status_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_pmu_status_unpack(&s_recv_data_cache.pmu_status, data, len);
    // todo
    if (Calculate_Crc(data, len) != 0)
    {
        return VCU_CRC_CHECK_FAILED;
    }
    if (reader != NULL)
    {
        struct psa_can_pmu_status_t *status = &s_recv_data_cache.pmu_status;
        ChassisStatus *chassis_status = &reader->chassis_status;
        chassis_status->pwr_state.veh_pwrup = psa_can_pmu_status_pmu_veh_pwrup_sts_decode(status->pmu_veh_pwrup_sts);
        chassis_status->pwr_state.adcu_pwrup = psa_can_pmu_status_pmu_adcu_pwrup_sts_decode(status->pmu_adcu_pwrup_sts);
        chassis_status->pwr_state.mcu_pwrup = psa_can_pmu_status_pmu_mcu_pwrup_sts_decode(status->pmu_mcu_pwrup_sts);
        chassis_status->pwr_state.led_pwrup = psa_can_pmu_status_pmu_led_pwrup_sts_decode(status->pmu_led_pwrup_sts);
        chassis_status->pwr_state.eps_pwrup = psa_can_pmu_status_pmu_eps_pwrup_sts_decode(status->pmu_eps_pwrup_sts);
        chassis_status->pwr_state.ccu_pwrup = psa_can_pmu_status_pmu_ccu_pwrup_sts_decode(status->pmu_ccu_pwrup_sts);
        chassis_status->pwr_state.obd_pwrup = psa_can_pmu_status_pmu_obd_pwrup_sts_decode(status->pmu_obd_pwrup_sts);
        chassis_status->pwr_state.wfc_pwrup = psa_can_pmu_status_pmu_wfc_pwrup_sts_decode(status->pmu_wfc_pwrup_sts);
        chassis_status->pwr_state.dchager_pwrup = psa_can_pmu_status_pmu_dchager_pwrup_sts_decode(status->pmu_dchager_pwrup_sts);
        chassis_status->pwr_state.power_off_req = psa_can_pmu_status_pmu_power_off_req_decode(status->pmu_power_off_req);
        chassis_status->pwr_state.estop_sts = psa_can_pmu_status_pmu_estop_sts_decode(status->pmu_estop_sts);
        chassis_status->pwr_state.park_enable_sts = psa_can_pmu_status_pmu_park_enable_sts_decode(status->pmu_park_enable_sts);
        chassis_status->pwr_state.fault_level = psa_can_pmu_status_pmu_fault_level_decode(status->pmu_fault_level);
        chassis_status->pwr_state.fault_code = psa_can_pmu_status_pmu_fault_code_decode(status->pmu_fault_code);
        chassis_status->drv_state.park_st = chassis_status->pwr_state.park_enable_sts; // 驻车是PMU控制的
        ret = VCU_OK;
    }
    Diag_Update_Node(Node_PMU);
    return ret;
}

/**
 * @brief 处理mcu状态1
 *
 * @param data
 * @param len
 * @return int
 */
static int mcu_status_l1_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_mcu_status_l1_unpack(&s_recv_data_cache.mcu_status_l1, data, len);
    // todo
    if (reader != NULL)
    {
        struct psa_can_mcu_status_l1_t *status = &s_recv_data_cache.mcu_status_l1;
        ChassisStatus *chassis_status = &reader->chassis_status;
        chassis_status->drv_state.mcu_state_l.ready = psa_can_mcu_status_l1_ready_state_decode(status->ready_state);
        chassis_status->drv_state.mcu_state_l.gear = psa_can_mcu_status_l1_gear_decode(status->gear);
        chassis_status->drv_state.mcu_state_l.motor_speed = psa_can_mcu_status_l1_motor_speed_decode(status->motor_speed);
        ret = VCU_OK;
    }
    Diag_Update_Node(Node_MCU_L);
    return ret;
}

/**
 * @brief 处理mcu状态2
 *
 * @param data
 * @param len
 * @return int
 */
static int mcu_status_l2_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_mcu_status_l2_unpack(&s_recv_data_cache.mcu_status_l2, data, len);
    // todo
    return ret;
}
/**
 * @brief 处理mcu状态3
 *
 * @param data
 * @param len
 * @return int
 */
static int mcu_status_l3_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_mcu_status_l3_unpack(&s_recv_data_cache.mcu_status_l3, data, len);
    // todo
    if (reader != NULL)
    {
        struct psa_can_mcu_status_l3_t *status = &s_recv_data_cache.mcu_status_l3;
        ChassisStatus *chassis_status = &reader->chassis_status;
        chassis_status->drv_state.mcu_state_l.error_code = psa_can_mcu_status_l3_fault_code_decode(status->fault_code);

        ret = VCU_OK;
    }
    return ret;
}

/**
 * @brief 处理mcu状态1
 *
 * @param data
 * @param len
 * @return int
 */
static int mcu_status_r1_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_mcu_status_r1_unpack(&s_recv_data_cache.mcu_status_r1, data, len);
    // todo
    if (reader != NULL)
    {
        struct psa_can_mcu_status_r1_t *status = &s_recv_data_cache.mcu_status_r1;
        ChassisStatus *chassis_status = &reader->chassis_status;
        chassis_status->drv_state.mcu_state_r.ready = psa_can_mcu_status_r1_ready_state_decode(status->ready_state);
        chassis_status->drv_state.mcu_state_r.gear = psa_can_mcu_status_r1_gear_decode(status->gear);
        chassis_status->drv_state.mcu_state_r.motor_speed = psa_can_mcu_status_r1_motor_speed_decode(status->motor_speed);
        ret = VCU_OK;
    }
    Diag_Update_Node(Node_MCU_R);
    return ret;
}

/**
 * @brief 处理mcu状态2
 *
 * @param data
 * @param len
 * @return int
 */
static int mcu_status_r2_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_mcu_status_r2_unpack(&s_recv_data_cache.mcu_status_r2, data, len);
    // todo
    return ret;
}
/**
 * @brief 处理mcu状态3
 *
 * @param data
 * @param len
 * @return int
 */
static int mcu_status_r3_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_mcu_status_r3_unpack(&s_recv_data_cache.mcu_status_r3, data, len);
    // todo
    if (reader != NULL)
    {
        struct psa_can_mcu_status_r3_t *status = &s_recv_data_cache.mcu_status_r3;
        ChassisStatus *chassis_status = &reader->chassis_status;
        chassis_status->drv_state.mcu_state_r.error_code = psa_can_mcu_status_r3_fault_code_decode(status->fault_code);
        ret = VCU_OK;
    }
    return ret;
}

/**
 * @brief 处理ccu状态1
 *
 * @param data
 * @param len
 * @return int
 */
static int ccu_status2_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_ccu_status2_unpack(&s_recv_data_cache.ccu_status2, data, len);
    // todo
    if (Calculate_Crc(data, len) != 0)
    {
        return VCU_CRC_CHECK_FAILED;
    }
    if (reader != NULL)
    {
        struct psa_can_ccu_status2_t *status = &s_recv_data_cache.ccu_status2;
        ChassisStatus *chassis_status = &reader->chassis_status;
        chassis_status->sweep.dustbin_full_st = psa_can_ccu_status2_ccu_dustbin_full_st_decode(status->ccu_dustbin_full_st);
        chassis_status->sweep.remain_water = psa_can_ccu_status2_ccu_remain_water_decode(status->ccu_remain_water);
        chassis_status->veh_info.remain_water = chassis_status->sweep.remain_water;
        chassis_status->sweep.main_brush_pos = psa_can_ccu_status2_ccu_main_brush_pos_act_decode(status->ccu_main_brush_pos_act);
        chassis_status->sweep.side_brush_lift_pos = psa_can_ccu_status2_ccu_side_brush_lift_pos_act_decode(status->ccu_side_brush_lift_pos_act);
        chassis_status->sweep.side_brush_extend_pos = psa_can_ccu_status2_ccu_side_brush_extend_pos_act_decode(status->ccu_side_brush_extend_pos_act);
        chassis_status->sweep.high_pump_angle = psa_can_ccu_status2_ccu_high_pump_angle_act_decode(status->ccu_high_pump_angle_act);
        // chassis_status->sweep.high_pump_angle = psa_can_ccu_status2_ccu_wash_probe_adjust_act_decode(status->ccu_wash_probe_adjust_act);
        ret = VCU_OK;
    }
    return ret;
}

/**
 * @brief 处理ccu故障码
 *
 * @param data
 * @param len
 * @param reader
 * @return int
 */
static int ccu_error_code_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_ccu_error_code_status_unpack(&s_recv_data_cache.ccu_err_code, data, len);
    // todo
    if (Calculate_Crc(data, len) != 0)
    {
        return VCU_CRC_CHECK_FAILED;
    }
    if (reader != NULL)
    {
        struct psa_can_ccu_error_code_status_t *status = &s_recv_data_cache.ccu_err_code;
        ChassisStatus *chassis_status = &reader->chassis_status;
        chassis_status->sweep.error_code = status->ccu_error_code_1 | (status->ccu_error_code_2 << 8) || (status->ccu_error_code_2 << 16) || (status->ccu_error_code_2 << 24);
        ret = VCU_OK;
    }
    return ret;
}

/**
 * @brief 处理ccu状态
 *
 * @param data
 * @param len
 * @return int
 */
static int ccu_status_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_ccu_status_unpack(&s_recv_data_cache.ccu_status, data, len);
    // todo
    if (Calculate_Crc(data, len) != 0)
    {
        return VCU_CRC_CHECK_FAILED;
    }
    if (reader != NULL)
    {
        struct psa_can_ccu_status_t *status = &s_recv_data_cache.ccu_status;
        ChassisStatus *chassis_status = &reader->chassis_status;
        chassis_status->sweep.fender_sts = psa_can_ccu_status_ccu_fender_sts_decode(status->ccu_fender_sts);
        chassis_status->sweep.water_pump_sts = psa_can_ccu_status_ccu_water_pump_sts_decode(status->ccu_water_pump_sts);
        chassis_status->sweep.one_clk_dump_sts = psa_can_ccu_status_ccu_one_clk_dump_sts_decode(status->ccu_one_clk_dump_sts);
        chassis_status->sweep.one_clk_clean_sts = psa_can_ccu_status_ccu_one_clk_clean_sts_decode(status->ccu_one_clk_clean_sts);
        chassis_status->sweep.sweeping_sts = psa_can_ccu_status_ccu_sweeping_sts_decode(status->ccu_sweeping_sts);
        chassis_status->sweep.water_add_sts = psa_can_ccu_status_ccu_water_add_sts_decode(status->ccu_water_add_sts);
        chassis_status->sweep.vbr_sts = psa_can_ccu_status_ccu_vbr_sts_decode(status->ccu_vbr_sts);
        chassis_status->sweep.dust_bin_lift_sts = psa_can_ccu_status_ccu_dust_bin_lift_sts_decode(status->ccu_dust_bin_lift_sts);
        chassis_status->sweep.main_brush_lift_sts = psa_can_ccu_status_ccu_main_brush_lift_sts_decode(status->ccu_main_brush_lift_sts);
        chassis_status->sweep.side_brush_extend_sts = psa_can_ccu_status_ccu_side_brush_extend_sts_decode(status->ccu_side_brush_extend_sts);
        chassis_status->sweep.side_brush_lift_sts = psa_can_ccu_status_ccu_side_brush_lift_sts_decode(status->ccu_side_brush_lift_sts);
        chassis_status->sweep.side_brush_sts = psa_can_ccu_status_ccu_side_brush_sts_decode(status->ccu_side_brush_sts);
        chassis_status->sweep.main_brush_sts = psa_can_ccu_status_ccu_main_brush_sts_decode(status->ccu_main_brush_sts);
        chassis_status->sweep.dust_bin_open_sts = psa_can_ccu_status_ccu_dust_bin_open_sts_decode(status->ccu_dust_bin_open_sts);
        chassis_status->sweep.dust_bin_dump_sts = psa_can_ccu_status_ccu_dust_bin_dump_sts_decode(status->ccu_dust_bin_dump_sts);
        chassis_status->sweep.dust_bin_compress_sts = psa_can_ccu_status_ccu_dust_bin_compress_sts_decode(status->ccu_dust_bin_compress_sts);
        chassis_status->sweep.vacuum_sts = psa_can_ccu_status_ccu_vacuum_sts_decode(status->ccu_vacuum_sts);
        chassis_status->sweep.high_water_pump_sts = psa_can_ccu_status_ccu_high_water_pump_sts_decode(status->ccu_high_water_pump_sts);
        chassis_status->sweep.blower_sts = psa_can_ccu_status_ccu_blower_sts_decode(status->ccu_blower_sts);
        chassis_status->sweep.wash_probe_adjust_sts = psa_can_ccu_status_ccu_wash_probe_adjust_sts_decode(status->ccu_wash_probe_adjust_sts);
        chassis_status->sweep.high_pump_adjust_sts = psa_can_ccu_status_ccu_high_pump_adjust_sts_decode(status->ccu_high_pump_adjust_sts);
        chassis_status->sweep.wash_valve_sts = psa_can_ccu_status_ccu_wash_vale_sts_decode(status->ccu_wash_vale_sts);
        chassis_status->sweep.clean_valve_sts = psa_can_ccu_status_ccu_clean_vale_sts_decode(status->ccu_clean_vale_sts);
        chassis_status->sweep.fault_level = psa_can_ccu_status_ccu_fault_level_decode(status->ccu_fault_level);
        ret = VCU_OK;
    }

    Diag_Update_Node(Node_CCU);
    return ret;
}

/**
 * @brief 处理bms状态2
 *
 * @param data
 * @param len
 * @return int
 */
static int bms_status_1_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_bms_status_1_unpack(&s_recv_data_cache.bms_status_1, data, len);
    // todo
    if (reader != NULL)
    {
        struct psa_can_bms_status_1_t *status = &s_recv_data_cache.bms_status_1;
        ChassisStatus *chassis_status = &reader->chassis_status;
        chassis_status->veh_info.bat_soc = psa_can_bms_status_1_bms_status_sys_soc_decode(status->bms_status_sys_soc);
        ret = VCU_OK;
    }
    return ret;
}

/**
 * @brief 处理bms错误状态
 *
 * @param data
 * @param len
 * @return int
 */
static int bms_fault_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_bms_fault_unpack(&s_recv_data_cache.bms_fault, data, len);
    // todo
    if (reader != NULL)
    {
        struct psa_can_bms_fault_t *status = &s_recv_data_cache.bms_fault;
        ChassisStatus *chassis_status = &reader->chassis_status;
        chassis_status->veh_state.bat_low_soc = psa_can_bms_fault_bms_fault_soc_low_f_decode(status->bms_fault_soc_low_f);
        chassis_status->veh_state.bms_err_level = psa_can_bms_fault_bms_fault_err_level_f_decode(status->bms_fault_err_level_f);
        ret = VCU_OK;
    }
    return ret;
}

/**
 * @brief 处理eps状态
 *
 * @param data
 * @param len
 * @return int
 */
static int eps_status_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_eps_status_unpack(&s_recv_data_cache.eps_status, data, len);
    // todo
    if (reader != NULL)
    {
        struct psa_can_eps_status_t *status = &s_recv_data_cache.eps_status;
        ChassisStatus *chassis_status = &reader->chassis_status;
        chassis_status->drv_state.str_work_mode = psa_can_eps_status_eps_work_mode_status_decode(status->eps_work_mode_status);
        chassis_status->drv_state.str_angle = psa_can_eps_status_eps_str_angle_act_decode(status->eps_str_angle_act);
        chassis_status->drv_state.str_angle_speed = psa_can_eps_status_eps_angle_spd_decode(status->eps_angle_spd);
        chassis_status->drv_state.str_error_code = psa_can_eps_status_eps_angle_spd_decode(status->eps_fault_code);

        ret = VCU_OK;
    }
    Diag_Update_Node(Node_EPS);
    return ret;
}

/**
 * @brief 处理rcu 控制命令
 *
 * @param data
 * @param len
 * @return int
 */
static int rcu_ctrl_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_rcu_ctrl_cmd_unpack(&s_recv_data_cache.rcu_ctrl_cmd, data, len);
    // todo
    if (Calculate_Crc(data, len) != 0)
    {
        return VCU_CRC_CHECK_FAILED;
    }

    if (reader != NULL)
    {
        struct psa_can_rcu_ctrl_cmd_t *cmd = &s_recv_data_cache.rcu_ctrl_cmd;
        ChassisCmd *chassis_cmd = &reader->chassis_cmd;
        // 遥控模式
        uint8_t ctr_mode = psa_can_rcu_ctrl_cmd_rcu_ctrl_mod_req_decode(cmd->rcu_ctrl_mod_req); // 0是手动，这里取反
        if (ctr_mode == 0)
        {
            chassis_cmd->rcu.ctrl_mod = 1; // 手动
        }
        else if (ctr_mode == 1)
        {
            chassis_cmd->rcu.ctrl_mod = 0; // 自动
        }
        // 转向角
        chassis_cmd->rcu.target_angle = psa_can_rcu_ctrl_cmd_rcu_ster_per_decode(cmd->rcu_ster_per);
        // 油门大小
        chassis_cmd->rcu.tgt_pedpos = psa_can_rcu_ctrl_cmd_rcu_ster_per_decode(cmd->rcu_acc_per);
        // 挡位
        chassis_cmd->rcu.tgt_gear = cmd->rcu_gear_mod;
        chassis_cmd->rcu.spd_limit = cmd->rcu_speed_limit_per;

        // 驻车
        chassis_cmd->rcu.park_enable = psa_can_rcu_ctrl_cmd_rcu_epb_enable_decode(cmd->rcu_epb_enable);
        // 一键倒垃圾
        chassis_cmd->rcu.one_clk_dump_ctrl = psa_can_rcu_ctrl_cmd_rcu_one_clk_dump_ctrl_decode(cmd->rcu_one_clk_dump_ctrl);
        //  一键清扫
        chassis_cmd->rcu.one_clk_clean_ctrl = psa_can_rcu_ctrl_cmd_rcu_one_clk_clean_ctrl_decode(cmd->rcu_one_clk_clean_ctrl);
        chassis_cmd->rcu.vbr_ctrl = psa_can_rcu_ctrl_cmd_rcu_one_clk_clean_ctrl_decode(cmd->rcu_vibrate_req);
        chassis_cmd->rcu.fender_ctrl = psa_can_rcu_ctrl_cmd_rcu_one_clk_clean_ctrl_decode(cmd->rcu_fender_open_req);
        chassis_cmd->rcu.water_pump_ctrl = psa_can_rcu_ctrl_cmd_rcu_one_clk_clean_ctrl_decode(cmd->rcu_water_pump);

        ret = VCU_OK;
    }
    return ret;
}

/**
 * @brief 处理adcu驱动控制请求
 *
 * @param cmd
 * @return int
 */
static int adcu_drive_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_adcu_drive_cmd_unpack(&s_recv_data_cache.adcu_drive_cmd, data, len);
    // todo
    if (Calculate_Crc(data, len) != 0)
    {
        return VCU_CRC_CHECK_FAILED;
    }

    if (reader != NULL)
    {
        struct psa_can_adcu_drive_cmd_t *cmd = &s_recv_data_cache.adcu_drive_cmd;
        ChassisCmd *chassis_cmd = &reader->chassis_cmd;
        chassis_cmd->drv.driving_mode = psa_can_adcu_drive_cmd_adcu_drving_mode_decode(cmd->adcu_drving_mode);
        chassis_cmd->drv.ctrl_mode = psa_can_adcu_drive_cmd_adcu_drv_ctrl_mode_decode(cmd->adcu_drv_ctrl_mode);
        chassis_cmd->drv.tgt_gear = psa_can_adcu_drive_cmd_adcu_drv_tgt_gear_decode(cmd->adcu_drv_tgt_gear);
        chassis_cmd->drv.tgt_pedpos = psa_can_adcu_drive_cmd_adcu_drv_tgt_pedpos_decode(cmd->adcu_drv_tgt_pedpos);
        chassis_cmd->drv.tgt_veh_spd = psa_can_adcu_drive_cmd_adcu_drv_tgt_veh_spd_decode(cmd->adcu_drv_tgt_veh_spd);
        chassis_cmd->drv.tgt_veh_acc_spd = psa_can_adcu_drive_cmd_adcu_drv_tgt_veh_acc_spd_decode(cmd->adcu_drv_tgt_veh_acc_spd);
        chassis_cmd->drv.veh_spd_limit = psa_can_adcu_drive_cmd_adcu_drv_veh_spd_limit_decode(cmd->adcu_drv_veh_spd_limit);
        ret = VCU_OK;
    }
    Diag_Update_Node(Node_ADCU);
    return ret;
}

/**
 * @brief 处理adcu刹车控制请求
 *
 * @param cmd
 * @return int
 */
static int adcu_brake_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_adcu_brake_cmd_unpack(&s_recv_data_cache.adcu_brake_cmd, data, len);
    // todo
    if (Calculate_Crc(data, len) != 0)
    {
        return VCU_CRC_CHECK_FAILED;
    }
    if (reader != NULL)
    {
        struct psa_can_adcu_brake_cmd_t *cmd = &s_recv_data_cache.adcu_brake_cmd;
        ChassisCmd *chassis_cmd = &reader->chassis_cmd;
        chassis_cmd->brake.park_enable = psa_can_adcu_brake_cmd_adcu_brk_park_enable_decode(cmd->adcu_brk_park_enable);
        chassis_cmd->power.park_enable = chassis_cmd->brake.park_enable;
        chassis_cmd->brake.work_mode = psa_can_adcu_brake_cmd_adcu_brk_ctrl_mode_decode(cmd->adcu_brk_ctrl_mode);
        if (chassis_cmd->brake.work_mode == PSA_CAN_ADCU_BRAKE_CMD_ADCU_BRK_CTRL_MODE_BRAKE__PEDAL__POS__MODE_CHOICE)
        {
            chassis_cmd->brake.target_brake_val = psa_can_adcu_brake_cmd_adcu_brk_tgt_pedpos_decode(cmd->adcu_brk_tgt_pedpos);
        }
        else
        {
            chassis_cmd->brake.target_pressure = psa_can_adcu_brake_cmd_adcu_brk_tgt_pedpos_decode(cmd->adcu_brk_tgt_press);
        }
        ret = VCU_OK;
    }
    return ret;
}

/**
 * @brief 处理adcu车身控制请求
 *
 * @param cmd
 * @return int
 */
static int adcu_body_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_adcu_lamp_cmd_unpack(&s_recv_data_cache.adcu_body_cmd, data, len);

    if (Calculate_Crc(data, len) != 0)
    {
        return VCU_CRC_CHECK_FAILED;
    }
    // todo
    if (reader != NULL)
    {
        struct psa_can_adcu_lamp_cmd_t *cmd = &s_recv_data_cache.adcu_body_cmd;
        ChassisCmd *chassis_cmd = &reader->chassis_cmd;
        chassis_cmd->body.warning_lamp = psa_can_adcu_lamp_cmd_adcu_warning_lamp_cmd_decode(cmd->adcu_warning_lamp_cmd);
        chassis_cmd->body.head_lamp = psa_can_adcu_lamp_cmd_adcu_head_lamp_cmd_decode(cmd->adcu_head_lamp_cmd);
        chassis_cmd->body.dbl_flash_lamp = psa_can_adcu_lamp_cmd_adcu_dbl_flash_lamp_cmd_decode(cmd->adcu_dbl_flash_lamp_cmd);
        chassis_cmd->body.turn_l_lamp = psa_can_adcu_lamp_cmd_adcu_turn_l_lamp_cmd_decode(cmd->adcu_turn_l_lamp_cmd);
        chassis_cmd->body.turn_r_lamp = psa_can_adcu_lamp_cmd_adcu_turn_r_lamp_cmd_decode(cmd->adcu_turn_r_lamp_cmd);
        chassis_cmd->body.back_lamp = psa_can_adcu_lamp_cmd_adcu_back_lamp_cmd_decode(cmd->adcu_back_lamp_cmd);
        chassis_cmd->body.horn = psa_can_adcu_lamp_cmd_adcu_horn_cmd_decode(cmd->adcu_horn_cmd);
        chassis_cmd->body.buzzer = psa_can_adcu_lamp_cmd_adcu_buzzer_cmd_decode(cmd->adcu_buzzer_cmd);
        chassis_cmd->body.brk_lamp = psa_can_adcu_lamp_cmd_adcu_brk_lamp_cmd_decode(cmd->adcu_brk_lamp_cmd);
        // chassis_cmd->body.fog_lamp = psa_can_adcu_lamp_cmd_adcu_fog_lamp_cmd_decode(cmd->adcu_fog_lamp_cmd);
        chassis_cmd->body.width_lamp = psa_can_adcu_lamp_cmd_adcu_width_lamp_cmd_decode(cmd->adcu_width_lamp_cmd);
        // chassis_cmd->body.wiper = psa_can_adcu_lamp_cmd_adcu_wiper_cmd_decode(cmd->adcu_wiper_cmd);
        ret = VCU_OK;
    }
    return ret;
}

/**
 * @brief 处理adcu电源请求
 *
 * @param cmd
 * @return int
 */
static int adcu_power_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_adcu_power_cmd_unpack(&s_recv_data_cache.adcu_power_cmd, data, len);
    // todo
    if (Calculate_Crc(data, len) != 0)
    {
        return VCU_CRC_CHECK_FAILED;
    }
    // todo
    if (reader != NULL)
    {
        struct psa_can_adcu_power_cmd_t *cmd = &s_recv_data_cache.adcu_power_cmd;
        ChassisCmd *chassis_cmd = &reader->chassis_cmd;
        chassis_cmd->power.veh_pwrup = psa_can_adcu_power_cmd_adcu_veh_pwrup_cmd_decode(cmd->adcu_veh_pwrup_cmd);
        chassis_cmd->power.wl_chg_wake_up = psa_can_adcu_power_cmd_adcu_wl_chg_wake_up_cmd_decode(cmd->adcu_wl_chg_wake_up_cmd);
        chassis_cmd->power.emg_brk_req = psa_can_adcu_power_cmd_adcu_emg_brk_req_decode(cmd->adcu_emg_brk_req);
        chassis_cmd->power.soft_emg_brk_req = psa_can_adcu_power_cmd_adcu_soft_emg_brk_req_decode(cmd->adcu_soft_emg_brk_req);
        chassis_cmd->power.rmt_pwr_on_req = psa_can_adcu_power_cmd_adcu_rmt_pwr_on_req_decode(cmd->adcu_rmt_pwr_on_req);
        chassis_cmd->power.crash_free = psa_can_adcu_power_cmd_adcu_crash_free_decode(cmd->adcu_crash_free);
        chassis_cmd->power.apv_pwr_off = psa_can_adcu_power_cmd_adcu_apv_pwr_off_decode(cmd->adcu_apv_pwr_off);
        chassis_cmd->power.end_chg_req = psa_can_adcu_power_cmd_adcu_end_chg_req_decode(cmd->adcu_end_chg_req);
        ret = VCU_OK;
    }
    return ret;
}

/**
 * @brief 时间同步
 *
 * @param data
 * @param len
 * @param reader
 * @return int
 */
static int adcu_date_time_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_adcu_date_time_unpack(&s_recv_data_cache.adcu_date_time, data, len);
    // todo
    if (reader != NULL)
    {
        struct psa_can_adcu_date_time_t *cmd = &s_recv_data_cache.adcu_date_time;
        ChassisCmd *chassis_cmd = &reader->chassis_cmd;
        chassis_cmd->time.gps_syst_atv = psa_can_adcu_date_time_gps_syst_atv_decode(cmd->gps_syst_atv);
        chassis_cmd->time.second = psa_can_adcu_date_time_time_second_decode(cmd->time_second);
        chassis_cmd->time.minute = psa_can_adcu_date_time_time_minute_decode(cmd->time_minute);
        chassis_cmd->time.hour = psa_can_adcu_date_time_time_hour_decode(cmd->time_hour);
        chassis_cmd->time.day = psa_can_adcu_date_time_time_day_decode(cmd->time_day);
        chassis_cmd->time.month = psa_can_adcu_date_time_time_month_decode(cmd->time_month);
        chassis_cmd->time.year = psa_can_adcu_date_time_time_year_decode(cmd->time_year);
        chassis_cmd->time.is_time_sync = 1;
        chassis_cmd->time.last_sync_ticks = HAL_GetTick();
        ret = VCU_OK;
    }
    return ret;
}

/**
 * @brief 处理adcu转向控制请求
 *
 * @param cmd
 * @return int
 */
static int adcu_steer_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_adcu_steer_cmd_unpack(&s_recv_data_cache.adcu_steer_cmd, data, len);
    // todo
    if (Calculate_Crc(data, len) != 0)
    {
        return VCU_CRC_CHECK_FAILED;
    }
    // todo
    if (reader != NULL)
    {
        struct psa_can_adcu_steer_cmd_t *cmd = &s_recv_data_cache.adcu_steer_cmd;
        ChassisCmd *chassis_cmd = &reader->chassis_cmd;
        chassis_cmd->steer.work_mode = psa_can_adcu_steer_cmd_adcu_str_work_mode_decode(cmd->adcu_str_work_mode);
        chassis_cmd->steer.target_angle = psa_can_adcu_steer_cmd_adcu_str_tgt_angle_decode(cmd->adcu_str_tgt_angle);
        chassis_cmd->steer.angle_speed = psa_can_adcu_steer_cmd_adcu_str_tgt_angle_spd_decode(cmd->adcu_str_tgt_angle_spd);
        chassis_cmd->steer.center = psa_can_adcu_steer_cmd_adcu_str_centering_decode(cmd->adcu_str_centering);
        ret = VCU_OK;
    }
    return ret;
}

/**
 * @brief 处理adcu清扫控制请求
 *
 * @param cmd
 * @return int
 */
static int adcu_sweep_cmd_handle(const uint8_t *data, uint8_t len, DataReader *reader)
{
    int ret = VCU_FAILED;
    ret = psa_can_adcu_sweep_cmd_unpack(&s_recv_data_cache.adcu_sweep_cmd, data, len);
    // todo
    if (Calculate_Crc(data, len) != 0)
    {
        return VCU_CRC_CHECK_FAILED;
    }
    // todo
    if (reader != NULL)
    {
        struct psa_can_adcu_sweep_cmd_t *cmd = &s_recv_data_cache.adcu_sweep_cmd;
        ChassisCmd *chassis_cmd = &reader->chassis_cmd;
        chassis_cmd->sweep.fender_ctrl = psa_can_adcu_sweep_cmd_adcu_fender_ctrl_decode(cmd->adcu_fender_ctrl);
        chassis_cmd->sweep.one_clk_clean_ctrl = psa_can_adcu_sweep_cmd_adcu_one_clk_clean_ctrl_decode(cmd->adcu_one_clk_clean_ctrl);
        chassis_cmd->sweep.one_clk_dump_ctrl = psa_can_adcu_sweep_cmd_adcu_one_clk_dump_ctrl_decode(cmd->adcu_one_clk_dump_ctrl);
        chassis_cmd->sweep.water_pump_ctrl = psa_can_adcu_sweep_cmd_adcu_water_pump_ctrl_decode(cmd->adcu_water_pump_ctrl);
        chassis_cmd->sweep.vbr_ctrl = psa_can_adcu_sweep_cmd_adcu_vbr_ctrl_decode(cmd->adcu_vbr_ctrl);
        chassis_cmd->sweep.water_add_ctrl = psa_can_adcu_sweep_cmd_adcu_water_add_ctrl_decode(cmd->adcu_water_add_ctrl);
        chassis_cmd->sweep.sweeping_ctrl = psa_can_adcu_sweep_cmd_adcu_sweeping_ctrl_decode(cmd->adcu_sweeping_ctrl);
        chassis_cmd->sweep.side_brush_lift_ctrl = psa_can_adcu_sweep_cmd_adcu_side_brush_lift_ctrl_decode(cmd->adcu_side_brush_lift_ctrl);
        chassis_cmd->sweep.side_brush_extend_ctrl = psa_can_adcu_sweep_cmd_adcu_side_brush_extend_ctrl_decode(cmd->adcu_side_brush_extend_ctrl);
        chassis_cmd->sweep.main_brush_lift_ctrl = psa_can_adcu_sweep_cmd_adcu_main_brush_lift_ctrl_decode(cmd->adcu_main_brush_lift_ctrl);
        chassis_cmd->sweep.dust_bin_lift_ctrl = psa_can_adcu_sweep_cmd_adcu_dust_bin_lift_ctrl_decode(cmd->adcu_dust_bin_lift_ctrl);
        chassis_cmd->sweep.dust_bin_dump_ctrl = psa_can_adcu_sweep_cmd_adcu_dust_bin_dump_ctrl_decode(cmd->adcu_dust_bin_dump_ctrl);
        chassis_cmd->sweep.dust_bin_open_ctrl = psa_can_adcu_sweep_cmd_adcu_dust_bin_open_ctrl_decode(cmd->adcu_dust_bin_open_ctrl);
        chassis_cmd->sweep.main_brush_ctrl = psa_can_adcu_sweep_cmd_adcu_main_brush_ctrl_decode(cmd->adcu_main_brush_ctrl);
        chassis_cmd->sweep.side_brush_ctrl = psa_can_adcu_sweep_cmd_adcu_side_brush_ctrl_decode(cmd->adcu_side_brush_ctrl);
        chassis_cmd->sweep.blower_ctrl = psa_can_adcu_sweep_cmd_adcu_blower_ctrl_decode(cmd->adcu_blower_ctrl);
        chassis_cmd->sweep.high_water_pump_ctrl = psa_can_adcu_sweep_cmd_adcu_high_water_pump_ctrl_decode(cmd->adcu_high_water_pump_ctrl);
        chassis_cmd->sweep.vacuum_ctrl = psa_can_adcu_sweep_cmd_adcu_vacuum_ctrl_decode(cmd->adcu_vacuum_ctrl);
        chassis_cmd->sweep.dust_bin_compress_ctrl = psa_can_adcu_sweep_cmd_adcu_dust_bin_compress_ctrl_decode(cmd->adcu_dust_bin_compress_ctrl);
        chassis_cmd->sweep.wash_valve_ctrl = psa_can_adcu_sweep_cmd_adcu_wash_valve_ctrl_decode(cmd->adcu_wash_valve_ctrl);
        chassis_cmd->sweep.clean_valve_ctrl = psa_can_adcu_sweep_cmd_adcu_clean_valve_ctrl_decode(cmd->adcu_clean_valve_ctrl);
        chassis_cmd->sweep.high_pump_adjust_ctrl = psa_can_adcu_sweep_cmd_adcu_high_pump_adjust_ctrl_decode(cmd->adcu_high_pump_adjust_ctrl);
        chassis_cmd->sweep.wash_probe_adjust_ctrl = psa_can_adcu_sweep_cmd_adcu_wash_probe_adjust_ctrl_decode(cmd->adcu_wash_probe_adjust_ctrl);
        ret = VCU_OK;
    }
    return ret;
}
// /**
//  * @brief 处理tboxt nm消息
//  *
//  * @param cmd
//  * @return int
//  */
// static int tbox_nm_handle(const uint8_t *data, uint8_t len, DataReader *reader)
// {
//     int ret = VCU_FAILED;
//     ret = psa_can_tbox_nm_unpack(&s_recv_data_cache.tbox_nm, data, len);
//     // todo
//     return ret;
// }

void Can_Msg_Parse(CanMsg *msg, DataReader *reader)
{
    for (int i = 0; i < s_recv_msg_handle_map_size; i++)
    {
        if (msg->id == s_recv_msg_handle_map[i].id)
        {
            //            printf("R:%x\r\n", msg->id);
            s_recv_msg_handle_map[i].handle(msg->buffer, msg->len, reader);
            break;
        }
    }
}

int Can_Msg_GetIds(CanNet net, uint32_t *ids, int size)
{
    int index = 0;
    for (int i = 0; i < s_recv_msg_handle_map_size; i++)
    {
        if (index >= size)
        {
            break;
        }
        if (net == s_recv_msg_handle_map[i].net)
        {
            ids[index++] = s_recv_msg_handle_map[i].id;
        }
    }

    return index;
}
