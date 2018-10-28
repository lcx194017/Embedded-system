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

void ModuleCall::server_thread_proc()
{
	while (server_threads_flag )
	{

	}
}

