/*
 * file name:	gpio.c
 * author: 		schaefer christian
 * date: 		05.05.2019
 */
#include "../include/gpio.h"

/* variable declarations - default values */
int PIN_BASE = 100;
int SPI_CHAN = 0;
data* series;

/*
 * initializes the gpio library and interfaces
 * returns 0 if successfull
 */
int init()
{
    int ret = wiringPiSetup();
    series = init_series();

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
int saveSPI(int amount, int interval, char filename[])
{
    int i;
    if(NULL == series)
    {
        fprintf(stderr, "[ DEBUG ] series is NULL!\n");
        return -1;
    }

    if(NULL == filename || strlen(filename) < 1 )
    {
        fprintf(stderr, "[ DEBUG ] no file specified - will not save\n");
        filename = NULL;
    }
    else
    {
        fprintf(stderr, "[ DEBUG ] saving values to %s\n", filename);
    }

    for(i = 0; i < amount; i++)
    {
        new_data(series, readSPI(), filename);
        delayMicroseconds(interval);
    }
    return 0;
}

/*
 * reads and returns the SPI value;
 */
int readSPI()
{    
    return analogRead(PIN_BASE + SPI_CHAN);
}

/*
 * toggles a pin within a loop
 */
void toggleGPIO(int gpioPin)
{
    pinMode(gpioPin, OUTPUT);

    for(;;)
    {
        fprintf(stderr, "[ DEBUG ] Toggle: on ... "); 
        digitalWrite(gpioPin, HIGH);
        fprintf(stderr, "of\n"); 
        delay(1000);
        digitalWrite(gpioPin, LOW);
    }
}

/* 
 * switches on a gpio pin
 */ 
int set_gpio_high(int gpioPin)
{
    fprintf(stderr, "[ DEBUG ] Set Pin %d to HIGH\n", gpioPin); 
    pinMode(gpioPin, OUTPUT);
    digitalWrite(gpioPin, HIGH);
    return 0;
}

/* 
 * switches off a gpio pin
 */ 
int set_gpio_low(int gpioPin)
{
    fprintf(stderr, "[ DEBUG ] Set Pin %d to LOW\n", gpioPin); 
    pinMode(gpioPin, OUTPUT);
    digitalWrite(gpioPin, LOW);
    return 0;
}