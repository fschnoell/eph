/*
 * file name:	main.c
 * author: 		schaefer christian
 * date: 		05.05.2019
 */

#include "../include/main.h"

int main(void)
{
    char *f_test_data = "/home/scct/eph/assignment-1_adc/data/test_data.log";

    init();

    /* these values will not be saved */
    /* saveSPI(10, 500, NULL); */

    /* these values will be saved to ../data/test_data.log */
    saveSPI(10, 500*10*100, f_test_data);

    return 0;
}

