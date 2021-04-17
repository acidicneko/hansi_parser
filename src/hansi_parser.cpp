/*
Copyright© Ayush Yadav 2021 under MIT License.
Hobby ANSI Parser(HANSIP) is forked from VTConsole, made by https://github.com/sleepy-monax
HANSIP is a modified version of VTConsole.
But instead of a terminal, it is a ANSI Parser only.
*/
#include "hansi_parser.h"
hansi_parser g_parser = {.state = HTERM_ESC}; // global parser object
bool isdigit(char c){
	if(c >= '0' && c <= '9'){
		return true;
	}
	return false;
}

void hansi_handle_csr(ansi_args* stack, int count){
	bool csr_x = true;
	bool done = false;
	for(int i = 0; i < count; i++){
		if(!stack[i].empty){
			if(done)	break;
			if(csr_x){
				// do your magic here
				// use stack[i].value for X cursor's value
				setCursorX(stack[i].value);
				csr_x = false;
			}
			else{
				// do your magic here
				//use stack[i].value for Y cursor's value
				setCursorY(stack[i].value);
				done = true;
			}
		}
	}
}

void hansi_handle_sgr(ansi_args* stack, int count){
	for (int i = 0; i < count; i++)
    {
        if (stack[i].empty || stack[i].value == 0)
        {
            // restore default attributes
        }
        else
        {
            int attr = stack[i].value;
            if (attr == 1)
            {
                // enable bright values, probably a boolean
            }
            else if (attr >= 30 && attr <= 37)
            {
                // attr - 30 is the color code
            }
            else if (attr >= 40 && attr <= 47)
            {
                // attr - 40 is the color code
            }
        }
    }
}

void hansi_handler(char c){
	if(g_parser.state == HTERM_ESC){
		if(c == '\033'){
			g_parser.state = HTERM_BRACKET;
			g_parser.index = 0;
            g_parser.args[g_parser.index].value = 0;
            g_parser.args[g_parser.index].empty = true;
		}
		else{
			g_parser.state = HTERM_ESC;
			fb_putchar(c);
		}
	}
	else if(g_parser.state == HTERM_BRACKET){
		if(c == '['){
			g_parser.state = HTERM_ARGS;
		}
		else{
			g_parser.state = HTERM_ESC;
			fb_putchar(c);
		}
	}
	else if(g_parser.state == HTERM_ARGS){
		if(isdigit(c)){
			g_parser.args[g_parser.index].value *= 10;
			g_parser.args[g_parser.index].value += (c - '0');
			g_parser.args[g_parser.index].empty = false;
		}
		else{
			if(g_parser.index < MAX_ARGS)
				g_parser.index++;
			g_parser.args[g_parser.index].value = 0;
			g_parser.args[g_parser.index].empty = true;
			g_parser.state = HTERM_ENDARGS;
		}
	}
	if(g_parser.state == HTERM_ENDARGS){
		if(c == ';'){
			g_parser.state = HTERM_ARGS;
		}
		else{
			switch(c){
				case 'm':
					hterm_handle_sgr(&g_parser.args[0], g_parser.index);
					break;
				case 'H':
					hterm_handle_csr(&g_parser.args[0], g_parser.index);
					break;
				default:
					break;
			}
			g_parser.state = HTERM_ESC;
		}
	}
}
