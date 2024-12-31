/*
 * @Author: hanson
 * @Date: 2024-12-31 11:49:49
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-31 14:49:47
 * @Description:
 * @FilePath: \test\other\project\can\src\main.cpp
 */
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <unistd.h>
#include <cerrno>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;
    int s;
    int o;
    std::string device = "can0";
    int can_id = 0x710;
    int dlc = 0;
    const char *optstring = "Dd:i:"; // 有三个选项-abc，其中c选项后有冒号，所以后面必须有参数
    while ((o = getopt(argc, argv, optstring)) != -1) {
        switch (o) {
            case 'D':
                printf("opt is D, oprarg is: %s\n", optarg);
                device = optarg;
                break;
            case 'i':
                printf("opt is i, oprarg is: %s\n", optarg);
                sscanf (optarg,"%x",&can_id);
                break;
            case 'd':
                printf("opt is d, oprarg is: %s\n", optarg);
                sscanf (optarg,"%d",&dlc);
                break;
            case '?':
                printf("error optopt: %c\n", optopt);
                printf("error opterr: %d\n", opterr);
                break;
        }
    }

    printf("device:%s,can_id:%x,dlc:%d\r\n",device.c_str(),can_id,dlc);

    // 创建 socket
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (s < 0)
    {
        std::cerr << "Error while opening socket" << std::endl;
        return -1;
    }

    // 指定 CAN 接口
    strcpy(ifr.ifr_name, device.c_str());
    ioctl(s, SIOCGIFINDEX, &ifr);
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    // 绑定 socket 到 CAN 接口
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cerr << "Error in socket bind" << std::endl;
        return -2;
    }

    // 设置远程帧
    frame.can_id = can_id | CAN_RTR_FLAG; // CAN ID 和远程传输请求标志
    frame.can_dlc = dlc;                   // 数据长度码（请求的字节数）

    // 发送远程帧
    if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
    {
        std::cerr << "Error while sending CAN remote frame" << std::endl;
        return -3;
    }

    // 关闭 socket
    close(s);
    return 0;
}
