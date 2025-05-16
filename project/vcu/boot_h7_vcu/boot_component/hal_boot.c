#include "hal_boot.h"
#include "app.h"

boot_ops_t *boot_ops_ptr;

void boot_ops_init(boot_ops_t *ops)
{
    boot_ops_ptr = ops;
}

void boot_init(boot_ops_t *ops)
{
    boot_ops_init(ops);

    log_info("task init...\r\n");
    sys_ops_api = boot_get_sys_ops_ptr();
    boot_param_handler();
    serial_parse_init();
}

void boot_run(void)
{
    task_led_entry(50);
    task_port_msg_recv();
    task_bootloader_entry(1000);
}

void boot_flash_read(uint32_t addr, uint8_t *data, uint16_t len)
{
    boot_ops_ptr->flash_ops->read(addr, data, len);
}

void boot_flash_write(uint32_t addr, uint8_t *data, uint16_t len)
{
    boot_ops_ptr->flash_ops->write(addr, data, len);
}

void boot_flash_erase(uint32_t addr)
{
    boot_ops_ptr->flash_ops->erase(addr);
}

void boot_flash_unlock(void)
{
    boot_ops_ptr->flash_ops->unlock();
}

void boot_flash_lock(void)
{
    boot_ops_ptr->flash_ops->lock();
}

uint8_t boot_get_port_type(void)
{
    return boot_ops_ptr->sys_ops->port_type;
}

static ringbuf_t *get_fifo_ptr(uint8_t fifo_num)
{
    ringbuf_t *mrb = 0;

    if (fifo_num == RX_FIFO)
        mrb = boot_ops_ptr->fifo_ops->recv_fifo_ptr;
    else if (fifo_num == TX_FIFO)
        mrb = boot_ops_ptr->fifo_ops->send_fifo_ptr;

    return mrb;
}

uint8_t boot_fifo_is_empty(uint8_t fifo_num)
{
    // return rb_is_empty(get_fifo_ptr(fifo_num));
    return boot_ops_ptr->fifo_ops->ringbuf_is_empty(get_fifo_ptr(fifo_num));
}

uint16_t boot_fifo_payload_length(uint8_t fifo_num)
{
    // return rb_get_payload_size(get_fifo_ptr(fifo_num));
    return boot_ops_ptr->fifo_ops->ringbuf_get_payload_size(get_fifo_ptr(fifo_num));
}

uint8_t boot_fifo_read(void *addr, uint16_t len, uint8_t fifo_num)
{
    // return rb_pop_bytes(get_fifo_ptr(fifo_num), addr, len);
    return boot_ops_ptr->fifo_ops->ringbuf_pop_bytes(get_fifo_ptr(fifo_num), addr, len);
}

uint8_t boot_fifo_write(const void *addr, uint16_t len, uint8_t fifo_num)
{
    uint8_t ret;
    uint16_t tx_len;
    static uint8_t buf[256] = {0};

    if (boot_get_port_type() == CAN_PORT)
    {
        if (boot_fifo_payload_length(TX_FIFO) > 1008)
            return 1;
    }
    // ret = rb_push_bytes(get_fifo_ptr(fifo_num), addr, len);
    ret = boot_ops_ptr->fifo_ops->ringbuf_push_bytes(get_fifo_ptr(fifo_num), addr, len);

    if (fifo_num == TX_FIFO)
    {
        if (!boot_fifo_is_empty(TX_FIFO))
        {
            tx_len = boot_fifo_payload_length(TX_FIFO);
            ret += boot_fifo_read(buf, tx_len, TX_FIFO);
            log_info("ret = %d\r\n", ret);
            boot_ops_ptr->sys_ops->port_send_data(buf, tx_len);
        }
    }

    return ret;
}

sys_ops_t *boot_get_sys_ops_ptr(void)
{
    return boot_ops_ptr->sys_ops;
}

#if USE_INTERFACE_CAN
uint8_t boot_uavcan_queue_can_send(const CanardFrame *txf)
{
    iFrame_t can_msg;
    can_msg.timestamp_usec = txf->timestamp_usec;
    can_msg.id = txf->extended_can_id;
    can_msg.size = txf->payload_size;
    memcpy(can_msg.data, txf->payload, txf->payload_size);

    return boot_fifo_write((uint8_t *)&can_msg, sizeof(can_msg), TX_FIFO);
}

void boot_accept_canard_frame(const CanardFrame *frame)
{
    sys_ops_api->accept_canard_frame(frame);
}
#endif
