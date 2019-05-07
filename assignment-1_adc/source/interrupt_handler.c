/*
 * file name:	interrupt_handler.c
 * author: 		schaefer christian
 * date: 		07.05.2019
 */

#include "../include/interrupt_handler.h"

volatile enum KEY_CMD gl_keyCmd = NONE;

/* 
 * starts start_ir_listener() in a seperate thread
 */
int start_listener_thread()
{
    pthread_t pThread;
    return pthread_create(&pThread, NULL, start_ir_listener, NULL);
}

/* 
 * listener function waiting for keyboard interrupts
 */ 
int start_ir_listener()
{
    fprintf(stderr, "[ DEBUG ] starting to listen for keyboard inputs\n");

    while(1)
    {
        fflush(stdin);
        char key_press = getc(stdin);
        if(key_press == 's')
        {
            gl_keyCmd = START;
            fprintf(stderr, "[ DEBUG ] s pressed! \n");
        }
        else if(key_press == 'q')
        {
            gl_keyCmd = STOP;
            fprintf(stderr, "[ DEBUG ] q pressed! \n");
        }
    }
}