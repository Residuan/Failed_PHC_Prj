#include "a4988.h"

void A4988Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	
	A4988Speed(1);
	GPIO_ResetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_15);
}

void A4988Speed(u16 speed)
{
	switch(speed)
	{
		case 1:GPIO_ResetBits(GPIOB, GPIO_Pin_0);GPIO_ResetBits(GPIOB, GPIO_Pin_1);GPIO_ResetBits(GPIOB, GPIO_Pin_10);
					 GPIO_ResetBits(GPIOB, GPIO_Pin_14);GPIO_ResetBits(GPIOB, GPIO_Pin_13);GPIO_ResetBits(GPIOB, GPIO_Pin_12);break;
		
		case 2:GPIO_SetBits(GPIOB, GPIO_Pin_0);GPIO_ResetBits(GPIOB, GPIO_Pin_1);GPIO_ResetBits(GPIOB, GPIO_Pin_10);
					 GPIO_SetBits(GPIOB, GPIO_Pin_14);GPIO_ResetBits(GPIOB, GPIO_Pin_13);GPIO_ResetBits(GPIOB, GPIO_Pin_12);break;
		
		case 4:GPIO_ResetBits(GPIOB, GPIO_Pin_0);GPIO_SetBits(GPIOB, GPIO_Pin_1);GPIO_ResetBits(GPIOB, GPIO_Pin_10);
					 GPIO_ResetBits(GPIOB, GPIO_Pin_14);GPIO_SetBits(GPIOB, GPIO_Pin_13);GPIO_ResetBits(GPIOB, GPIO_Pin_12);break;
		
		case 8:GPIO_SetBits(GPIOB, GPIO_Pin_0);GPIO_SetBits(GPIOB, GPIO_Pin_1);GPIO_ResetBits(GPIOB, GPIO_Pin_10);
					 GPIO_SetBits(GPIOB, GPIO_Pin_14);GPIO_SetBits(GPIOB, GPIO_Pin_13);GPIO_ResetBits(GPIOB, GPIO_Pin_12);break;
		
		case 16:GPIO_SetBits(GPIOB, GPIO_Pin_0);GPIO_SetBits(GPIOB, GPIO_Pin_1);GPIO_SetBits(GPIOB, GPIO_Pin_10);
						GPIO_SetBits(GPIOB, GPIO_Pin_14);GPIO_SetBits(GPIOB, GPIO_Pin_13);GPIO_SetBits(GPIOB, GPIO_Pin_12);break;
		
		default:break;
	}
}

/*void A4988FandR( FandR)
{
	switch(FandR)
	{
		case 0:GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		printf("正转\n");
		break;
		case 1:GPIO_SetBits(GPIOB, GPIO_Pin_9);
		printf("反转\n");
		break;
		default:printf("Not FandR!%8d\n", FandR);break;
	}

}*/

void A4988Control(u16 ospeed, u8 ForR, u32 step)
{
	/*if(fabs((int)step) == 0) GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_15);
	else GPIO_ResetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_15);*/
	//int i;
	//GPIO_ResetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_15);
	A4988Speed(ospeed);

	switch(ForR)
	{
		case 0:GPIO_ResetBits(GPIOA, GPIO_Pin_4); GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		printf("正转\n");
		break;
		case 1:GPIO_SetBits(GPIOA, GPIO_Pin_4);GPIO_SetBits(GPIOB, GPIO_Pin_5);
		printf("反转\n");
		break;
		default:printf("Not FandR!%8d\n", ForR);break;
	}

	//TIM4->CCR1 = step;
	
	/*for(i = 1; i <= step; i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_8);
		GPIO_SetBits(GPIOB, GPIO_Pin_9);
		DelayUs(500);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		DelayUs(500);
	}*/
	//GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_15);
}


int TurnControl(float pid)
{
	if(pid < 0)
	{
		return 0;
	}
	else return 1;

}









