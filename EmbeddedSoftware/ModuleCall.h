#pragma once
#include "global.h"
#include "FileTransferClient.h"
#include "FileTransferServer.h"

class ModuleCall
{
public:
	ModuleCall();
	~ModuleCall();

	//工作线程执行函数
	static void working_thread_proc();  

	//资源监控线程执行函数
	static void resource_monitoring_thread_proc();

	//错误处理线程执行函数
	static void error_handling_thread_proc();

	//服务器线程执行函数
	static void server_thread_proc();

	//作为客户端发送数据执行函数
	static void client_send_file(const string filepath, bool* flag);

	//作为服务器接收数据执行函数
	static void server_recevie_file(const SOCKET sdListen);
};

