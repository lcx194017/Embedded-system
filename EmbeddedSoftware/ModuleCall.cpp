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
				//JSON�����ļ���ش���
			case JSONCONFIGURATIONERROR:
				switch (customError.Error_desc()) 
				{
				case SYSTEMINFO_NOT_EXIST:
				case CHANNELSETTINGS_NOT_EXIST:
				case TRIGGERSETTINGS_NOT_EXIST:
				case SYSTEMSETTINGS_NOT_EXIST:
					//�������ɹ���������ش���ı�־λ��������в��ùأ��Ѿ�������
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

				//TDMS��ش���
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
// �����������µ��߳��н��е��ã���ʼ����Ϻ��ѭ�������ͻ��˵����ӣ��ͻ������ӵ�����
// ���¿�һ���߳̽��д���
//************************************
void ModuleCall::server_thread_proc()
{
	FileTransferServer server;

	if (!server.InitSock())   
	{
		//��ʼ��ʧ��
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

	while (server_threads_flag)   //ѭ�������ͻ��˵�����
	{
		SOCKET sdListen = server.AcceptConnection(server.getSocket());
		if (sdListen == INVALID_SOCKET)   //��Ч�Ŀͻ�������
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
// �����߳��е���client_send_file����ļ����ݷ��ͣ����͹�����������ִ��󣬻Ὣ�������������
// ͬʱ��flagָʾ���δ�����
//************************************
void ModuleCall::client_send_file(const string filepath, bool* flag)
{
	FileTransferClient client;
	if (!client.InitSock())
	{
		//��ʼ��Socketʧ��
		CustomError customError(FILETRANSFERERROR, SEND_INIT_SOCKET_FAIL, MIDDLE);
		error_queue.push(customError);
		systemError.fileTransferError.File_send_fail_set();
		*flag = false;
		return;
	}

	SOCKET saRemote = client.ConnectServer(client.ResolveAdress(SERVER_IP), PORT);
	if (saRemote == INVALID_SOCKET)
	{
		//���ӷ�����ʧ��
		CustomError customError(FILETRANSFERERROR, SEND_CONNECT_FAIL, MIDDLE);
		error_queue.push(customError);
		systemError.fileTransferError.File_send_fail_set();
		*flag = false;
		client.CloseSocket();
		goto Error;
	}
	if (!client.ProcessConnection(saRemote, filepath.c_str()))
	{
		//���ݴ������ʧ��
		CustomError customError(FILETRANSFERERROR, SEND_PROCESS_FAIL, MIDDLE);
		error_queue.push(customError);
		systemError.fileTransferError.File_send_fail_set();
		goto Error;
	}

Error:
	*flag = false;
	client.CloseSocket();
}


//�������µ��߳��е��ã�����ļ�����
//������Ҫ�Ľ��ĵط����ļ�����ʧ�ܵ�ʱ�򣬲���֪�����Ǹ��ļ�����ʧ�ܡ�
//ͨ������ģ��û����������ļ�����������ϸ��Ϣ
void ModuleCall::server_recevie_file(const SOCKET sdListen)
{
	bool res = FileTransferServer::ProcessConnection(sdListen);

	//�ļ�����ʧ��
	if (!res)
	{
		CustomError customError(FILETRANSFERERROR, RECEVICE_PROCESS_FAIL, MIDDLE);
		error_queue.push(customError);
		systemError.fileTransferError.File_receive_fail_set();
	}
}




