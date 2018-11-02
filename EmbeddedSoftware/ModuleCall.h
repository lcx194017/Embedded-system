#pragma once
#include "global.h"
#include "FileTransferClient.h"
#include "FileTransferServer.h"

class ModuleCall
{
public:
	ModuleCall();
	~ModuleCall();

	//�����߳�ִ�к���
	static void working_thread_proc();  

	//��Դ����߳�ִ�к���
	static void resource_monitoring_thread_proc();

	//�������߳�ִ�к���
	static void error_handling_thread_proc();

	//�������߳�ִ�к���
	static void server_thread_proc();

	//��Ϊ�ͻ��˷�������ִ�к���
	static void client_send_file(const string filepath, bool* flag);

	//��Ϊ��������������ִ�к���
	static void server_recevie_file(const SOCKET sdListen);
};

