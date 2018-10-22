/* TEMPERATURE SENSOR INTERFACE
 * Final Year Thesis - EEE4022S
 * Anja Mühr (2018)
 */

/*
 * The "TM_..." functions used here are sourced from Tilen Majerle at https://github.com/MaJerle/stm32f429
 */


#include "tempSensor.h"

uint8_t ROM[8];							// unique ROM address of device
TM_OneWire_t OneWire;					// struct for 1-Wire protocol comms

// Initialise temperature sensor
void initTempSensor(void) {
	TM_OneWire_Init(&OneWire, GPIO_Temp, Pin_Temp);		// initialise 1-wire
	TM_OneWire_First(&OneWire);						// check for device on 1-wire
	TM_OneWire_GetFullROM(&OneWire, &ROM);				// get ROM address of sensor
	TM_DS18B20_SetResolution(&OneWire, &ROM, TM_DS18B20_Resolution_12bits);	// set resolution
}

// Return current temperature
float getTemperature(void) {
	float temp;
	TM_DS18B20_Start(&OneWire, &ROM);						// start temperature conversion
	while (!TM_DS18B20_AllDone(&OneWire));					// wait until line pulls high indicating completion
	while(!TM_DS18B20_Read(&OneWire, &ROM, &temp));		// read temperature (wait until line pulls high)
	return temp;
}
