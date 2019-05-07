/* 
 * 
 * author: Michael Linortner 
 * date: 19. Feb 2019
 * 
 */

#include "keyControlledLoop.h"
#include "countingLoop.h"
#include<pthread.h>
#include<stdio.h>

volatile enum KEY_CMD gl_keyCmd = NONE;

int startKeyControlledLoop(int (*f)())
{
	
	// start the thread to read from keyboard input
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
	int thrId;
	pthread_t pThread;
	
	thrId = pthread_create(&pThread, NULL, readKeyboardCmd, NULL);
	#pragma GCC diagnostic pop
	
	
	// loop to wait for start command
	int bQuite = 0;
	int returnCode = -1;
	
	while(!bQuite)
	{
		switch(gl_keyCmd)
		{
			case START:	
			{ 
				returnCode = f(); // leave the loop when function f returns!
				bQuite = 1;
				break; 
			} 
			case STOP:
			{
				bQuite = 1;
				break;
			}
			default: break;
		}
	}
	
	printf("key controlled loop stopped!\n");
	return returnCode;
}

/*
 * Uses the function getchar() to read from inputstream of the console (keyboard). After pressing enter, getchar() returns every single character from the input stream.
 */
void* readKeyboardCmd(void* data)
{

	char key = '\0';
	
	printf("Press 's' to start, 'q' to stop + ENTER\n");
	printf("wait for input > ");
	
	while(1)
	{

		int keyCounter = 0;
		
		while(1){ 
			
			char keyvalue = getchar(); // read character from inputstream (keyboard). This funktion blocks!
			if(keyvalue == 10 || keyvalue == 13){
				// we received a line feed or carriage return character, end of input sequence reached
				break;
			}
			key = keyvalue;
			keyCounter++;
		}
		if(keyCounter > 1)
		{
			// we only listen to single character commands, all others anyway invalid input!
			printf("wait for input > ");
			continue;
		}
	
		if(key == 's')
		{
			gl_keyCmd = START;
			printf("received START command!\n");
			printf("wait for input > ");
		}
		else if(key == 'q')
		{
			gl_keyCmd = STOP;
			printf("received STOP command!\n");
			//printf("wait for input > ");
		}
		
	}
}