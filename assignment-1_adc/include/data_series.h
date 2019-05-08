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
#include <math.h>

#define e_constant 2.71828

typedef struct analog_value
{   
    int pos;
    double data;
    struct analog_value* next;
} analog_value;

double resistor;
double capacitor;

analog_value*   init_series();
analog_value*   new_data(analog_value* series, int val, char voltage_file[]);
double          calc_current(double voltage, double time, double resistor, double capacitor);
int             calculate_current_series(int interval, char input_log[], char output_log[], int charging_state);
int             save_to_file(int counter, double value, char* file);
int             check_file(char* filename);
void            set_capacitor(double value);
void            set_resistor(double value);

#endif