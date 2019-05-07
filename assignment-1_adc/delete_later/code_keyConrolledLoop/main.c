/*
 * A Simple multi-thread C-Programm to start a endless loop after
 * pressing the key s and stops after pressing the key q.
 * 
 * 
 * For threading the pthread library is used. Make shure to link the
 * library ("-lpthread")!
 * 
 * 
 * author: Michael Linortner 
 * date: 19. Feb 2019
 * 
 */
#include "countingLoop.h"

int main(){
	
	
	int res = startCountingLoop();
	
	return res;	
}