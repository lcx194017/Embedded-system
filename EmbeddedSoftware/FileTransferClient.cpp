#include "FileTransferClient.h"


FileTransferClient::FileTransferClient()
{
}


FileTransferClient::~FileTransferClient()
{
}


//************************************
// Method:    InitSock
// FullName:  FileTransferClient::InitSock
// Access:    private 
// Returns:   bool
// Qualifier: 
// 初始化socket
//************************************
bool FileTransferClient::InitSock()   
{
	WSADATA wsData;
	WORD wr = MAKEWORD(2, 2);
	if (WSAStartup(wr, &wsData) == 0)
	{
		return true;
	}
	return false;
}


//************************************
// Method:    ResolveAdress
// FullName:  FileTransferClient::ResolveAdress
// Access:    private 
// Returns:   u_long
// Qualifier:
// Parameter: const char * serverIp
// 解析IP地址
//************************************
u_long FileTransferClient::ResolveAdress(const char *serverIp)  
{
	u_long nAddr = inet_addr(serverIp);
	if (nAddr == INADDR_NONE)  //表明serverIp使用的是主机名形式
	{
		hostent *ent = gethostbyname(serverIp);
		if (ent == NULL)
		{
			cout << "获取主机名出错" << WSAGetLastError() << endl;
		}
		else
		{
			nAddr = *((u_long *)ent->h_addr_list[0]);
		}
	}
	if (nAddr == INADDR_NONE)
	{
		cout << "解析主机地址失败" << endl;
	}
	return nAddr;
}


//************************************
// Method:    ConnectServer
// FullName:  FileTransferClient::ConnectServer
// Access:    private 
// Returns:   SOCKET
// Qualifier: 
// Parameter: u_long serverIp
// Parameter: int port
// 连接服务器
//************************************
SOCKET FileTransferClient::ConnectServer(u_long serverIp, int port)   
{
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == INVALID_SOCKET)
	{
		cout << "创建套接字失败" << endl;
		return INVALID_SOCKET;
	}
	sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr.S_un.S_addr = serverIp;
	saServer.sin_port = htons(port);
	if (connect(sd, (sockaddr*)&saServer, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		cout << "连接服务器失败" << WSAGetLastError() << endl;
		closesocket(sd);
		return INVALID_SOCKET;
	}
	return sd;
}


bool FileTransferClient::ProcessConnection(SOCKET sd, const char* filePath)      //进行通信
{
	//-------------------------------------------------
	//可以将下面代码看做设置系统缓冲区
	int nRecvBuf = 1024000;//设置为1000K
	setsockopt(sd, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	//发送缓冲区
	int nSendBuf = 1024000;//设置为1000K
	setsockopt(sd, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));
	//---------------------------------------------------------

	char fileDrive[_MAX_DRIVE];
	char fileDir[_MAX_DIR];
	char fileName[_MAX_FNAME];
	char fileExt[_MAX_EXT];
	_splitpath(filePath, fileDrive, fileDir, fileName, fileExt);  //将文件路径解析
	strcat(fileName, fileExt);   //连接
	int file_name_length = (int)strlen(fileName);   //文件名长度

	if (send(sd, (char *)&file_name_length, sizeof(int), 0) == SOCKET_ERROR)  //发送文件名
	{
		cout << "发送文件名长度出错" << WSAGetLastError() << endl;
	}

	Sleep(10);

	if (send(sd, fileName, file_name_length, 0) == SOCKET_ERROR)  //发送文件名
	{
		cout << "发送文件名出错" << WSAGetLastError() << endl;
	}

	Sleep(10);

	if (!SendFileLength(sd, filePath))  //发送文件长度
	{
		cout << "发送文件长度出错" << endl;
		return false;
	}

	Sleep(10);

	if (!SendFile(sd, filePath))  //发送文件
	{
		cout << "发送文件出错" << endl;
		return false;
	}

	return true;
}

bool FileTransferClient::SendFileLength(SOCKET sd, const char *filePath)
{
	FILE *pFile;
	pFile = fopen(filePath, "r+b");
	fseek(pFile, 0, SEEK_END);
	nFileLength = (int)_ftelli64(pFile);
	fclose(pFile);
	if (send(sd, (char *)&nFileLength, sizeof(int), 0) == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}
bool FileTransferClient::SendFile(SOCKET sd, const char *filePath)   //发送文件
{
	cout << "进入到发送文件内容" << endl;
	FILE *pFile;
	pFile = fopen(filePath, "r+b");
	fseek(pFile, 0, SEEK_SET);   //定位到文件首位置
	int i = 0;
	char buff[MAX_PACK_SIZE];
	while (i < nFileLength)
	{
		int nSize;
		if (i + MAX_PACK_SIZE > nFileLength)
		{
			nSize = (int)(nFileLength - i);
		}
		else
		{
			nSize = MAX_PACK_SIZE - 1;
		}
		fread(buff, sizeof(char), nSize, pFile);
		int nSend;
		nSend = send(sd, buff, nSize, 0);
		if (nSend == SOCKET_ERROR)
		{
			cout << "发送失败" << endl;
			return false;
		}
		i += nSend;
		fseek(pFile, -(nSize - nSend), SEEK_CUR);  //定位到实际已发送到的位置
		memset(buff, 0, sizeof(char)*MAX_PACK_SIZE); //将buff清空
	}
	fclose(pFile);
	return true;
}

void FileTransferClient::CloseSocket()   //关闭套接字
{
	closesocket(sd);
	WSACleanup();
}
