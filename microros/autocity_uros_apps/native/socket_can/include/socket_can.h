/*
 * @Author: hanson
 * @Date: 2024-08-16 17:46:51
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-14 16:59:30
 * @Description:
 * @FilePath: \ucanbus\native\socket_can\include\socket_can.h
 */

#ifndef __NATIVE_SOCKET_CAN__H_
#define __NATIVE_SOCKET_CAN__H_

#include <stdint.h>

#define A_CAN_MAX_DLEN 8

#ifdef __cplusplus
extern "C"
{
#endif
    struct a_can_frame
    {
        /** 32 bit CAN_ID + EFF/RTR/ERR flags */
        uint32_t can_id;

        /** The length of the message */
        uint8_t can_dlc;

        /** @cond INTERNAL_HIDDEN */
        uint8_t pad;  /* padding */
        uint8_t res0; /* reserved / padding */
        uint8_t res1; /* reserved / padding */
        /** @endcond */

        /** The message data */
        uint8_t data[A_CAN_MAX_DLEN];
    };

    struct a_can_filter
    {
        uint32_t can_id;
        uint32_t can_mask;
    };

    /*
     * @Description:open a socket can
     * @param:dev_name dev name
     * @return:socke fd
     */
    int socket_can_open(const char *dev_name);

    /*
     * @Description:close a socket can
     * @param:fd socke fd
     * @return:suc:0,failed:-1
     */
    int socket_can_close(int fd);

    /*
     * @Description:send can frame
     * @param:fd to send
     * @param:frame to send
     * @return:suc:send len,failed:-1
     */
    int socket_can_send(int fd, struct a_can_frame *aframe);

    /*
     * @Description:recv can frame
     * @param:fd to recv from
     * @param:frame to recv
     * @return:suc:recv len,failed:-1
     */
    int socket_can_recv(int fd, struct a_can_frame *aframe);

    /*
     * @Description:set filter
     * @param:fd to set
     * @param:filter want set
     * @param:size of filter
     * @return:suc:0,failed:-1
     */
    int socket_can_set_filter(int fd, struct a_can_filter *filter, uint32_t size);

#ifdef __cplusplus
}
#endif
#endif // !__NATIVE_SOCKET_CAN__H_
