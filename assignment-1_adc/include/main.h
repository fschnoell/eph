/*
 * file name:	main.h
 * author: 		schaefer christian
 * date: 		10.05.2019
 */
#ifndef MAIN_H
#define MAIN_H


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../include/gpio.h"
#include "../include/data.h"

extern header* charging_list;
extern header* discharging_list;

int main(void);

#endif