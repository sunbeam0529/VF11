/*
 * CPU.h
 *
 *  Created on: Oct 4, 2016
 *      Author: Administrator
 */

#ifndef CPU_H_
#define CPU_H_

#include "derivative.h"
#include "AD1.h"
#include "PWM1.h"
#include "PWM2.h"
#include "PWM3.h"
#include <hidef.h>

void CLK_CONFIG(void);
void Peripheral_Init(void);
void Watch_Dog_init(void);
void Feed_Dog(void);

#endif /* CPU_H_ */
