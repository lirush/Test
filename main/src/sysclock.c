#include "sysclock.h"
#include "stm32f4xx_gpio.h"

void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;		
	RCC_ClocksTypeDef RCC_ClockFreq;
	// ���������� ������� � "0"
	RCC_DeInit();
	// �������� ������� �����
	RCC_HSEConfig(RCC_HSE_ON);//RCC_HSE_Bypass);
	// ��� ���� ��������������� ������� �� �������� ������
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus != ERROR)  
	{
		
    // ������� �������� ������ ��������, ����������
    // ��������� ������������� ������ ������
		FLASH_PrefetchBufferCmd(ENABLE);
    //-------------------------------------------------------------------
 		// ����
		//������� ����� 25���
		//�������� ������� ����: 120���		
		//-------------------------------------------------------------------
		/* Flash 2 wait state  ������� ��������*/
		FLASH_SetLatency(FLASH_Latency_2);

		RCC_HCLKConfig(RCC_SYSCLK_Div1); /* HCLK = SYSCLK    AHB clock = SYSCLK=120*/

		RCC_PCLK1Config(RCC_HCLK_Div4);  //APB1 clock = HCLK/4 120/4=30 ��� CAN
		RCC_PCLK2Config(RCC_HCLK_Div4);  //APB2 clock = HCLK/2 120/4=30 
		
		//RCC_PLLSource_HSE=25 - �������� ��� PLL, PLLM=25,  PLLN=240, PLLP=2, PLLQ=5
		//  HSE/PLLM=VCO, VCO*PLLN/PLLP=PLLCLK, VCO*PLLN/PLLQ=PLL48CK ��. 48 ��� ������� 
		RCC_PLLConfig(RCC_PLLSource_HSE,25, 240, 2, 4);
		//��������� PLL
		RCC_PLLCmd(ENABLE);

		// ��� ���� ����������� PLL
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY ) == RESET)
		{}
		// PLL - �����������
		// �������� PLL ��� �������� ������������ �������
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		// ��� ���� PLL �� ������ ��������� �������
		while (RCC_GetSYSCLKSource() != 0x08)
		{}
		
	}
	RCC_GetClocksFreq(&RCC_ClockFreq);
	
}
