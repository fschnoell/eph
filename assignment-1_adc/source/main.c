/*
 * file name:	main.c
 * author: 		schaefer christian
 * date: 		28.04.2019
 */

#include "../include/main.h"

int main(void)
{
    init();

    char f_test_data[] = "../data/test_data.log";

    /* these values will not be saved */
    saveSPI(10, 500, NULL);

    /* these values will be saved to ../data/test_data.log */
    saveSPI(10, 500, f_test_data);

    return 0;
}

