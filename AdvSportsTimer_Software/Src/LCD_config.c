#include "LCD_config.h"

void write_instr_byte(unsigned char byte){
	unsigned char lowestNybble;
	unsigned char highestNybble;
	lowestNybble = byte & 0x0F;
	highestNybble = (byte>>4) & 0x0F;
	write_nybble(highestNybble);
	toggle_EN();
	write_nybble(lowestNybble);
	toggle_EN();
}

void print_byte(unsigned char byte){
	//seperate the two nibbles(4-bits)
	unsigned char lowestNybble;
	unsigned char highestNybble;
	lowestNybble = byte & 0x0F;
	highestNybble = (byte>>4) & 0x0F;

	//write the highesr 4 bits and toggle the rs and en
	write_nybble(highestNybble);
	HAL_GPIO_TogglePin(RS_PIN_PORT, RS_PIN_NUM);
	toggle_EN();
	HAL_GPIO_TogglePin(RS_PIN_PORT, RS_PIN_NUM);

	//now the lowest 4 bits
	write_nybble(lowestNybble);
	HAL_GPIO_TogglePin(RS_PIN_PORT, RS_PIN_NUM);
	toggle_EN();
	HAL_GPIO_TogglePin(RS_PIN_PORT, RS_PIN_NUM);
}

void write_nybble(unsigned char nybble){
	HAL_GPIO_WritePin(D7_PIN_PORT,D7_PIN_NUM,(nybble>>3)&1);
	HAL_GPIO_WritePin(D6_PIN_PORT,D6_PIN_NUM,(nybble>>2)&1);
	HAL_GPIO_WritePin(D5_PIN_PORT,D5_PIN_NUM,(nybble>>1)&1);
	HAL_GPIO_WritePin(D4_PIN_PORT,D4_PIN_NUM,nybble&1);
}

void toggle_EN(void){
	HAL_GPIO_TogglePin(EN_PIN_PORT, EN_PIN_NUM);
	for(int i = 0; i < 2000; i++);
	HAL_GPIO_TogglePin(EN_PIN_PORT, EN_PIN_NUM);
	for(int i = 0; i < 2000; i++);
}

void LCD_init(void){
	//make sure that the RW is low to signal a write
	HAL_GPIO_WritePin(RW_PIN_PORT, RW_PIN_NUM, GPIO_PIN_RESET);
	write_instr_byte(0x02);
	write_instr_byte(0x28);
	write_instr_byte(0x0C);
//	write_instr_byte(0x06);
	write_instr_byte(0x02);
}

void print_string(char * str){
	int i = 0;
	while(str[i] != '\0'){
		print_byte(str[i]);
		i++;
	}
}

void cursor_toHome(void){
	//write_instr_byte(0x01);
	write_instr_byte(0x02); //put cursor back to the original spot
}

void move_cursor(unsigned char position){
	unsigned char n_position = 0x80 + position;
	write_instr_byte(0xFE);
	write_instr_byte(n_position);
}

void clear_screen(void){
	write_instr_byte(0x01);
	write_instr_byte(0x02);
}
