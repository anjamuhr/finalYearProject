/* FAN INTERFACE
 * Final Year Thesis - EEE4022S
 * Anja Mühr (2018)
 */

#include "fan.h"

int fanDutyCycle = stdFanDutyCycle;		// current fan duty cycle (for PWM)
int fanOnDutyCycle = stdFanDutyCycle;	// last duty cycle before fan turned off


// Initialise fan (GPIO pin & PWM)
void initFan(void) {

	// initialise PWM GPIO pin
	initGPIO(GPIO_Fan, Pin_Fan, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_50MHz);

	// connect GPIO pin to PWM timer
	GPIO_PinAFConfig(GPIO_Fan, getPinSource(Pin_Fan), getAFTimer(PWMTimer));

}

// Increase fan speed (increment duty cycle)
int increaseFanSpeed(void) {
	if (fanDutyCycle < maxFanDutyCycle) {	// check fan speed is not at maximum
			fanDutyCycle = fanDutyCycle + 100;
			TIM_SetCompare2(PWMTimer,fanDutyCycle);
			return 1;
		} else return 0;
}

// Decrease fan speed (decrement duty cycle)
int decreaseFanSpeed(void) {
	if (fanDutyCycle > minFanDutyCycle) {	// check fan speed is not at minimum
		fanDutyCycle = fanDutyCycle - 100;
		TIM_SetCompare2(PWMTimer,fanDutyCycle);
		return 1;
	} else return 0;
}

// Turn on fan with duty cycle equal to last known duty cycle
void fanOn (void) {
	fanDutyCycle = fanOnDutyCycle;
	TIM_SetCompare2(PWMTimer,fanDutyCycle);
}

// Turn off fan (duty cycle = 0)
void fanOff(void) {
	fanOnDutyCycle = fanDutyCycle;
	fanDutyCycle = 0;
	TIM_SetCompare2(PWMTimer,fanDutyCycle);
}

