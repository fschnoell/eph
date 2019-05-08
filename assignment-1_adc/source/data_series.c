/*
 * file name:	voltage.h
 * author: 		schaefer christian
 * date: 		05.05.2019
 */

#include "../include/data_series.h"

/*
 * Takes an input (voltage data) file and calculates respectivly the current values
 * charging_state = 0 (charging)
 * charging_state = 1 (discharging)
 */
int calculate_current_series(int interval, char input_log[], char output_log[], int charging_state)
{
    int counter = 0;
    int voltage = 0;
    double current = 0;

    FILE* f_input_data;
    analog_value* calc_current_series = init_series();

    f_input_data = fopen(input_log, "r");

    if(NULL == f_input_data)
    {
        fprintf(stderr, "[ DEBUG ] error opening file for reading: %s\n", input_log);
        return -1;
    }
    fprintf(stderr, "[ DEBUG ] starting reading from file %s\n", input_log);
    while (fscanf(f_input_data, "%d\t%d", &counter, &voltage) != EOF)
    {
        fprintf(stderr, "[ DEBUG ] reading: counter:%d voltage: %d \n", counter, voltage);
        if(1 == charging_state)
        {
            voltage = voltage * (-1);
        }

        current = calc_current(voltage, counter * interval, resistor, capacitor);
        fprintf(stderr, "[ DEBUG ] calculated new current value: %f \n", current);
        new_data(calc_current_series, current, output_log);
    }

    fclose(f_input_data);
    return 0;
}
 
/*
 * calculates the respective current to the voltage 
 */
double calc_current(double voltage, double t, double resistor, double capacitor)
{
    double tau = resistor * capacitor;
    fprintf(stderr, "[ DEBUG ] voltage: %f \n", voltage);
    fprintf(stderr, "[ DEBUG ] time: %f \n", t);
    fprintf(stderr, "[ DEBUG ] resistor: %f \n", resistor);
    fprintf(stderr, "[ DEBUG ] capacitor: %f \n", capacitor);
    fprintf(stderr, "[ DEBUG ] voltage / resistor: %f \n", voltage / resistor);
    fprintf(stderr, "[ DEBUG ] tau %f \n", tau);

    fprintf(stderr, "[ DEBUG ] e function: %lf \n", pow(e_constant, (-1) * (t / tau)));

    

    return (voltage / resistor * pow(e_constant, (-1) * ( t / (resistor * tau))));
}


/*
 *  sets the global resistor value
 */
void set_resistor(double value)
{
    resistor = value;
}

/*
 *  sets the global capacitor value
 */
void set_capacitor(double value)
{
    capacitor = value;
}

/*
 * initializes a new series of data
 */
analog_value* init_series()
{
    analog_value* new_series = (analog_value *)malloc(sizeof(analog_value));
    new_series->pos = 0;
    new_series->next = NULL;
    new_series->data = 0;
    return new_series;
}

/*
 * creates a new data object and saves it to the series;
 */
analog_value* new_data(analog_value* series, int val, char* filename)
{
    analog_value* new_data;
    fprintf(stderr, "[ DEBUG ] saving new data: %d\n", val);

    new_data = (analog_value *)malloc(sizeof(analog_value));
    new_data->next = NULL;
    new_data->data = ( 3.3 / 1023) * (double)val ;
    new_data->pos = series->pos++;

    fprintf(stderr, "[ DEBUG ] adding to series: %f\n", new_data->data);

    series->next = new_data;
    
    if( NULL == filename || strlen(filename) < 1)
    {
        fprintf(stderr, "[ DEBUG ] no file provided, will not log!\n");
        return new_data;
    }

    if(save_to_file(new_data->pos, new_data->data, filename) == 0)
    {
        fprintf(stdout, "[ INFO ] saving new data: %f to %s\n", new_data->data, filename);   
        return new_data;    
    }
    else
    {
        fprintf(stderr, "[ DEBUG ] failed to save data!\n");
    }

    return new_data;
}

/* 
 * saves the actual values to the logger
 */
int save_to_file(int counter, double value, char* filename)
{
    FILE* fData_log;

    /* ab+ creates the file if it isn't existing */
    fData_log = fopen(filename, "ab+");

    if(NULL == fData_log)
    {
        fprintf(stderr, "[ DEBUG ] error opening file: %s\n", filename);
        return -1;
    }

    fprintf(fData_log, "%d\t%f\n", counter, value);

    fclose(fData_log);
    return 0;
}

/*
 * UNUSED
 * checks if the file is available and if we have correct permissions
 * return codes:
 *  0 - file ok & w+r permissions
 * -1 - file does not exist
 * -2 - file ok but no permissions
 */
int check_file(char* filename)
{
    if(access(filename, F_OK) != -1) 
    {
        fprintf(stderr, "[ DEBUG ] file exists %s\n", filename);
        
        if(access(filename, W_OK) != -1 && access(filename, R_OK) != -1)
        {
            fprintf(stderr, "[ DEBUG ] read & write permission set\n");
            return 0;
        }
        else
        {
            fprintf(stderr, "[ DEBUG ] file permissions not correct!\n");
            return -2;
        }        
    }
    
    fprintf(stderr, "[ DEBUG ] file does not exist %s\n", filename);
    return -1;
}