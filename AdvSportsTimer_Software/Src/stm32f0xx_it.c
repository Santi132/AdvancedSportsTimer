/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#include "stm32f0xx_it.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
volatile unsigned int Milliseconds, Seconds, Minutes;
volatile unsigned int start;
volatile unsigned int lap_flag, lap_ms, lap_sec, lap_min;
Mode timer_mode = NORMAL;
volatile unsigned int clear_screen_flag, time_up_flag;

/******************************************************************************/
/*            Cortex-M0 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
	if(start){
		if(timer_mode){
			if(Milliseconds == 0){
				if(Seconds == 0){
					//Out of seconds
					if(Minutes == 0){
						//Times up
						time_up_flag = 1;
						start = 0;
					}
					else{
						Minutes--;
						Seconds = 59;
					}
				}
				else{
					//still have some seconds
					Seconds--;
					Milliseconds = 999;
				}
			}
			else{
				Milliseconds--;
			}
		}
		else{
			Milliseconds++;
			if(Milliseconds == 1000){
				Seconds++;
				Milliseconds = 0;
			}
			if(Seconds == 60){
				Minutes++;
				Seconds = 0;
			} 
			if(Minutes == 60){
				Minutes = 0;
			}
		}
	}
	
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */
void EXTI2_3_IRQHandler(void){
	//check to see if the correct line was triggered
	if((EXTI->IMR & EXTI_IMR_MR2) && (EXTI->PR & EXTI_PR_PR2)){
		//PA2 was triggered
		if(start){
			start = 0; //STOP
			lap_flag = 0;
			lap_min = 0;
			lap_sec = 0;
			lap_ms = 0;
		}
		else{
			start = 1; //START
			clear_screen_flag = 1;
		}
		while(GPIOA->IDR & GPIO_IDR_2){}
		EXTI->PR |= EXTI_PR_PR2;
	}
	else{
		//PA3 was triggered
		if(timer_mode){
			//were in COUNTDOWN mode
			if(Seconds > 30){
				Minutes++;
				Seconds = Seconds - 30;
			}
			else{
				Seconds += 30;
				if(Seconds == 60){
					Minutes++;
					Seconds = 0;
				}
			}
		}
		else{	
			lap_flag = 1;
			lap_min = Minutes;
			lap_sec = Seconds;
			lap_ms = Milliseconds;
		}
		while(GPIOA->IDR & GPIO_IDR_3){}
		EXTI->PR |= EXTI_PR_PR3;
	}
}

void EXTI0_1_IRQHandler(void){
	if((EXTI->IMR & EXTI_IMR_MR0) && (EXTI->PR & EXTI_PR_PR0)){
		//PA0 was triggered change the mode
		if(timer_mode){ //is it in COUNTDOWN mode
			//right now there is only two modes, might add some later
			timer_mode = NORMAL;
		}
		else{
			timer_mode = COUNTDOWN;
		}
		Minutes = 0;
		Seconds = 0;
		Milliseconds = 0;
		clear_screen_flag = 1;
		while(GPIOA->IDR & GPIO_IDR_0){}
		EXTI->PR |= EXTI_PR_PR0;
	}
	else{
		//PA1 was triggered
		//show heartbeat?
		if(timer_mode){
			//COUNTDOWN mode
			if(Seconds < 30){
				if(Minutes != 0){
					Minutes--;
					Seconds = 30 + Seconds;
				}
			}
			else{
				Seconds -= 30;
			}
		}
		while(GPIOA->IDR & GPIO_IDR_1){}
		EXTI->PR |= EXTI_PR_PR1;
	}
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
