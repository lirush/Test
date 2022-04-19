#ifndef _LEDS_H
#define _LEDS_H

#include "stm32f4xx_gpio.h"

enum nLEDS{LED0,LED1,LED2,LED3,LED4,LED5,LED6,LED7};

void Init_GPIO(void);
void LedsRunningShadow(void);
void LedsWave(void);
void LedsRunningLight(void);
void LedBlink(uint8_t num_led);

#endif
