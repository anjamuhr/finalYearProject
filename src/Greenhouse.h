/* OVERALL GREENHOUSE FUNCTIONS HEADER
 * Final Year Thesis - EEE4022S
 * Anja Mühr (2018)
 */

#ifndef GREENHOUSE_H_
#define GREENHOUSE_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdio.h>
#include "lib.h"
#include "tempSensor.h"
#include "fogger.h"
#include "fan.h"
#include "heat.h"
#include "leds.h"

#define PWMTimer TIM2			// define which timer will be used for PWM

// initialise all components of greenhouse
void configGreenhouse(void);
// initialise timers
void initTimers(void);

// decrease temp of greenhouse
void tooHot(void);

// increase temp of greenhouse
void tooCold(void);

// variable (stateGermination) read & write
int getStateGermination(void);
void setStateGermination(void);
void clearStateGermination(void);


#endif /* GREENHOUSE_H_ */
