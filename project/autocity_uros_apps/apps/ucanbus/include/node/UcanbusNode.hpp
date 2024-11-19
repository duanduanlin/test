/*
 * @Author: hanson
 * @Date: 2024-08-23 17:21:05
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-29 15:21:47
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\include\node\UcanbusNode.hpp
 */

#ifndef __UCANBUS_INCLUDE_UCANBUSNODE__H_
#define __UCANBUS_INCLUDE_UCANBUSNODE__H_

#include "node/BaseNode.hpp"
#include "msg_wrap/ChassisMsgWrap.hpp"
#include "msg_wrap/ControlMsgWrap.hpp"
// #include "msg_wrap/StdMsgWrap.hpp"

class UcanbusNode : public BaseNode
{
private:
    /*pub sub handler*/
    std::shared_ptr<Publisher<ChassisMsgWrap>> _chassic_pub;
    // std::shared_ptr<Publisher<StdMsgWrap>> _std_pub;
    std::shared_ptr<Subscriber<ControlMsgWrap>> _control_cmd_sub;
    static bool _save_publish_data;

public:
    UcanbusNode(const std::string &node_name);
    ~UcanbusNode();

    int Setup();

    void PublishChassis(ChassisMsgWrap &msg);

    // void PublishStdMsg(StdMsgWrap &msg);

    ControlMsgWrap *GetControlCmdMsg();

private:
    static void _control_callback(ControlMsgWrap &msg);
};
#endif //__UCANBUS_INCLUDE_UCANBUSNODE__H_
