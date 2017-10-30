#include "EInt1.h"


//100usÑÓ³Ùº¯Êý
void Cpu_Delay100US(word us100)
{
  asm {
    loop:
    LD D6,#0x0071                      /* (1_5 c: 240 ns) number of iterations */
    label0:
    DEC D6                             /* (1 c: 160 ns) decrement d1 */
    BNE label0                         /* (4 c: 640 ns) repeat 113x */
    NOP                                /* (1 c: 160 ns) wait for 1 c */
    NOP                                /* (1 c: 160 ns) wait for 1 c */
    NOP                                /* (1 c: 160 ns) wait for 1 c */
    /* 100 us delay block end */
    DBNE D2, loop                      /* us100 parameter is passed via D register */
  };
  /*lint -restore Enable MISRA rule (1.1,14.2) checking. */
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt VectorNumber_Vports EInt1_Interrupt(void)
{                         
	PIFS = 0x01U;                         /* Clear flag */
    AD1_Init();
}
#pragma CODE_SEG EInt1_CODE




