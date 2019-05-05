/*
 * file name:	voltage.h
 * author: 		schaefer christian
 * date: 		05.05.2019
 */

#include "../include/data_series.h"


/*
 * initializes a new series of data
 */
data* init_series()
{
    data* new_series = (data *)malloc(sizeof(data));
    new_series->pos = 0;
    new_series->next = NULL;
    new_series->value = 0;
    return new_series;
}

/*
 * creates a new data object and saves it to the series;
 */
data* new_data(data* series, int val, char* filename)
{
    data* new_data;
    fprintf(stderr, "[ DEBUG ] saving new data: %d\n", val);

    new_data = (data *)malloc(sizeof(data));
    new_data->next = NULL;
    new_data->value = val;
    new_data->pos = series->pos++;

    fprintf(stderr, "[ DEBUG ] adding to series\n");

    series->next = new_data;
    
    if(save_to_file(new_data->pos, new_data->value, filename) == 0)
    {
        fprintf(stdout, "[ INFO ] saving new data: %d to %s\n", new_data->value, filename);   
        return new_data;    
    }
    else
    {
        fprintf(stderr, "[ DEBUG ] failed to save data!\n");
    }
    return NULL;
}

/* 
 * saves the actual values to the logger
 */
int save_to_file(int counter, int value, char* filename)
{
    FILE* fData_log;

    /* ab+ creates the file if it isn't existing */
    fData_log = fopen(filename, "ab+");

    if(NULL == fData_log)
    {
        fprintf(stderr, "[ DEBUG ] error opening file: %s\n", filename);
        return -1;
    }

    fprintf(fData_log, "%d\t%d\n", counter, value);

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