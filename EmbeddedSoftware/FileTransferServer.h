#pragma once
#include<iostream>
#include<WinSock2.h>
#include "messageProtocol.h"
#pragma comment(lib,"Ws2_32.lib")
#define PORT 12345
using namespace std;

class FileTransferServer
{
public:
	FileTransferServer();
	~FileTransferServer();
	void setSocket(SOCKET s) 
	{
		sd = s;
	}
	SOCKET getSocket() { return sd; }

	bool InitSock();      //��ʼwinsocket
	SOCKET BindListen();  //�󶨼����׽���
	SOCKET AcceptConnection(SOCKET sd);  //���տͻ���
	static bool ProcessConnection(SOCKET sd);  //��������
	void CloseSocket();   //�ر��׽���
private:
	SOCKET sd;
	int fileLength;
	char fileName[MAX_FILE_NAME_LENGTH];
	
	bool ReceiveFile(SOCKET sd);     //�����ļ�����
	bool RecvFileName(SOCKET sd, int length);     //�����ļ���
	int bytesToInt(byte* bytes);
};



