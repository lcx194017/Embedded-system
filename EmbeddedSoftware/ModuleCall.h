#pragma once
#include "global.h"


class ModuleCall
{
public:
	ModuleCall();
	~ModuleCall();

	//�����߳�
	static void working_thread_proc();  

	//��Դ����߳�
	static void resource_monitoring_thread_proc();

	//�������߳�
	static void error_handling_thread_proc();

	//�������߳�
	static void server_thread_proc();
};

