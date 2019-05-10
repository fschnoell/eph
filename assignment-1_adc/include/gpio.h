/*
 * file name:	gpio.h
 * author: 		schaefer christian
 * date: 		10.05.2019
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <wiringPi.h>
#include "../include/main.h"
#include "../include/data.h"
#include "../include/interrupt_handler.h"

extern int PIN_BASE;
extern int SPI_CHAN;

int     init();
int     readSPI();
int     save_spi_series(header* list, int amount, int interval);
void    toggleGPIO(int pin);
void    set_gpio_output(int gpioPin, int value);
double  bin_to_voltage(int binary);
#endif 