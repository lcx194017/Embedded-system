#pragma once
#include <windows.h>
#include <climits>
using namespace std;


/*
	edit by lcx
	错误模块设计：
	错误的状态定义标识了当前整个系统的状态，SystemEorror为全局性错误标志，下面又分为若干个子模块（和系统的模块划分相对应），
	子模块中定义了错误的具体类型。
	每个子模块中的错误类型都必须定义成private，以防随意修改破坏系统，错误的状态通过3个函数来修改和获取
	unsigned int **** ();  ——>  获取错误是否存在，以及数量。0：没有错误， >=1 ：存在  （定义成unsigned int 是标识错误次数）
	void ****_set();  ——> 错误出现时，置位。 多次出现就是次数+1
	void ****_clear();  ——> 当错误处理模块处理完错误后调用，清除错误标志。

	系统中同时为错误处理维持一个优先级队列，错误处理线程从队列中取出错误并处理
	队列中放的是自定义错误，即CustomError，通过错误类型、错误描述、错误优先级进行定义

	错误产生时：
				(1)设置相应的错误标志位 ——> (2)构造自定义错误类型，并加入优先级队列
	错误处理时：
				(1)从队列中取出优先级最高的错误  ——> (2)若处理成功，清除错误标志位； 如不成功则进行相应的措施，严重的时候关机重启
*/


//Json配置文件模块错误定义
class JsonConfigurationError
{
public:
	JsonConfigurationError();
	~JsonConfigurationError();


	unsigned int SystemInfo_not_exist() const { return systemInfo_not_exist; }
	void SystemInfo_not_exist_set()
	{
		if (systemInfo_not_exist < UINT_MAX)
			systemInfo_not_exist++;
	}
	void SystemInfo_not_exist_clear() { systemInfo_not_exist = 0; }

	unsigned int SystemInfo_open_error() const { return systemInfo_open_error; }
	void SystemInfo_open_error_set()
	{
		if (systemInfo_open_error < UINT_MAX)
			systemInfo_open_error++;
	}
	void SystemInfo_open_error_clear() { systemInfo_open_error = 0; }

	unsigned int SystemInfo_checkout_fail() const { return systemInfo_checkout_fail; }
	void SystemInfo_checkout_fail_set()
	{
		if (systemInfo_checkout_fail < UINT_MAX)
			systemInfo_checkout_fail++;
	}
	void SystemInfo_checkout_fail_clear() { systemInfo_checkout_fail = 0; }

	unsigned int SystemInfo_read_fail() const { return systemInfo_read_fail; }
	void SystemInfo_read_fail_set()
	{
		if (systemInfo_read_fail < UINT_MAX)
			systemInfo_read_fail++;
	}
	void SystemInfo_read_fail_clear() { systemInfo_read_fail = 0; }

	unsigned int SystemInfo_write_fail() const { return systemInfo_write_fail; }
	void SystemInfo_write_fail_set()
	{
		if (systemInfo_write_fail < UINT_MAX)
			systemInfo_write_fail++;
	}
	void SystemInfo_write_fail_clear() { systemInfo_write_fail = 0; }


	unsigned int ChannelSettings_not_exist() const { return channelSettings_not_exist; }
	void ChannelSettings_not_exist_set()
	{ 
		if(channelSettings_not_exist < UINT_MAX)
			channelSettings_not_exist++;
	}
	void ChannelSettings_not_exist_clear() { channelSettings_not_exist = 0; }

	unsigned int ChannelSettings_open_error() const { return channelSettings_open_error; }
	void ChannelSettings_open_error_set()
	{ 
		if(channelSettings_open_error < UINT_MAX)
			channelSettings_open_error++; 
	}
	void ChannelSettings_open_error_clear() { channelSettings_open_error = 0; }

	unsigned int ChannelSettings_checkout_fail() const { return channelSettings_checkout_fail; }
	void ChannelSettings_checkout_fail_set()
	{ 
		if(channelSettings_checkout_fail < UINT_MAX)
			channelSettings_checkout_fail++; 
	}
	void ChannelSettings_checkout_fail_clear() { channelSettings_checkout_fail = 0; }

	unsigned int ChannelSettings_read_fail() const { return channelSettings_read_fail; }
	void ChannelSettings_read_fail_set()
	{ 
		if(channelSettings_read_fail < UINT_MAX)
			channelSettings_read_fail++; 
	}
	void ChannelSettings_read_fail_clear() { channelSettings_read_fail = 0; }

	unsigned int ChannelSettings_write_fail() const { return channelSettings_write_fail; }
	void ChannelSettings_write_fail_set()
	{ 
		if(channelSettings_write_fail < UINT_MAX)
			channelSettings_write_fail++; 
	}
	void ChannelSettings_write_fail_clear() { channelSettings_write_fail = 0; }


	unsigned int TriggerSettings_not_exist() const { return triggerSettings_not_exist; }
	void TriggerSettings_not_exist_set()
	{ 
		if(triggerSettings_not_exist < UINT_MAX)
			triggerSettings_not_exist++; 
	}
	void TriggerSettings_not_exist_clear() { triggerSettings_not_exist = 0; }

	unsigned int TriggerSettings_open_error() const { return triggerSettings_open_error; }
	void TriggerSettings_open_error_set()
	{ 
		if(triggerSettings_open_error < UINT_MAX)
			triggerSettings_open_error++; 
	}
	void TriggerSettings_open_error_clear() { triggerSettings_open_error = 0; }

	unsigned int TriggerSettings_checkout_fail() const { return triggerSettings_checkout_fail; }
	void TriggerSettings_checkout_fail_set()
	{ 
		if(triggerSettings_checkout_fail < UINT_MAX)
			triggerSettings_checkout_fail++;
	}
	void TriggerSettings_checkout_fail_clear() { triggerSettings_checkout_fail = 0; }

	unsigned int TriggerSettings_read_fail() const { return triggerSettings_read_fail; }
	void TriggerSettings_read_fail_set()
	{ 
		if(triggerSettings_read_fail < UINT_MAX)
			triggerSettings_read_fail++; 
	}
	void TriggerSettings_read_fail_clear() { triggerSettings_read_fail = 0; }

	unsigned int TriggerSettings_write_fail() const { return triggerSettings_write_fail; }
	void TriggerSettings_write_fail_set()
	{ 
		if(triggerSettings_write_fail < UINT_MAX)
			triggerSettings_write_fail++;
	}
	void TriggerSettings_write_fail_clear() { triggerSettings_write_fail = 0; }



	unsigned int SystemSettings_not_exist() const { return systemSettings_not_exist; }
	void SystemSettings_not_exist_set()
	{ 
		if(systemSettings_not_exist < UINT_MAX)
			systemSettings_not_exist++; 
	}
	void SystemSettings_not_exist_clear() { systemSettings_not_exist = 0; }

	unsigned int SystemSettings_open_error() const { return systemSettings_open_error; }
	void SystemSettings_open_error_set()
	{
		if(systemSettings_open_error < UINT_MAX)
			systemSettings_open_error++;
	}
	void SystemSettings_open_error_clear() { systemSettings_open_error = 0; }

	unsigned int SystemSettings_checkout_fail() const { return systemSettings_checkout_fail; }
	void SystemSettings_checkout_fail_set()
	{ 
		if(systemSettings_checkout_fail < UINT_MAX)
		systemSettings_checkout_fail ++; 
	}
	void SystemSettings_checkout_fail_clear() { systemSettings_checkout_fail = 0; }

	unsigned int SystemSettings_read_fail() const { return systemSettings_read_fail; }
	void SystemSettings_read_fail_set()
	{ 
		if(systemSettings_read_fail < UINT_MAX)
		systemSettings_read_fail ++; 
	}
	void SystemSettings_read_fail_clear() { systemSettings_read_fail = 0; }

	unsigned int SystemSettings_write_fail() const { return systemSettings_write_fail; }
	void SystemSettings_write_fail_set()
	{ 
		if(systemSettings_write_fail < UINT_MAX)
			systemSettings_write_fail++;
	}
	void SystemSettings_write_fail_clear() { systemSettings_write_fail = 0; }

private:

	volatile long systemInfo_not_exist = 0;
	volatile long systemInfo_open_error = 0;
	volatile long systemInfo_checkout_fail = 0;
	volatile long systemInfo_read_fail = 0;
	volatile long systemInfo_write_fail = 0;

	volatile long channelSettings_not_exist = 0;
	volatile long channelSettings_open_error = 0;
	volatile long channelSettings_checkout_fail = 0;
	volatile long channelSettings_read_fail = 0;
	volatile long channelSettings_write_fail = 0;

	volatile long triggerSettings_not_exist = 0;
	volatile long triggerSettings_open_error = 0;
	volatile long triggerSettings_checkout_fail = 0;
	volatile long triggerSettings_read_fail = 0;
	volatile long triggerSettings_write_fail = 0;

	volatile long systemSettings_not_exist = 0;
	volatile long systemSettings_open_error = 0;
	volatile long systemSettings_checkout_fail = 0;
	volatile long systemSettings_read_fail = 0;
	volatile long systemSettings_write_fail = 0;

};

//TDMS模块错误定义
class TDMSError {
public:
	TDMSError();
	~TDMSError();
	volatile long Tdms_read_fail() const { return tdms_read_fail; }
	void Tdms_read_fail_set() 
	{ 
		if (tdms_read_fail < UINT_MAX)
			tdms_read_fail++;
	}
	void Tdms_read_fail_clear() { tdms_read_fail = 0; }
	
	volatile long Tdms_write_fail() const { return tdms_write_fail; }
	void Tdms_write_fail_set() 
	{ 
		if (tdms_write_fail < UINT_MAX)
		tdms_write_fail++; 
	}
	void Tdms_write_fail_clear() { tdms_write_fail = 0; }
private:
	volatile long tdms_read_fail = 0;
	volatile long tdms_write_fail = 0;
};


/************************************************************************/
/* 系统错误模块，该模块下还有若干子集，对应各模块中的错误               */
/************************************************************************/
class SystemError
{
public:
	SystemError();
	~SystemError();
	JsonConfigurationError getJsonConfigurationError() const { return jsonconfigurationError; }
private:
	JsonConfigurationError jsonconfigurationError;
	TDMSError tdmsError;
};


//错误优先级枚举
enum ErrorPriority 
{
	LOW, MIDDLE, HIGH
};

//错误子模块类型枚举
enum ErrorSubmoduleType
{
	//Json配置模块错误
	JSONCONFIGURATIONERROR, 
	//TDMS模块错误
	TDMSERROR
};

//错误描述枚举
enum ErrorDesc
{
	//JSON配置文件读写相关的错误项
	SYSTEMINFO_NOT_EXIST,SYSTEMINFO_OPEN_ERROR,SYSTEMINFO_CHECKOUT_FAIL,SYSTEMINFO_READ_FAIL,SYSTEMINFO_WRITE_FAIL,
	CHANNELSETTINGS_NOT_EXIST,CHANNELSETTINGS_OPEN_ERROR,CHANNELSETTINGS_CHECKOUT_FAIL,CHANNELSETTINGS_READ_FAIL,CHANNELSETTINGS_WRITE_FAIL,
	TRIGGERSETTINGS_NOT_EXIST,TRIGGERSETTINGS_OPEN_ERROR,TRIGGERSETTINGS_CHECKOUT_FAIL,TRIGGERSETTINGS_READ_FAIL,TRIGGERSETTINGS_WRITE_FAIL,
	SYSTEMSETTINGS_NOT_EXIST,SYSTEMSETTINGS_OPEN_ERROR,SYSTEMSETTINGS_CHECKOUT_FAIL,SYSTEMSETTINGS_READ_FAIL,SYSTEMSETTINGS_WRITE_FAIL,
	//TDMS读写错误项
	TDMS_READ_FAIL, TDMS_WRITE_FAIL
};


//自定义错误
class CustomError
{
public:
	CustomError(ErrorSubmoduleType type, ErrorDesc desc, ErrorPriority priority)
	{
		Error_type(type);
		Error_desc(desc);
		Error_priority(priority);
	}

	ErrorDesc Error_desc() const { return error_desc; }
	void Error_desc(ErrorDesc val) { error_desc = val; }

	ErrorPriority Error_priority() const { return error_priority; }
	void Error_priority(ErrorPriority val) { error_priority = val; }

	ErrorSubmoduleType Error_type() const { return error_type; }
	void Error_type(ErrorSubmoduleType val) { error_type = val; }

	bool operator < (const CustomError &a) const;

	ErrorSubmoduleType getErrorSubmoduleType();
	ErrorDesc getErrorDesc();
	ErrorPriority getErrorPriority();
	
private:
	ErrorSubmoduleType error_type;
	ErrorDesc error_desc;
	ErrorPriority error_priority;
};

