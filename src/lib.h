// LIB
// Anja Mühr


#ifndef LIB_H_
#define LIB_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_onewire.h"
#include "tm_stm32f4_ds18b20.h"
#include <stdio.h>
#include <sys/time.h>



#define GREENLED LED4
#define BLUELED LED6
#define ORANGELED LED3
#define REDLED LED5



typedef enum {
	orange = 3,
	green = 4,
	red = 5,
	blue = 6,

} LED_Type;


/*
 * lib.c
 *
 *  Created on: 10 Oct 2018
 *      Author: DELL P66F
 */

#include "lib.h"



/* --------------------------- LEDs -------------------------------------------------------*/


/* Initialize a specific LED in standard output mode */
void initLEDStd(LED_Type LED);

/* Returns pin number of specific LED (green, red, orange, blue) */
uint16_t getLEDPin(LED_Type led);
/* Initialises LED to use PWM on TIM4 (green, red, orange, blue) */
void initLEDPWM(LED_Type LED);

/* Returns pin source for specific GPIO_Pin */
uint16_t getPinSource(uint16_t GPIO_Pin);

/* Initialises all LEDs in standard output mode */
void initAllLEDsStd(void);

/* Initialises any timer */
void initTimer(TIM_TypeDef* TIMx, int period, int prescaler);

void enableInterrupt(TIM_TypeDef* TIMx);

int getIRQChannel(TIM_TypeDef* TIMx);

uint32_t getTimerBus(TIM_TypeDef* TIMx);

void stdTimer(TIM_TypeDef* TIMx, int period, int prescaler);

void initPWMChannel(TIM_TypeDef* TIMx, int pulse, int channel);

uint8_t getAFTimer(TIM_TypeDef* TIMx);

void writeFile(char * filename, float temp);

void GPIO_EnableClock(GPIO_TypeDef* GPIOx);

void initGPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd, GPIOSpeed_TypeDef GPIO_Speed);


#endif /* LIB_H_ */
