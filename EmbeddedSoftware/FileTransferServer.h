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
	bool InitSock();    //初始winsocket
	SOCKET BindListen();  //绑定监听套接字
	SOCKET AcceptConnection(SOCKET sd);  //接收客户端
	bool ProcessConnection(SOCKET sd);  //传送数据
	bool ReceiveFile(SOCKET sd);     //接收文件内容
	bool RecvFileName(SOCKET sd, int length);     //接收文件名
	void CloseSocket();   //关闭套接字
	int bytesToInt(byte* bytes);
};



