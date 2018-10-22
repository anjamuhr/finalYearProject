/* FOGGER INTERFACE
 * Final Year Thesis - EEE4022S
 * Anja Mühr (2018)
 */

#include "fogger.h"

// Initialise fogger
void initFogger(void) {
	// initialise fogger GPIO pin
	initGPIO(GPIO_Fogger, Pin_Fogger, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_50MHz);

}

// Turn fogger on (pull line high)
void foggerOn(void) {
	GPIO_WriteBit(GPIO_Fogger, Pin_Fogger, Bit_SET);
	fanOff();		// turn fans off to minimise mist loss
	heatOff();
}

// Turn fogger off (pull line low)
void foggerOff(void) {
	GPIO_WriteBit(GPIO_Fogger, Pin_Fogger, Bit_RESET);
	fanOn();		// turn fans back on
	heatOn();
}
