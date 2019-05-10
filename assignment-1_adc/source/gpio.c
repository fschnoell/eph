/*
 * file name:	gpio.c
 * author: 		schaefer christian
 * date: 		10.05.2019
 */

#include "../include/gpio.h"

#define gpio_voltage 3.3

/* variable declarations - default values */
int PIN_BASE = 100;
int SPI_CHAN = 0;



/*
 * initializes the gpio library and interfaces
 * returns 0 if successfull
 */
int init()
{
    int ret = wiringPiSetup();

    if(ret)
    {
        fprintf(stderr, "[ DEBUG ] error while initializing wiringPi library: %d\n", ret);
        return -1;
    }
    if(!mcp3004Setup(PIN_BASE, SPI_CHAN))
    {
        fprintf(stderr, "[ DEBUG ] error while mcp3004 setup\n");
        return -2;
    }
    fprintf(stdout, "[ INFO ] initialization successfull!\n");
    return 0;
}

/*
 * saves a defined amount of values in a file with a given interval (in us)
 * eg:../data/spi_values.
 */
int save_spi_series(header* data_list, int amount, int interval)
{
    int i;
    fprintf(stdout, "[ INFO ] starting to save data from spi\n");

    if(NULL == data_list)
    {
        fprintf(stderr, "[ DEBUG ] series is NULL!\n");
        return -1;
    }

    for(i = 0; i < amount; i++)
    {
        /* save data here */
        /* new_data(data_list, bin_to_voltage(analogRead(PIN_BASE + SPI_CHAN)) ,0); */
        /* insert_tail(data_list, new_data(analogRead(PIN_BASE + SPI_CHAN), 0));   */    
        insert_tail(data_list, new_data(bin_to_voltage(analogRead(PIN_BASE + SPI_CHAN)), 0));  

        delayMicroseconds(interval);
    }
    return 0;
}

/* 
 * converts the read value (0-1023) into actual voltage values
 */
double bin_to_voltage(int binary)
{
     return ( gpio_voltage / 1023) * (double)binary ;
}

/*
 * sets a gpio high or low 
 * int gpioPin: wiringPi Pin enumeration!
 * int value:   1 (high) or 0 (low)
 */
void set_gpio_output(int gpioPin, int value)
{
    fprintf(stderr, "[ DEBUG ] Set Pin %d to %d\n", gpioPin, value); 
    pinMode(gpioPin, OUTPUT);
    digitalWrite(gpioPin, value);
}