#ifndef _TIM_H
#define _TIM_H

#include "stm32f10x.h"

void TIM4_Int_Init(void);
void TIM3_Init(u16 duty);
void Clock_Start(void);
u32 Clock_End(void);

#endif


