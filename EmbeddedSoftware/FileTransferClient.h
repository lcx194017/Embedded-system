#pragma once
/************************************************************************/
/* 向服务器(后台，不是云端，云端使用http传输)发送文件                       */
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
	bool InitSock();   //初始化winsock
	u_long ResolveAdress(const char *serverIp);       //解析服务器地址
	SOCKET ConnectServer(u_long serverIp, int port);  //连接服务器
	bool ProcessConnection(SOCKET sd, const char* filePath);                //客户端服务器交互
	void CloseSocket();                               //释放套接字
	bool SendFileLength(SOCKET sd, const char *filePath);   //发送文件长度
	bool SendFile(SOCKET sd, const char *filePath);         //发送文件
};

