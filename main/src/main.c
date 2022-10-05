/*
*** Òåñòîâûé ïðîåêò
*** Ìèãàíèå ñâåòîäèîäîâ â 4-õ ðåæèìàõ:
*** 	LEDS_RUNNING_SHADOW
***		LEDS_WAVE
***		LEDS_RUNNING_LIGHT
***		LED_BLINK
*** ðåæèì âûáèðàåòñÿ ìàêðîñîì â config.h
*** ñâåòîäèîäû ïîäêëþ÷åíû ê ïîðòó E. pin: 0-8
*** â ðåæèìå LED_BLINK âûáðàí LED0
***
*** Âíåøíèé êâàðö 25ÌÃö
*** Òàêòîâàÿ ÷àñòîòà ÿäðà: 120ÌÃö	
***
*** Ïåðèîä ïåðåêëþ÷åíèÿ ñâåòîäèîäà íàñòðàèâàåòñÿ òàéìåðîì TIM2 
<<<<<<< HEAD
*** git test branch 
=======
*** git test branch
*** git test branch and merge
>>>>>>> origin/main
*** 
*/

#include "main.h"

int main()
{
	RCC_Configuration();							
	
	TIM2_Init(20);										//20ìñ ïåðåêëþ÷åíèå ñâåòîäèîäîâ
	
	Init_GPIO();
	
	while(1)
	{
		;
	}
	
}
