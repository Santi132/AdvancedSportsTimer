#ifndef _LCD_H_
#define _LCD_H_

//includes
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_gpio.h"
#include "stm32f0xx.h"

//Stuff for the RS Pin
#define RS_PIN_NUM GPIO_PIN_8
#define RS_PIN_PORT GPIOA

//Stuff for the EN pin
#define EN_PIN_NUM GPIO_PIN_9
#define EN_PIN_PORT GPIOA

//The RW pin
#define RW_PIN_NUM GPIO_PIN_1
#define RW_PIN_PORT GPIOB

//Data line GPIOS
#define D4_PIN_NUM GPIO_PIN_10
#define D4_PIN_PORT GPIOA
#define D5_PIN_NUM GPIO_PIN_11
#define D5_PIN_PORT GPIOA
#define D6_PIN_NUM GPIO_PIN_12
#define D6_PIN_PORT GPIOA
#define D7_PIN_NUM GPIO_PIN_15
#define D7_PIN_PORT GPIOA

//Writes out a byte and nybble respectively
void write_instr_byte(unsigned char byte);
void print_byte(unsigned char byte);
//Writes the corresponding pins according to the 4 bits passed
void write_nybble(unsigned char nibble);

//prints characters to the screen
void print_string(char * str);

//Toggles on the enable pin and waits 2 milliseconds
void toggle_EN(void);

//Initialize the screen 
void LCD_init(void);

//Move the cursor position
void move_cursor(unsigned char position);

//resets the position of the cursor
void cursor_toHome(void);

//clears the display
void clear_screen(void);

#endif
