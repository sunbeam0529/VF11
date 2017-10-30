/*
 * Note: This file is recreated by the project wizard whenever the MCU is
 *       changed and should not be edited by hand
 */

/* Include the derivative-specific header file */
#ifndef _DERIVATIVE__H
#define _DERIVATIVE__H

#include <mc9s12zvl32.h>

//输出口
#define   SCL            PTJ_PTJ1
#define   SDA            PTJ_PTJ0

#define   FAN_1_LED      PTT_PTT1   
#define   FAN_2_LED      PTS_PTS0
#define   FAN_3_LED      PTT_PTT7  		
#define   FAN_4_LED      PTP_PTP0   	
#define   FAN_5_LED      PTP_PTP2   
#define   FAN_6_LED      PTP_PTP4    
#define   FAN_7_LED      PTS_PTS1 
#define   FAN_8_LED   	 PTS_PTS2          
            
#define   O_FAN_EN       PTS_PTS3   
#define   O_FAN_RLY_SIGN PTT_PTT3 

//蜂鸣器驱动
#define   O_BUZZER       PWMDTY5//PTP_PTP5
//LED光亮度
#define   O_LED_PWM      PWMDTY1//PTP_PTP1	
//风机驱动
#define   O_FAN_PWM      PWMDTY4 //PTT_PTT0



/********此处为PE_Types*************/
#define setRegBit(reg, bit)                                     (reg |= reg##_##bit##_##MASK)
#define clrRegBit(reg, bit)                                     (reg &= ~reg##_##bit##_##MASK)
#define getRegBit(reg, bit)                                     (reg & reg##_##bit##_##MASK)
#define setReg(reg, val)                                        (reg = (word)(val))
#define getReg(reg)                                             (reg)
#define setRegBits(reg, mask)                                   (reg |= (word)(mask))
#define getRegBits(reg, mask)                                   (reg & (word)(mask))
#define clrRegBits(reg, mask)                                   (reg &= (word)(~(mask)))
#define setRegBitGroup(reg, bits, val)                          (reg = (word)((reg & ~reg##_##bits##_##MASK) | ((val) << reg##_##bits##_##BITNUM)))
#define getRegBitGroup(reg, bits)                               ((reg & reg##_##bits##_##MASK) >> reg##_##bits##_##BITNUM)
#define setRegMask(reg, maskAnd, maskOr)                        (reg = (word)((getReg(reg) & ~(maskAnd)) | (maskOr)))
#define setRegBitVal(reg, bit, val)                             ((val) == 0 ? (reg &= ~reg##_##bit##_##MASK) : (reg |= reg##_##bit##_##MASK))
#define changeRegBits(reg, mask)                                (reg ^= (mask))
#define changeRegBit(reg, bit)                                  (reg ^= reg##_##bit##_##MASK)

/******************************************************************/
/* Uniform multiplatform peripheral access macros - 16 bit access */
/******************************************************************/
#define setReg16Bit(RegName, BitName)                           (RegName |= RegName##_##BitName##_##MASK)
#define clrReg16Bit(RegName, BitName)                           (RegName &= ~(word)RegName##_##BitName##_##MASK)
#define invertReg16Bit(RegName, BitName)                        (RegName ^= RegName##_##BitName##_##MASK)
#define testReg16Bit(RegName, BitName)                          (RegName & RegName##_##BitName##_##MASK)

/* Whole peripheral register access macros */
#define setReg16(RegName, val)                                  (RegName = (word)(val))
#define getReg16(RegName)                                       (RegName)

/* Bits peripheral register access macros */
#define testReg16Bits(RegName, GetMask)                         (RegName & (GetMask))
#define clrReg16Bits(RegName, ClrMask)                          (RegName &= (word)(~(word)(ClrMask)))
#define setReg16Bits(RegName, SetMask)                          (RegName |= (word)(SetMask))
#define invertReg16Bits(RegName, InvMask)                       (RegName ^= (word)(InvMask))
#define clrSetReg16Bits(RegName, ClrMask, SetMask)              (RegName = (RegName & (~(word)(ClrMask))) | (word)(SetMask))
#define seqClrSetReg16Bits(RegName, BitsMask, BitsVal)          ((RegName &= ~(~(word)(BitsVal) & (word)(BitsMask))),\
                                                                (RegName |= (word)(BitsVal) & (word)(BitsMask)) )
#define seqSetClrReg16Bits(RegName, BitsMask, BitsVal)          ((RegName |= (word)(BitsVal) & (word)(BitsMask)),\
                                                                (RegName &= ~(~(word)(BitsVal) & (word)(BitsMask))) )
#define seqResetSetReg16Bits(RegName, BitsMask, BitsVal)        ((RegName &= ~(word)(BitsMask)),\
                                                                (RegName |= (word)(BitsVal) & (word)(BitsMask)) )
#define clrReg16BitsByOne(RegName, ClrMask, BitsMask)           (RegName &= (word)(ClrMask) & (word)(BitsMask))

/* Bit group peripheral register access macros */
#define testReg16BitGroup(RegName, GroupName)                   (RegName & RegName##_##GroupName##_##MASK)
#define getReg16BitGroupVal(RegName, GroupName)                 ((RegName & RegName##_##GroupName##_##MASK) >> RegName##_##GroupName##_##BITNUM)
#define setReg16BitGroupVal(RegName, GroupName, GroupVal)       (RegName = (RegName & ~(word)RegName##_##GroupName##_##MASK) | (((word)(GroupVal)) << RegName##_##GroupName##_##BITNUM))
#define seqClrSetReg16BitGroupVal(RegName,GroupName,GroupVal)   ((RegName &= ~(~(((word)(GroupVal)) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK)),\
                                                                (RegName |= (((word)(GroupVal)) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK) )
#define seqSetClrReg16BitGroupVal(RegName,GroupName,GroupVal)   ((RegName |= (((word)(GroupVal)) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK),\
                                                                (RegName &= ~(~(((word)(GroupVal)) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK)) )
#define seqResetSetReg16BitGroupVal(RegName,GroupName,GroupVal) ((RegName &= ~(word)RegName##_##GroupName##_##MASK),\
                                                                (RegName |= (((word)(GroupVal)) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK) )

/*****************************************************************/
/* Uniform multiplatform peripheral access macros - 8 bit access */
/*****************************************************************/
#define setReg8Bit(RegName, BitName)                             (RegName |= RegName##_##BitName##_##MASK)
#define clrReg8Bit(RegName, BitName)                             (RegName &= (byte)~(byte)RegName##_##BitName##_##MASK)
#define invertReg8Bit(RegName, BitName)                          (RegName ^= RegName##_##BitName##_##MASK)
#define testReg8Bit(RegName, BitName)                            (RegName & RegName##_##BitName##_##MASK)

/* Whole peripheral register access macros */
#define setReg8(RegName, val)                                    (RegName = (byte)(val))
#define getReg8(RegName)                                         (RegName)

/* Bits peripheral register access macros */
#define testReg8Bits(RegName, GetMask)                           (RegName & (GetMask))
#define clrReg8Bits(RegName, ClrMask)                            (RegName &= (byte)(~(byte)(ClrMask)))
#define setReg8Bits(RegName, SetMask)                            (RegName |= (byte)(SetMask))
#define invertReg8Bits(RegName, InvMask)                         (RegName ^= (byte)(InvMask))
#define clrSetReg8Bits(RegName, ClrMask, SetMask)                (RegName = (RegName & ((byte)(~(byte)(ClrMask)))) | (byte)(SetMask))
#define seqClrSetReg8Bits(RegName, BitsMask, BitsVal)            ((RegName &= (byte)~((byte)~((byte)(BitsVal)) & ((byte)(BitsMask)))),\
                                                                 (RegName |= ((byte)(BitsVal)) & ((byte)(BitsMask))) )
#define seqSetClrReg8Bits(RegName, BitsMask, BitsVal)            ((RegName |= (byte)(BitsVal) & (byte)(BitsMask)),\
                                                                 (RegName &= (byte)~((byte)~((byte)(BitsVal)) & (byte)(BitsMask))) )
#define seqResetSetReg8Bits(RegName, BitsMask, BitsVal)          ((RegName &= (byte)~((byte)(BitsMask))),\
                                                                 (RegName |= (byte)(BitsVal) & (byte)(BitsMask)) )
#define clrReg8BitsByOne(RegName, ClrMask, BitsMask)             (RegName &= (byte)(ClrMask) & (byte)(BitsMask))

/* Bit group peripheral register access macros */
#define testReg8BitGroup(RegName, GroupName)                     (RegName & RegName##_##GroupName##_##MASK)
#define getReg8BitGroupVal(RegName, GroupName)                   ((RegName & RegName##_##GroupName##_##MASK) >> RegName##_##GroupName##_##BITNUM)
#define setReg8BitGroupVal(RegName, GroupName, GroupVal)         (RegName = (RegName & (byte)~(byte)RegName##_##GroupName##_##MASK) | (byte)(((byte)(GroupVal)) << RegName##_##GroupName##_##BITNUM))
#define seqClrSetReg8BitGroupVal(RegName,GroupName,GroupVal)     ((RegName &= (byte)~((byte)~(byte)(((byte)(GroupVal)) << RegName##_##GroupName##_##BITNUM) & (byte)RegName##_##GroupName##_##MASK)),\
                                                                 (RegName |= (byte)(((byte)(GroupVal)) << RegName##_##GroupName##_##BITNUM) & (byte)RegName##_##GroupName##_##MASK) )
#define seqSetClrReg8BitGroupVal(RegName,GroupName,GroupVal)     ((RegName |= (byte)(((byte)(GroupVal)) << RegName##_##GroupName##_##BITNUM) & (byte)RegName##_##GroupName##_##MASK),\
                                                                 (RegName &= (byte)~((byte)~(byte)(((byte)(GroupVal)) << RegName##_##GroupName##_##BITNUM) & (byte)RegName##_##GroupName##_##MASK)) )
#define seqResetSetReg8BitGroupVal(RegName,GroupName,GroupVal)   ((RegName &= (byte)~(byte)RegName##_##GroupName##_##MASK),\
                                                                 (RegName |= (byte)(((byte)(GroupVal)) << RegName##_##GroupName##_##BITNUM) & RegName##_##GroupName##_##MASK) )


/******此处为PE_Error的宏定义********/
#define ERR_OK           0U            /* OK */
#define ERR_SPEED        1U            /* This device does not work in the active speed mode. */
#define ERR_RANGE        2U            /* Parameter out of range. */
#define ERR_VALUE        3U            /* Parameter of incorrect value. */
#define ERR_OVERFLOW     4U            /* Timer overflow. */
#define ERR_MATH         5U            /* Overflow during evaluation. */
#define ERR_ENABLED      6U            /* Device is enabled. */
#define ERR_DISABLED     7U            /* Device is disabled. */
#define ERR_BUSY         8U            /* Device is busy. */
#define ERR_NOTAVAIL     9U            /* Requested value or method not available. */
#define ERR_RXEMPTY      10U           /* No data in receiver. */
#define ERR_TXFULL       11U           /* Transmitter is full. */
#define ERR_BUSOFF       12U           /* Bus not available. */
#define ERR_OVERRUN      13U           /* Overrun error is detected. */
#define ERR_FRAMING      14U           /* Framing error is detected. */
#define ERR_PARITY       15U           /* Parity error is detected. */
#define ERR_NOISE        16U           /* Noise error is detected. */
#define ERR_IDLE         17U           /* Idle error is detected. */
#define ERR_FAULT        18U           /* Fault error is detected. */
#define ERR_BREAK        19U           /* Break char is received during communication. */
#define ERR_CRC          20U           /* CRC error is detected. */
#define ERR_ARBITR       21U           /* A node losts arbitration. This error occurs if two nodes start transmission at the same time. */
#define ERR_PROTECT      22U           /* Protection error is detected. */
#define ERR_UNDERFLOW    23U           /* Underflow error is detected. */
#define ERR_UNDERRUN     24U           /* Underrun error is detected. */
#define ERR_COMMON       25U           /* Common error of a device. */
#define ERR_LINSYNC      26U           /* LIN synchronization error is detected. */
#define ERR_FAILED       27U           /* Requested functionality or process failed. */
#define ERR_QFULL        28U           /* Queue is full. */

#endif
