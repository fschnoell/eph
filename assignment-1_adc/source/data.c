/*
 * file name:	data.c
 * author: 		schaefer christian
 * date: 		10.05.2019
 */

#include "../include/data.h"
#define e_constant 2.71828182845904523536

/*
 * initializes a new series of data
 */
header* init_data_list()
{
    header *new_head  = (header *)malloc(sizeof(header));
    new_head->len   = 0;
    new_head->first = NULL;
    new_head->last  = NULL;
    return new_head;
}

/*
 * Adds a new item at the tail of the list
 */
data* insert_tail(header *header, data *new_item)
{
    /* check if the list does not contain any elements */
    if(header->len == 0)
    {
        header->first = new_item;
        header->last  = new_item;
        /* printf("[ DEBUG ] adding first element to the list with data %f\n", new_item->data); */
    }
    else
    {
        header->last->next = new_item;
        new_item->prev = header->last;
        header->last = new_item;
    /*    printf("[ DEBUG ] adding new element to the list with data %f\n", new_item->data); */
    }
    new_item->pos = header->len;
    header->len++;
    fprintf(stderr, "[ DEBUG ] new element added: %d\n", new_item->pos);        
    return new_item;
}

/*
 * creates a new data object and saves it to the series;
 * data* series: data list
 * voltage: voltage data
 * current: current data (set 0 if not available)
 */
data* new_data(double voltage, double current)
{
    data* new_set;

    new_set = (data *)malloc(sizeof(data));
    new_set->next = NULL;
    new_set->voltage = voltage;
    new_set->current = current;
    
    fprintf(stderr, "[ DEBUG ] saving new data: voltage: %f - current: %f\n", new_set->voltage, new_set->current);
    return new_set;
}

/*
 * calculates the respective current to the voltage 
 */
double calc_current(double voltage, double t, double resistor, double capacitor)
{
    double tau = resistor * capacitor;
    /*
    fprintf(stderr, "[ DEBUG ] voltage: \t%f \n", voltage);
    fprintf(stderr, "[ DEBUG ] resistor: \t%f \n", resistor);
    fprintf(stderr, "[ DEBUG ] time: \t%f \n", t);
    fprintf(stderr, "[ DEBUG ] tau:\t \t%f \n", tau);
    fprintf(stderr, "[ DEBUG ] t / tau:\t%f \n", (-1) * (t / tau));
    fprintf(stderr, "[ DEBUG ] e: \t \t%f \n", e_constant);
    fprintf(stderr, "[ DEBUG ] e function:\t %f \n", pow(e_constant, (-1) * (t / tau)));
    fprintf(stderr, "_________________________________________\n");
    */
    return (voltage / resistor * pow(e_constant, (-1) * ( t / tau )));
}

/*
 * calculates the voltage data of the whole series
 * charging_state: 
 * 1  if charging
 * -1 if discharging
 */
void calc_current_series(header* series, double interval_time, int charging_state)
{
    int i = 0;
    data* temp;
    temp = series->first;
    
    fprintf(stdout, "[ INFO ] calculating current series\n");

    for (;i < series->len; i++)
    {
        temp->current = calc_current(charging_state * temp->voltage, temp->pos * interval_time, resistor, capacitor);
        temp = temp->next;
    }
}

/* 
 * saves the measured voltage data to a file
 */
int save_voltage_series_to_file(header* series, char *filename)
{
    FILE* fData_log;
    int i = 0;
    data* temp;
    fprintf(stdout, "[ INFO ] saving voltage series to %s\n", filename);
    
    /* ab+ creates the file if it isn't existing */
    fData_log = fopen(filename, "ab+");

    if(NULL == fData_log)
    {
        fprintf(stderr, "[ DEBUG ] error opening file: %s\n", filename);
        return -1;
    }
    temp = series->first;
    for (;i < series->len; i++)
    {
        fprintf(fData_log, "%d\t%f\n", temp->pos, temp->voltage);
        fprintf(stderr, "[ DEBUG ] saving to file %d\t%f\n", i, temp->voltage);          
        temp = temp->next;
    }
    fclose(fData_log);
    return 0;
}

/* 
 * saves the calculated current data to a file
 */
int save_current_series_to_file(header* series, char *filename)
{
    FILE* fData_log;
    int i = 0;
    data* temp;
    fprintf(stdout, "[ INFO ] saving current series to %s\n", filename);
    
    /* ab+ creates the file if it isn't existing */
    fData_log = fopen(filename, "ab+");

    if(NULL == fData_log)
    {
        fprintf(stderr, "[ DEBUG ] error opening file: %s\n", filename);
        return -1;
    }
    fprintf(stderr, "[ DEBUG ] WEEEEEEEE current: \n");          
    temp = series->first;
    for (;i < series->len; i++)
    {
        fprintf(fData_log, "%d\t%f\n", temp->pos, temp->current);
        fprintf(stderr, "[ DEBUG ] saving to file %d\t%f\n", i, temp->current);          
        temp = temp->next;
    }
    
    fclose(fData_log);
    return 0;
}