/* FAN INTERFACE HEADER
 * Final Year Thesis - EEE4022S
 * Anja Mühr (2018)
 */

#ifndef FAN_H_
#define FAN_H_

#include "Greenhouse.h"

#define GPIO_Fan GPIOA					// GPIO used for fan
#define Pin_Fan GPIO_Pin_1				// pin used
#define stdFanDutyCycle 4000			// initial duty cycle
#define maxFanDutyCycle 6000
#define minFanDutyCycle 2000


// Initialise fan (GPIO pin & PWM)
void initFan(void);

// Increase fan speed (increment duty cycle)
int increaseFanSpeed(void);

// Decrease fan speed (decrement duty cycle)
int decreaseFanSpeed(void);

// Turn fan on to previous duty cycle value
void fanOn (void);

// Turn off fan
void fanOff (void);


#endif /* FAN_H_ */
