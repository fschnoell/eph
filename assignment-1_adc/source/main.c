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
    char *f_char_current_curve =  "/home/scct/eph/assignment-1_adc/data/cap_char_current.log";
    char *f_dis_current_curve =  "/home/scct/eph/assignment-1_adc/data/cap_dis_current.log";

    init(1000, 47e-06);

    /* these values will not be saved */
    /* saveSPI(10, 500, NULL); */


    set_gpio_high(BCM26); 
    /* charging curve */
    saveSPI(1024, 100, f_charging_curve);

    /* discharging curve */
    set_gpio_low(BCM26);
    saveSPI(1024, 100, f_discharging_curve);

    /* we cannot directly measure the current with the adc, so we have to calculate it afterwards */
    calculate_current_series(100, f_charging_curve, f_char_current_curve, 0);
    /* calculate_current_series(100, f_discharging_curve, f_dis_current_curve, 1); */



    return 0;
}
