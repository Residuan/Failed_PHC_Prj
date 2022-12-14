#ifndef _I2C_H
#define _I2C_H

#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "systick.h"

#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))




void i2cinit(void);
u8 WriteI2C_Byte(u8 addr, u8 data);
u8 Read_Byte(u8* pBuffer, u8 raddr, u16 Num);
uint8_t Read_Len(u8 addr, u8 reg, u8 Num, u8 *buf);
u8 WriteI2C_Len(u8 addr,u8 reg, u8 len, u8 *buf);
u8 stm32_i2c_write(unsigned char slave_addr, unsigned char reg_addr, unsigned char length, unsigned char const *data);
u8 stm32_i2c_read(unsigned char slave_addr, unsigned char reg_addr, unsigned char length, unsigned char *data);

unsigned short Get_I2C_Retry(void);
////int Sensors_I2C_WriteRegister(unsigned char slave_addr,
////                                        unsigned char reg_addr,
////                                        unsigned short len,
////                                        const unsigned char *data_ptr);
////int Sensors_I2C_ReadRegister(unsigned char slave_addr,
////                                       unsigned char reg_addr,
////                                       unsigned short len,
////                                       unsigned char *data_ptr);


#endif

////#ifndef __BSP_I2C_H
////#define	__BSP_I2C_H

////#include "stm32f10x.h"
////#include "./usart.h"


//////若定义这个宏，使用硬件iic，否则使用软件iic,
//////使用硬件IIC时不能与液晶屏共用，因为FSMC的NADV与IIC1的SDA 是同一个引脚，互相影响了
//////若不用FSMC时，推荐用硬件IIC

//////#define HARD_IIC 

//////MPU6050的AD0引脚接GND时，地址为0x68 ,接3.3V时，地址为0x69，注意要匹配。
////#define MPU6050_ADDR   0x68


/////*********************软件IIC使用的宏****************************/

//////
////#define Soft_I2C_SDA 		GPIO_Pin_7
////#define Soft_I2C_SCL 		GPIO_Pin_6
////#define Soft_I2C_PORT   GPIOB
//////
////#define Soft_I2C_SCL_0 		GPIO_ResetBits(Soft_I2C_PORT, Soft_I2C_SCL)
////#define Soft_I2C_SCL_1 		GPIO_SetBits(Soft_I2C_PORT, Soft_I2C_SCL)
////#define Soft_I2C_SDA_0 		GPIO_ResetBits(Soft_I2C_PORT, Soft_I2C_SDA)
////#define Soft_I2C_SDA_1   	GPIO_SetBits(Soft_I2C_PORT, Soft_I2C_SDA)





/////**************************I2C参数定义，I2C1或I2C2********************************/
////#define             SENSORS_I2Cx                                I2C1
////#define             SENSORS_I2C_APBxClock_FUN                   RCC_APB1PeriphClockCmd
////#define             SENSORS_I2C_CLK                             RCC_APB1Periph_I2C1
////#define             SENSORS_I2C_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
////#define             SENSORS_I2C_GPIO_CLK                        RCC_APB2Periph_GPIOB     
////#define             SENSORS_I2C_SCL_PORT                        GPIOB   
////#define             SENSORS_I2C_SCL_PIN                         GPIO_Pin_6
////#define             SENSORS_I2C_SDA_PORT                        GPIOB 
////#define             SENSORS_I2C_SDA_PIN                         GPIO_Pin_7

/////*等待超时时间*/
////#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
////#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

/////*信息输出*/
////#define MPU_DEBUG_ON         0
////#define MPU_DEBUG_FUNC_ON    0

////#define MPU_INFO(fmt,arg...)           printf("<<-MPU-INFO->> "fmt"\n",##arg)
////#define MPU_ERROR(fmt,arg...)          printf("<<-MPU-ERROR->> "fmt"\n",##arg)
////#define MPU_DEBUG(fmt,arg...)          do{\
////                                          if(MPU_DEBUG_ON)\
////                                          printf("<<-MPU-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
////                                          }while(0)

////#define MPU_DEBUG_FUNC()               do{\
////                                         if(MPU_DEBUG_FUNC_ON)\
////                                         printf("<<-MPU-FUNC->> Func:%s@Line:%d\n",__func__,__LINE__);\
////                                       }while(0)


////void I2C_Bus_Init(void);
////uint8_t I2C_ByteWrite(uint8_t pBuffer, uint8_t WriteAddr);
////uint8_t I2C_BufferRead(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);
////																					
////void Set_I2C_Retry(unsigned short ml_sec);
////unsigned short Get_I2C_Retry(void);
////int Sensors_I2C_ReadRegister(unsigned char Address, unsigned char RegisterAddr, 
////                                          unsigned short RegisterLen, unsigned char *RegisterValue);
////int Sensors_I2C_WriteRegister(unsigned char Address, unsigned char RegisterAddr, 
////                                           unsigned short RegisterLen, const unsigned char *RegisterValue);
////																					

////#endif /* __BSP_I2C_H */

																					

																					

////#ifndef __BSP_I2C_H
////#define	__BSP_I2C_H

////#include "stm32f10x.h"
////#include "usart.h"


//////若定义这个宏，使用硬件iic，否则使用软件iic,
//////使用硬件IIC时不能与液晶屏共用，因为FSMC的NADV与IIC1的SDA 是同一个引脚，互相影响了
//////若不用FSMC时，推荐用硬件IIC

//////#define HARD_IIC 

//////MPU6050的AD0引脚接GND时，地址为0x68 ,接3.3V时，地址为0x69，注意要匹配。
////#define MPU6050_ADDR   0x68


/////*********************软件IIC使用的宏****************************/

//////
////#define Soft_I2C_SDA 		GPIO_Pin_11
////#define Soft_I2C_SCL 		GPIO_Pin_10
////#define Soft_I2C_PORT   GPIOB
//////
////#define Soft_I2C_SCL_0 		GPIO_ResetBits(Soft_I2C_PORT, Soft_I2C_SCL)
////#define Soft_I2C_SCL_1 		GPIO_SetBits(Soft_I2C_PORT, Soft_I2C_SCL)
////#define Soft_I2C_SDA_0 		GPIO_ResetBits(Soft_I2C_PORT, Soft_I2C_SDA)
////#define Soft_I2C_SDA_1   	GPIO_SetBits(Soft_I2C_PORT, Soft_I2C_SDA)





/////**************************I2C参数定义，I2C1或I2C2********************************/
////#define             SENSORS_I2Cx                                I2C1
////#define             SENSORS_I2C_APBxClock_FUN                   RCC_APB1PeriphClockCmd
////#define             SENSORS_I2C_CLK                             RCC_APB1Periph_I2C1
////#define             SENSORS_I2C_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
////#define             SENSORS_I2C_GPIO_CLK                        RCC_APB2Periph_GPIOB     
////#define             SENSORS_I2C_SCL_PORT                        GPIOB   
////#define             SENSORS_I2C_SCL_PIN                         GPIO_Pin_10
////#define             SENSORS_I2C_SDA_PORT                        GPIOB 
////#define             SENSORS_I2C_SDA_PIN                         GPIO_Pin_11

/////*等待超时时间*/
////#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
////#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

/////*信息输出*/
////#define MPU_DEBUG_ON         0
////#define MPU_DEBUG_FUNC_ON    0

////#define MPU_INFO(fmt,arg...)           printf("<<-MPU-INFO->> "fmt"\n",##arg)
////#define MPU_ERROR(fmt,arg...)          printf("<<-MPU-ERROR->> "fmt"\n",##arg)
////#define MPU_DEBUG(fmt,arg...)          do{\
////                                          if(MPU_DEBUG_ON)\
////                                          printf("<<-MPU-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
////                                          }while(0)

////#define MPU_DEBUG_FUNC()               do{\
////                                         if(MPU_DEBUG_FUNC_ON)\
////                                         printf("<<-MPU-FUNC->> Func:%s@Line:%d\n",__func__,__LINE__);\
////                                       }while(0)


////void I2C_Bus_Init(void);
////uint8_t I2C_ByteWrite(uint8_t pBuffer, uint8_t WriteAddr);
////uint8_t I2C_BufferRead(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);
////																					
////void Set_I2C_Retry(unsigned short ml_sec);
////unsigned short Get_I2C_Retry(void);
////int Sensors_I2C_ReadRegister(unsigned char Address, unsigned char RegisterAddr, 
////                                          unsigned short RegisterLen, unsigned char *RegisterValue);
////int Sensors_I2C_WriteRegister(unsigned char Address, unsigned char RegisterAddr, 
////                                           unsigned short RegisterLen, const unsigned char *RegisterValue);
////																					

////#endif /* __BSP_I2C_H */

																					

																					

																					

																	








