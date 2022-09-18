#include "mpu6050.h"



static float rad2deg = 57.29578;
static int gx, gy;
static int ax, ay, az;
static float pitch,roll;

static float angle1, angle2;
static float ex_gyro = 0, ey_gyro = 0;
static int dt = 0;
static float ki = 0.01;


void MPU6050_Init(void)
{
  int i=0,j=0;
  for(i=0;i<1000;i++)
  {
    for(j=0;j<1000;j++)
    {
      ;
    }
  }
	WriteI2C_Byte(0x6B, 0x00);//解除休眠 
	WriteI2C_Byte(0x19, 0x07);//设置采样率
	WriteI2C_Byte(0x1A, 0x06);//
	WriteI2C_Byte(0x1C, 0x01);//加速度传感器
	WriteI2C_Byte(0x1B, 0x18);//自检和测量跨度，不自检
	WriteI2C_Byte(0x23, 0x78);
	
}
void MPUReadData(u8 reg_add,unsigned char* Read,u8 num)
{
	Read_Byte(Read,reg_add,num);
}




void MPUReadGyro(short *GyroOut)//读取角速度
{
	u8 data[6];
	MPUReadData(0x43, data, 6);
	GyroOut[0] = (data[0] << 8) | data[1];
	GyroOut[1] = (data[2] << 8) | data[3];
	GyroOut[2] = (data[4] << 8) | data[5];
	
}

void MPUReadAcc(short *AccOut)//读取加速度
{
	u8 data1[6];
	MPUReadData(0x3B, data1, 6);
	AccOut[0] = (data1[0] << 8) | data1[1];
	AccOut[1] = (data1[2] << 8) | data1[3];
	AccOut[2] = (data1[4] << 8) | data1[5];
}

u8 ReadID(void)//读取MPU6050的ID，一般为0x68
{
	
	unsigned char ID = 0;
	
  Read_Byte(&ID, 0x75, 1);
	if(ID != 0x68)
	{
		return printf("淦\nERROR ID:%d\n", ID);
	}
	else
	{
		printf("MPU6050 ID = %x\r\n",ID);
		return 1;
	}
}

float MPU_Get_Pitch(float ax_offset)//封装Pitch角的获取
{
	short Gyro[3];
	short Acc[3];
	MPUReadGyro(Gyro);
	MPUReadAcc(Acc);
	gx = Gyro[0];
	gy = Gyro[1];
	//gz = Gyro[2];
	ax = Acc[0];
	ay = Acc[1];
	az = Acc[2];
	

	angle1 = atan2((ax - ax_offset), az) * rad2deg;//互补滤波可用，但开机偏移2度
	ex_gyro = gx * dt /1000.f;
	pitch = ki * (ex_gyro + pitch) + (1 - ki) * angle1;
	return pitch;
}

float MPU_Get_Roll(float ay_offset)//封装Roll角的获取
{
	short Gyro[3];
	short Acc[3];
	MPUReadGyro(Gyro);
	MPUReadAcc(Acc);
	gx = Gyro[0];
	gy = Gyro[1];
	//gz = Gyro[2];
	ax = Acc[0];
	ay = Acc[1];
	az = Acc[2];
	
	angle2 = atan2(ay - ay_offset, az) * rad2deg;//互补滤波可用，正常使用
	ey_gyro = gy * dt /1000.f;
	roll = ki * (ey_gyro + roll) + (1 - ki) * angle2;
	return roll;
}



////#include "mpu6050.h"
////#include "delay.h"
////#include "usart.h"
////#include "anbt_i2c.h"
//////初始化MPU6050
//////返回值:0,成功
//////其他,错误代码
////u8 MPU_Init(void)
////{ 
////	u8 res; 
////	MPU_IIC_Init();//初始化IIC总线
////	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//复位MPU6050
////    DelayMs(100);
////	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//唤醒MPU6050 
////	MPU_Set_Gyro_Fsr(3);					//陀螺仪传感器,±2000dps
////	MPU_Set_Accel_Fsr(0);					//加速度传感器,±2g
////	MPU_Set_Rate(200);						//设置采样率50Hz
////	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//关闭所有中断
////	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C主模式关闭
////	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//关闭FIFO
////	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT引脚低电平有效
////	res=MPU_Read_Byte(MPU_DEVICE_ID_REG); 
////	if(res==MPU_ADDR)//器件ID正确
////	{
////		printf("MPUID:%d\n", MPU_ADDR);
////		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//设置CLKSEL,PLL X轴为参考
////		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	//加速度与陀螺仪都工作
////		MPU_Set_Rate(200);						//设置采样率为50Hz
//// 	}else return printf("淦！\n");
////	return 0;
////}
//////设置MPU6050陀螺仪传感器满量程范围
//////fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
//////返回值:0,设置成功
//////    其他,设置失败 
////u8 MPU_Set_Gyro_Fsr(u8 fsr)
////{
////	return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围  
////}
//////设置MPU6050加速度传感器满量程范围
//////fsr:0,±2g;1,±4g;2,±8g;3,±16g
//////返回值:0,设置成功
//////    其他,设置失败 
////u8 MPU_Set_Accel_Fsr(u8 fsr)
////{
////	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围  
////}
//////设置MPU6050的数字低通滤波器
//////lpf:数字低通滤波频率(Hz)
//////返回值:0,设置成功
//////    其他,设置失败 
////u8 MPU_Set_LPF(u16 lpf)
////{
////	u8 data=0;
////	if(lpf>=188)data=1;
////	else if(lpf>=98)data=2;
////	else if(lpf>=42)data=3;
////	else if(lpf>=20)data=4;
////	else if(lpf>=10)data=5;
////	else data=6; 
////	return MPU_Write_Byte(MPU_CFG_REG,data);//设置数字低通滤波器  
////}
//////设置MPU6050的采样率(假定Fs=1KHz)
//////rate:4~1000(Hz)
//////返回值:0,设置成功
//////    其他,设置失败 
////u8 MPU_Set_Rate(u16 rate)
////{
////	u8 data;
////	if(rate>1000)rate=1000;
////	if(rate<4)rate=4;
////	data=1000/rate-1;
////	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
//// 	return MPU_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
////}

//////得到温度值
//////返回值:温度值(扩大了100倍)
////short MPU_Get_Temperature(void)
////{
////    u8 buf[2]; 
////    short raw;
////	float temp;
////	MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
////    raw=((u16)buf[0]<<8)|buf[1];  
////    temp=36.53+((double)raw)/340;  
////    return temp*100;;
////}
//////得到陀螺仪值(原始值)
//////gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//////返回值:0,成功
//////    其他,错误代码
////u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
////{
////    u8 buf[6],res;  
////	res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
////	if(res==0)
////	{
////		*gx=((u16)buf[0]<<8)|buf[1];  
////		*gy=((u16)buf[2]<<8)|buf[3];  
////		*gz=((u16)buf[4]<<8)|buf[5];
////	} 	
////    return res;;
////}
//////得到加速度值(原始值)
//////gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//////返回值:0,成功
//////    其他,错误代码
////u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
////{
////    u8 buf[6],res;  
////	res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
////	if(res==0)
////	{
////		*ax=((u16)buf[0]<<8)|buf[1];  
////		*ay=((u16)buf[2]<<8)|buf[3];  
////		*az=((u16)buf[4]<<8)|buf[5];
////	} 	
////    return res;;
////}
//////IIC连续写
//////addr:器件地址 
//////reg:寄存器地址
//////len:写入长度
//////buf:数据区
//////返回值:0,正常
//////    其他,错误代码
////u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
////{
////	u8 i; 
////    MPU_IIC_Start(); 
////	MPU_IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
////	if(MPU_IIC_Wait_Ack())	//等待应答
////	{
////		MPU_IIC_Stop();		 
////		return 1;		
////	}
////    MPU_IIC_Send_Byte(reg);	//写寄存器地址
////    MPU_IIC_Wait_Ack();		//等待应答
////	for(i=0;i<len;i++)
////	{
////		MPU_IIC_Send_Byte(buf[i]);	//发送数据
////		if(MPU_IIC_Wait_Ack())		//等待ACK
////		{
////			MPU_IIC_Stop();	 
////			return 1;		 
////		}		
////	}    
////    MPU_IIC_Stop();	 
////	return 0;	
////} 
//////IIC连续读
//////addr:器件地址
//////reg:要读取的寄存器地址
//////len:要读取的长度
//////buf:读取到的数据存储区
//////返回值:0,正常
//////    其他,错误代码
////u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
////{ 
//// 	MPU_IIC_Start(); 
////	MPU_IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
////	if(MPU_IIC_Wait_Ack())	//等待应答
////	{
////		MPU_IIC_Stop();		 
////		return 1;		
////	}
////    MPU_IIC_Send_Byte(reg);	//写寄存器地址
////    MPU_IIC_Wait_Ack();		//等待应答
////    MPU_IIC_Start();
////	MPU_IIC_Send_Byte((addr<<1)|1);//发送器件地址+读命令	
////    MPU_IIC_Wait_Ack();		//等待应答 
////	while(len)
////	{
////		if(len==1)*buf=MPU_IIC_Read_Byte(0);//读数据,发送nACK 
////		else *buf=MPU_IIC_Read_Byte(1);		//读数据,发送ACK  
////		len--;
////		buf++; 
////	}    
////    MPU_IIC_Stop();	//产生一个停止条件 
////	return 0;	
////}
//////IIC写一个字节 
//////reg:寄存器地址
//////data:数据
//////返回值:0,正常
//////    其他,错误代码
////u8 MPU_Write_Byte(u8 reg,u8 data) 				 
////{ 
////    MPU_IIC_Start(); 
////	MPU_IIC_Send_Byte((MPU_ADDR<<1)|0);//发送器件地址+写命令	
////	if(MPU_IIC_Wait_Ack())	//等待应答
////	{
////		MPU_IIC_Stop();		 
////		return 1;		
////	}
////    MPU_IIC_Send_Byte(reg);	//写寄存器地址
////    MPU_IIC_Wait_Ack();		//等待应答 
////	MPU_IIC_Send_Byte(data);//发送数据
////	if(MPU_IIC_Wait_Ack())	//等待ACK
////	{
////		MPU_IIC_Stop();	 
////		return 1;		 
////	}		 
////    MPU_IIC_Stop();	 
////	return 0;
////}
//////IIC读一个字节 
//////reg:寄存器地址 
//////返回值:读到的数据
////u8 MPU_Read_Byte(u8 reg)
////{
////	u8 res;
////    MPU_IIC_Start(); 
////	MPU_IIC_Send_Byte((MPU_ADDR<<1)|0);//发送器件地址+写命令	
////	MPU_IIC_Wait_Ack();		//等待应答 
////    MPU_IIC_Send_Byte(reg);	//写寄存器地址
////    MPU_IIC_Wait_Ack();		//等待应答
////    MPU_IIC_Start();
////	MPU_IIC_Send_Byte((MPU_ADDR<<1)|1);//发送器件地址+读命令	
////    MPU_IIC_Wait_Ack();		//等待应答 
////	res=MPU_IIC_Read_Byte(0);//读取数据,发送nACK 
////    MPU_IIC_Stop();			//产生一个停止条件 
////	return res;		
////}



