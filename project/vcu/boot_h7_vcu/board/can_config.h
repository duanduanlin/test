#ifndef __CAN_CONFIG_H__
#define __CAN_CONFIG_H__





#define CAN1_USED 1
#define CAN2_USED 1

#define CAN_RAM_DATA_WORDS   (4U)

#define CAN1_FILTER_STD_NUM             (8U)
#define CAN1_FILTER_EXT_NUM             (8U)
#define CAN1_RX_FIFO0_ELEM_NUM          (8U)
#define CAN1_RX_FIFO1_ELEM_NUM          (0U)
#define CAN1_RX_BUF_NUM                 (0U)
#define CAN1_TX_EVENT_FIFO_NUM          (8U)
#define CAN1_TX_BUF_NUM                 (8U)
#define CAN1_TX_FIFO_ELEM_NUM           (8U)



#define CAN2_FILTER_STD_NUM             (8U)
#define CAN2_FILTER_EXT_NUM             (8U)
#define CAN2_RX_FIFO0_ELEM_NUM          (8U)
#define CAN2_RX_FIFO1_ELEM_NUM          (0U)
#define CAN2_RX_BUF_NUM                 (0U)
#define CAN2_TX_EVENT_FIFO_NUM          (16U)
#define CAN2_TX_BUF_NUM                 (0U)
#define CAN2_TX_FIFO_ELEM_NUM           (16U)
// CAN1 controller configuration ------

#ifndef CAN1_RX_FIFO0_ELEM_NUM
#define CAN1_RX_FIFO0_ELEM_NUM          (8U)
#endif
#if    (CAN1_RX_FIFO0_ELEM_NUM > 64U)
#error  Too many Receive FIFO0 Elements defined for CAN1, maximum number of Receive FIFO0 Elements is 64 !!!
#endif

#ifndef CAN1_RX_FIFO1_ELEM_NUM
#define CAN1_RX_FIFO1_ELEM_NUM          (8U)
#endif
#if    (CAN1_RX_FIFO1_ELEM_NUM > 64U)
#error  Too many Receive FIFO1 Elements defined for CAN1, maximum number of Receive FIFO1 Elements is 64 !!!
#endif

#ifndef CAN1_RX_BUF_NUM
#define CAN1_RX_BUF_NUM                 (16U)
#endif
#if    (CAN1_RX_BUF_NUM > 64U)
#error  Too many Receive Buffers defined for CAN1, maximum number of Receive Buffers is 64 !!!
#endif

#ifndef CAN1_TX_EVENT_FIFO_NUM
#define CAN1_TX_EVENT_FIFO_NUM                 (16U)
#endif
#if    (CAN1_TX_EVENT_FIFO_NUM > 32U)
#error  Too many Tx Event fifos defined for CAN1, maximum number of Receive Buffers is 32 !!!
#endif

#ifndef CAN1_TX_FIFO_ELEM_NUM
#define CAN1_TX_FIFO_ELEM_NUM           (8U)
#endif
#if    (CAN1_TX_FIFO_ELEM_NUM > 32U)
#error  Too many Transmit FIFO Elements defined for CAN1, maximum number of Transmit FIFO Elements is 32 !!!
#endif

#ifndef CAN1_TX_BUF_NUM
#define CAN1_TX_BUF_NUM                 (16U)
#endif
#if    (CAN1_TX_BUF_NUM > 32U)
#error  Too many Transmit Buffers defined for CAN1, maximum number of Transmit Buffers is 32 !!!
#endif

#if    ((CAN1_TX_FIFO_ELEM_NUM + CAN1_TX_BUF_NUM) > 32U)
#error  Too many Transmit Elements and Buffers defined for CAN1, maximum number of Transmit Elements and Buffers together is 32 !!!
#endif

#ifndef CAN1_FILTER_STD_NUM
#define CAN1_FILTER_STD_NUM             (128U)
#endif
#if    (CAN1_FILTER_STD_NUM > 128U)
#error  Standard Filter Elements defined for CAN1, maximum number of Standard Filter Elements is 128 !!!
#endif

#ifndef CAN1_FILTER_EXT_NUM
#define CAN1_FILTER_EXT_NUM             (64U)
#endif
#if    (CAN1_FILTER_EXT_NUM > 64U)
#error  Extended Filter Elements defined for CAN1, maximum number of Extended Filter Elements is 64 !!!
#endif

#define CAN1_RX_FIFO_EN                ((CAN1_RX_FIFO0_ELEM_NUM != 0U) || (CAN1_RX_FIFO1_ELEM_NUM != 0U))
#define CAN1_RX_BUF_EN                  (CAN1_RX_BUF_NUM        != 0U)
#define CAN1_TX_FIFO_EN                 (CAN1_TX_FIFO_ELEM_NUM  != 0U)
#define CAN1_TX_BUF_EN                  (CAN1_TX_BUF_NUM        != 0U)
#define CAN1_RX_FIFO_OBJ_NUM           ((CAN1_RX_FIFO0_ELEM_NUM != 0U) + (CAN1_RX_FIFO1_ELEM_NUM != 0U))
#define CAN1_RX_BUF_OBJ_NUM             (CAN1_RX_BUF_NUM)
#define CAN1_RX_TOT_OBJ_NUM             (CAN1_RX_FIFO_OBJ_NUM + CAN1_RX_BUF_OBJ_NUM)
#define CAN1_TX_FIFO_OBJ_NUM           ((CAN1_TX_FIFO_ELEM_NUM  != 0U))
#define CAN1_TX_BUF_OBJ_NUM             (CAN1_TX_BUF_NUM)
#define CAN1_TX_TOT_OBJ_NUM             (CAN1_TX_FIFO_OBJ_NUM + CAN1_TX_BUF_OBJ_NUM)
#define CAN1_TOT_OBJ_NUM                (CAN1_RX_TOT_OBJ_NUM  + CAN1_TX_TOT_OBJ_NUM)
#define CAN1_TOT_ELEM_NUM               (CAN1_RX_FIFO0_ELEM_NUM + CAN1_RX_FIFO1_ELEM_NUM + CAN1_RX_BUF_NUM + CAN1_TX_BUF_NUM)

#define CAN1_RAM_OFS_STD_ID             (0U)
#define CAN1_RAM_OFS_EXT_ID             (CAN1_RAM_OFS_STD_ID        +   CAN1_FILTER_STD_NUM)
#define CAN1_RAM_OFS_RX_FIFO0           (CAN1_RAM_OFS_EXT_ID        +  (CAN1_FILTER_EXT_NUM    * 2U))
#define CAN1_RAM_OFS_RX_FIFO1           (CAN1_RAM_OFS_RX_FIFO0      +  (CAN1_RX_FIFO0_ELEM_NUM * CAN_RAM_DATA_WORDS))
#define CAN1_RAM_OFS_RX_BUFFER          (CAN1_RAM_OFS_RX_FIFO1      +  (CAN1_RX_FIFO1_ELEM_NUM * CAN_RAM_DATA_WORDS))
#define CAN1_RAM_OFS_TX_EVENT_FIFO      (CAN1_RAM_OFS_RX_BUFFER     +  (CAN1_RX_BUF_NUM        * CAN_RAM_DATA_WORDS))
#define CAN1_RAM_OFS_TX_BUFFER          (CAN1_RAM_OFS_TX_EVENT_FIFO +  (CAN1_TX_EVENT_FIFO_NUM * 2U))
#define CAN1_RAM_OFS_TX_FIFO            (CAN1_RAM_OFS_TX_BUFFER     +  (CAN1_TX_BUF_NUM  * CAN_RAM_DATA_WORDS))
#define CAN1_TOT_RAM                    (CAN1_RAM_OFS_TX_FIFO       +  (CAN1_TX_FIFO_ELEM_NUM  ) * CAN_RAM_DATA_WORDS)


#ifndef CAN2_RX_FIFO0_ELEM_NUM
#define CAN2_RX_FIFO0_ELEM_NUM          (8U)
#endif
#if    (CAN2_RX_FIFO0_ELEM_NUM > 64U)
#error  Too many Receive FIFO0 Elements defined for CAN2, maximum number of Receive FIFO0 Elements is 64 !!!
#endif

#ifndef CAN2_RX_FIFO1_ELEM_NUM
#define CAN2_RX_FIFO1_ELEM_NUM          (8U)
#endif
#if    (CAN2_RX_FIFO1_ELEM_NUM > 64U)
#error  Too many Receive FIFO1 Elements defined for CAN2, maximum number of Receive FIFO1 Elements is 64 !!!
#endif

#ifndef CAN2_RX_BUF_NUM
#define CAN2_RX_BUF_NUM                 (16U)
#endif
#if    (CAN2_RX_BUF_NUM > 64U)
#error  Too many Receive Buffers defined for CAN2, maximum number of Receive Buffers is 64 !!!
#endif

#ifndef CAN2_TX_EVENT_FIFO_NUM
#define CAN2_TX_EVENT_FIFO_NUM                 (16U)
#endif
#if    (CAN2_TX_EVENT_FIFO_NUM > 32U)
#error  Too many Tx Event fifos defined for CAN2, maximum number of Receive Buffers is 32 !!!
#endif

#ifndef CAN2_TX_FIFO_ELEM_NUM
#define CAN2_TX_FIFO_ELEM_NUM           (8U)
#endif
#if    (CAN2_TX_FIFO_ELEM_NUM > 32U)
#error  Too many Transmit FIFO Elements defined for CAN2, maximum number of Transmit FIFO Elements is 32 !!!
#endif

#ifndef CAN2_TX_BUF_NUM
#define CAN2_TX_BUF_NUM                 (16U)
#endif
#if    (CAN2_TX_BUF_NUM > 32U)
#error  Too many Transmit Buffers defined for CAN2, maximum number of Transmit Buffers is 32 !!!
#endif

#if    ((CAN2_TX_FIFO_ELEM_NUM + CAN2_TX_BUF_NUM) > 32U)
#error  Too many Transmit Elements and Buffers defined for CAN2, maximum number of Transmit Elements and Buffers together is 32 !!!
#endif

#ifndef CAN2_FILTER_STD_NUM
#define CAN2_FILTER_STD_NUM             (128U)
#endif
#if    (CAN2_FILTER_STD_NUM > 128U)
#error  Standard Filter Elements defined for CAN2, maximum number of Standard Filter Elements is 128 !!!
#endif

#ifndef CAN2_FILTER_EXT_NUM
#define CAN2_FILTER_EXT_NUM             (64U)
#endif
#if    (CAN2_FILTER_EXT_NUM > 64U)
#error  Extended Filter Elements defined for CAN2, maximum number of Extended Filter Elements is 64 !!!
#endif

#define CAN2_RX_FIFO_EN                ((CAN2_RX_FIFO0_ELEM_NUM != 0U) || (CAN2_RX_FIFO1_ELEM_NUM != 0U))
#define CAN2_RX_BUF_EN                  (CAN2_RX_BUF_NUM        != 0U)
#define CAN2_TX_FIFO_EN                 (CAN2_TX_FIFO_ELEM_NUM  != 0U)
#define CAN2_TX_BUF_EN                  (CAN2_TX_BUF_NUM        != 0U)
#define CAN2_RX_FIFO_OBJ_NUM           ((CAN2_RX_FIFO0_ELEM_NUM != 0U) + (CAN2_RX_FIFO1_ELEM_NUM != 0U))
#define CAN2_RX_BUF_OBJ_NUM             (CAN2_RX_BUF_NUM)
#define CAN2_RX_TOT_OBJ_NUM             (CAN2_RX_FIFO_OBJ_NUM + CAN2_RX_BUF_OBJ_NUM)
#define CAN2_TX_FIFO_OBJ_NUM           ((CAN2_TX_FIFO_ELEM_NUM  != 0U))
#define CAN2_TX_BUF_OBJ_NUM             (CAN2_TX_BUF_NUM)
#define CAN2_TX_TOT_OBJ_NUM             (CAN2_TX_FIFO_OBJ_NUM + CAN2_TX_BUF_OBJ_NUM)
#define CAN2_TOT_OBJ_NUM                (CAN2_RX_TOT_OBJ_NUM  + CAN2_TX_TOT_OBJ_NUM)
#define CAN2_TOT_ELEM_NUM               (CAN2_RX_FIFO0_ELEM_NUM + CAN2_RX_FIFO1_ELEM_NUM + CAN2_RX_BUF_NUM + CAN2_TX_BUF_NUM)

#define CAN2_RAM_OFS_STD_ID             (0U)
#define CAN2_RAM_OFS_EXT_ID             (CAN2_RAM_OFS_STD_ID        +   CAN2_FILTER_STD_NUM)
#define CAN2_RAM_OFS_RX_FIFO0           (CAN2_RAM_OFS_EXT_ID        +  (CAN2_FILTER_EXT_NUM    * 2U))
#define CAN2_RAM_OFS_RX_FIFO1           (CAN2_RAM_OFS_RX_FIFO0      +  (CAN2_RX_FIFO0_ELEM_NUM * CAN_RAM_DATA_WORDS))
#define CAN2_RAM_OFS_RX_BUFFER          (CAN2_RAM_OFS_RX_FIFO1      +  (CAN2_RX_FIFO1_ELEM_NUM * CAN_RAM_DATA_WORDS))
#define CAN2_RAM_OFS_TX_EVENT_FIFO      (CAN2_RAM_OFS_RX_BUFFER     +  (CAN2_RX_BUF_NUM        * CAN_RAM_DATA_WORDS))
#define CAN2_RAM_OFS_TX_BUFFER          (CAN2_RAM_OFS_TX_EVENT_FIFO +  (CAN2_TX_EVENT_FIFO_NUM * 2U))
#define CAN2_RAM_OFS_TX_FIFO            (CAN2_RAM_OFS_TX_BUFFER     +  (CAN2_TX_BUF_NUM  * CAN_RAM_DATA_WORDS))
#define CAN2_TOT_RAM                    (CAN2_RAM_OFS_TX_FIFO       +  (CAN2_TX_FIFO_ELEM_NUM  ) * CAN_RAM_DATA_WORDS)

// Check Message RAM configuration
#if ((CAN1_USED == 1) && (CAN2_USED == 0) && (CAN1_TOT_RAM > 2560U))
  #error Message RAM contains only 10 kB, current configuration of CAN1 requires more memory, please reduce number of FIFO or buffer elements for Receive or Transmit!
#endif
#if ((CAN1_USED == 0) && (CAN2_USED == 1) && (CAN2_TOT_RAM > 2560U))
  #error Message RAM contains only 10 kB, current configuration of CAN2 requires more memory, please reduce number of FIFO or buffer elements for Receive or Transmit!
#endif
#if ((CAN1_USED == 1) && (CAN2_USED == 1) && ((CAN1_TOT_RAM + CAN2_TOT_RAM) > 2560U))
  #error Message RAM contains only 10 kB, current configuration of CAN1 and CAN2 requires more memory, please reduce number of FIFO or buffer elements for Receive or Transmit!
#endif

#endif