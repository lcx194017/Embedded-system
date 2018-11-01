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
private:
	SOCKET sd;
	int fileLength;
	char fileName[MAX_FILE_NAME_LENGTH];
	bool InitSock();    //��ʼwinsocket
	SOCKET BindListen();  //�󶨼����׽���
	SOCKET AcceptConnection(SOCKET sd);  //���տͻ���
	bool ProcessConnection(SOCKET sd);  //��������
	bool ReceiveFile(SOCKET sd);     //�����ļ�����
	bool RecvFileName(SOCKET sd, int length);     //�����ļ���
	void CloseSocket();   //�ر��׽���
	int bytesToInt(byte* bytes);
};



