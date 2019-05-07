/* 
 * author: Michael Linortner 
 * date: 19. Feb 2019
 * 
 */

#include "countingLoop.h"
#include "keyControlledLoop.h"
#include <stdio.h>


int startCountingLoop(void){

	return startKeyControlledLoop(&runCountingLoop);
}

int runCountingLoop()
{
	int i = 0;
	
	printf("start counting loop!\n");
	while(1)
	{
		printf("counting loop, i = %d\n", i++);
		for(int d = 0; d < 100000; d++); // just a delay loop
		if(gl_keyCmd == STOP)
		{
			break;
		}
	}
	printf("counting loop stopped!\n");
	return 0;
}