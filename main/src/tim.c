#include "tim.h"
#include "stm32f4xx_tim.h"
#include "config.h"
#include "leds.h"

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
    {
			#ifdef LEDS_RUNNING_SHADOW
				LedsRunningShadow();
			#endif
			
			#ifdef LEDS_WAVE
				LedsWave();
			#endif

			#ifdef LEDS_RUNNING_LIGHT
				LedsRunningLight();
			#endif	

			#ifdef LED_BLINK
				LedBlink(LED0);
			#endif			
			
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		}
}

void  TIM2_Init(unsigned short int period)
{
	uint16_t prs=(6*period);
	/* Подаём такты на TIM2 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	
  TIM_TimeBaseInitTypeDef timer_base;
  TIM_TimeBaseStructInit(&timer_base);
  timer_base.TIM_Prescaler = prs;                           //Timclk=60МГц
	timer_base.TIM_Period = 10000;
  TIM_TimeBaseInit(TIM2, &timer_base);


  /* Разрешаем таймеру генерировать прерывание по захвату */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2,ENABLE);
  /* Включаем таймер */
  NVIC_EnableIRQ(TIM2_IRQn);
}
