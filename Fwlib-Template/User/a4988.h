#ifndef _A4988_H
#define _A4988_H
#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "pid.h"
#include <math.h>

void A4988Init(void);
void A4988Speed(u16 speed);
//void A4988FandR(u8 FandR);
void A4988Control(u16 ospeed, u8 ForR, u32 step);
int TurnControl(float pid);



#endif






