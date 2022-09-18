#include "stm32f10x.h"
#include "i2c.h"
#include "delay.h"
#include "OLED.h"
#include "usart.h"
#include "mpu6050.h"
#include "a4988.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "pid.h"
//#include "softi2c.h"
//#include "anbt_dmp_driver.h"
//#include "anbt_dmp_mpu6050.h"
//#include "anbt_i2c.h"
#include "tim.h"
#include "spi.h"


//#include "kalman_cal.h"

#define q30  1073741824.0f
#define PI 3.1415926


float pitch,roll,yaw;

short Gyro[3];
short Acc[3];

int g = 0;
int gx, gy, gz;
int ax, ay, az;

float pid;

/*****************************************************/

float ax_offset = 0, ay_offset = 0; //x,y轴的加速度偏移量
float gx_offset = 0, gy_offset = 0; //x,y轴的角速度偏移量

/*****************************************************/
void Init_ALL()
{
	
	USART_Config();
	printf("USART is Ready��\n");
	
	i2cinit();
	//SPI_OLED_Init();
	//MPU_IIC_Init();
	//I2C_Bus_Init();

	MPU6050_Init();
	DelayInit();
	//MPU_Init();
	A4988Init();
	TIM3_Init(10);//初始化后直接在PA6输出PWM信号，占空比为0
	TIM4_Int_Init();
	//OLED_Init();
	//AnBT_DMP_MPU6050_Init();
	//ANBT_I2C_Configuration();
	//OLED_Display_On();
}



int main(void)
{
	int i;
	u32 time;
	Init_ALL();
	printf("Init is Ready!\n");
	Clock_Start();
	ReadID();

	printf("Hello World!\n");
	for (i = 1; i <= 1000; i++) 
		{
			MPUReadGyro(Gyro);
			MPUReadAcc(Acc);
			ax = Acc[0];
			ay = Acc[1];
			az = Acc[2];
			gx = Gyro[0];
			gy = Gyro[1];
			gz = Gyro[2];
			ax_offset = ax_offset + ax;//计算x轴加速度的偏移总量
			ay_offset = ay_offset + ay;//计算y轴加速度的偏移总量
		}
	ax_offset = ax_offset / 1000;
	ay_offset = ay_offset / 1000;
	time = Clock_End();
	printf("Init is OK! Time: %d\n", time);
		
	//OLED_Fill(0xff);C:\Keil_v5\UV4\UV4.exe
	while(1)
		{
			//DelayMs(100);
			pitch = MPU_Get_Pitch(ax_offset);
			//roll = MPU_Get_Roll(ay_offset);
			pid = balance(pitch, gy);
			//printf("互补Pitch: %+.2f, 互补Roll: %+.2f\n", pitch, roll);
			printf("PID:%f\n", pid);
			A4988Control(8, TurnControl(pid), pid);
			
			
		}
	
}










