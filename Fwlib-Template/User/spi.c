#include "spi.h"
#include "delay.h"
#include "usart.h"

void SPI_OLED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 |GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CRCPolynomial = 0;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_Init(SPI1, &SPI_InitStructure);
	
	SPI_Cmd(SPI1, ENABLE);
	DC_H();
	CS_L();
}


void SPI_WriteCmd(u8 Data)	//写命令
{
	DC_L();
	SPI_I2S_SendData(SPI1,Data);
}
 
void OLED_WriteData8(u8 Data)	//写8位数据
{
	DC_H();
	SPI_I2S_SendData(SPI1,Data);
}
 
void OLED_WriteData16(u16 Data)	//写16位数据
{
	DC_H();
	SPI_I2S_SendData(SPI1,(Data>>8) ) ;	//Date右移8位
	SPI_I2S_SendData(SPI1,Data);		
}

void OLED_Init(void)
{
	RES_H();
	DelayMs(100);
	RES_L();
	DelayMs(200);
	RES_H(); 
	
	DelayMs(200);
	SPI_WriteCmd(0xAE);//--display off
  SPI_WriteCmd(0x00);//--set low column address
  SPI_WriteCmd(0x10);//--set high column address
  SPI_WriteCmd(0x40);//--set start line address  
  SPI_WriteCmd(0xB0);//--set page address
  SPI_WriteCmd(0x81);// contract control
  SPI_WriteCmd(0xFF);//--128   
  SPI_WriteCmd(0xA1);//set segment re-map  0 to 127 
  SPI_WriteCmd(0xA6);//set normal  display  
  SPI_WriteCmd(0xA8);//set multiplex ratio(1 to 64)
  SPI_WriteCmd(0x3F);//--1/32 duty
  SPI_WriteCmd(0xC8);//Com scan direction
  SPI_WriteCmd(0xD3);//set display offset
  SPI_WriteCmd(0x00);//no offset
  SPI_WriteCmd(0xD5);//set display clock divide ratio/oscillator frequency  
  SPI_WriteCmd(0x80);//
  SPI_WriteCmd(0xD8);//set area color mode off
  SPI_WriteCmd(0x05);//
  SPI_WriteCmd(0xD9);//Set Pre-Charge Period
  SPI_WriteCmd(0xF1);//
  SPI_WriteCmd(0xDA);//set com pin  hardware configuartion
  SPI_WriteCmd(0x12);//
  SPI_WriteCmd(0xDB);//set Vcomh
  SPI_WriteCmd(0x30);//0x20,0.77xVcc
  SPI_WriteCmd(0x8D);//set charge pump enable
  SPI_WriteCmd(0x14);//
  SPI_WriteCmd(0xAF);//--turn on oled panel

	OLED_Clear();
	OLED_SetPos(0,0); 
}

void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		SPI_WriteCmd (0xb0+i);    //设置页地址（0~7）
		SPI_WriteCmd (0x00);      //设置显示位置—列低地址
		SPI_WriteCmd (0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WriteData8(0); 
	} //更新显示
}

void OLED_SetPos(u8 x, u8 y)
{
	SPI_WriteCmd(0xb0+y);
	SPI_WriteCmd(((x&0xf0)>>4)|0x10);
	SPI_WriteCmd((x&0x0d)|0x01);
}


void OLED_Fill(u8 DAT)
{
	u8 m,n;
	for(m = 0;m < 8;m++)
	{
		SPI_WriteCmd(0xb0+m);
		SPI_WriteCmd(0x00);
		SPI_WriteCmd(0x10);
		for(n = 0;n < 128;n++)
		{
			OLED_WriteData8(DAT);
		}
	}
}

void OLED_DrawBMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[])
{
	u16 j = 0;
	u8 x, y;
	
	if(y1%8 == 0) y = y1/8;
	else y = y1/8 - 1;
	for(y = y0;y < y1;y++)
	{
		OLED_SetPos(x0, y);
		for(x = x0;x < x1;x++)
		{
			OLED_WriteData8(BMP[j++]);
		}
	}
}

//开启OLED显示    
void OLED_Display_On(void)
{
	SPI_WriteCmd(0X8D);  //SET DCDC命令
	SPI_WriteCmd(0X14);  //DCDC ON
	SPI_WriteCmd(0XAF);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	SPI_WriteCmd(0X8D);  //SET DCDC命令
	SPI_WriteCmd(0X10);  //DCDC OFF
	SPI_WriteCmd(0XAE);  //DISPLAY OFF
}		   			 





