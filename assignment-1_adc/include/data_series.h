/*
 * file name:	voltage.h
 * author: 		schaefer christian
 * date: 		28.04.2019
 */
#ifndef VOLTAGE_H
#define VOLTAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct data
{   
    int pos;
    int value;
    struct data* next;
} data;

data*   init_series();
data*   new_data(data* series, int val, char filename[]);
int     save_to_file(int counter, int value, char* filename);
int     check_file(char* filename);

#endif