/* LED GROW LIGHTS INTERFACE
 * Final Year Thesis - EEE4022S
 * Anja Mühr (2018)
 */

#include "leds.h"

int LEDDutyCycle = stdLEDDutyCycle;		// current LED duty cycle (for PWM) - off at start

// Initialise LEDs (GPIO pin & PWM)
void initLEDs(void) {

	// initialise PWM GPIO pin
	initGPIO(GPIO_LEDs, Pin_LEDs, GPIO_Mode_AF, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_50MHz);
	// connect GPIO pin to PWM timer
	GPIO_PinAFConfig(GPIO_LEDs, getPinSource(Pin_LEDs), getAFTimer(PWMTimer));

}

// Increase led brightness (increment duty cycle)
int increaseLight(void) {

	if (LEDDutyCycle < maxLEDDutyCycle) {	// check brightness is not at maximum
		LEDDutyCycle = LEDDutyCycle +200;
		TIM_SetCompare4(PWMTimer,LEDDutyCycle);
		return 1;
	} else return 0;
}

// Decrease led brightness (decrement duty cycle)
int decreaseLight(void) {

	if (LEDDutyCycle > minLEDDutyCycle) {	// check brightness is not at minimum
		LEDDutyCycle = LEDDutyCycle - 200;
		TIM_SetCompare4(PWMTimer,LEDDutyCycle);
		return 1;
	} else return 0;
}

// Turn lights off
void turnLightsOff(void) {

	LEDDutyCycle = 0;
	TIM_SetCompare2(PWMTimer,LEDDutyCycle);
}

// Turn lights on to std brightness
void turnLightsOn(void) {

	LEDDutyCycle = stdLEDDutyCycle;
	TIM_SetCompare2(PWMTimer,LEDDutyCycle);

}


