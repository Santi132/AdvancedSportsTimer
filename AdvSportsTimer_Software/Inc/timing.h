/*This file handles the timing aspects of the
 * sports timer
 */

#ifndef _TIMING_H_
#define _TIMING_H_

#include "buttons.h"

//my defines
#define TIME_STR_SIZE 10
#define MIL_STR_START 6
#define SEC_STR_START 3
#define MIN_STR_START 0

extern char time_str[TIME_STR_SIZE];
extern char lap_str[TIME_STR_SIZE];
extern volatile unsigned int Milliseconds, Seconds, Minutes;

/*
 * The format for presenting the time to screen is min min:sec sec :ms ms ms
 * spaces there to show order
 */
void update_time_str(void);

void update_lap_str(void);

#endif
