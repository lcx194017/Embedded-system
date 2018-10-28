#pragma once
#include "global.h"


class ModuleCall
{
public:
	ModuleCall();
	~ModuleCall();

	//工作线程
	static void working_thread_proc();  

	//资源监控线程
	static void resource_monitoring_thread_proc();

	//错误处理线程
	static void error_handling_thread_proc();

	//服务器线程
	static void server_thread_proc();
};

