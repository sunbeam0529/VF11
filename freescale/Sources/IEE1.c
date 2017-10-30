#include "IEE1.h"

/* Internal type for addressing of the EEPROM. */
typedef const  word * IEE1_TAddress_;  /* Type of address to the EEPROM */

#pragma DATA_SEG IEE1_DATA             /* Select data segment "IEE1_DATA" */
#pragma CODE_SEG IEE1_CODE

/*lint -save  -e923 -e926 -e927 -e928 -e929 Disable MISRA rule (11.3,11.4) checking. */

static word BackupArray[0x02];         /* Array for backup data from erased sector */

/*---------------------------USER CODE---------------------------*/ 
//关于数据的初始化，当读取的第1个数据为0xAA，表示这个区擦除次数以上限
//128个字节，一次为8个字节，也就是说循环次数为16次，分为16个区

l_u32 EEP_SAVE_count=0;    //EEPROM存储的次数  
byte Array_save[8]={0};    //EEPROM存储的数组数据
byte OFFSET_Save_Address=0;//值为0-15，表示16个区

//读取偏置地址
void Function_OFFSET_Save_Address_read(void)
{
	byte EEP_OFFSET_i=0;
	byte EEP_OFFSET_state=0xAA;
	for(EEP_OFFSET_i=0;EEP_OFFSET_i<16;EEP_OFFSET_i++)
	{
		IEE1_GetByte((IEE1_TAddress)(EEP_SAVE_ADDRESS_start+EEP_OFFSET_i*8),&EEP_OFFSET_state);
		if(EEP_OFFSET_state != 0xAA)
		{
			OFFSET_Save_Address=EEP_OFFSET_i;
			break;
		}
	}
}

//读取烧写次数函数
void Function_EEP_SAVE_count_read(void)
{
	byte EEP_SAVE_count_p1,EEP_SAVE_count_p2,EEP_SAVE_count_p3;
	IEE1_GetByte((IEE1_TAddress)(EEP_SAVE_ADDRESS_start+5+OFFSET_Save_Address*8),&EEP_SAVE_count_p1);
	IEE1_GetByte((IEE1_TAddress)(EEP_SAVE_ADDRESS_start+6+OFFSET_Save_Address*8),&EEP_SAVE_count_p2);
	IEE1_GetByte((IEE1_TAddress)(EEP_SAVE_ADDRESS_start+7+OFFSET_Save_Address*8),&EEP_SAVE_count_p3);
	EEP_SAVE_count=(l_u32)((EEP_SAVE_count_p1&0x0f)<<16)|(EEP_SAVE_count_p2<<8)|EEP_SAVE_count_p3;
}


//5个字节的数组，1个24位的数据,也就是说是八个字节的数组的数据
//当需要存储数据的时候，将数据放入数组，调用此函数，就能保存
void Function_array_save(void)
{
	byte i=0;
	EEP_SAVE_count++;
	if(EEP_SAVE_count>EEP_SAVE_count_max)
	{		
		IEE1_SetByte((IEE1_TAddress)(EEP_SAVE_ADDRESS_start+OFFSET_Save_Address*8),0xAA);
		OFFSET_Save_Address++;	
		EEP_SAVE_count=0;//次数清零
		if(OFFSET_Save_Address>15)//最后一个区满了，重新置为0xFF
		{
			OFFSET_Save_Address=0;
			Function_array_init_save();
		}
	}
	Array_save[5]=EEP_SAVE_count>>16;      //EEP_SAVE_count高八位
	Array_save[6]=EEP_SAVE_count>>8;
	Array_save[7]=EEP_SAVE_count;  
	for(i=1;i<8;i++)//第一个数据为标志
	{
		IEE1_SetByte((IEE1_TAddress)(EEP_SAVE_ADDRESS_start+OFFSET_Save_Address*8+i),Array_save[i]);
	}
}

//当16个区都满了，需要进行初始化
void Function_array_init_save(void)
{
	byte i=0;
	for(i=0;i<16;i++)
	{
		IEE1_SetByte((IEE1_TAddress)(EEP_SAVE_ADDRESS_start+i*8),0xFF);
	}
}


/*
** ===================================================================
**     Method      :  BackupSector (component IntEEPROM)
**
**     Description :
**         The method backups the content of a sector being erased.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void BackupSector(IEE1_TAddress_ Addr, word From, word To)
{
  word i;

  for (i = From; i < To; i = i + 2U) {
    BackupArray[i/2U] = *(word *) (Addr + (i/2U)); /* Save one sector to RAM */
  }
}

/*
** ===================================================================
**     Method      :  WriteBlock (component IntEEPROM)
**
**     Description :
**         The method writes the block of data to EEPROM memory.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static byte WriteBlock(IEE1_TAddress Addr, word From, word To, const word* Data)
{
  byte err = 0U;
  word i;
  byte j;
  dword PhraseAddr;

  if(From == To) {
    return ERR_OK;
  }
  i = From;
  PhraseAddr = (dword)Addr;
  while(i < To) {
  /* FSTAT: ACCERR=1,FPVIOL=1 */
    FSTAT = 0x30U;                     /* Clear error flags */
    FCCOBIX = 5U;                      /* Five bytes will be loaded to FCCOBn registers */
    FCCOB0HI = 0x11U;                  /* Program D-Flash command */
    FCCOB0LO = (byte)(PhraseAddr >> 16U); /* High address word */
    FCCOB1 = (word)PhraseAddr;         /* Low address word */
    for(j = 0U; j < 4U; j++) {
      *((volatile word*)&FCCOB2 + j) = *((const word *)(Data + (i/2U))); /* Load new data */
      i += 2U;
      if(i >= To) {
        FCCOBIX = j + 2U;              /* Correct number of bytes written to FCCOBn*/
        break;
      }
    }
    FSTAT = 0x80U;                     /* Clear flag command buffer empty */
    while (FSTAT_CCIF == 0U) {}        /* Wait to command complete */
    if ((FSTAT & 0x30U) != 0U) {       /* Is protection violation or acces error detected ? */
      return ERR_NOTAVAIL;             /* If yes then error */
    }
    if (FSTAT_MGSTAT) {                /* Was attempt to write data to the given address errorneous? */
      err = 1U;                        /* If yes then mark an error */
    }
    PhraseAddr += 8U;
  }
  if(err != 0U) {
    return ERR_VALUE;                  /* If yes then error */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  EraseSectorInternal (component IntEEPROM)
**
**     Description :
**         The method erase a specific sector.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static byte EraseSectorInternal(IEE1_TAddress Addr)
{
  if (FSTAT_CCIF == 0U) {              /* Is command complete ? */
    return ERR_BUSY;                   /* If yes then error */
  }
  /* FSTAT: ACCERR=1,FPVIOL=1 */
  FSTAT = 0x30U;                       /* Clear error flags */
  FCCOBIX = 1U;                        /* Two FCCOBn registers will be loaded */
  FCCOB0HI = 0x12U;                    /* Erase D-Flash sector command */
  FCCOB0LO = (byte)(((dword)Addr) >> 16); /* High address word */
  FCCOB1 = (word)(((dword)Addr) & 0xFFFFFFFEUL); /* Low address word aligned to word*/
  FSTAT = 0x80U;                       /* Clear flag command buffer empty */
  while (FSTAT_CCIF == 0U) {}          /* Wait to command complete */
  if ((FSTAT & 0x23U) != 0U) {         /* Is access error or other error detected ? */
    return ERR_NOTAVAIL;               /* If yes then error */
  }
  return ERR_OK;                       /* OK */
}
/*
** ===================================================================
**     Method      :  WriteWord (component IntEEPROM)
**
**     Description :
**         The method writes the word data to EEPROM memory.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static byte WriteWord(IEE1_TAddress AddrRow,word Data16)
{
  if (FSTAT_CCIF == 0U) {              /* Is previous command in process ? */
    return ERR_BUSY;                   /* If yes then error */
  }
  /* FSTAT: ACCERR=1,FPVIOL=1 */
  FSTAT = 0x30U;                       /* Clear error flags */
  FCCOBIX = 2U;                        /* Three FCCOBn registers will be loaded */
  FCCOB0HI = 0x11U;                    /* Program D-Flash command */
  FCCOB0LO = (byte)(((dword)AddrRow) >> 16); /* High address word */
  FCCOB1 = (word)((dword)AddrRow);     /* Low address word */
  FCCOB2 = Data16;                     /* Load new data */
  FSTAT = 0x80U;                       /* Clear flag command complete */
  if ((FSTAT & 0x30U) != 0U) {         /* Is protection violation or acces error detected ? */
    return ERR_NOTAVAIL;               /* If yes then error */
  }
  while (!FSTAT_CCIF) {}               /* Wait for command completition */
  if (FSTAT_MGSTAT) {                  /* Was attempt to write data to the given address errorneous? */
    return ERR_VALUE;                  /* If yes then error */
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  IEE1_SetByte (component IntEEPROM)
**     Description :
**         This method writes a given byte to a specified address in
**         EEPROM. The method also sets address pointer for <SetActByte>
**         and <GetActByte> methods (applicable only if these methods
**         are enabled). The pointer is set to address passed as the
**         parameter.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Addr            - Address to EEPROM
**         Data            - Data to write
**     Returns     :
**         ---             - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_SPEED - the component does not work
**                           in the active speed mode 
**                           - ERR_BUSY - device is busy 
**                           - ERR_VALUE - verification of written data
**                           failed (read value does not match with
**                           written value) 
**                           - ERR_NOTAVAIL - other device-specific
**                           error 
**                           - ERR_RANGE - parameter Addr is out of range
** ===================================================================
*/
byte IEE1_SetByte(IEE1_TAddress Addr,byte Data)
{
  byte err;
  word Data16;
  IEE1_TAddress SecAddr;               /* EEPROM Sector address */

  if(((dword)Addr < (dword)IEE1_AREA_START) || ((dword)Addr > (dword)IEE1_AREA_END)) { /* Is given address out of EEPROM area array ? */
    return ERR_RANGE;                  /* If yes then error */
  }
  if(!FSTAT_CCIF) {                    /* Is reading from EEPROM possible? */
    return ERR_BUSY;                   /* If no then error */
  }
  SecAddr = (IEE1_TAddress)((dword)Addr & 0x00FFFFFEUL); /* Aligned word address */
  if (*((word *)(SecAddr)) == 0xFFFFU) { /* Is the word erased? */
    if (((dword)Addr) & 1U) {          /* Not Aligned word ? */
      return(WriteWord(SecAddr, ((*SecAddr) & 0xFF00U) | Data));
    } else {
      return(WriteWord(Addr, ((word)Data << 8) | (*(((byte *)Addr) + 1U)))); /* Aligned word ? */
    }
  } else {                             /* Is given address non-erased ? */
    SecAddr = (IEE1_TAddress)((dword)Addr & 0x00FFFFFCUL); /* Sector Aligned address */
    BackupSector(SecAddr, 0U, 0x04U);  /* Backup sector */
    Data16 = BackupArray[(((dword)Addr) % 0x04U) / 2U]; /* Store new data to backup array*/
    if (((dword)Addr) & 1U) {          /* Not Aligned word ? */
      Data16 = (Data16 & 0xFF00U) | Data;
    } else {
      Data16 = ((word)Data << 8) | (Data16 & 0xFFU);
    }
    BackupArray[(((dword)Addr) % 0x04U) / 2U] = Data16; /* Write new data to saved sector */
    err = EraseSectorInternal(Addr);   /* Erase sector */
    if(err != 0U) {
      return(err);                     /* Return error code if previous operation finished not correctly */
    }
    err = WriteBlock(SecAddr, 0U, 0x04U,BackupArray); /* Restore sector */
    return(err);
  }
}

/*
** ===================================================================
**     Method      :  IEE1_GetByte (component IntEEPROM)
**     Description :
**         This method reads a byte from a specified EEPROM address.
**         The method also sets address pointer for <SetActByte> and
**         <GetActByte> methods (applicable only if these methods are
**         enabled). The pointer is set to address passed as the
**         parameter.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Addr            - EEPROM Address
**       * Data            - A pointer to the returned 8-bit data
**     Returns     :
**         ---             - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_BUSY - device is busy 
**                           - ERR_RANGE - parameter Addr is out of range
** ===================================================================
*/
byte IEE1_GetByte(IEE1_TAddress Addr,byte *Data)
{
  if(((dword)Addr < (dword)IEE1_AREA_START) || ((dword)Addr > (dword)IEE1_AREA_END)) { /* Is given address out of EEPROM area array ? */
    return ERR_RANGE;                  /* If yes then error */
  }
  if(!FSTAT_CCIF) {                    /* Is reading from EEPROM possible? */
    return ERR_BUSY;                   /* If no then error */
  }
  *Data = *((byte *)Addr);
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  IEE1_Init (component IntEEPROM)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void IEE1_Init(void)
{
  FCLKDIV = 0x07U;                     /* Set up Clock Divider Register */
}

/*lint -restore Enable MISRA rule (11.3,11.4) checking. */

/* END IEE1. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS12Z series of microcontrollers.
**
** ###################################################################
*/
