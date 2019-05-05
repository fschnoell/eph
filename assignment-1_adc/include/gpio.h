/*
 * file name:	gpio.h
 * author: 		schaefer christian
 * date: 		05.05.2019
 */
#ifndef GPIO_H
#define GPIO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <wiringPi.h>
#include "../include/data_series.h"

extern int PIN_BASE;
extern int SPI_CHAN;

int     init();
int     readSPI();
int     saveSPI(int amount, int interval, char filename[]);
void    toggleGPIO(int pin);
int     set_gpio_high(int gpioPin);
int     set_gpio_low(int gpioPin);


#endif 