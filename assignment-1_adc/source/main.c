/*
 * file name:	main.c
 * author: 		schaefer christian
 * date: 		05.05.2019
 */

#include "../include/main.h"

/* wiringPi Pin enumeration */
#define BCM26 25

/* to calculate the current we need to measure the overall voltage (over R & C) --> Channel 4 @ ADC
 * to be done
 * 
 * 
 */

int main(void)
{
    char *f_charging_curve = "/home/scct/eph/assignment-1_adc/data/cap_charging_curve.log";
    char *f_discharging_curve = "/home/scct/eph/assignment-1_adc/data/cap_discharging_curve.log";

    init();

    /* these values will not be saved */
    /* saveSPI(10, 500, NULL); */


    set_gpio_high(BCM26); 
    /* charging curve */
    saveSPI(1024, 100, f_charging_curve);

    /* discharging curve */
    set_gpio_low(BCM26);
    saveSPI(1024, 100, f_discharging_curve);

    return 0;
}
