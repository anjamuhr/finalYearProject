/* HEAT SINK FAN INTERFACE
 * Final Year Thesis - EEE4022S
 * Anja Mühr (2018)
 */

#include "heat.h"

int heatDutyCycle = stdHeatDutyCycle;		// current heat duty cycle (for PWM)
int heatOnDutyCycle = stdHeatDutyCycle;		// last duty cycle before heat turned off

// Initialise LEDs (GPIO pin & PWM)
void initHeat(void) {

	// initialise PWM GPIO pin
	initGPIO(GPIO_Heat, Pin_Heat, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_50MHz);

	// connect GPIO pin to PWM timer
	GPIO_PinAFConfig(GPIO_Heat, getPinSource(Pin_Heat), getAFTimer(PWMTimer));

}

// Increase heat (increment duty cycle)
int increaseHeatFan(void) {

	if (heatDutyCycle < maxHeatDutyCycle) {	// check heat fan is not at maximum
		heatDutyCycle = heatDutyCycle + 100;
		TIM_SetCompare1(PWMTimer,heatDutyCycle);
		return 1;
		} else return 0;
}

// Decrease heat (decrement duty cycle)
int decreaseHeatFan(void) {

	if (heatDutyCycle > minHeatDutyCycle) {	// check heat fan is not at minimum
		heatDutyCycle = heatDutyCycle - 100;
		TIM_SetCompare1(PWMTimer,heatDutyCycle);
		return 1;
	} else return 0;
}

// Turn heat on to previous duty cycle value
void heatOn (void) {
	heatDutyCycle = heatOnDutyCycle;
	TIM_SetCompare1(PWMTimer,heatDutyCycle);
}

// Turn heat off
void heatOff(void) {
	heatOnDutyCycle = heatDutyCycle;
	heatDutyCycle = 0;
	TIM_SetCompare1(PWMTimer,heatDutyCycle);
}

