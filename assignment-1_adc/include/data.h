/*
 * file name:	data.h
 * author: 		schaefer christian
 * date: 		10.05.2019
 */

#ifndef DATA_H
#define DATA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

typedef struct header
{
    int len;
    struct data* first;
    struct data* last;
} header;

typedef struct data
{   
    int pos;
    double voltage;
    double current;
    struct data* next;
    struct data* prev;
} data;

double resistor;
double capacitor;

header*     init_data_list();
data*       new_data(double voltage, double current);
data*       insert_tail(header *header, data *new_item);
double      calc_current(double voltage, double time, double resistor, double capacitor);
void        calc_current_series(header* series, double interval_time, int charging_state);
int         save_voltage_series_to_file(header* series, char *filename);
int         save_current_series_to_file(header* series, char *filename);


/*
data*           new_data(data* series, int val, char voltage_file[]);
double          calc_current(double voltage, double time, double resistor, double capacitor);
int             calculate_current_series(int interval, char input_log[], char output_log[], int charging_state);
int             save_to_file(int counter, double value, char* file);
int             check_file(char* filename);
void            set_capacitor(double value);
void            set_resistor(double value);
*/
#endif