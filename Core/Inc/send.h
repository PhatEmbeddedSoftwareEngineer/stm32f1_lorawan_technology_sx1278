/*
	written by huynh tang thien phat
	date 19/2/2024
*/

#ifndef __SEND_H
#define __SEND_H
#include "main.h"
#include <stdio.h>
extern float Yaw_m,Pitch_m,Roll_m;
/*
	define for uart
*/
#define GPIO_CRH_ALT9 ((uint32_t)0x000000B0) 
#define GPIO_CRH_INPUT10 ((uint32_t)0x00000800)

#ifdef __cplusplus
extern "C"
{
#endif

void initUART1(void);

void SetSystem72Mhz(void);
void usart1_sendByte(unsigned char c);
void SendKyTu(const char str[100],char str2[]);
void sendNumber(const char str[100],int data);
void sendNumberAll(const char str[100],int pitch,int yaw,int roll);
void sendNumberAndChu(const char str[100],char str2[],int data);
void sendFloatAndChu(const char str[100],char str2[],float data);

#ifdef __cplusplus
}
#endif

#endif
