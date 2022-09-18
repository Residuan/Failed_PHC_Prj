#include "pid.h"
#include "anbt_dmp_driver.h"
#include "anbt_dmp_mpu6050.h"
#include "delay.h"
#include "a4988.h"

float Target = 0;//目标角度
float Kp = 1;//比例P系数
float Ki = 1;//积分I系数
float Kd = 1;//微分D系数


//float P = 0;//比例P
//float I = 0;//积分I
//float D = 0;//微分D

float error;
float first_value, second_value;
float count_error;
float last_error;





float balance(float Angle, float Gyro)
{
		
  float Bias, balance, ferror, lastbias;
  Bias=Angle - Target;
	
	ferror = ferror + Bias * Ki;
	
  balance=Kp * Bias + ferror + Kd * (Bias - lastbias);
	lastbias = Bias;

  //balance = Kp * Bias + Kd * Gyro;

  return balance;
}






















