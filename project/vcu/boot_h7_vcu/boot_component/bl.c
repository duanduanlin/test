#include "bl.h"
#include "app.h"

#define MSG_TX_BUF_SIZE 256

static uint8_t msg_tx_buf[MSG_TX_BUF_SIZE];

typedef void (*app_func_callback)(void);

static void msg_packet_200_handler(uint8_t *buf, uint32_t len);
static void msg_packet_203_handler(uint8_t *buf, uint32_t len);
static void msg_packet_205_handler(uint8_t *buf, uint32_t len);
static void msg_packet_209_handler(uint8_t *buf, uint32_t len);
static void msg_packet_211_handler(uint8_t *buf, uint32_t len);
static void port_msg_pack_send(uint8_t cmd, uint8_t *data, uint16_t len);
static uint8_t write_app_program_to_flash(uint8_t *fw_block_buf, uint16_t current_packet, uint16_t total_packet, uint16_t packet_length, uint16_t actual);
static void jump_to_app(uint32_t addr);

uint8_t test_buf[8] = {00, 01, 02, 03, 04, 05, 06, 07};
void app_ota_msg_handler(uint8_t cmd, uint8_t *pd, uint16_t len)
{
    log_info("cmd = %x\r\n", cmd);

    switch (cmd)
    {
    case 0x02:
        log_info("test cmd...\r\n");
        // boot_fifo_write(test_buf, 8, TX_FIFO);
        // dma_uart3_tx(test_buf, 8);
        boot_fifo_write(test_buf, 8, TX_FIFO);
        break;

    case OTA_CMD_200:
        msg_packet_200_handler(pd, len);
        break;

    case OTA_CMD_203_DATA:
        msg_packet_203_handler(pd, len);
        break;

    case OTA_CMD_205_REBOOT:
        msg_packet_205_handler(pd, len);
        break;

    case OTA_CMD_209:
        msg_packet_209_handler(pd, len);
        break;

    case OTA_CMD_211:
        msg_packet_211_handler(pd, len);
        break;

    default:
        log_info("no handler cmd = %x\r\n", cmd);
        break;
    }
}

static uint8_t msg_rec_buf[1056];//两包数据的长度
static uint16_t msg_rec_buf_push_index=0;
static uint16_t msg_rec_buf_pop_index=0;
static uint16_t msg_rec_kb=0;
static uint8_t can_packet_last=255;//数据帧的序号，用于判断是否丢帧
static uint8_t rec_status=0;
#define FLASH_PACKS_LEN 512
static void msg_packet_200_handler(uint8_t *buf, uint32_t len)
{
    log_info("upgrade start...\r\n");

    OTA_200_ALLOW_REC rec_content;
    OTA_200_ALLOW_REC pack_content;
    OTA_202_NowStatus upgrade_permit;

    memcpy(&rec_content, buf, sizeof(OTA_200_ALLOW_REC));

    if(rec_content.Board_ID_Dest != sys_ops_api->module_self) return;
    
    pack_content.Board_ID_Sour = sys_ops_api->module_self;
    pack_content.Board_ID_Dest = MODULE_ADCU;
    pack_content.status = 1;
    for(uint8_t i=0;i<4;i++) pack_content.unused[i] = 0;
    pack_content.OTA_200_CheckSum = calc_checksum(&pack_content, 7);
    can_send_msg(OTA_CMD_200,&pack_content,sizeof(OTA_200_ALLOW_REC));   
    sys_ops_api->delay_ms(3); // 延时

    upgrade_param.load_firmware_size = 0x00;
    upgrade_param.upgrade_flag = FW_UPGRADE_START;
    boot_param_write();
    //每次重新升级的时候重置升级传输参数
    rec_status = 0;
    can_packet_last = 255;
    msg_rec_kb = 0;
    msg_rec_buf_pop_index = 0;
    msg_rec_buf_push_index = 0;

    upgrade_permit.Board_ID_Sour = sys_ops_api->module_self;
    upgrade_permit.Board_ID_Dest = MODULE_ADCU;
    upgrade_permit.status = 1;
    for(uint8_t i=0;i<4;i++) upgrade_permit.unused[i] = 0;
    upgrade_permit.OTA_202_CheckSum = calc_checksum(&upgrade_permit, 7);
    can_send_msg(OTA_CMD_202_START, (uint8_t *)&upgrade_permit, sizeof(OTA_202_NowStatus));

    boot_flash_unlock();
    boot_flash_erase(sys_ops_api->flash_start_addr + sys_ops_api->app_offset_addr);
    boot_flash_lock();
}

void upgrade_start_ack_msg(void)
{
    OTA_202_NowStatus upgrade_permit;

    upgrade_permit.Board_ID_Sour = sys_ops_api->module_self;
    upgrade_permit.Board_ID_Dest = MODULE_ADCU;
    upgrade_permit.status = 1;
    for(uint8_t i=0;i<4;i++) upgrade_permit.unused[i] = 0;
    upgrade_permit.OTA_202_CheckSum = calc_checksum(&upgrade_permit, 7);
    can_send_msg(OTA_CMD_202_START, (uint8_t *)&upgrade_permit, sizeof(OTA_202_NowStatus));

    boot_flash_unlock();
    boot_flash_erase(sys_ops_api->flash_start_addr + sys_ops_api->app_offset_addr);
    boot_flash_lock();
}


static void msg_packet_203_handler(uint8_t *buf, uint32_t len)
{
    // log_info("203:upgrade fw block...\r\n");

    uint16_t crc_code;
    uint8_t ret = 3;
    static uint16_t current_packet = 1; //当前写入flash的包的序号，用于计算flash地址

    OTA_203_cir_send rec_content;
    OTA_204_RecStatus ack_content;

    memcpy(&rec_content, buf, sizeof(rec_content));

    if(rec_content.Board_ID_Dest != sys_ops_api->module_self)return;

    if((uint8_t)(can_packet_last+1) != rec_content.packs) return;

    memcpy(&msg_rec_buf[msg_rec_buf_push_index], &rec_content.data_N[0], 4);

    if (upgrade_param.upgrade_flag == FW_UPGRADE_START)
    {
        upgrade_param.upgrade_flag = FW_UPGRADING;
        boot_param_write();
    }

    msg_rec_buf_push_index += 4;
    if(msg_rec_buf_push_index >= 1056) msg_rec_buf_push_index=0;
    
    switch(rec_status)
    {
        //识别帧头
        case 0:
            if(strncmp(&msg_rec_buf[msg_rec_buf_pop_index], "CTRL", 4)  == 0)
            {
                rec_status = 1;
                log_info("203:uec_status = 1;\r\n");
            }
        break;

        //内容接收
        case 1:
            if(abs(msg_rec_buf_push_index - msg_rec_buf_pop_index) > FLASH_PACKS_LEN)//一包内容接收完毕   
            {
                rec_status = 2;
                log_info("203:uec_status = 2;\r\n");
            }
        break;

        //识别帧尾
        case 2:
            if(strncmp(&msg_rec_buf[msg_rec_buf_pop_index + FLASH_PACKS_LEN + 4], "AUTOCITY", 8)  == 0)
            {
                rec_status = 3;
                log_info("203:uec_status = 3;\r\n");
            }
        break;

        //CRC
        case 3:
            crc_code = msg_rec_buf[msg_rec_buf_pop_index + FLASH_PACKS_LEN + 12]*256 + msg_rec_buf[msg_rec_buf_pop_index + FLASH_PACKS_LEN + 13];
            if(crc_code == calc_crc16_table(&msg_rec_buf[msg_rec_buf_pop_index], FLASH_PACKS_LEN+12) )
            {
                boot_flash_unlock();
                ret = write_app_program_to_flash(&msg_rec_buf[msg_rec_buf_pop_index+4],
                                                current_packet,
                                                current_packet,
                                                FLASH_PACKS_LEN,
                                                FLASH_PACKS_LEN);
                boot_flash_lock();

                log_info("ret = %d\r\n", ret);

                current_packet++;

                if(msg_rec_buf_pop_index == 0)msg_rec_buf_pop_index = 528;
                else if(msg_rec_buf_pop_index == 528)msg_rec_buf_pop_index = 0;

                rec_status = 0;
                msg_rec_kb += 1;
                log_info("203:uec_status = 0;rec %d kb\r\n",msg_rec_kb);
            }
        break;
    }

    can_packet_last = rec_content.packs;
    ack_content.Board_ID_Sour = sys_ops_api->module_self;
    ack_content.Board_ID_Dest = MODULE_ADCU;
    ack_content.status = 1;
    ack_content.packs = can_packet_last;
    for(uint8_t i=0;i<3;i++) ack_content.unused[i] = 0;
    ack_content.OTA_204_CheckSum = calc_checksum(&ack_content, 7);
    can_send_msg(OTA_CMD_204_ACK, (uint8_t *)&ack_content, sizeof(ack_content));
}

static void msg_packet_205_handler(uint8_t *buf, uint32_t len)
{
    log_info("upgrade end...\r\n");

    OTA_205_RebootStatus rec_content;
    OTA_205_RebootStatus reboot_content;

    memcpy(&rec_content, buf, sizeof(rec_content));

    if(rec_content.Board_ID_Dest != sys_ops_api->module_self) return;

    reboot_content.Board_ID_Sour = sys_ops_api->module_self;
    reboot_content.Board_ID_Dest = MODULE_ADCU;
    reboot_content.status = 1;
    

    upgrade_param.upgrade_flag = FW_UPGRADE_END;
    upgrade_param.running_safe_flag = 0;
    boot_param_write();
    for(uint8_t i=0;i<4;i++) reboot_content.unused[i] = 0;
    reboot_content.OTA_205_CheckSum = calc_checksum(&reboot_content, 7);
    can_send_msg(OTA_CMD_205_REBOOT, (uint8_t *)&reboot_content, sizeof(reboot_content));

    // reboot-待抽象实现
}

static void msg_packet_209_handler(uint8_t *buf, uint32_t len)
{
    log_info("version check cmd...\r\n");

    OTA_209_Query_ver version_rec_content;
    OTA_210_ver version_check_ack_content;
    uint8_t version_buf[3];

    memcpy(&version_rec_content, buf, sizeof(version_rec_content));

    if(version_rec_content.Board_ID_Dest != sys_ops_api->module_self) return;

    // version_check_ack_content.upd_info.src = MODULE_SELF;
    version_check_ack_content.Board_ID_Sour = sys_ops_api->module_self;
    version_check_ack_content.Board_ID_Dest = MODULE_ADCU;
    version_check_ack_content.run_area = RUN_AREA_BOOT;
    version_check_ack_content.update_status = upgrade_param.upgrade_flag;

    if(version_rec_content.check == VERSION_TYPE_BOOT)
    {
        version_check_ack_content.version_type = VERSION_TYPE_BOOT;
        // 使用 sscanf 直接提取数字
        sscanf((void *)upgrade_param.bootloader_version, "%d.%d.%d", &version_buf[0], &version_buf[1], &version_buf[2]);
        version_check_ack_content.version1 = version_buf[0];
        version_check_ack_content.version2 = version_buf[1];
        version_check_ack_content.version3 = version_buf[2];
    }
    else if(version_rec_content.check == VERSION_TYPE_APP)
    {
        version_check_ack_content.version_type = VERSION_TYPE_APP;
        // 使用 sscanf 直接提取数字
        sscanf((void *)upgrade_param.app_version, "%d.%d.%d", &version_buf[0], &version_buf[1], &version_buf[2]);
        version_check_ack_content.version1 = version_buf[0];
        version_check_ack_content.version2 = version_buf[1];
        version_check_ack_content.version3 = version_buf[2];
    }

    version_check_ack_content.OTA_210_CheckSum = calc_checksum(&version_check_ack_content, 7);
    can_send_msg(OTA_CMD_210, (uint8_t *)&version_check_ack_content, sizeof(version_check_ack_content));
}

static void msg_packet_211_handler(uint8_t *buf, uint32_t len)
{
    log_info("upgrade status...\r\n");

    OTA_211_ALLOW_up rec_content;
    OTA_211_ALLOW_up upgrade_status_content;
    

    memcpy(&rec_content, buf, sizeof(rec_content));

    if(rec_content.Board_ID_Dest != sys_ops_api->module_self) return;
    
    upgrade_status_content.Board_ID_Sour = sys_ops_api->module_self;
    upgrade_status_content.Board_ID_Dest = MODULE_ADCU;
    upgrade_status_content.Status = 1;
    for(uint8_t i=0;i<4;i++) upgrade_status_content.unused[i] = 0;
    upgrade_status_content.OTA_211_CheckSum = calc_checksum(&upgrade_status_content, 7);
    can_send_msg(OTA_CMD_211, (uint8_t *)&upgrade_status_content, sizeof(upgrade_status_content));
}

static void port_msg_pack_send(uint8_t cmd, uint8_t *data, uint16_t len)
{
    uint16_t msg_len;

    if (boot_get_port_type() == UART_PORT)
    {
        msg_len = scp_msg_pack(msg_tx_buf, cmd, data, len);
        boot_fifo_write(msg_tx_buf, msg_len, TX_FIFO);
    }
    else if (boot_get_port_type() == CAN_PORT)
    {
        sys_ops_api->uavcan_msg_pack_publish(0,
                                            cmd, 
                                            len, 
                                            data);
    }

    // boot_fifo_write(msg_tx_buf, msg_len, TX_FIFO);
    // dma_uart3_tx(msg_tx_buf, msg_len);
}

static uint8_t write_app_program_to_flash(uint8_t *fw_block_buf, uint16_t current_packet, uint16_t total_packet, uint16_t packet_length, uint16_t actual)
{
    uint32_t start_addr;

    if ((packet_length != 128) && (packet_length != 256) && (packet_length != 512) && (packet_length != 1024))
    {
        log_info("invaild packet length...\r\n");

        return 1;
    }

    log_info("actual = %d\r\n", actual);
    log_info("packet_length = %d\r\n", packet_length);

    start_addr = sys_ops_api->flash_start_addr + sys_ops_api->app_offset_addr + (current_packet - 1) * packet_length;

    boot_flash_write(start_addr, fw_block_buf, actual);

    if (memcmp((void *)start_addr, (void *)fw_block_buf, actual) != 0)
    {
        return 2;
    }

    return 0;
}

static void port_can_msg_recv(void)
{
#if USE_INTERFACE_CAN
    CanardFrame frame;
    iFrame_t iframe;

    if (!boot_fifo_is_empty(RX_FIFO))
    {
        boot_fifo_read(&iframe, sizeof(iframe), RX_FIFO);

        frame.timestamp_usec = iframe.timestamp_usec;
        frame.extended_can_id = iframe.id;//实际是标准帧
        frame.payload_size = iframe.size;
        frame.payload = &iframe.data[0];

        // // accept_canard_frame(&frame);
        // sys_ops_api->accept_canard_frame(&frame);
        // 调用数据处理函数（用户自定义）
        if (iframe.id == OTA_CMD_200)
        {
            msg_packet_200_handler(iframe.data, 8);  //已包含202发送
        }
        else if(iframe.id == OTA_CMD_203_DATA){
            msg_packet_203_handler(iframe.data,8);
        }
        else if(iframe.id == OTA_CMD_209){
            msg_packet_209_handler(iframe.data, 8);
        }
        else if (iframe.id == OTA_CMD_211)
        {
            msg_packet_211_handler(iframe.data, 8);
        }
        else if (iframe.id == OTA_CMD_205_REBOOT)
        {
            msg_packet_205_handler(iframe.data, 8);   //重启
        }
    }
#endif
}

static void port_serial_msg_recv(void)
{
    uint8_t data;

    boot_fifo_read(&data, 1, RX_FIFO);
    // log_info("serial data = %x\r\n", data);
    serial_msg_parse(data);
}

void task_port_msg_recv(void)
{
    if (boot_get_port_type() == UART_PORT)
    {
        if (!boot_fifo_is_empty(RX_FIFO))
        {
            port_serial_msg_recv();
        }
    }
    else if (boot_get_port_type() == CAN_PORT)
    {
        port_can_msg_recv();
    }
}

void task_bootloader_entry(uint32_t period)
{
    static struct timer_pcb timer_pcb = {0};

    if (is_run_time(&timer_pcb, period))
    {
        log_info("bootloader task run...\r\n");

        if (upgrade_param.upgrade_flag == FW_UPGRADE_NORMAL || upgrade_param.upgrade_flag == FW_UPGRADE_END)
        {
            log_info("jump to app...\r\n");
            jump_to_app(sys_ops_api->flash_start_addr + sys_ops_api->app_offset_addr);
        }
    }
}

static app_func_callback app_func;
static void jump_to_app(uint32_t addr)
{
    if (((*(volatile uint32_t *)addr) & sys_ops_api->ram_valid_addr_range) == 0x20000000)
    {
        sys_ops_api->reset();
        app_func = (app_func_callback) * (volatile uint32_t *)(addr + 4);
        // __set_MSP(*(volatile uint32_t *)addr);
        sys_ops_api->set_msp(addr);
        app_func();

        while (1)
            ;    
    }
    else
    {
        upgrade_param.upgrade_flag = FW_UPGRADE_IN_BOOT;
    }
}

void ecb_process_received_canard_transfer(CanardTransfer *transfer)
{
    log_info("received uavcan msg: from %d, kind %d, portID %d\r\n", transfer->remote_node_id, transfer->transfer_kind, transfer->port_id);

    app_ota_msg_handler(transfer->port_id, (uint8_t *)transfer->payload, transfer->payload_size);
}

static void uavcan_test_msg(void)
{
    upgrade_notify_content_type content = {0};

    // content.upd_info.src = MODULE_SELF;
    content.upd_info.src = sys_ops_api->module_self;
    content.upd_info.dest = MODULE_CONTROL_PC;
    content.status = 1;
    port_msg_pack_send(OTA_CMD_200, (uint8_t *)&content, sizeof(content));
}

void task_uavcan_test_entry(uint32_t period)
{
    static struct timer_pcb timer_pcb = {0};

    if (is_run_time(&timer_pcb, period))
    {
        log_info("uavcan test task run...\r\n");

        uavcan_test_msg();
    }
}
