// LIB
// Anja Mühr

#include "lib.h"


/* --------------------------- LEDs -------------------------------------------------------*/

/* Initialize a specific LED in standard output mode */
void initLEDStd(LED_Type LED) {

	// initialise PWM GPIO pin
	TM_GPIO_Init(GPIOD, getLEDPin(LED), TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Medium);

}

/* Returns pin number of specific LED (green, red, orange, blue) */
uint16_t getLEDPin(LED_Type led) {
	if (led == 3) {
		return LED3_PIN;
	} else if (led == 4) {
		return LED4_PIN;
	} else if (led == 5) {
		return LED5_PIN;
	} else if (led == 6) {
		return LED6_PIN;
	}
}

/* Initialises LED to use PWM on TIM4 (green, red, orange, blue) */
void initLEDPWM(LED_Type LED) {

	TM_GPIO_Init(GPIOD, getLEDPin(LED), TM_GPIO_Mode_AF, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Medium);

	GPIO_PinAFConfig(GPIOD, getPinSource(getLEDPin(LED)), GPIO_AF_TIM3);//link the AF pin to the timer
}

/* Returns pin source for specific GPIO_Pin */
uint16_t getPinSource(uint16_t GPIO_Pin) {
	if ( GPIO_Pin == GPIO_Pin_0 ) { return GPIO_PinSource0; }
	if ( GPIO_Pin == GPIO_Pin_1 ) { return GPIO_PinSource1; }
	if ( GPIO_Pin == GPIO_Pin_2 ) { return GPIO_PinSource2; }
	if ( GPIO_Pin == GPIO_Pin_3 ) { return GPIO_PinSource3; }
	if ( GPIO_Pin == GPIO_Pin_4 ) { return GPIO_PinSource4; }
	if ( GPIO_Pin == GPIO_Pin_5 ) { return GPIO_PinSource5; }
	if ( GPIO_Pin == GPIO_Pin_6 ) { return GPIO_PinSource6; }
	if ( GPIO_Pin == GPIO_Pin_7 ) { return GPIO_PinSource7; }
	if ( GPIO_Pin == GPIO_Pin_8 ) { return GPIO_PinSource8; }
	if ( GPIO_Pin == GPIO_Pin_9 ) { return GPIO_PinSource9; }
	if ( GPIO_Pin == GPIO_Pin_10 ) { return GPIO_PinSource10; }
	if ( GPIO_Pin == GPIO_Pin_11 ) { return GPIO_PinSource11; }
	if ( GPIO_Pin == GPIO_Pin_12 ) { return GPIO_PinSource12; }
	if ( GPIO_Pin == GPIO_Pin_13 ) { return GPIO_PinSource13; }
	if ( GPIO_Pin == GPIO_Pin_14 ) { return GPIO_PinSource14; }
	if ( GPIO_Pin == GPIO_Pin_15 ) { return GPIO_PinSource15; }
}

/* Initialises all LEDs in standard output mode */
void initAllLEDsStd(void) {

	TM_GPIO_Init(GPIOD, LED3_PIN | LED4_PIN | LED5_PIN | LED6_PIN, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Medium);

}

/* --------------------------- TIMERS -----------------------------------------------------*/

/* Initialises any timer */
void initTimer(TIM_TypeDef* TIMx, int period, int prescaler)  {

	TM_TIMER_PROPERTIES_EnableClock(TIMx);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);

	TIM_TimeBaseInitStruct.TIM_Period = period;
	TIM_TimeBaseInitStruct.TIM_Prescaler = prescaler;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStruct);

	TIM_Cmd(TIMx, ENABLE); // enable counter
}

/* Enables interrupts for a specific timer */
void enableInterrupt(TIM_TypeDef* TIMx) {

	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = getIRQChannel(TIMx);//set up the interrupt handler for TIM2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);


}

/* Gets IRQChannel for a specific timer */
int getIRQChannel(TIM_TypeDef* TIMx) {
	//if (TIMx == TIM1) { return TIM1_IRQn; }
	if (TIMx == TIM2) { return TIM2_IRQn; }
	if (TIMx == TIM3) { return TIM3_IRQn; }
	if (TIMx == TIM4) { return TIM4_IRQn; }
	if (TIMx == TIM5) { return TIM5_IRQn; }
	//if (TIMx == TIM6) { return TIM6_IRQn; }
	if (TIMx == TIM7) { return TIM7_IRQn; }
	//if (TIMx == TIM8) { return TIM8_IRQn; }
	//if (TIMx == TIM9) { return TIM9_IRQn; }
	//if (TIMx == TIM10) { return TIM10_IRQn; }
	//if (TIMx == TIM11) { return TIM11_IRQn; }
	//if (TIMx == TIM12) { return TIM12_IRQn; }
}

/* Initialises and starts a standard timer */
void stdTimer(TIM_TypeDef* TIMx, int period, int prescaler) {

	initTimer(TIMx, period, prescaler);
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE); // enable timer interrupt
	enableInterrupt(TIMx);
}

/* Initialises and starts a PWM timer on PWM1 initialised at 10% */
void initPWMChannel(TIM_TypeDef* TIMx, int pulse, int channel) {

	TIM_OCInitTypeDef TIM_OCInitStruct;

	// PWM1 Mode configuration:
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;				// PWM mode (set on compare-match)
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = pulse;							// (max period 1000)
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;

	if (channel == 1) {
		// PWM initialisation
		TIM_OC1Init(TIMx, &TIM_OCInitStruct);
		TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
	} else if (channel == 2) {
		// PWM initialisation
		TIM_OC2Init(TIMx, &TIM_OCInitStruct);
		TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
	} else if (channel == 3) {
		// PWM initialisation
		TIM_OC3Init(TIMx, &TIM_OCInitStruct);
		TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
	} else if (channel == 4) {
		// PWM initialisation
		TIM_OC4Init(TIMx, &TIM_OCInitStruct);
		TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}



}

uint8_t getAFTimer(TIM_TypeDef* TIMx) {

	if (TIMx == TIM2) {
		return GPIO_AF_TIM2;
	} else if (TIMx == TIM4) {
		return GPIO_AF_TIM4;
	}
}


void writeFile(char * filename, float temp) {

	FILE *fp;
	filename=strcat(filename,".csv");
	fp=fopen(filename,"w+");
	fprintf(fp,"%3.5f\n", temp);
	fclose(fp);
}

void initGPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd, GPIOSpeed_TypeDef GPIO_Speed) {

	/* Enable clock for GPIO */
	GPIO_EnableClock(GPIOx);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;//set up the LED
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
	GPIO_InitStructure.GPIO_OType = GPIO_OType;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;

	GPIO_Init(GPIOx, &GPIO_InitStructure);

}

void GPIO_EnableClock(GPIO_TypeDef* GPIOx) {
	if (GPIOx == GPIOA) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	} else if (GPIOx == GPIOB) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	} else if (GPIOx == GPIOC) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	} else if (GPIOx == GPIOD) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	} else if (GPIOx == GPIOE) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	} else if (GPIOx == GPIOF) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	}
}
