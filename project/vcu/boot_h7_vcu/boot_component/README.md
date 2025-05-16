# boot_component submodule

## 移植步骤
### 1. 克隆(直接克隆或添加为子模块)boot_component仓库
### 2. 修改boot_cfg.h配置文件
```
// header file
#include "ring_buffer.h"-包含基础工程中fifo头文件
// ringbuf data type
#define ringbuf_t mrb_t-替换mrb_t为自定义的fifo数据类型
// port
#define USE_INTERFACE_CAN 1
#define USE_INTERFACE_UART 0
使能使用的硬件接口，1为使能，0为使能，两个端口不能同时使能
// log info
#define log_info(format, ...) printf(format, ##__VA_ARGS__)
添加信息打印接口
```
### 3. 基础工程中包含hal_boot.h头文件，实现boot_ops_t类型中抽象的boot接口，具体如下:
- boot类
```
typedef struct
{
    flash_ops_t *flash_ops;
    fifo_ops_t *fifo_ops;
    sys_ops_t *sys_ops;
} boot_ops_t;
```

   - flash接口
   ```
   typedef struct
   {
       void (*unlock)(void); // flash上锁
       void (*lock)(void); // flash解锁
       函数参数:
       param1:uint32_t-flash页地址，此参数需在flash合法地址范围内
       void (*erase)(uint32_t); // flash擦除
       函数参数:
       param1:uint32_t-flash地址，此参数需在flash合法地址范围内
       param2:uint8_t *-数据buf指针
       param3:uint16_t-数据字节数
       void (*read)(uint32_t, uint8_t *, uint16_t); // flash读
       函数参数:
       param1:uint32_t-flash地址，此参数需在flash合法地址范围内
       param2:uint8_t *-数据buf指针
       param3:uint16_t-数据字节数
       void (*write)(uint32_t, uint8_t *, uint16_t); // flash写
   } flash_ops_t;
   ```

   - ringbuf接口
   ```
   typedef struct
   {
       ringbuf_t *recv_fifo_ptr; // 接收fifo句柄
       ringbuf_t *send_fifo_ptr; // 发送fifo句柄
       函数参数:
       param1:ringbuf_t *-fifo句柄
       返回值:
       int8_t:0-非空 其他为空
       int8_t (*ringbuf_is_empty)(ringbuf_t *); // fifo是否为空
       函数参数:
       param1:ringbuf_t *-fifo句柄
       返回值:
       uint16_t:有效数据个数
       uint16_t (*ringbuf_get_payload_size)(ringbuf_t *); // fifo有效数据长度
       函数参数:
       param1:ringbuf_t *-fifo句柄
       param2:void *-数据buf指针
       param3:void *-数据字节数
       返回值:
       int8_t:0-出队成功 -1:出队失败
       int8_t (*ringbuf_pop_bytes)(ringbuf_t *, void *, uint16_t len); // fifo出队
       函数参数:
       param1:ringbuf_t *-fifo句柄
       param2:void *-数据buf指针
       param3:void *-数据字节数
       返回值:
       int8_t:0-出队成功 -1:出队失败
       int8_t (*ringbuf_push_bytes)(ringbuf_t *, const void *, uint16_t len); // fifo入队
   } fifo_ops_t;
   ```

   - 系统操作接口
   ```
   typedef struct
   {
       typedef enum
       {
           CAN_PORT = 1,
           UART_PORT,
           USB_PORT,
       } port_type_t;
       uint8_t port_type; // port类型，可能取值如上枚举类型
       uint8_t module_self; // 模块ID
       uint16_t flash_param_max_size; // app最大块大小，单位为KB
       uint16_t flash_app_max_size; // param最大块大小，单位为KB
       uint32_t flash_start_addr; // flash起始地址
       uint32_t param_offset_addr; // param偏移地址，地址为整页起始地址
       uint32_t app_offset_addr; // app偏移地址，地址为整页起始地址
       uint32_t ram_valid_addr_range; / 内存有效地址范围
       uint8_t boot_version[10]; // boot版本号   
       void (*reboot)(void); // 系统重启接口
       void (*reset)(void); // 系统reset接口，跳转app前对系统及外设的预处理操作
       函数参数:
       param1:uint32_t-flash有效地址
       void (*set_msp)(uint32_t); // 设置msp指针接口
       uint32_t (*get_sys_tick)(void); // 获取系统时基，周期为1ms
       函数参数:
       param1:uint32_t-延时计数值
       void (*delay_ms)(uint32_t); // 毫秒级延时
       void (*task_led_callback)(void); // led任务回调函数
       函数参数:
       param1:uint8_t *-数据buf指针
       param2:uint16_t-数据字节数
       void (*port_send_data)(uint8_t *, uint16_t); // port数据发送函数
   #if USE_INTERFACE_CAN
       函数参数:
       param1:CanardFrame *-数据帧类型指针
       int8_t (*accept_canard_frame)(const CanardFrame *); // uavcan数据解析接口
       函数参数:
       param1:CanardMicrosecond-ms级系统时基 CanardPortID
       param2:CanardPortID-命令ID
       param3:size_t-数据帧字节数
       param4:void *-数据buf指针
       uint8_t (*uavcan_msg_pack_publish)(CanardMicrosecond, CanardPortID, size_t, const void *); // uavcan数据发送接口
   #endif
   } sys_ops_t;
   sys_ops_t sys_ops;
   ```

### 4. 实现上述接口定义，在基础工程初始化函数中调用boot_init(&sys_ops)对boot进行初始化

### 5. 在基础工程主循环中调用boot_run()函数
