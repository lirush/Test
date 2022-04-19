#include "sysclock.h"
#include "stm32f4xx_gpio.h"

void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;		
	RCC_ClocksTypeDef RCC_ClockFreq;
	// Сбрасываем клокинг в "0"
	RCC_DeInit();
	// Включаем внешний кварц
	RCC_HSEConfig(RCC_HSE_ON);//RCC_HSE_Bypass);
	// Ждём пока устанавливается внешний ВЧ тактовый сигнал
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus != ERROR)  
	{
		
    // Внешний тактовый сигнал появился, стабильный
    // разрешаем использование буфера команд
		FLASH_PrefetchBufferCmd(ENABLE);
    //-------------------------------------------------------------------
 		// итак
		//Внешний кварц 25МГц
		//Тактовая частота ядра: 120МГц		
		//-------------------------------------------------------------------
		/* Flash 2 wait state  двойная задержка*/
		FLASH_SetLatency(FLASH_Latency_2);

		RCC_HCLKConfig(RCC_SYSCLK_Div1); /* HCLK = SYSCLK    AHB clock = SYSCLK=120*/

		RCC_PCLK1Config(RCC_HCLK_Div4);  //APB1 clock = HCLK/4 120/4=30 для CAN
		RCC_PCLK2Config(RCC_HCLK_Div4);  //APB2 clock = HCLK/2 120/4=30 
		
		//RCC_PLLSource_HSE=25 - источник для PLL, PLLM=25,  PLLN=240, PLLP=2, PLLQ=5
		//  HSE/PLLM=VCO, VCO*PLLN/PLLP=PLLCLK, VCO*PLLN/PLLQ=PLL48CK см. 48 стр мануала 
		RCC_PLLConfig(RCC_PLLSource_HSE,25, 240, 2, 4);
		//Разрешаем PLL
		RCC_PLLCmd(ENABLE);

		// Ждём пока устаканится PLL
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY ) == RESET)
		{}
		// PLL - устаканился
		// Выбираем PLL как источник тактирования системы
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		// Ждём пока PLL не станет клокингом системы
		while (RCC_GetSYSCLKSource() != 0x08)
		{}
		
	}
	RCC_GetClocksFreq(&RCC_ClockFreq);
	
}
