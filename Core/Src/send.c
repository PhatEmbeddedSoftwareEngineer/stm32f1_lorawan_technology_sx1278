#include "send.h"

void initUART1(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
	GPIOA->CRH |= GPIO_CRH_ALT9|GPIO_CRH_INPUT10;
	GPIOA->ODR |= GPIO_ODR_ODR10;  //pull-up PA10
	USART1->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
	USART1->BRR = 625;	 // 72MHz/9600bps = 7500
}

void SetSystem72Mhz(void)
{
	// NHAN 9 VOI TAN SO 
	RCC->CFGR |= (7<<18); // or RCC->CFGR |= RCC_CFGR_PLLMULL9;
	// CHIA CHO 1.5 
	RCC->CFGR &= ~ (1<<22);
	// SET HSEON 
	RCC->CR |= (1<<16);
	// WAIT HSERDY 
	while((RCC->CR & RCC_CR_HSERDY)==0);
	// PLL FOR MODE HSE 
	RCC->CFGR |= (1<<16);
	
	// TUONG TU VOI HSE TA KICH HOAT PLLON VA CHO NO READY
	RCC->CR |= RCC_CR_PLLON;
	while((RCC->CR & RCC_CR_PLLRDY)==0);
	//Flash pre-fetch enable and wait-state=2
	  //0WS: 0-24MHz
	  //1WS: 24-48MHz
	  //2WS: 48-72MHz
	FLASH->ACR |= FLASH_ACR_PRFTBE|FLASH_ACR_LATENCY_1;
	 //Select PLL as main System Clock source
	RCC->CFGR &= ~ RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	//Wait until PLL system source is active
	while((RCC->CFGR & RCC_CFGR_SWS)!=RCC_CFGR_SWS_PLL);
	
	// AHB DIV1
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	// APB1 DIV 2
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	// APP2 DIV 1
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	// ADC PSC = 6 , 2X6 = 12 
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	
	// khong anh xa lai ma pin CHO TIM2 
	AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_NOREMAP;
	
}
void usart1_sendByte(unsigned char c)
{
	USART1->DR = c;
	
	while((USART1->SR&(1<<6)) == 0);  //wait until the TC flag is set 
	USART1->SR &= ~(1<<6);
}

void SendKyTu(const char str[100],char str2[])
{
	sprintf(str,"%s ",str2);
	int j=0;
	while(str[j] != '\0')
	{
		usart1_sendByte(str[j]);
		j++;
	}
	usart1_sendByte('\n');
}

void sendNumberAll(const char str[100],int pitch,int yaw,int roll)
{
	sprintf(str,"%d %d %d ",pitch,yaw,roll);
	int j=0;
	while(str[j] != '\0')
	{
		usart1_sendByte(str[j]);
		j++;
	}
	usart1_sendByte('\n');
}

void sendNumber(const char str[100],int data)
{
	sprintf(str,"\n%d",data);
	int j=0;
	while(str[j] != '\0')
	{
		usart1_sendByte(str[j]);
		j++;
	}
}
void sendNumberAndChu(const char str[100],char str2[],int data)
{
	sprintf(str,"\n%s%d",str2,data);
	int j=0;
	while(str[j] != '\0')
	{
		usart1_sendByte(str[j]);
		j++;
	}
}
void sendFloatAndChu(const char str[100],char str2[],float data)
{
	sprintf(str,"\n%s%.4f",str2,data);
	int j=0;
	while(str[j] != '\0')
	{
		usart1_sendByte(str[j]);
		j++;
	}
}
