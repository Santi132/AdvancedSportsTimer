#ifndef _BUTTONS_H_
#define _BUTTONS_H_
/*This holds the basic use of the buttons in the advanced sports timer*/

#include "stm32f030xc.h"

extern volatile unsigned int start;
extern volatile unsigned int lap_flag, lap_ms, lap_sec, lap_min;


/*initialize the PA3 pin to an external interrupt, that toggles start or stop*/
void button_init(void);
#endif
