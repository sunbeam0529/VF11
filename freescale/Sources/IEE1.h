#ifndef __IEE1
#define __IEE1

#include "derivative.h"
#include "lin.h"

#ifndef __BWUserType_IEE1_TAddress
#define __BWUserType_IEE1_TAddress
  /* User type for addressing of the EEPROM. Actual type depends on the CPU family. */
  typedef  word * IEE1_TAddress;       /* Type of address to the EEPROM */
#endif

#pragma CODE_SEG IEE1_CODE


/* EEPROM area start address (in the format used by component methods). */
#define IEE1_AREA_START                 ((IEE1_TAddress)0x00100000UL)
#define IEE1_AREA_START_INT             (0x00100000UL)
/* EEPROM area last address (in the format used by component methods). */
#define IEE1_AREA_END                   ((IEE1_TAddress)0x0010007FUL)
#define IEE1_AREA_END_INT               (0x0010007FUL)
/* EEPROM area size (in bytes). */
#define IEE1_AREA_SIZE                  0x80U
/* EEPROM area sector size: minimal erasable unit (in bytes). */
#define IEE1_AREA_SECTOR_SIZE           0x04U
/* TRUE if the component setting allows clear bits of already programmed flash memory location without destruction of the value in surrounding addresses by sector erase. */
#define IEE1_ALLOW_CLEAR                (TRUE)
/* Size of programming phrase, i.e. number of bytes that must be programmed at once */
#define IEE1_PROGRAMMING_PHRASE         (0x02U)

#define EEPROMStart IEE1_AREA_START    /* [DEPRECATED] Start address of used EEPROM array */
#define EEPROMEnd IEE1_AREA_END        /* [DEPRECATED] End address of used EEPROM array */

/* Flags parameter of OnError event can contain following error values (values may be OR-ed together) */
/* Double bit fault detect */
#define IEE1_DOUBLE_FAULT               (0x02U)
/* Single bit fault detect */
#define IEE1_SINGLE_FAULT               (0x01U)

/*------------------------USER CODE------------------------------*/ 
 
#define EEP_SAVE_ADDRESS_start 0x00100000UL //EEPROM存储的开始地址
#define EEP_SAVE_ADDRESS_end   0x0010007FUL //EEPROM存储的终止地址
#define EEP_SAVE_count_max  100000         //EEPROM存储的最大次数，算上归零的那次，实际为EEP_SAVE_count_max+1次
  

extern l_u32 EEP_SAVE_count;                //EEPROM存储的次数                                   
extern byte Array_save[8];    				//EEPROM存储的数组数据
extern byte OFFSET_Save_Address;//EEP_SAVE_count的最高四位，也就是20-23位，正好最大值为16，初始化的时候要读出

byte IEE1_SetByte(IEE1_TAddress Addr,byte Data);
byte IEE1_GetByte(IEE1_TAddress Addr,byte *Data);
void IEE1_Init(void);
void Function_array_init_save(void);
void Function_OFFSET_Save_Address_read(void);
void Function_EEP_SAVE_count_read(void);
void Function_array_save(void);



#pragma CODE_SEG DEFAULT


#endif
