/*
 * servo.h
 *
 *  Created on: Feb 4, 2025
 *      Author: danie
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "main.h"

extern int pwmValue;				// use pwmValue variable declared in main.c
extern TIM_HandleTypeDef htim2;		// use htim2 variable declared in main.c

void toggle_power_button(void) {
	while (pwmValue > 1400) {	// Move arm to the right at constant speed
		pwmValue -= 5;
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwmValue);
		HAL_Delay(2);
	}

	while (pwmValue > 1200) {	// Once button is reached, hold down for 4 seconds
		pwmValue -= 5;			// to turn off AC by gradually pushing arm down
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwmValue);
		if (pwmValue > 1300) {
			HAL_Delay(200);
		}
		else {
			HAL_Delay(500);
		}
	}
	while (pwmValue < 2500) {	// Arm goes back to initial state after button press
		pwmValue += 5;
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwmValue);
		HAL_Delay(2);
	}
}

#endif /* INC_SERVO_H_ */
