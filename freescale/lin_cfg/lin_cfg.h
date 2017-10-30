/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2016-2017 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      lin_cfg.h 
* 
* @author    FPT Software
*  
* @version   1.0 
*  
* @date      Tue Jun 20 15:31:09 CST 2017
*  
* @brief     Hardware configuration file
* 
******************************************************************************/
#ifndef    _LIN_CFG_H_  
#define    _LIN_CFG_H_  
#include "lin_hw_cfg.h" 
/* Define operating mode */
#define _MASTER_MODE_     0 
#define _SLAVE_MODE_      1 
#define LIN_MODE   _SLAVE_MODE_
/* Define protocol version */
#define PROTOCOL_21       0  
#define PROTOCOL_J2602    1  
#define PROTOCOL_20       2 
#define LIN_PROTOCOL    PROTOCOL_21

#define SCI_ADDR        SCI0_ADDR    /* For slave */ 

#define LIN_BAUD_RATE    19200    	 /*For slave*/ 
/**********************************************************************/
/***************          Diagnostic class selection  *****************/
/**********************************************************************/
#define _DIAG_CLASS_I_          0
#define _DIAG_CLASS_II_         1
#define _DIAG_CLASS_III_        2

#define _DIAG_CLASS_SUPPORT_    _DIAG_CLASS_III_
/**************** FRAME SUPPORT DEFINITION ******************/
#define _TL_SINGLE_FRAME_       0
#define _TL_MULTI_FRAME_        1

#define _TL_FRAME_SUPPORT_      _TL_MULTI_FRAME_
/*************** DIAGNOSTIC SERVICES INDEX  ************/
#define DIAGSRV_READ_DATA_BY_IDENTIFIER_ORDER       0   /**< Diagnostic service: read data by identifier */
#define DIAGSRV_WRITE_DATA_BY_IDENTIFIER_ORDER      1   /**< Diagnostic service: write data by identifier */
#define DIAGSRV_SESSION_CONTROL_ORDER               2   /**< Diagnostic service: session control */
#define DIAGSRV_IO_CONTROL_BY_IDENTIFIER_ORDER      3   /**< Diagnostic service: I/O control by identifier */
#define DIAGSRV_FAULT_MEMORY_READ_ORDER             4   /**< Diagnostic service: read and clear DTC (fault memory) */
#define DIAGSRV_FAULT_MEMORY_CLEAR_ORDER            5   /**< Diagnostic service: fault memory clear */
/*Diagnostic class III */
#define _DIAG_NUMBER_OF_SERVICES_     6           /**< Number of diagnostic services class II and class III */
/* frame buffer size */
#define LIN_FRAME_BUF_SIZE			16
#define LIN_FLAG_BUF_SIZE			2

/**********************************************************************/
/***************               Interfaces           *******************/
/**********************************************************************/
typedef enum { 
   LI0
}l_ifc_handle; 

/**********************************************************************/
/***************               Signals              *******************/
/**********************************************************************/
/* Number of signals */
#define LIN_NUM_OF_SIGS  9
/* List of signals */   
typedef enum {

   /* Interface_name = LI0 */

   LI0_L_AC_BlowerLevel

   , LI0_L_AC_Control_Lock_Req
  
   , LI0_L_AC_OnOff_Req
  
   , LI0_L_RCP_OverVoltage
  
   , LI0_L_RCP_UnderVoltage
  
   , LI0_L_RCP_Blower_Speed
  
   , LI0_L_RCP_Lock_Status
  
   , LI0_L_RCP_Blower_Err
  
   , LI0_L_RCP_Error
  
  
} l_signal_handle; 
/**********************************************************************/
/*****************               Frame             ********************/
/**********************************************************************/
/* Number of frames */
#define LIN_NUM_OF_FRMS  4 
/* List of frames */
typedef enum {
/* All frames for master node */

   /* Interface_name = LI0 */

   LI0_AC_1

   , LI0_RCP_1
  
   , LI0_MasterReq
  
   , LI0_SlaveResp
  
  
} l_frame_handle; 
 
/**********************************************************************/
/***************             Configuration          *******************/
/**********************************************************************/
/* Size of configuration in ROM and RAM used for interface: LI1 */
#define LIN_SIZE_OF_CFG  6 
#define LIN_CFG_FRAME_NUM  2 
/*********************************************************************
 * global macros
 *********************************************************************/
#define l_bool_rd(SIGNAL) l_bool_rd_##SIGNAL()
#define l_bool_wr(SIGNAL, A) l_bool_wr_##SIGNAL(A)
#define l_u8_rd(SIGNAL) l_u8_rd_##SIGNAL()
#define l_u8_wr(SIGNAL, A) l_u8_wr_##SIGNAL(A)
#define l_u16_rd(SIGNAL) l_u16_rd_##SIGNAL()
#define l_u16_wr(SIGNAL, A) l_u16_wr_##SIGNAL(A)
#define l_bytes_rd(SIGNAL, start, count, data)  l_bytes_rd_##SIGNAL(start, count, data)
#define l_bytes_wr(SIGNAL, start, count, data) l_bytes_wr_##SIGNAL(start, count, data)
#define l_flg_tst(FLAG) l_flg_tst_##FLAG()
#define l_flg_clr(FLAG) l_flg_clr_##FLAG()
#define LIN_TEST_BIT(A,B) ((l_bool)((((A) & (1U << (B))) != 0U) ? 1U : 0U))
#define LIN_SET_BIT(A,B)                      ((A) |= (l_u8) (1U << (B)))
#define LIN_CLEAR_BIT(A,B)               ((A) &= ((l_u8) (~(1U << (B)))))
#define LIN_BYTE_MASK  ((l_u16)(((l_u16)((l_u16)1 << CHAR_BIT)) - (l_u16)1))
#define LIN_FRAME_LEN_MAX                                             10U

/* Returns the low byte of the 32-bit value    */
#define BYTE_0(n)                              ((l_u8)((n) & (l_u8)0xFF))
/* Returns the second byte of the 32-bit value */
#define BYTE_1(n)                        ((l_u8)(BYTE_0((n) >> (l_u8)8)))
/* Returns the third byte of the 32-bit value  */
#define BYTE_2(n)                       ((l_u8)(BYTE_0((n) >> (l_u8)16)))
/* Returns high byte of the 32-bit value       */
#define BYTE_3(n)                       ((l_u8)(BYTE_0((n) >> (l_u8)24)))

/*
 * defines for signal access
 */


#define LIN_BYTE_OFFSET_LI0_L_AC_Control_Lock_Req    5
#define LIN_BIT_OFFSET_LI0_L_AC_Control_Lock_Req    4
#define LIN_SIGNAL_SIZE_LI0_L_AC_Control_Lock_Req    2
#define LIN_FLAG_BYTE_OFFSET_LI0_L_AC_Control_Lock_Req    0
#define LIN_FLAG_BIT_OFFSET_LI0_L_AC_Control_Lock_Req    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_AC_Control_Lock_Req    0

#define LIN_BYTE_OFFSET_LI0_L_AC_OnOff_Req    5
#define LIN_BIT_OFFSET_LI0_L_AC_OnOff_Req    6
#define LIN_SIGNAL_SIZE_LI0_L_AC_OnOff_Req    2
#define LIN_FLAG_BYTE_OFFSET_LI0_L_AC_OnOff_Req    0
#define LIN_FLAG_BIT_OFFSET_LI0_L_AC_OnOff_Req    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_AC_OnOff_Req    0

#define LIN_BYTE_OFFSET_LI0_L_RCP_OverVoltage    14
#define LIN_BIT_OFFSET_LI0_L_RCP_OverVoltage    0
#define LIN_SIGNAL_SIZE_LI0_L_RCP_OverVoltage    1
#define LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_OverVoltage    1
#define LIN_FLAG_BIT_OFFSET_LI0_L_RCP_OverVoltage    3
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_RCP_OverVoltage    1

#define LIN_BYTE_OFFSET_LI0_L_RCP_UnderVoltage    14
#define LIN_BIT_OFFSET_LI0_L_RCP_UnderVoltage    1
#define LIN_SIGNAL_SIZE_LI0_L_RCP_UnderVoltage    1
#define LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_UnderVoltage    1
#define LIN_FLAG_BIT_OFFSET_LI0_L_RCP_UnderVoltage    4
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_RCP_UnderVoltage    1

#define LIN_BYTE_OFFSET_LI0_L_RCP_Blower_Speed    14
#define LIN_BIT_OFFSET_LI0_L_RCP_Blower_Speed    2
#define LIN_SIGNAL_SIZE_LI0_L_RCP_Blower_Speed    4
#define LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_Blower_Speed    1
#define LIN_FLAG_BIT_OFFSET_LI0_L_RCP_Blower_Speed    5
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_RCP_Blower_Speed    1

#define LIN_BYTE_OFFSET_LI0_L_RCP_Lock_Status    14
#define LIN_BIT_OFFSET_LI0_L_RCP_Lock_Status    6
#define LIN_SIGNAL_SIZE_LI0_L_RCP_Lock_Status    1
#define LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_Lock_Status    1
#define LIN_FLAG_BIT_OFFSET_LI0_L_RCP_Lock_Status    6
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_RCP_Lock_Status    1

#define LIN_BYTE_OFFSET_LI0_L_RCP_Blower_Err    13
#define LIN_BIT_OFFSET_LI0_L_RCP_Blower_Err    7
#define LIN_SIGNAL_SIZE_LI0_L_RCP_Blower_Err    1
#define LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_Blower_Err    1
#define LIN_FLAG_BIT_OFFSET_LI0_L_RCP_Blower_Err    2
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_RCP_Blower_Err    1

#define LIN_BYTE_OFFSET_LI0_L_RCP_Error    13
#define LIN_BIT_OFFSET_LI0_L_RCP_Error    6
#define LIN_SIGNAL_SIZE_LI0_L_RCP_Error    1
#define LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_Error    1
#define LIN_FLAG_BIT_OFFSET_LI0_L_RCP_Error    1
#define LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_RCP_Error    1




#define LIN_FLAG_BYTE_OFFSET_LI0_AC_1             0
#define LIN_FLAG_BIT_OFFSET_LI0_AC_1              0

#define LIN_FLAG_BYTE_OFFSET_LI0_RCP_1             1
#define LIN_FLAG_BIT_OFFSET_LI0_RCP_1              0


/**********************************************************************/
/***************        Static API Functions        *******************/
/**********************************************************************/
/*
 * the static signal access macros
 */


/* static access macros for signal LI0_L_AC_Control_Lock_Req */
#define l_u8_rd_LI0_L_AC_Control_Lock_Req() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_AC_Control_Lock_Req] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_L_AC_Control_Lock_Req) - 1) \
    << LIN_BIT_OFFSET_LI0_L_AC_Control_Lock_Req )) >> LIN_BIT_OFFSET_LI0_L_AC_Control_Lock_Req))
#define l_u8_wr_LI0_L_AC_Control_Lock_Req(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_AC_Control_Lock_Req] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_AC_Control_Lock_Req] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_L_AC_Control_Lock_Req) - 1) << LIN_BIT_OFFSET_LI0_L_AC_Control_Lock_Req)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_L_AC_Control_Lock_Req) - 1) & (A)) << LIN_BIT_OFFSET_LI0_L_AC_Control_Lock_Req))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_AC_Control_Lock_Req] = 1;}

/* static access macros for signal LI0_L_AC_OnOff_Req */
#define l_u8_rd_LI0_L_AC_OnOff_Req() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_AC_OnOff_Req] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_L_AC_OnOff_Req) - 1) \
    << LIN_BIT_OFFSET_LI0_L_AC_OnOff_Req )) >> LIN_BIT_OFFSET_LI0_L_AC_OnOff_Req))
#define l_u8_wr_LI0_L_AC_OnOff_Req(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_AC_OnOff_Req] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_AC_OnOff_Req] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_L_AC_OnOff_Req) - 1) << LIN_BIT_OFFSET_LI0_L_AC_OnOff_Req)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_L_AC_OnOff_Req) - 1) & (A)) << LIN_BIT_OFFSET_LI0_L_AC_OnOff_Req))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_AC_OnOff_Req] = 1;}

/* static access macros for signal LI0_L_RCP_OverVoltage */
#define l_bool_rd_LI0_L_RCP_OverVoltage() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_OverVoltage], \
   	LIN_BIT_OFFSET_LI0_L_RCP_OverVoltage))
#define l_bool_wr_LI0_L_RCP_OverVoltage(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_OverVoltage], \
  	LIN_BIT_OFFSET_LI0_L_RCP_OverVoltage)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_OverVoltage], \
  	LIN_BIT_OFFSET_LI0_L_RCP_OverVoltage));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_RCP_OverVoltage] = 1;}

/* static access macros for signal LI0_L_RCP_UnderVoltage */
#define l_bool_rd_LI0_L_RCP_UnderVoltage() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_UnderVoltage], \
   	LIN_BIT_OFFSET_LI0_L_RCP_UnderVoltage))
#define l_bool_wr_LI0_L_RCP_UnderVoltage(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_UnderVoltage], \
  	LIN_BIT_OFFSET_LI0_L_RCP_UnderVoltage)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_UnderVoltage], \
  	LIN_BIT_OFFSET_LI0_L_RCP_UnderVoltage));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_RCP_UnderVoltage] = 1;}

/* static access macros for signal LI0_L_RCP_Blower_Speed */
#define l_u8_rd_LI0_L_RCP_Blower_Speed() \
    ((l_u8) ((lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_Blower_Speed] & \
    (((1U << LIN_SIGNAL_SIZE_LI0_L_RCP_Blower_Speed) - 1) \
    << LIN_BIT_OFFSET_LI0_L_RCP_Blower_Speed )) >> LIN_BIT_OFFSET_LI0_L_RCP_Blower_Speed))
#define l_u8_wr_LI0_L_RCP_Blower_Speed(A) \
    {lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_Blower_Speed] = \
    ((l_u8) (((l_u8) (lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_Blower_Speed] & \
    ((l_u8) (~(((1U << LIN_SIGNAL_SIZE_LI0_L_RCP_Blower_Speed) - 1) << LIN_BIT_OFFSET_LI0_L_RCP_Blower_Speed)))))  | \
    ((l_u8) ((((1U << LIN_SIGNAL_SIZE_LI0_L_RCP_Blower_Speed) - 1) & (A)) << LIN_BIT_OFFSET_LI0_L_RCP_Blower_Speed))));\
    lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_RCP_Blower_Speed] = 1;}

/* static access macros for signal LI0_L_RCP_Lock_Status */
#define l_bool_rd_LI0_L_RCP_Lock_Status() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_Lock_Status], \
   	LIN_BIT_OFFSET_LI0_L_RCP_Lock_Status))
#define l_bool_wr_LI0_L_RCP_Lock_Status(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_Lock_Status], \
  	LIN_BIT_OFFSET_LI0_L_RCP_Lock_Status)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_Lock_Status], \
  	LIN_BIT_OFFSET_LI0_L_RCP_Lock_Status));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_RCP_Lock_Status] = 1;}

/* static access macros for signal LI0_L_RCP_Blower_Err */
#define l_bool_rd_LI0_L_RCP_Blower_Err() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_Blower_Err], \
   	LIN_BIT_OFFSET_LI0_L_RCP_Blower_Err))
#define l_bool_wr_LI0_L_RCP_Blower_Err(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_Blower_Err], \
  	LIN_BIT_OFFSET_LI0_L_RCP_Blower_Err)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_Blower_Err], \
  	LIN_BIT_OFFSET_LI0_L_RCP_Blower_Err));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_RCP_Blower_Err] = 1;}

/* static access macros for signal LI0_L_RCP_Error */
#define l_bool_rd_LI0_L_RCP_Error() \
   	(LIN_TEST_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_Error], \
   	LIN_BIT_OFFSET_LI0_L_RCP_Error))
#define l_bool_wr_LI0_L_RCP_Error(A) \
	{(A) ? \
  	(LIN_SET_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_Error], \
  	LIN_BIT_OFFSET_LI0_L_RCP_Error)):\
  	(LIN_CLEAR_BIT(lin_pFrameBuf[LIN_BYTE_OFFSET_LI0_L_RCP_Error], \
  	LIN_BIT_OFFSET_LI0_L_RCP_Error));\
  	lin_frame_flag_tbl[LIN_FLAG_UPDATE_BYTE_OFFSET_LI0_L_RCP_Error] = 1;}



/* Signal flag APIs */


#define l_flg_tst_LI0_L_AC_Control_Lock_Req_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_AC_Control_Lock_Req],\
         LIN_FLAG_BIT_OFFSET_LI0_L_AC_Control_Lock_Req)
#define l_flg_clr_LI0_L_AC_Control_Lock_Req_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_AC_Control_Lock_Req],\
         LIN_FLAG_BIT_OFFSET_LI0_L_AC_Control_Lock_Req)

#define l_flg_tst_LI0_L_AC_OnOff_Req_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_AC_OnOff_Req],\
         LIN_FLAG_BIT_OFFSET_LI0_L_AC_OnOff_Req)
#define l_flg_clr_LI0_L_AC_OnOff_Req_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_AC_OnOff_Req],\
         LIN_FLAG_BIT_OFFSET_LI0_L_AC_OnOff_Req)

#define l_flg_tst_LI0_L_RCP_OverVoltage_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_OverVoltage],\
         LIN_FLAG_BIT_OFFSET_LI0_L_RCP_OverVoltage)
#define l_flg_clr_LI0_L_RCP_OverVoltage_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_OverVoltage],\
         LIN_FLAG_BIT_OFFSET_LI0_L_RCP_OverVoltage)

#define l_flg_tst_LI0_L_RCP_UnderVoltage_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_UnderVoltage],\
         LIN_FLAG_BIT_OFFSET_LI0_L_RCP_UnderVoltage)
#define l_flg_clr_LI0_L_RCP_UnderVoltage_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_UnderVoltage],\
         LIN_FLAG_BIT_OFFSET_LI0_L_RCP_UnderVoltage)

#define l_flg_tst_LI0_L_RCP_Blower_Speed_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_Blower_Speed],\
         LIN_FLAG_BIT_OFFSET_LI0_L_RCP_Blower_Speed)
#define l_flg_clr_LI0_L_RCP_Blower_Speed_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_Blower_Speed],\
         LIN_FLAG_BIT_OFFSET_LI0_L_RCP_Blower_Speed)

#define l_flg_tst_LI0_L_RCP_Lock_Status_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_Lock_Status],\
         LIN_FLAG_BIT_OFFSET_LI0_L_RCP_Lock_Status)
#define l_flg_clr_LI0_L_RCP_Lock_Status_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_Lock_Status],\
         LIN_FLAG_BIT_OFFSET_LI0_L_RCP_Lock_Status)

#define l_flg_tst_LI0_L_RCP_Blower_Err_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_Blower_Err],\
         LIN_FLAG_BIT_OFFSET_LI0_L_RCP_Blower_Err)
#define l_flg_clr_LI0_L_RCP_Blower_Err_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_Blower_Err],\
         LIN_FLAG_BIT_OFFSET_LI0_L_RCP_Blower_Err)

#define l_flg_tst_LI0_L_RCP_Error_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_L_RCP_Error)
#define l_flg_clr_LI0_L_RCP_Error_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_L_RCP_Error],\
         LIN_FLAG_BIT_OFFSET_LI0_L_RCP_Error)



/* Frame flag APIs */

#define l_flg_tst_LI0_AC_1_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_AC_1],\
         LIN_FLAG_BIT_OFFSET_LI0_AC_1)
#define l_flg_clr_LI0_AC_1_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_AC_1],\
         LIN_FLAG_BIT_OFFSET_LI0_AC_1)

#define l_flg_tst_LI0_RCP_1_flag() \
         LIN_TEST_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RCP_1],\
         LIN_FLAG_BIT_OFFSET_LI0_RCP_1)
#define l_flg_clr_LI0_RCP_1_flag() \
         LIN_CLEAR_BIT(lin_flag_handle_tbl[LIN_FLAG_BYTE_OFFSET_LI0_RCP_1],\
         LIN_FLAG_BIT_OFFSET_LI0_RCP_1)



/* INTERFACE MANAGEMENT */

#define l_ifc_init_LI0() l_ifc_init(LI0)



#define l_ifc_wake_up_LI0() l_ifc_wake_up(LI0)



#define l_ifc_rx_LI0() l_ifc_rx(LI0)



#define l_ifc_tx_LI0() l_ifc_tx(LI0)



#define l_ifc_aux_LI0() l_ifc_aux(LI0)



#define l_ifc_read_status_LI0() l_ifc_read_status(LI0)


#endif    /* _LIN_CFG_H_ */