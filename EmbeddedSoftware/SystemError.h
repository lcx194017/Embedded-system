#pragma once
#include <windows.h>
#include <climits>
using namespace std;


/*
	edit by lcx
	����ģ����ƣ�
	�����״̬�����ʶ�˵�ǰ����ϵͳ��״̬��SystemEorrorΪȫ���Դ����־�������ַ�Ϊ���ɸ���ģ�飨��ϵͳ��ģ�黮�����Ӧ����
	��ģ���ж����˴���ľ������͡�
	ÿ����ģ���еĴ������Ͷ����붨���private���Է������޸��ƻ�ϵͳ�������״̬ͨ��3���������޸ĺͻ�ȡ
	unsigned int **** ();  ����>  ��ȡ�����Ƿ���ڣ��Լ�������0��û�д��� >=1 ������  �������unsigned int �Ǳ�ʶ���������
	void ****_set();  ����> �������ʱ����λ�� ��γ��־��Ǵ���+1
	void ****_clear();  ����> ��������ģ�鴦����������ã���������־��

	ϵͳ��ͬʱΪ������ά��һ�����ȼ����У��������̴߳Ӷ�����ȡ�����󲢴���
	�����зŵ����Զ�����󣬼�CustomError��ͨ���������͡������������������ȼ����ж���

	�������ʱ��
				(1)������Ӧ�Ĵ����־λ ����> (2)�����Զ���������ͣ����������ȼ�����
	������ʱ��
				(1)�Ӷ�����ȡ�����ȼ���ߵĴ���  ����> (2)������ɹ�����������־λ�� �粻�ɹ��������Ӧ�Ĵ�ʩ�����ص�ʱ��ػ�����
*/


//Json�����ļ�ģ�������
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

//TDMSģ�������
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
/* ϵͳ����ģ�飬��ģ���»��������Ӽ�����Ӧ��ģ���еĴ���               */
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


//�������ȼ�ö��
enum ErrorPriority 
{
	LOW, MIDDLE, HIGH
};

//������ģ������ö��
enum ErrorSubmoduleType
{
	//Json����ģ�����
	JSONCONFIGURATIONERROR, 
	//TDMSģ�����
	TDMSERROR
};

//��������ö��
enum ErrorDesc
{
	//JSON�����ļ���д��صĴ�����
	SYSTEMINFO_NOT_EXIST,SYSTEMINFO_OPEN_ERROR,SYSTEMINFO_CHECKOUT_FAIL,SYSTEMINFO_READ_FAIL,SYSTEMINFO_WRITE_FAIL,
	CHANNELSETTINGS_NOT_EXIST,CHANNELSETTINGS_OPEN_ERROR,CHANNELSETTINGS_CHECKOUT_FAIL,CHANNELSETTINGS_READ_FAIL,CHANNELSETTINGS_WRITE_FAIL,
	TRIGGERSETTINGS_NOT_EXIST,TRIGGERSETTINGS_OPEN_ERROR,TRIGGERSETTINGS_CHECKOUT_FAIL,TRIGGERSETTINGS_READ_FAIL,TRIGGERSETTINGS_WRITE_FAIL,
	SYSTEMSETTINGS_NOT_EXIST,SYSTEMSETTINGS_OPEN_ERROR,SYSTEMSETTINGS_CHECKOUT_FAIL,SYSTEMSETTINGS_READ_FAIL,SYSTEMSETTINGS_WRITE_FAIL,
	//TDMS��д������
	TDMS_READ_FAIL, TDMS_WRITE_FAIL
};


//�Զ������
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

