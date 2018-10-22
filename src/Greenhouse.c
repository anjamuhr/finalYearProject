/* OVERALL GREENHOUSE FUNCTIONS
 * Final Year Thesis - EEE4022S
 * Anja Mühr (2018)
 */

#include "Greenhouse.h"


int stateGermination = 1;	             // 0 if germination is complete, 1 if not


// Configure everything
void configGreenhouse(void) {

	initTempSensor();		// initialise temp sensor

	initFan();				// initialise fan

	initLEDs();				// initialise LEDs

	initHeat();				// initialise heat sink fan

	initFogger();			// initialise fogger

	initTimers();			// initialise timers

	foggerOn();				// start fogger

}

// Initialise timers for PWM and interrupts
void initTimers(void) {

	initTimer(PWMTimer, 8399, 0);
	initPWMChannel(PWMTimer, stdFanDutyCycle, 2);				// channel 2 for PA1 (fan)
	initPWMChannel(PWMTimer, stdLEDDutyCycle, 4);				// channel 4 for PA3 (LEDs)
	initPWMChannel(PWMTimer, stdHeatDutyCycle, 1);				// channel 1 for PA7 (heat)

	// Timer 3 set up @ 1Hz
	stdTimer(TIM3, 10000, 8400);

	// Timer 7 set up @ 1Hz
	stdTimer(TIM7, 10000, 8400);
}

// Called if measured temp is greater than desired temp == attempts to cool down greenhouse
void tooHot(void){

	if (decreaseLight()){} 						// don't turn off completely = don't want to deprive plants of light
	else if (increaseHeatFan()) {}				// increase heat fan speed to dissapate heat from sink faster
	else { increaseFanSpeed(); }				// increase air flow fan speed
}

// Called if measured temp is less than desired temp == attempts to warm up greenhouse
void tooCold(void) {

	if (increaseLight()) {}						// increase brightness of LEDs
	else if (decreaseFanSpeed()) {}				// reduce airflow fan speed
	else { decreaseHeatFan(); }					// reduce heat sink fan last (don't want the LEDs to overheat)

}

// return whether germination has occured or not
int getStateGermination(void) {
	return stateGermination;
}

// germination has not occured
void setStateGermination(void) {
	stateGermination = 1;
}

// germination has occured
void clearStateGermination(void) {
	stateGermination = 0;
}









