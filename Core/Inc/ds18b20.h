/*
 * ds18b20.h
 *
 *  Created on: Feb 3, 2025
 *      Author: danie
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

void delay(uint16_t time);
uint8_t DS18B20_Init(void);
void DS18B20_Write(uint8_t data);
uint8_t DS18B20_Read(void);


#endif /* INC_DS18B20_H_ */
