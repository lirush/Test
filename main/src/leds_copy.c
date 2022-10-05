#include "leds.h"

void Init_GPIO(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void LedsRunningShadow(void)
{
	static uint8_t i=0;
	
	GPIOE->ODR = ~(1<<i++) & 0x00ff;
	i &= 7;
}

void LedsWave(void)
{
	static uint8_t i=0;
	static uint8_t ch=0;
	
	switch(ch)
	{
		case 0:
			GPIOE->ODR = (0xf<<i);
		break;
		case 1:
			GPIOE->ODR = ~(0xf<<i) & 0x00ff;	
		break;
	}
	if(i++==4) {ch^=(1<<0); i=1;}
}

void LedsRunningLight(void)
{
	static uint8_t i=0;
	
	GPIOE->ODR = (1<<i++) & 0x00ff;
	i &= 7;
}

void LedBlink(uint8_t num_led)
{
	GPIOE->ODR ^= (1<<num_led);
}
