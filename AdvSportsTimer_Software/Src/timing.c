#include "timing.h"

char time_str[TIME_STR_SIZE];
char lap_str[TIME_STR_SIZE];

void update_time_str(void){
	unsigned int temp_s = Seconds, temp_ms = Milliseconds, temp_m = Minutes;
	time_str[MIN_STR_START+1] = '0' + temp_m%10;
	temp_m /= 10;
	time_str[MIN_STR_START] = '0' + temp_m%10;

	time_str[2] = ':';

	time_str[SEC_STR_START+1] = '0' + temp_s%10;
	temp_s /= 10;
	time_str[SEC_STR_START] = '0' + temp_s%10;

	time_str[5] = ':';

	time_str[MIL_STR_START+2] = '0' + temp_ms%10;
	temp_ms /= 10;
	time_str[MIL_STR_START+1] = '0' + temp_ms%10;
	temp_ms /= 10;
	time_str[MIL_STR_START] = '0' + temp_ms%10;

	time_str[TIME_STR_SIZE-1] = '\0';
}

void update_lap_str(void){
	unsigned int temp_s = lap_sec, temp_ms = lap_ms, temp_m = lap_min;
	lap_str[MIN_STR_START+1] = '0' + temp_m%10;
	temp_m /= 10;
	lap_str[MIN_STR_START] = '0' + temp_m%10;

	lap_str[2] = ':';

	lap_str[SEC_STR_START+1] = '0' + temp_s%10;
	temp_s /= 10;
	lap_str[SEC_STR_START] = '0' + temp_s%10;

	lap_str[5] = ':';

	lap_str[MIL_STR_START+2] = '0' + temp_ms%10;
	temp_ms /= 10;
	lap_str[MIL_STR_START+1] = '0' + temp_ms%10;
	temp_ms /= 10;
	lap_str[MIL_STR_START] = '0' + temp_ms%10;

	lap_str[TIME_STR_SIZE-1] = '\0';
}


