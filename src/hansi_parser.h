/*
Copyright© Ayush Yadav 2021 under MIT License.
Hobby ANSI Parser(HANSIP) is forked from VTConsole, made by https://github.com/sleepy-monax
HANSIP is a modified version of VTConsole.
But instead of a terminal, it is a ANSI Parser only.
*/

#ifndef __HANSIP__
#define __HANSIP__

#define MAX_ARGS	8
#define HTERM_ESC	1
#define HTERM_BRACKET	2
#define HTERM_ARGS	3
#define HTERM_ENDARGS	4

class ansi_args{
	public:
	int value;
	bool empty;
};

class hansi_parser{
	public:
	int state = HTERM_ESC;
	int index;
	ansi_args args[MAX_ARGS];
};

// check line 43, 50, 54, 58 to implement color changing abilities of your framebuffer

// On line 74 and 83, replace fb_putchar() with your framebuffer specific putchar function.

// implement these in your framebuffer driver
extern void setCursorX(stack[i].value);
extern void setCursorY(stack[i].value);

// a global parser for ANSI. don't touch it
extern hansi_parser g_parser;

//pass all your characters through this function
void hansi_handler(char c);

#endif
