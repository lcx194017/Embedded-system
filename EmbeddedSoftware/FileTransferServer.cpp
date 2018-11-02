#include "FileTransferServer.h"



FileTransferServer::FileTransferServer()
{
}


FileTransferServer::~FileTransferServer()
{
}

bool FileTransferServer::InitSock()   //��ʼ��winsocket
{
	WSADATA wsData;
	WORD wr = MAKEWORD(2, 2);
	if (WSAStartup(wr, &wsData) == 0)
	{
		return true;
	}
	return false;
}
SOCKET FileTransferServer::BindListen()  //���׽���
{
	SOCKET sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == INVALID_SOCKET)
	{
		cout << "�����׽���ʧ��" << WSAGetLastError() << endl;
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
		cout << "��ʧ��" << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}
	if (listen(sd, 10) == SOCKET_ERROR)
	{
		closesocket(sd);
		cout << "����ʧ��" << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}
	return sd;

}
SOCKET FileTransferServer::AcceptConnection(SOCKET sd)    //���տͻ���
{
	sockaddr_in saRemote;
	int nSize = sizeof(sockaddr_in);
	SOCKET sdListen = accept(sd, (sockaddr*)&saRemote, &nSize);
	if (sdListen == INVALID_SOCKET)
	{
		cout << "���տͻ���ʧ��" << WSAGetLastError() << endl;
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
	//���Խ�������뿴������ϵͳ������
	int nRecvBuf = 1024000;//����Ϊ1000K
	setsockopt(sd, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	//���ͻ�����
	int nSendBuf = 1024000;//����Ϊ1000K
	setsockopt(sd, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));

	//-------------------------------------------------------------
	char file_name_length_bytes[4];
	if (recv(sd, file_name_length_bytes, 4, 0) == SOCKET_ERROR)
	{
		cout << "�����ļ����Ƴ���ʧ��" << WSAGetLastError() << endl;
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
		cout << "�����ļ�����ʧ��" << WSAGetLastError() << endl;
		return false;
	}

	fileLength = bytesToInt((byte*)file_length_bytes);
	cout << "���յ��ļ��ĳ���Ϊ" << fileLength << endl;
	Sleep(10);

	cout << "��ʼ�����ļ�" << endl;
	if (!ReceiveFile(sd))
	{
		cout << "�����ļ�ʧ��" << endl;
		return false;
	}
	cout << "�����ļ��ɹ�" << endl;
	return true;
}

bool FileTransferServer::RecvFileName(SOCKET sd, int length)
{
	if (recv(sd, fileName, length, 0) == SOCKET_ERROR)
	{
		cout << "�����ļ���ʧ��" << WSAGetLastError() << endl;
		return false;
	}
	cout << "���յ��ļ���Ϊ" << fileName << endl;
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
