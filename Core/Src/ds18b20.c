/*
 * ds18b20.c
 *
 *  Created on: Feb 3, 2025
 *      Author: danie
 */
#include "main.h"
#include "ds18b20.h"

extern TIM_HandleTypeDef htim6;

#define DS18B20_PORT GPIOA
#define DS18B20_PIN GPIO_PIN_4

void delay(uint16_t time)
{
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	while ((__HAL_TIM_GET_COUNTER(&htim6)) < time);
}

uint8_t DS18B20_Init(void)
{
	uint8_t response = 0;
	set_pin_output(DS18B20_PORT, DS18B20_PIN);
	HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);
	delay(480);

	set_pin_input(DS18B20_PORT, DS18B20_PIN);
	delay(80);

	if (!(HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN)))
	{
		response = 1;
	}
	else
	{
		response = -1;
	}

	delay(400);		// 80 + 400 = 480us delay
	return response;
}

void DS18B20_Write(uint8_t data)
{
	set_pin_output(DS18B20_PORT, DS18B20_PIN);

	for (int i = 0; i < 8; i++)
	{
		if ((data & (1<<i)) != 0) // if i-th bit is high, write 1
		{
			set_pin_output(DS18B20_PORT, DS18B20_PIN);
			HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);
			delay(1);	// pull low for 1us

			set_pin_input(DS18B20_PORT, DS18B20_PIN);
			delay(50);	// then release pin for 60us
		}
		else // if i-th bit is low, write 0
		{
			set_pin_output(DS18B20_PORT, DS18B20_PIN);
			HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);
			delay(50);	// pull low for 60us

			set_pin_input(DS18B20_PORT, DS18B20_PIN);	// then release pin
		}
	}
}

uint8_t DS18B20_Read(void)
{
	uint8_t value = 0;

	set_pin_input(DS18B20_PORT, DS18B20_PIN);

	for (int i = 0; i < 8; i++)
	{
		set_pin_output(DS18B20_PORT, DS18B20_PIN);

		HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);
		delay(1);

		set_pin_input(DS18B20_PORT, DS18B20_PIN);
		if (HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN)) // if pin is high, read 1
		{
			value |= 1<<i;
		}
		delay(50);
	}
	return value;
}
