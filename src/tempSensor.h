/* TEMPERATURE SENSOR INTERFACE HEADER
 * Final Year Thesis - EEE4022S
 * Anja Mühr (2018)
 */

/*
 * The "TM_..." functions and libraries used here are public domain: sourced from Tilen Majerle at https://github.com/MaJerle/stm32f429
 */

#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_

#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_onewire.h"
#include "tm_stm32f4_ds18b20.h"
#include "Greenhouse.h"

// temperature sensor PC1
#define GPIO_Temp GPIOC			// GPIO used for the temp sensor
#define Pin_Temp GPIO_Pin_1		// pin used
#define setTemp 20				// desired temperature
#define sensorCheckTime 10		// how often the temperature must be checked

// Initialise temperature sensor
void initTempSensor(void);

// Return current temperature
float getTemperature(void);

#endif /* TEMPSENSOR_H_ */
