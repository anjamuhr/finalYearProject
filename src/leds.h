/* LED GROW LIGHTS INTERFACE (HEADER)
 * Final Year Thesis - EEE4022S
 * Anja Mühr (2018)
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "Greenhouse.h"

// LEDs PA3
#define GPIO_LEDs GPIOA				// GPIO used by LEDs
#define Pin_LEDs GPIO_Pin_3			// pin used by LEDs
#define lightOnTime 14              // number of hours with light on
#define lightTotalTime 24        	// total light interval (i.e. time off + time on)
#define germTime 48		            // total number of hours needed for germination
#define stdLEDDutyCycle 4000		// start up duty cycle (for PWM)
#define maxLEDDutyCycle 8300
#define minLEDDutyCycle 500


// Initialise LEDs (GPIO pin & PWM)
void initLEDs();

// Increase led brightness (increment duty cycle)
int increaseLight(void);

// Decrease led brightness (decrement duty cycle)
int decreaseLight(void);

// Turn lights off
void turnLightsOff(void);

// Turn lights on to std brightness
void turnLightsOn(void);

#endif /* LEDS_H_ */
