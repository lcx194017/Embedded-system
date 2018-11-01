#pragma once
/************************************************************************/
/* �������(��̨�������ƶˣ��ƶ�ʹ��http����)�����ļ�                       */
/************************************************************************/

#include<iostream>
#include<fstream>
#include<vector>
#include<WinSock2.h>
#include"messageProtocol.h"
#pragma comment(lib,"Ws2_32.lib")
using namespace std;


#define SERVER_IP "127.0.0.1"
#define PORT  10000

class FileTransferClient
{
public:
	FileTransferClient();
	~FileTransferClient();

private:
	int nFileLength;
	char fileName[_MAX_FNAME + _MAX_EXT];
	SOCKET sd;
	bool InitSock();   //��ʼ��winsock
	u_long ResolveAdress(const char *serverIp);       //������������ַ
	SOCKET ConnectServer(u_long serverIp, int port);  //���ӷ�����
	bool ProcessConnection(SOCKET sd, const char* filePath);                //�ͻ��˷���������
	void CloseSocket();                               //�ͷ��׽���
	bool SendFileLength(SOCKET sd, const char *filePath);   //�����ļ�����
	bool SendFile(SOCKET sd, const char *filePath);         //�����ļ�
};

