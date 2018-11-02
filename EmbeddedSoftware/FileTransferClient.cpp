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
// ��ʼ��socket
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
// ����IP��ַ
//************************************
u_long FileTransferClient::ResolveAdress(const char *serverIp)  
{
	u_long nAddr = inet_addr(serverIp);
	if (nAddr == INADDR_NONE)  //����serverIpʹ�õ�����������ʽ
	{
		hostent *ent = gethostbyname(serverIp);
		if (ent == NULL)
		{
			cout << "��ȡ����������" << WSAGetLastError() << endl;
		}
		else
		{
			nAddr = *((u_long *)ent->h_addr_list[0]);
		}
	}
	if (nAddr == INADDR_NONE)
	{
		cout << "����������ַʧ��" << endl;
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
// ���ӷ�����
//************************************
SOCKET FileTransferClient::ConnectServer(u_long serverIp, int port)   
{
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == INVALID_SOCKET)
	{
		cout << "�����׽���ʧ��" << endl;
		return INVALID_SOCKET;
	}
	sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr.S_un.S_addr = serverIp;
	saServer.sin_port = htons(port);
	if (connect(sd, (sockaddr*)&saServer, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		cout << "���ӷ�����ʧ��" << WSAGetLastError() << endl;
		closesocket(sd);
		return INVALID_SOCKET;
	}
	return sd;
}


bool FileTransferClient::ProcessConnection(SOCKET sd, const char* filePath)      //����ͨ��
{
	//-------------------------------------------------
	//���Խ�������뿴������ϵͳ������
	int nRecvBuf = 1024000;//����Ϊ1000K
	setsockopt(sd, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	//���ͻ�����
	int nSendBuf = 1024000;//����Ϊ1000K
	setsockopt(sd, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));
	//---------------------------------------------------------

	char fileDrive[_MAX_DRIVE];
	char fileDir[_MAX_DIR];
	char fileName[_MAX_FNAME];
	char fileExt[_MAX_EXT];
	_splitpath(filePath, fileDrive, fileDir, fileName, fileExt);  //���ļ�·������
	strcat(fileName, fileExt);   //����
	int file_name_length = (int)strlen(fileName);   //�ļ�������

	if (send(sd, (char *)&file_name_length, sizeof(int), 0) == SOCKET_ERROR)  //�����ļ���
	{
		cout << "�����ļ������ȳ���" << WSAGetLastError() << endl;
	}

	Sleep(10);

	if (send(sd, fileName, file_name_length, 0) == SOCKET_ERROR)  //�����ļ���
	{
		cout << "�����ļ�������" << WSAGetLastError() << endl;
	}

	Sleep(10);

	if (!SendFileLength(sd, filePath))  //�����ļ�����
	{
		cout << "�����ļ����ȳ���" << endl;
		return false;
	}

	Sleep(10);

	if (!SendFile(sd, filePath))  //�����ļ�
	{
		cout << "�����ļ�����" << endl;
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
bool FileTransferClient::SendFile(SOCKET sd, const char *filePath)   //�����ļ�
{
	cout << "���뵽�����ļ�����" << endl;
	FILE *pFile;
	pFile = fopen(filePath, "r+b");
	fseek(pFile, 0, SEEK_SET);   //��λ���ļ���λ��
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
			cout << "����ʧ��" << endl;
			return false;
		}
		i += nSend;
		fseek(pFile, -(nSize - nSend), SEEK_CUR);  //��λ��ʵ���ѷ��͵���λ��
		memset(buff, 0, sizeof(char)*MAX_PACK_SIZE); //��buff���
	}
	fclose(pFile);
	return true;
}

void FileTransferClient::CloseSocket()   //�ر��׽���
{
	closesocket(sd);
	WSACleanup();
}
