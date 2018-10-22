/* FOGGER INTERFACE HEADER
 * Final Year Thesis - EEE4022S
 * Anja Mühr (2018)
 */

#ifndef FOGGER_H_
#define FOGGER_H_

#include "Greenhouse.h"

// fogger PC3
#define GPIO_Fogger GPIOC				// GPIO used for fogger
#define Pin_Fogger GPIO_Pin_3			// pin used
#define foggerOnTime 60                 // time with fogger on (seconds)
#define foggerTotalTime 180             // total fogger interval (i.e. time spent on + time spent off)


// Initialise fogger */
void initFogger(void);

// Turn fogger on (pull line high)
void foggerOn(void);

// Turn fogger off (pull line low)
void foggerOff(void);

#endif /* FOGGER_H_ */
