/* HEAT SINK FAN INTERFACE HEADER
 * Final Year Thesis - EEE4022S
 * Anja Mühr (2018)
 */

#ifndef HEAT_H_
#define HEAT_H_

#include "Greenhouse.h"

// heating PA5
#define GPIO_Heat GPIOA				// GPIO used for heat fan
#define Pin_Heat GPIO_Pin_5			// pin used
#define stdHeatDutyCycle 8000		// std duty cycle (start up) = high to reduce LED heat
#define maxHeatDutyCycle 8300
#define minHeatDutyCycle 2000


// Initialise LEDs (GPIO pin & PWM)
void initHeat(void);

// Increase heat (increment duty cycle)
int increaseHeatFan(void);

// Decrease heat (decrement duty cycle)
int decreaseHeatFan(void);

// Turn heat off
void heatOff(void);

// Turn heat on to previous duty cycle value
void heatOn(void);


#endif /* HEAT_H_ */
