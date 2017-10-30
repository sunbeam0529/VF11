/*
 * CPU.c
 *
 *  Created on: Oct 4, 2016
 *      Author: Administrator
 */

#include "CPU.h"

//bus时钟为8M，内部高速时钟为16M，程序运行为16M
void CLK_CONFIG(void)
{
	/*** !!! Here you can place your own code using property "User code before PE initialization" on the build options tab of the CPU compoennt. !!! ***/
	
	/* ### MC9S12ZVL32_48 "Cpu" init code ... */
	/*  PE initialization code after reset */
	/* IVBR: IVB_ADDR=0x7FFF,??=0 */
	setReg16(IVBR, 0xFFFEU);              
	/* ECLKCTL: NECLK=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
	setReg8(ECLKCTL, 0x80U);              
	/*  System clock initialization */
	/* CPMUPROT: ??=0,??=0,??=1,??=0,??=0,??=1,??=1,PROT=0 */
	setReg8(CPMUPROT, 0x26U);            /* Disable protection of clock configuration registers */ 
	/* CPMUCLKS: PSTP=0 */
	clrReg8Bits(CPMUCLKS, 0x40U);         
	/* CPMUCLKS: PLLSEL=1 */
	setReg8Bits(CPMUCLKS, 0x80U);        /* Enable the PLL to allow write to divider registers */ 
	/* CPMUPOSTDIV: ??=0,??=0,??=0,POSTDIV4=0,POSTDIV3=0,POSTDIV2=0,POSTDIV1=0,POSTDIV0=1 */
	setReg8(CPMUPOSTDIV, 0x01U);         /* Set the post divider register */ 
	/* Whenever changing PLL reference clock (REFCLK) frequency to a higher value
	it is recommended to write CPMUSYNR = 0x00 in order to stay within specified
	maximum frequency of the MCU */
	/* CPMUSYNR: VCOFRQ1=0,VCOFRQ0=0,SYNDIV5=0,SYNDIV4=0,SYNDIV3=0,SYNDIV2=0,SYNDIV1=0,SYNDIV0=0 */
	setReg8(CPMUSYNR, 0x00U);            /* Set the multiplier register */ 
	/* CPMUPLL: ??=0,??=0,FM1=0,FM0=0,??=0,??=0,??=0,??=0 */
	setReg8(CPMUPLL, 0x00U);             /* Set the PLL frequency modulation */ 
	/* CPMUSYNR: VCOFRQ1=0,VCOFRQ0=0,SYNDIV5=0,SYNDIV4=0,SYNDIV3=1,SYNDIV2=1,SYNDIV1=1,SYNDIV0=1 */
	setReg8(CPMUSYNR, 0x0FU);            /* Set the multiplier register */ 
	while(CPMUIFLG_LOCK == 0U) {         /* Wait until the PLL is within the desired tolerance of the target frequency */
	}
	/* CPMUPROT: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,PROT=0 */
	setReg8(CPMUPROT, 0x00U);            /* Enable protection of clock configuration registers */ 
	/* CPMUCOP: RSBCK=0,WRTMASK=1 */
	clrSetReg8Bits(CPMUCOP, 0x40U, 0x20U); 
	/* CPMUHTCTL: ??=0,??=0,VSEL=0,??=0,HTE=0,HTDS=0,HTIE=0,HTIF=0 */
	setReg8(CPMUHTCTL, 0x00U);            
	/* CPMUVREGCTL: ??=0,??=0,??=0,??=0,??=0,??=0,EXTXON=0,INTXON=1 */
	setReg8(CPMUVREGCTL, 0x01U);          
	/*** End of PE initialization code after reset ***/
}

void Peripheral_Init(void)
{
//-----------Int. priority init-------	
	setReg8(INT_CFADDR, 0x28U);           
	setReg8(INT_CFDATA3, 0x04U);         /*  0x2B  0x00FFFEAC   4   no   ivVtim1ch0 */
//	setReg8(INT_CFADDR, 0x48U);           
//  setReg8(INT_CFDATA1, 0x04U);         /*  0x49  0x00FFFF24   4   no   ivVports */
//------------Timer1 init--------	
	/* TIM1TSCR1: TEN=0,TSWAI=0,TSFRZ=0,TFFCA=0,PRNT=1,??=0,??=0,??=0 */
	setReg8(TIM1TSCR1, 0x08U);            
	/* TIM1OCPD: OCPD0=1 */
	setReg8Bits(TIM1OCPD, 0x01U);         
	/* TIM1TIOS: IOS0=1 */
	setReg8Bits(TIM1TIOS, 0x01U);         
	/* TIM1TCTL2: OM0=0,OL0=0 */
	clrReg8Bits(TIM1TCTL2, 0x03U);        
	/* TIM1TTOV: TOV0=0 */
	clrReg8Bits(TIM1TTOV, 0x01U);         
	/* TIM1TSCR2: TOI=0 */
	clrReg8Bits(TIM1TSCR2, 0x80U);        
	/* TIM1TFLG1: ??=1,??=1,??=1,??=1,??=1,??=1,C1F=1,C0F=1 */
	setReg8(TIM1TFLG1, 0xFFU);            
	/* TIM1TIE: C0I=1 */
	setReg8Bits(TIM1TIE, 0x01U);          
	/* TIM1PTPSR: PTPS7=0,PTPS6=0,PTPS5=0,PTPS4=0,PTPS3=0,PTPS2=0,PTPS1=0,PTPS0=0 */
	setReg8(TIM1PTPSR, 0x00U);	
//-----------IO PORT init-------------------	  
	/* PTJ: PTJ1=0,PTJ0=0 */
	clrReg8Bits(PTJ, 0x03U);              
	/* PPSJ: PPSJ1=0,PPSJ0=0 */
	clrReg8Bits(PPSJ, 0x03U);             
	/* WOMJ: WOMJ1=1,WOMJ0=1 */
	setReg8Bits(WOMJ, 0x03U);             
	/* PERJ: PERJ1=1,PERJ0=1 */
	setReg8Bits(PERJ, 0x03U);             
	/* DDRJ: DDRJ1=1,DDRJ0=1 */
	setReg8Bits(DDRJ, 0x03U); 
	/* PIES: PIES3=0,PIES2=0,PIES1=0,PIES0=0 */
	clrReg8Bits(PIES, 0x0FU);             
	/* PTS: PTS3=0,PTS2=0,PTS1=0,PTS0=0 */
	clrReg8Bits(PTS, 0x0FU);              
	/* WOMS: WOMS3=0,WOMS2=0,WOMS1=0,WOMS0=0 */
	clrReg8Bits(WOMS, 0x0FU);             
	/* DDRS: DDRS3=1,DDRS2=1,DDRS1=1,DDRS0=1 */
	setReg8Bits(DDRS, 0x0FU);             
	/* PIEP: PIEP4=0,PIEP2=0,PIEP0=0 */
	clrReg8Bits(PIEP, 0x15U);             
	/* PTP: PTP5=0,PTP4=0,PTP2=0,PTP1=0,PTP0=0 */
	clrReg8Bits(PTP, 0x37U);              
	/* PERP: PERP4=0,PERP2=0,PERP0=0 */
	clrReg8Bits(PERP, 0x15U);             
	/* DDRP: DDRP5=1,DDRP4=1,DDRP2=1,DDRP1=1,DDRP0=1 */
	setReg8Bits(DDRP, 0x37U);             
	/* PTT: PTT7=0,PTT3=0,PTT1=0,PTT0=0 */
	clrReg8Bits(PTT, 0x8BU);              
	/* PERT: PERT7=0,PERT6=0,PERT3=0,PERT1=0 */
	clrReg8Bits(PERT, 0xCAU);             
	/* DDRT: DDRT7=1,DDRT6=0,DDRT3=1,DDRT1=1,DDRT0=1 */
	clrSetReg8Bits(DDRT, 0x40U, 0x8BU);		

//-----------PWM init---------
	/* PWME: PWME7=0,PWME6=0,PWME5=0,PWME4=0,PWME3=0,PWME2=0,PWME1=0,PWME0=0 */
	setReg8(PWME, 0x00U);                 
	/* MODRR1: PWM5RR=0,PWM2RR=1 */
	clrSetReg8Bits(MODRR1, 0x20U, 0x04U); 
	/* PWMCTL: CON45=0,CON23=0,CON01=0,PSWAI=0,PFRZ=0 */
	clrReg8Bits(PWMCTL, 0x7CU);           
	/* PWMCAE: CAE5=0,CAE2=0,CAE1=0 */
	clrReg8Bits(PWMCAE, 0x26U);           
	/* PWMPOL: PPOL5=0,PPOL2=0,PPOL1=0 */
	//clrReg8Bits(PWMPOL, 0x26U); 
	setReg8Bits(PWMPOL, 0x26U);//改变极性  
	
//------------
	/* CPMUINT: LOCKIE=0,OSCIE=0 */
	clrReg8Bits(CPMUINT, 0x12U);          
	/* CPMULVCTL: LVIE=0 */
	clrReg8Bits(CPMULVCTL, 0x02U);        
	/* ECCIE: SBEEIE=0 */
	clrReg8Bits(ECCIE, 0x01U);            
	/* ECCDCMD: ECCDRR=0 */
	clrReg8Bits(ECCDCMD, 0x80U);          
	/* RDRP: RDRP7=0,RDRP5=0,RDRP3=0,RDRP1=0 */
	clrReg8Bits(RDRP, 0xAAU);             
	/* IRQCR: IRQEN=0 */
	clrReg8Bits(IRQCR, 0x40U);
//-------------
	/* TIM1TC0: BIT=0x1F40 */
	setReg16(TIM1TC0, 0x1F40U);          /* Store given value to the compare register */ 
	/* ### Programable pulse generation "PWM1" init code ... */
	PWM1_Init();
	/* ### Programable pulse generation "PWM2" init code ... */
	PWM2_Init();
	/* ### Programable pulse generation "PWM3" init code ... */
	PWM3_Init();
	/* ### ADC "AD1" init code ... */
	AD1_Init();
	/* ### External interrupt "EInt1" init code ... */
	//PIFS = 0x01U;                         /* Clear flag */
	//PIES_PIES0 = 1U;                     /* Enable interrupt */
	/* Common peripheral initialization - ENABLE */
	/* TIM1TSCR1: TEN=1,TSWAI=0,TSFRZ=0,TFFCA=0,PRNT=1,??=0,??=0,??=0 */
	setReg8(TIM1TSCR1, 0x88U);
	EnableInterrupts;
}

//COP stops in stop mode
void Watch_Dog_init(void)
{
	/* ###  WatchDog "WDog1" init code ... */
	/* CPMUPROT: ??=0,??=0,??=1,??=0,??=0,??=1,??=1,PROT=0 */
	setReg8(CPMUPROT, 0x26U);            /* Disable protection of clock-source register */ 
	/* CPMUCLKS: CSAD=1,PCE=0,COPOSCSEL0=0 */
	clrSetReg8Bits(CPMUCLKS, 0x05U, 0x20U); 
	/* CPMUPROT: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,PROT=0 */
	setReg8(CPMUPROT, 0x00U);            /* Re-Enable protection of clock-source register */ 
	/* CPMURFLG: COPRF=0 */
	setReg8(CPMURFLG, 0x00U);            /* Clear COP reset flag */ 
	/* CPMUCOP: WCOP=0,CR2=1,CR1=0,CR0=0 */
	clrSetReg8Bits(CPMUCOP, 0x83U, 0x04U); 
}

//clear the count
void Feed_Dog(void)
{
	CPMUARMCOP = 0x55U;
	CPMUARMCOP = 0xAAU;
}

