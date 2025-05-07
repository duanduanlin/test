/*
 * @Author: dding3
 * @Date: 2025-04-01 09:50:05
 * @LastEditors: dding3
 * @LastEditTime: 2025-05-06 18:21:44
 * @Description:
 * @FilePath: \ps_vcu\modules\diag.h
 */
#ifndef MODULES_DIAG_H_
#define MODULES_DIAG_H_

#include "stdint.h"

typedef enum node
{
    Node_ADCU,
    Node_CCU,
    Node_MCU_L,
    Node_MCU_R,
    Node_EPS,
    Node_PMU,
    Node_OBD,
} Node;

//sd 故障
void Diag_Set_VcuFault_SD(void);
void Diag_Clear_VcuFault_SD(void);
//dc12电压异常
void Diag_Set_VcuFault_DC12(void);
void Diag_Clear_VcuFault_DC12(void);
//时间未同步
void Diag_Set_VcuFault_TimeNotSync(void);
void Diag_Clear_VcuFault_TimeNotSync(void);
//时间未同步
void Diag_Set_VcuFault_DchargeNotDisconnect(void);
void Diag_Clear_VcuFault_DchargeNotDisconnect(void);

//节点丢失判断
void Diag_Update_Node(Node node);
void Diag_Check_Node(void);

//mcu故障
void Diag_Set_McuFault(uint8_t code_l,uint8_t code_r);

//ccu故障
void Diag_Set_CcuFault(uint32_t code);

void Diag_Get_VcuFaultCode(uint8_t *data, int len);
void Diag_Get_McuFaultCode(uint8_t *data, int len);
void Diag_Get_CcuFaultCode(uint8_t *data, int len);
#endif // MODULES_DIAG_H_
