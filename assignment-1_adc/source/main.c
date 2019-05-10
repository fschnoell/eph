/*
 * file name:	main.c
 * author: 		schaefer christian
 * date: 		10.05.2019
 */

#include "../include/main.h"

/* wiringPi Pin enumeration */
#define BCM26 25

header* charging_list;
header* discharging_list;

int main(void)
{
    char *f_charge_voltage       = "/home/scct/eph/assignment-1_adc/data/f_charge_voltage.log";
    char *f_charge_current       = "/home/scct/eph/assignment-1_adc/data/f_charge_current.log";
    char *f_dis_charge_voltage   = "/home/scct/eph/assignment-1_adc/data/f_discharge_voltage.log";
    char *f_dis_charge_current   = "/home/scct/eph/assignment-1_adc/data/f_discharge_current.log";

    init();
    charging_list = init_data_list();
    discharging_list = init_data_list();
    
    resistor  = 1000;
    capacitor = 47e-06;
    
    /* charging curve */
    set_gpio_output(BCM26, 1); 
    save_spi_series(charging_list, 1024, 100);
    
    /* calculate currente */
    calc_current_series(charging_list, 100e-06, 1);

    /* save results to file */
    save_voltage_series_to_file(charging_list, f_charge_voltage);
    save_current_series_to_file(charging_list, f_charge_current);
    
    /* discharging curve */     
    set_gpio_output(BCM26, 0); 
    save_spi_series(discharging_list, 1024, 100);

     /* calculate currente */
    calc_current_series(discharging_list, 100e-06, -1);

    /* save results to file */
    save_voltage_series_to_file(discharging_list, f_dis_charge_voltage);
    save_current_series_to_file(discharging_list, f_dis_charge_current);

  

    return 0;
}
