/*
 * ePEBBs_pwm.c
 *
 *  Created on: Sep 21, 2022
 *      Author: andrea
 */

#include "main.h"
#include "ePEBBs_pwm.h"


extern float duty_h;

/* PWM OL_HB
 *
 * PA8			-> TIM1_CH1		->		PWM_AH
 * PA10			-> TIM1_CH3		->		PWM_BH
 * PB13			-> TIM1_CH1N	->		PWM_AL
 * PB15			-> TIM1_CH3N	->		PWM_BL
 *
 */

void GPIO_PWM_init(void){

	RCC -> AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN);

	GPIOA -> MODER &=~ (GPIO_MODER_MODE8 | GPIO_MODER_MODE10);
	GPIOB -> MODER &=~ (GPIO_MODER_MODE13 | GPIO_MODER_MODE15);

	GPIOA -> MODER &=~ (GPIO_MODER_MODE8 | GPIO_MODER_MODE10);
	GPIOB -> MODER &=~ (GPIO_MODER_MODE13 | GPIO_MODER_MODE15);

	GPIOA -> MODER |= (GPIO_MODER_MODE8_1 | GPIO_MODER_MODE10_1);
	GPIOB -> MODER |= (GPIO_MODER_MODE13_1 | GPIO_MODER_MODE15_1);

	GPIOA -> OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR8 | GPIO_OSPEEDER_OSPEEDR10);
	GPIOB -> OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR13 | GPIO_OSPEEDER_OSPEEDR15);

	GPIOA -> AFR[1] |= ((1 << GPIO_AFRH_AFSEL8_Pos));
	GPIOA -> AFR[1] |= ((1 << GPIO_AFRH_AFSEL10_Pos));

	GPIOB -> AFR[1] |= ((1 << GPIO_AFRH_AFSEL13_Pos));
	GPIOB -> AFR[1] |= ((1 << GPIO_AFRH_AFSEL15_Pos));


}




void GPIO_PWM_init_v2(void){


}




void PWM_init(void){


	RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;

	TIM1 -> CCMR1 &=~ (TIM_CCMR1_CC1S | TIM_CCMR1_CC2S | TIM_CCMR1_OC1M | TIM_CCMR1_OC2M);
	TIM1 -> CCMR2 &=~ (TIM_CCMR2_CC3S | TIM_CCMR2_OC3M);

	TIM1 -> CCMR1 |= ((6 << TIM_CCMR1_OC1M_Pos) | (6 << TIM_CCMR1_OC2M_Pos));
	TIM1 -> CCMR2 |= ((6 << TIM_CCMR2_OC3M_Pos));

	TIM1 -> CCMR1 &=~ (TIM_CCMR1_CC1S | TIM_CCMR1_CC2S | TIM_CCMR1_OC1M | TIM_CCMR1_OC2M);
	TIM1 -> CCMR2 &=~ (TIM_CCMR2_CC3S | TIM_CCMR2_OC3M);

	TIM1 -> CCMR1 |= ((6 << TIM_CCMR1_OC1M_Pos) | (6 << TIM_CCMR1_OC2M_Pos));
	TIM1 -> CCMR2 |= ((6 << TIM_CCMR2_OC3M_Pos));

	TIM1 -> CCER |= TIM_CCER_CC1E | TIM_CCER_CC1NE | TIM_CCER_CC2E | TIM_CCER_CC2NE;
	TIM1 -> CCER |= TIM_CCER_CC3E | TIM_CCER_CC3NE;

	TIM1 -> CR1 &=~ TIM_CR1_CMS;
	TIM1 -> CR1 |= TIM_CR1_CMS_0;
	TIM1 -> PSC = 0;
	TIM1 -> ARR = (uint32_t)((SYS_CLOCK_FREQUENCY/(PWM_FREQUENCY*2)) & ~1);		// approssimare sempre a numero pari

	TIM1 -> CCR1 = (TIM1 -> ARR)/2;
	TIM1 -> CCR2 = (TIM1 -> ARR)/2;
	TIM1 -> CCR3 = (TIM1 -> ARR)/2;

	TIM1 -> BDTR |= TIM_BDTR_DTG_6 | TIM_BDTR_DTG_5 |TIM_BDTR_DTG_4 |TIM_BDTR_DTG_3 | TIM_BDTR_DTG_2 |TIM_BDTR_DTG_1 |TIM_BDTR_DTG_0;

	// Dead time 1.8uS per ponte ad H Leonardo

	TIM1 -> BDTR |= TIM_BDTR_MOE;

	TIM1 -> CR1 |= TIM_CR1_CEN;



}




void PWM_init_v2(void){


	RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;

	TIM1 -> CCMR1 &=~ (TIM_CCMR1_CC1S | TIM_CCMR1_CC2S | TIM_CCMR1_OC1M | TIM_CCMR1_OC2M);
	TIM1 -> CCMR2 &=~ (TIM_CCMR2_CC3S | TIM_CCMR2_OC3M);

	TIM1 -> CCMR1 |= ((3 << TIM_CCMR1_OC1M_Pos) | (3 << TIM_CCMR1_OC2M_Pos));
	TIM1 -> CCMR2 |= ((3 << TIM_CCMR2_OC3M_Pos));

	TIM1 -> CCER |= TIM_CCER_CC1E | TIM_CCER_CC1NE | TIM_CCER_CC2E | TIM_CCER_CC2NE;
	TIM1 -> CCER |= TIM_CCER_CC3E | TIM_CCER_CC3NE;

	TIM1 -> CCER |= TIM_CCER_CC2P | TIM_CCER_CC3P;

	TIM1 -> CR1 &=~ TIM_CR1_CMS;
	TIM1 -> CR1 |= TIM_CR1_CMS_0;
	TIM1 -> PSC = 0;
	TIM1 -> ARR = (uint32_t)(SYS_CLOCK_FREQUENCY/(PWM_FREQUENCY*2));		// approssimare sempre a numero pari

	TIM1 -> CCR1 = 0;
	TIM1 -> CCR2 = (TIM1 -> ARR);
	TIM1 -> CCR3 = (TIM1 -> ARR);

	TIM1 -> BDTR |= TIM_BDTR_MOE;

	TIM1 -> CR1 |= TIM_CR1_CEN;




}



