#include "FileTransferServer.h"



FileTransferServer::FileTransferServer()
{
}


FileTransferServer::~FileTransferServer()
{
}

bool FileTransferServer::InitSock()   //初始化winsocket
{
	WSADATA wsData;
	WORD wr = MAKEWORD(2, 2);
	if (WSAStartup(wr, &wsData) == 0)
	{
		return true;
	}
	return false;
}
SOCKET FileTransferServer::BindListen()  //绑定套接字
{
	SOCKET sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == INVALID_SOCKET)
	{
		cout << "创建套接字失败" << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}
	sockaddr_in sListen;
	sListen.sin_family = AF_INET;
	sListen.sin_addr.s_addr = htonl(INADDR_ANY);
	sListen.sin_port = htons(PORT);
	int nSize;
	nSize = sizeof(sockaddr_in);
	if (bind(sd, (sockaddr*)&sListen, nSize) == SOCKET_ERROR)
	{
		closesocket(sd);
		cout << "绑定失败" << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}
	if (listen(sd, 10) == SOCKET_ERROR)
	{
		closesocket(sd);
		cout << "监听失败" << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}
	return sd;

}
SOCKET FileTransferServer::AcceptConnection(SOCKET sd)    //接收客户端
{
	sockaddr_in saRemote;
	int nSize = sizeof(sockaddr_in);
	SOCKET sdListen = accept(sd, (sockaddr*)&saRemote, &nSize);
	if (sdListen == INVALID_SOCKET)
	{
		cout << "接收客户端失败" << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}
	return sdListen;
}
bool FileTransferServer::ReceiveFile(SOCKET sd)
{
	char buff[MAX_PACK_SIZE];
	FILE *pFile;
	pFile = fopen(fileName, "a+b");
	int i = 0;
	while (i + 1 < fileLength)
	{
		int nRecv = recv(sd, buff, MAX_PACK_SIZE, 0);
		if (nRecv == SOCKET_ERROR)
		{
			return false;
		}
		fwrite(buff, sizeof(char), nRecv, pFile);
		i += nRecv;
		memset(buff, 0, sizeof(char)*MAX_PACK_SIZE);
	}
	fclose(pFile);
	return true;
}
void FileTransferServer::CloseSocket()
{
	closesocket(sd);
	WSACleanup();
}
bool FileTransferServer::ProcessConnection(SOCKET sd)
{
	//----------------------------------------------
	//可以将下面代码看做设置系统缓冲区
	int nRecvBuf = 1024000;//设置为1000K
	setsockopt(sd, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	//发送缓冲区
	int nSendBuf = 1024000;//设置为1000K
	setsockopt(sd, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));

	//-------------------------------------------------------------
	char file_name_length_bytes[4];
	if (recv(sd, file_name_length_bytes, 4, 0) == SOCKET_ERROR)
	{
		cout << "接收文件名称长度失败" << WSAGetLastError() << endl;
		return false;
	}
	int file_name_length = bytesToInt((byte*)file_name_length_bytes);

	Sleep(10);
	if (!RecvFileName(sd, file_name_length))
	{
		return false;
	}

	Sleep(10);
	char file_length_bytes[4];
	if (recv(sd, file_length_bytes, 4, 0) == SOCKET_ERROR)
	{
		cout << "接收文件长度失败" << WSAGetLastError() << endl;
		return false;
	}

	fileLength = bytesToInt((byte*)file_length_bytes);
	cout << "接收到文件的长度为" << fileLength << endl;
	Sleep(10);

	cout << "开始接收文件" << endl;
	if (!ReceiveFile(sd))
	{
		cout << "接收文件失败" << endl;
		return false;
	}
	cout << "接收文件成功" << endl;
	return true;
}

bool FileTransferServer::RecvFileName(SOCKET sd, int length)
{
	if (recv(sd, fileName, length, 0) == SOCKET_ERROR)
	{
		cout << "接收文件名失败" << WSAGetLastError() << endl;
		return false;
	}
	cout << "接收的文件名为" << fileName << endl;
	return true;
}

int FileTransferServer::bytesToInt(byte* bytes)
{
	int addr = bytes[3] & 0xFF;
	addr |= ((bytes[2] << 8) & 0xFF00);
	addr |= ((bytes[1] << 16) & 0xFF0000);
	addr |= ((bytes[0] << 24) & 0xFF000000);
	return addr;
}
