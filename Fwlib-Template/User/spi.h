#ifndef _SPI_H
#define _SPI_H
#include "stm32f10x.h"

#define CS_L() GPIO_ResetBits(GPIOA, GPIO_Pin_15);
#define CS_H() GPIO_SetBits(GPIOA, GPIO_Pin_15);

#define DC_L() GPIO_ResetBits(GPIOA, GPIO_Pin_12);
#define DC_H() GPIO_SetBits(GPIOA, GPIO_Pin_12);

#define RES_L() GPIO_ResetBits(GPIOA, GPIO_Pin_11);
#define RES_H() GPIO_SetBits(GPIOA, GPIO_Pin_11);




//CLK(D0) -> PA5
//MISO(D1) -> PA6
//CS(Ƭѡ) -> PA7
//DC -> PB1
//RES -> PB2

void SPI_OLED_Init(void);

void SPI_WriteCmd(u8 Data);
void OLED_WriteData8(u8 Data);
void OLED_WriteData16(u16 Data);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_SetPos(u8 x, u8 y);
void OLED_Fill(u8 DAT);
void OLED_DrawBMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[]);
void OLED_Display_On(void);
void OLED_Display_Off(void);

#endif

