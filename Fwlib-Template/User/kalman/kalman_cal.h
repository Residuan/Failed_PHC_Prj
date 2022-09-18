#ifndef __KALMAN_CAL_H
#define __KALMAN_CAL_H	 
#include "mpu6050.h"
#include "math.h"
		 				    
//���������ݼ���
void Angle_Cal(void);
void Kalman_Cal_Pitch(float acc,float gyro);
void Kalman_Cal_Roll(float acc,float gyro);
	
//���������㷨��
extern short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ���� 
extern short gyrox,gyroy,gyroz;	//������ԭʼ���� 
extern short temperature;			//�������¶�����
extern float accel_x;	        //X����ٶ�ֵ
extern float accel_y;	    	  //Y����ٶ�ֵ
extern float accel_z;	        //Z����ٶ�ֵ
extern float gyro_x;				  //X�������ǽ��ٶ�����
extern float gyro_y;          //Y�������ǽ��ٶ�����
extern float gyro_z;		 		  //Z�������ǽ��ٶ�����	

extern float pitch_raw;  		   //������pitchԭʼ����
extern float pitch_kalman; 	   //pitch�˲�������
extern float roll_raw;  		   //�����rollԭʼ����
extern float roll_kalman; 		 //roll�˲�������		
//extern float Angle_x_temp;  		//�ɼ��ٶȼ����x��б�Ƕ�
//extern float Angle_y_temp;  		//�ɼ��ٶȼ����y��б�Ƕ�
//extern float Angle_X_Final; 		//X������б�Ƕ�
//extern float Angle_Y_Final; 		//Y������б�Ƕ�

extern u16 temp;        //�¶�
extern u16 gx,gy,gz;    //������ٶ�
extern u16 ax,ay,az;    //������ٶ�


#endif
