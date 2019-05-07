/* 
 * Functions to start a thread for listening on keyboard and starting a function f.
 * 
 * author: Michael Linortner 
 * date: 19. Feb 2019
 * 
 */
#ifndef KEY_CONTROLLED_LOOP_H
#define KEY_CONTROLLED_LOOP_H


/*
 * Commands
 */
enum KEY_CMD{
	
	NONE,
	START,
	STOP
};

/*
 * Global variable to store a command, received by a keyboard input
 */
volatile enum KEY_CMD gl_keyCmd;

/*
 * Starts an endless loop and an listener in a sperate thread to listen for key board input. If the key s (start) ist pressed, the function f is called. 
 * The endless loop stops if the function f returns or when f was never called (e.g. no start command appeared), the loop terminates
 * by pressing the key q (quit).
 * The function f could by itself execute an endless loop, which could be controlled by checking the global flag gl_keyCmd. If the 
 * global flag gl_keyCmd holds the value STOP, leave the loop and let f return.
 */
int startKeyControlledLoop(int (*f)());

/*
 * Reads the keyboard input and sets the global gl_keyCmd according the received key command.
 */
static void* readKeyboardCmd(void* data);



#endif

