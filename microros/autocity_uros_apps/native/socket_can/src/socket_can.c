/*
 * @Author: hanson
 * @Date: 2024-08-16 18:12:38
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-14 17:57:48
 * @Description:
 * @FilePath: \ucanbus\native\socket_can\src\socket_can.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include "socket_can.h"

static void copy_aframe_to_frame(const struct a_can_frame *aframe,
                                 struct can_frame *frame)
{
    frame->can_id = aframe->can_id;
    frame->can_dlc = aframe->can_dlc;
    memcpy(frame->data, aframe->data, sizeof(aframe->data));
}

static void copy_frame_to_aframe(const struct can_frame *frame,
                                 struct a_can_frame *aframe)
{
    aframe->can_id = frame->can_id;
    aframe->can_dlc = frame->can_dlc;
    memcpy(aframe->data, frame->data, sizeof(aframe->data));
}

int socket_can_open(const char *dev_name)
{
    struct ifreq ifr = {0};
    struct sockaddr_can can_addr = {0};
    int sockfd = -1;
    int ret;
    int enable = 1;

    /* 打开套接字 */
    sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (0 > sockfd)
    {
        printf("socket error\r\n");
        return -1;
    }

    /* 指定can0设备 */
    strcpy(ifr.ifr_name, dev_name);
    ioctl(sockfd, SIOCGIFINDEX, &ifr);
    can_addr.can_family = AF_CAN;
    can_addr.can_ifindex = ifr.ifr_ifindex;

    /* 将can0与套接字进行绑定 */
    ret = bind(sockfd, (struct sockaddr *)&can_addr, sizeof(can_addr));
    if (0 > ret)
    {
        printf("bind error\r\n");
        close(sockfd);
        return -1;
    }

    // 非阻塞
    if (fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0)
    {
        printf("fcntl error\r\n");
        return -1;
    }

    // support canfd
    ret = setsockopt(sockfd, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &enable, sizeof(enable));
    if (ret < 0)
    {
        printf("enable reception of can frame error code:%d\r\n ", ret);
        return -1;
    }

    printf("cancard init success\r\n");
    return sockfd;
}

int socket_can_close(int fd)
{
    if (fd > 0)
    {
        close(fd);
    }
    return 0;
}

int socket_can_send(int fd, struct a_can_frame *aframe)
{
    struct can_frame frame = {0};
    if (fd < 0)
    {
        printf("invalid fd\r\n");
        return -1;
    }

    copy_aframe_to_frame(aframe, &frame);

    int ret = write(fd, &frame, sizeof(frame)); // 发送数据

    if (ret != sizeof(struct can_frame))
    {
        ret = -1;
    }
    else
    {
        ret = sizeof(struct a_can_frame);
    }
    return ret;
}

int socket_can_recv(int fd, struct a_can_frame *aframe)
{
    struct can_frame frame = {0};
    if (fd < 0)
    {
        printf("invalid fd\r\n");
        return -1;
    }

    int ret = read(fd, &frame, sizeof(struct can_frame));

    if (ret != sizeof(struct can_frame))
    {
        ret = -1;
    }
    else
    {
        copy_frame_to_aframe(&frame, aframe);
        ret = sizeof(struct a_can_frame);
    }

    return ret;
}

int socket_can_set_filter(int fd, struct a_can_filter *filter, uint32_t size)
{
    struct can_filter rfilter[size];
    for (size_t i = 0; i < size; i++)
    {
        rfilter[i].can_id = filter[i].can_id;
        rfilter[i].can_mask = CAN_SFF_MASK;
    }

    return setsockopt(fd, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
}
