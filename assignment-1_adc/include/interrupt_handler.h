/*
 * file name:	interrupt_handler.h
 * author: 		schaefer christian
 * date: 		07.05.2019
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

/* "interrupt" key states */
enum KEY_CMD
{
    NONE, 
    START, 
    STOP
};

/* why volatile? - because we have global accessable variable which is used within a multi-threading application */
volatile enum KEY_CMD gl_keyCmd;

int start_listener_thread();
int start_ir_listener();
 

#endif