#include "ModuleCall.h"


ModuleCall::ModuleCall()
{
}


ModuleCall::~ModuleCall()
{
}


void ModuleCall::working_thread_proc()
{
	while (working_thread_flag)
	{

	}
}

void ModuleCall::resource_monitoring_thread_proc()
{
	while (monitoring_thread_flag)
	{
	
	}

}


void ModuleCall::error_handling_thread_proc()
{
	while (error_handling_thread_flag)
	{
		while (!error_queue.empty())
		{
			CustomError customError = error_queue.pop();
			switch (customError.Error_type())
			{
				//JSON配置文件相关错误
			case JSONCONFIGURATIONERROR:
				switch (customError.Error_desc()) 
				{
				case SYSTEMINFO_NOT_EXIST:
				case CHANNELSETTINGS_NOT_EXIST:
				case TRIGGERSETTINGS_NOT_EXIST:
				case SYSTEMSETTINGS_NOT_EXIST:
					//如果处理成功，清理相关错误的标志位，错误队列不用关，已经弹出了
					break;

				case SYSTEMINFO_CHECKOUT_FAIL:
				case CHANNELSETTINGS_CHECKOUT_FAIL:
				case TRIGGERSETTINGS_CHECKOUT_FAIL:
				case SYSTEMSETTINGS_CHECKOUT_FAIL:
					break;

				case SYSTEMINFO_READ_FAIL:
				case CHANNELSETTINGS_READ_FAIL:
				case TRIGGERSETTINGS_READ_FAIL:
				case SYSTEMSETTINGS_READ_FAIL:
					break;

				case SYSTEMINFO_WRITE_FAIL:
				case CHANNELSETTINGS_WRITE_FAIL:
				case TRIGGERSETTINGS_WRITE_FAIL:
				case SYSTEMSETTINGS_WRITE_FAIL:
					break;

				default:
					break;
				}
				break;

				//TDMS相关错误
			case TDMSERROR:
				switch (customError.Error_desc())
				{
				case TDMS_READ_FAIL:
					break;

				case TDMS_WRITE_FAIL:
					break;

				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
}

//************************************
// Method:    server_thread_proc
// FullName:  ModuleCall::server_thread_proc
// Access:    public static 
// Returns:   void
// Qualifier:
// 函数本身在新的线程中进行调用，初始化完毕后就循环监听客户端的连接，客户端连接的任务
// 再新开一个线程进行处理
//************************************
void ModuleCall::server_thread_proc()
{
	FileTransferServer server;

	if (!server.InitSock())   
	{
		//初始化失败
		CustomError customError(FILETRANSFERERROR, RECEIVE_INIT_SOCKET_FAIL, MIDDLE);
		error_queue.push(customError);
		systemError.fileTransferError.File_receive_fail_set();
		return;
	}

	server.setSocket(server.BindListen());

	if (server.getSocket() == INVALID_SOCKET)
	{
		CustomError customError(FILETRANSFERERROR, RECEIVE_SERVER_INVALID_SOCKET, MIDDLE);
		error_queue.push(customError);
		systemError.fileTransferError.File_receive_fail_set();
		goto Error;
	}

	while (server_threads_flag)   //循环监听客户端的连接
	{
		SOCKET sdListen = server.AcceptConnection(server.getSocket());
		if (sdListen == INVALID_SOCKET)   //无效的客户端连接
		{
			CustomError customError(FILETRANSFERERROR, RECEIVE_LISTEN_INVALID_SOCKET, LOW);
			error_queue.push(customError);
			systemError.fileTransferError.File_receive_fail_set();
		}

		thread td(server_recevie_file, sdListen);
		
	}

Error:
	server.CloseSocket();
}


//************************************
// Method:    client_send_file
// FullName:  ModuleCall::client_send_file
// Access:    public static 
// Returns:   void
// Qualifier:
// Parameter: const string filepath
// Parameter: bool * flag
// 在新线程中调用client_send_file完成文件数据发送，传送过程中如果出现错误，会将错误放入错误队列
// 同时用flag指示本次传输结果
//************************************
void ModuleCall::client_send_file(const string filepath, bool* flag)
{
	FileTransferClient client;
	if (!client.InitSock())
	{
		//初始化Socket失败
		CustomError customError(FILETRANSFERERROR, SEND_INIT_SOCKET_FAIL, MIDDLE);
		error_queue.push(customError);
		systemError.fileTransferError.File_send_fail_set();
		*flag = false;
		return;
	}

	SOCKET saRemote = client.ConnectServer(client.ResolveAdress(SERVER_IP), PORT);
	if (saRemote == INVALID_SOCKET)
	{
		//连接服务器失败
		CustomError customError(FILETRANSFERERROR, SEND_CONNECT_FAIL, MIDDLE);
		error_queue.push(customError);
		systemError.fileTransferError.File_send_fail_set();
		*flag = false;
		client.CloseSocket();
		goto Error;
	}
	if (!client.ProcessConnection(saRemote, filepath.c_str()))
	{
		//数据传输过程失败
		CustomError customError(FILETRANSFERERROR, SEND_PROCESS_FAIL, MIDDLE);
		error_queue.push(customError);
		systemError.fileTransferError.File_send_fail_set();
		goto Error;
	}

Error:
	*flag = false;
	client.CloseSocket();
}


//函数在新的线程中调用，完成文件接收
//后面需要改进的地方：文件接收失败的时候，并不知道是那个文件描述失败。
//通过错误模块没有描述这个文件传输错误的详细信息
void ModuleCall::server_recevie_file(const SOCKET sdListen)
{
	bool res = FileTransferServer::ProcessConnection(sdListen);

	//文件接收失败
	if (!res)
	{
		CustomError customError(FILETRANSFERERROR, RECEVICE_PROCESS_FAIL, MIDDLE);
		error_queue.push(customError);
		systemError.fileTransferError.File_receive_fail_set();
	}
}




