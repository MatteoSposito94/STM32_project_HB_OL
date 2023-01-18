/*
 * ePEBBs_pwm.h
 *
 *  Created on: Sep 21, 2022
 *      Author: andrea
 */

#ifndef INC_EPEBBS_PWM_H_
#define INC_EPEBBS_PWM_H_

#include "main.h"


#define SYS_CLOCK_FREQUENCY		72000000
#define PWM_FREQUENCY			20000			// CAMBIARE QUESTA FREQUENZA PER CAMBIARE LO SWITCHING

void GPIO_PWM_init(void);
void GPIO_PWM_init_v2(void);

void PWM_init(void);
void PWM_init_v2(void);


#endif /* INC_EPEBBS_PWM_H_ */
