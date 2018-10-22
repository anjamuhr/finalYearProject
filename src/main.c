/* MAIN
 * Final Year Thesis - EEE4022S
 * Anja Mühr (2018)
 */

#include "Greenhouse.h"

int foggerCount = 0;               		// counting variable for turning fogger on and off
int lightCount = 0;               		// counting variable for turning lights on and off
int sensorCount = 0;               		// counting variable for checking temp
int hourCount = 0;						// counting variable for calculating hours for turning lights on and off

float temp;								// current temperature

/*******************************************************************************
TIM2_IRQHandler
-- handles fogger & temperature check
*******************************************************************************/
void TIM3_IRQHandler(void) {

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {	// check for interrupt

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);			// clear interrupt pending bit
	//	GPIO_ToggleBits(GPIOD, GPIO_Pin_15);

		if (foggerCount < foggerTotalTime) {
			if (foggerCount == foggerOnTime) {
				foggerOff();		// turn off fogger
			}
			foggerCount ++;
		} else {
			// interval has elapsed so reset
			foggerOn();			// turn on fogger for new interval
			foggerCount = 0;
		}

		if (sensorCount < sensorCheckTime) {			// check temp
			sensorCount++;

		} else {
		temp = getTemperature();					// get temperature & check boundaries
			if (temp > setTemp) {
				tooHot();								// if too hot, cool down
			} else if (temp < setTemp){
				tooCold();								// if too cold, warm up
			}
			sensorCount = 0;
		}

	}
}

/*******************************************************************************
TIM7_IRQHandler
-- handles grow lights
*******************************************************************************/

void TIM7_IRQHandler(void) {

	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)		// check for interrupt
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);			// clear interrupt pending bit
	//	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);

		if (hourCount < 3599) {			// check if an hour has passed
					hourCount++;

		} else {

			hourCount = 0;


			// check if germination has occurred (i.e. 48 hours of darkness)

			/*	if (getStateGermination()) {
					if (lightCount < germTime) {
						lightCount++;
					} else {
						lightCount = 0;
						clearStateGermination();
						turnLightsOn();		// turn on LEDs after germTime is up
					}
				} else  { }*/

			if (lightCount < lightTotalTime) {
				if (lightCount == lightOnTime) {
					turnLightsOff();		// turn off LEDs for "night time"
				}
				lightCount++;
			} else {
				// interval has elapsed so reset
				turnLightsOn();			// turn on LEDs for new interval
				lightCount = 0;
			}

		}

	}
}


/* --------------------------------------- MAIN --------------------------------------------*/

int main(void) {

	// Initialisations


	initAllLEDsStd();

  	configGreenhouse();


	for (;;)	{	}

	return 0;
}


/* --------------------------------------- END ---------------------------------------------*/
