#include "pid.h"
#include "anbt_dmp_driver.h"
#include "anbt_dmp_mpu6050.h"
#include "delay.h"
#include "a4988.h"

float Target = 0;//Ŀ��Ƕ�
float Kp = 1;//����Pϵ��
float Ki = 1;//����Iϵ��
float Kd = 1;//΢��Dϵ��


//float P = 0;//����P
//float I = 0;//����I
//float D = 0;//΢��D

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






















