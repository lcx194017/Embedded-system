#include <iostream>
#include "global.h"
#include "ModuleCall.h"

using namespace std;

#define JSON_FILE_PATH  "JosnFile/"

//系统初始化
void system_init();

int main()
{

	//1、系统初始化
	system_init();

	if (!error_queue.empty())
		goto Error;

	{
		//2.启动各监听线程
		thread working_td(ModuleCall::working_thread_proc);     //工作线程启动
		thread monitor_td(ModuleCall::resource_monitoring_thread_proc);     //资源监控线程启动
		thread error_td(ModuleCall::error_handling_thread_proc);       //错误处理线程启动
		thread server_td(ModuleCall::server_thread_proc);      //服务器线程启动
	}

	//3.循环监听数据区域
	while (main_thread_flag)
	{

	}

	getchar();
	return 0;

Error:
	cout << "系统初始化失败!" << endl;
	return 0;
}


void system_init() 
{

	/*读取系统的JSON配置文件*/

	/*SystemInfo JSON 配置文件*/
	string file_path = JSON_FILE_PATH;
	file_path += "SystemInfo.json";
	int result = JSONModule::readJsonDataFromFile(file_path.c_str(), &systemInfo, SYSTEMINFO);

	//-1表示读取文件失败， - 2表示解析过程失败
	if (result != 0)
	{
		switch (result)
		{
		case -1:
			CustomError customError(JSONCONFIGURATIONERROR, SYSTEMINFO_NOT_EXIST, MIDDLE);
			error_queue.push(customError);
			systemError.jsonconfigurationError.SystemInfo_not_exist_set();
			break;
		case -2:
			CustomError customError(JSONCONFIGURATIONERROR, SYSTEMINFO_READ_FAIL, MIDDLE);
			error_queue.push(customError);
			systemError.jsonconfigurationError.SystemInfo_read_fail_set();
			break;
		default:
			break;
		}
	}

	//规则检查
	result = JSONModule::systemInfoCheck(systemInfo);

	if (result != 1)
	{
		CustomError customError(JSONCONFIGURATIONERROR, SYSTEMINFO_CHECKOUT_FAIL, MIDDLE);
		error_queue.push(customError);
		systemError.jsonconfigurationError.SystemInfo_checkout_fail_set();
	}

	/*-----------------------------------------------*/

	/*ChannelSettings JSON配置文件*/
	file_path = JSON_FILE_PATH;
	file_path += "ChannelSettings.json";
	result = JSONModule::readJsonDataFromFile(file_path.c_str(), &channelSettings, CHANNELSETTINGS);

	if (result != 0)
	{
		switch (result)
		{
		case -1:
			CustomError customError(JSONCONFIGURATIONERROR, CHANNELSETTINGS_NOT_EXIST, MIDDLE);
			error_queue.push(customError);
			systemError.jsonconfigurationError.ChannelSettings_not_exist_set();
			break;
		case -2:
			CustomError customError(JSONCONFIGURATIONERROR, CHANNELSETTINGS_READ_FAIL, MIDDLE);
			error_queue.push(customError);
			systemError.jsonconfigurationError.ChannelSettings_read_fail_set();
			break;
		default:
			break;
		}
	}

	//规则检查
	result = JSONModule::channelSettingsCheck(channelSettings);

	if (result != 1)
	{
		CustomError customError(JSONCONFIGURATIONERROR, CHANNELSETTINGS_CHECKOUT_FAIL, MIDDLE);
		error_queue.push(customError);
		systemError.jsonconfigurationError.ChannelSettings_checkout_fail_set();
	}


	/*-----------------------------------------------*/

	/*TriggerSettings JSON配置文件*/

	file_path = JSON_FILE_PATH;
	file_path += "TriggerSettings.json";
	result = JSONModule::readJsonDataFromFile(file_path.c_str(), &triggerSettings, TRIGGERSETTINGS);

	if (result != 0)
	{
		switch (result)
		{
		case -1:
			CustomError customError(JSONCONFIGURATIONERROR, TRIGGERSETTINGS_NOT_EXIST, MIDDLE);
			error_queue.push(customError);
			systemError.jsonconfigurationError.TriggerSettings_not_exist_set();
			break;
		case -2:
			CustomError customError(JSONCONFIGURATIONERROR, TRIGGERSETTINGS_READ_FAIL, MIDDLE);
			error_queue.push(customError);
			systemError.jsonconfigurationError.TriggerSettings_read_fail_set();
			break;
		default:
			break;
		}
	}

	//规则检查
	result = JSONModule::triggerSettingsCheck(triggerSettings);

	if (result != 1)
	{
		CustomError customError(JSONCONFIGURATIONERROR, TRIGGERSETTINGS_CHECKOUT_FAIL, MIDDLE);
		error_queue.push(customError);
		systemError.jsonconfigurationError.TriggerSettings_checkout_fail_set();
	}

	/*-----------------------------------------------*/

	/*SystemSettings JSON配置文件*/

	file_path = JSON_FILE_PATH;
	file_path += "SystemSettings.json";
	result = JSONModule::readJsonDataFromFile(file_path.c_str(), &systemSettings, SYSTEMSETTINGS);

	if (result != 0)
	{
		switch (result)
		{
		case -1:
			CustomError customError(JSONCONFIGURATIONERROR, SYSTEMSETTINGS_NOT_EXIST, MIDDLE);
			error_queue.push(customError);
			systemError.jsonconfigurationError.SystemSettings_not_exist_set();
			break;
		case -2:
			CustomError customError(JSONCONFIGURATIONERROR, SYSTEMSETTINGS_READ_FAIL, MIDDLE);
			error_queue.push(customError);
			systemError.jsonconfigurationError.SystemSettings_read_fail_set();
			break;
		default:
			break;
		}
	}

	//规则检查
	result = JSONModule::systemSettingsCheck(systemSettings);

	if (result != 1)
	{
		CustomError customError(JSONCONFIGURATIONERROR, SYSTEMINFO_CHECKOUT_FAIL, MIDDLE);
		error_queue.push(customError);
		systemError.jsonconfigurationError.SystemSettings_checkout_fail_set();
	}
}