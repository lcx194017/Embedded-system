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


//�����ļ�ģ�������
class ConfigurationError
{
public:
	ConfigurationError();
	~ConfigurationError();


	unsigned int SystemDesc_not_exist() const { return systemDesc_not_exist; }
	void SystemDesc_not_exist_set()
	{
		if (SystemDesc_not_exist() < UINT_MAX)
			systemDesc_not_exist++;
	}
	void SystemDesc_not_exist_clear() { systemDesc_not_exist = 0; }

	unsigned int SystemDesc_open_error() const { return systemDesc_open_error; }
	void SystemDesc_open_error_set()
	{
		if (systemDesc_open_error < UINT_MAX)
			systemDesc_open_error++;
	}
	void SystemDesc_open_error_clear() { systemDesc_open_error = 0; }

	unsigned int SystemDesc_checkout_fail() const { return systemDesc_checkout_fail; }
	void SystemDesc_checkout_fail_set()
	{
		if (systemDesc_checkout_fail < UINT_MAX)
			systemDesc_checkout_fail++;
	}
	void SystemDesc_checkout_fail_clear() { systemDesc_checkout_fail = 0; }

	unsigned int SystemDesc_read_fail() const { return systemDesc_read_fail; }
	void SystemDesc_read_fail_set()
	{
		if (systemDesc_read_fail < UINT_MAX)
			systemDesc_read_fail++;
	}
	void SystemDesc_read_fail_clear() { systemDesc_read_fail = 0; }

	unsigned int SystemDesc_write_fail() const { return systemDesc_write_fail; }
	void SystemDesc_write_fail_set()
	{
		if (systemDesc_write_fail < UINT_MAX)
			systemDesc_write_fail++;
	}
	void SystemDesc_write_fail_clear() { systemDesc_write_fail = 0; }


	unsigned int ChannelDesc_not_exist() const { return channelDesc_not_exist; }
	void ChannelDesc_not_exist_set()
	{ 
		if(channelDesc_not_exist < UINT_MAX)
			channelDesc_not_exist++;
	}
	void ChannelDesc_not_exist_clear() { channelDesc_not_exist = 0; }

	unsigned int ChannelDesc_open_error() const { return channelDesc_open_error; }
	void ChannelDesc_open_error_set()
	{ 
		if(channelDesc_open_error < UINT_MAX)
			channelDesc_open_error++; 
	}
	void ChannelDesc_open_error_clear() { channelDesc_open_error = 0; }

	unsigned int ChannelDesc_checkout_fail() const { return channelDesc_checkout_fail; }
	void ChannelDesc_checkout_fail_set()
	{ 
		if(channelDesc_checkout_fail < UINT_MAX)
			channelDesc_checkout_fail++; 
	}
	void ChannelDesc_checkout_fail_clear() { channelDesc_checkout_fail = 0; }

	unsigned int ChannelDesc_read_fail() const { return channelDesc_read_fail; }
	void ChannelDesc_read_fail_set()
	{ 
		if(channelDesc_read_fail < UINT_MAX)
			channelDesc_read_fail++; 
	}
	void ChannelDesc_read_fail_clear() { channelDesc_read_fail = 0; }

	unsigned int ChannelDesc_write_fail() const { return channelDesc_write_fail; }
	void ChannelDesc_write_fail_set()
	{ 
		if(channelDesc_write_fail < UINT_MAX)
			channelDesc_write_fail++; 
	}
	void ChannelDesc_write_fail_clear() { channelDesc_write_fail = 0; }


	unsigned int TriggerDesc_not_exist() const { return triggerDesc_not_exist; }
	void TriggerDesc_not_exist_set()
	{ 
		if(triggerDesc_not_exist < UINT_MAX)
			triggerDesc_not_exist++; 
	}
	void TriggerDesc_not_exist_clear() { triggerDesc_not_exist = 0; }

	unsigned int TriggerDesc_open_error() const { return triggerDesc_open_error; }
	void TriggerDesc_open_error_set()
	{ 
		if(triggerDesc_open_error < UINT_MAX)
			triggerDesc_open_error++; 
	}
	void TriggerDesc_open_error_clear() { triggerDesc_open_error = 0; }

	unsigned int TriggerDesc_checkout_fail() const { return triggerDesc_checkout_fail; }
	void TriggerDesc_checkout_fail_set()
	{ 
		if(triggerDesc_checkout_fail < UINT_MAX)
			triggerDesc_checkout_fail++;
	}
	void TriggerDesc_checkout_fail_clear() { triggerDesc_checkout_fail = 0; }

	unsigned int TriggerDesc_read_fail() const { return triggerDesc_read_fail; }
	void TriggerDesc_read_fail_set()
	{ 
		if(triggerDesc_read_fail < UINT_MAX)
			triggerDesc_read_fail++; 
	}
	void TriggerDesc_read_fail_clear() { triggerDesc_read_fail = 0; }

	unsigned int TriggerDesc_write_fail() const { return triggerDesc_write_fail; }
	void TriggerDesc_write_fail_set()
	{ 
		if(triggerDesc_write_fail < UINT_MAX)
			triggerDesc_write_fail++;
	}
	void TriggerDesc_write_fail_clear() { triggerDesc_write_fail = 0; }



	unsigned int OtherDesc_not_exist() const { return otherDesc_not_exist; }
	void OtherDesc_not_exist_set()
	{ 
		if(otherDesc_not_exist < UINT_MAX)
			otherDesc_not_exist++; 
	}
	void OtherDesc_not_exist_clear() { otherDesc_not_exist = 0; }

	unsigned int OtherDesc_open_error() const { return otherDesc_open_error; }
	void OtherDesc_open_error_set()
	{
		if(otherDesc_open_error < UINT_MAX)
			otherDesc_open_error++;
	}
	void OtherDesc_open_error_clear() { otherDesc_open_error = 0; }

	unsigned int OtherDesc_checkout_fail() const { return otherDesc_checkout_fail; }
	void OtherDesc_checkout_fail_set()
	{ 
		if(otherDesc_checkout_fail < UINT_MAX)
		otherDesc_checkout_fail ++; 
	}
	void OtherDesc_checkout_fail_clear() { otherDesc_checkout_fail = 0; }

	unsigned int OtherDesc_read_fail() const { return otherDesc_read_fail; }
	void OtherDesc_read_fail_set()
	{ 
		if(otherDesc_read_fail < UINT_MAX)
		otherDesc_read_fail ++; 
	}
	void OtherDesc_read_fail_clear() { otherDesc_read_fail = 0; }

	unsigned int OtherDesc_write_fail() const { return otherDesc_write_fail; }
	void OtherDesc_write_fail_set()
	{ 
		if(otherDesc_write_fail < UINT_MAX)
			otherDesc_write_fail++;
	}

private:

	volatile long systemDesc_not_exist = 0;
	volatile long systemDesc_open_error = 0;
	volatile long systemDesc_checkout_fail = 0;
	volatile long systemDesc_read_fail = 0;
	volatile long systemDesc_write_fail = 0;

	volatile long channelDesc_not_exist = 0;
	volatile long channelDesc_open_error = 0;
	volatile long channelDesc_checkout_fail = 0;
	volatile long channelDesc_read_fail = 0;
	volatile long channelDesc_write_fail = 0;

	volatile long triggerDesc_not_exist = 0;
	volatile long triggerDesc_open_error = 0;
	volatile long triggerDesc_checkout_fail = 0;
	volatile long triggerDesc_read_fail = 0;
	volatile long triggerDesc_write_fail = 0;

	volatile long otherDesc_not_exist = 0;
	volatile long otherDesc_open_error = 0;
	volatile long otherDesc_checkout_fail = 0;
	volatile long otherDesc_read_fail = 0;
	volatile long otherDesc_write_fail = 0;

};

//TDMSģ�������
class DataFileError {
public:
	DataFileError();
	~DataFileError();
};


/************************************************************************/
/* ϵͳ����ģ�飬��ģ���»��������Ӽ�����Ӧ��ģ���еĴ���               */
/************************************************************************/
class SystemError
{
public:
	SystemError();
	~SystemError();
	ConfigurationError getConfigurationError() const { return configurationError; }
private:
	ConfigurationError configurationError;
	DataFileError dataFileError;
};


//�������ȼ�ö��
enum ErrorPriority 
{
	LOW, MIDDLE, HIGH
};

//������ģ������ö��
enum ErrorSubmoduleType
{
	CONFIGURATIONERROR, DATAFILEERROR
};

//��������ö��
enum ErrorDesc
{
	SYSTEMDESC_NOT_EXIST,SYSTEMDESC_OPEN_ERROR,SYSTEMDESC_CHECKOUT_FAIL,SYSTEMDESC_READ_FAIL,SYSTEMDESC_WRITE_FAIL,
	CHANNELDESC_NOT_EXIST,CHANNELDESC_OPEN_ERROR,CHANNELDESC_CHECKOUT_FAIL,CHANNELDESC_READ_FAIL,CHANNELDESC_WRITE_FAIL,
	TRIGGERDESC_NOT_EXIST,TRIGGERDESC_OPEN_ERROR,TRIGGERDESC_CHECKOUT_FAIL,TRIGGERDESC_READ_FAIL,TRIGGERDESC_WRITE_FAIL,
	OTHERDESC_NOT_EXIST,OTHERDESC_OPEN_ERROR,OTHERDESC_CHECKOUT_FAIL,OTHERDESC_READ_FAIL,OTHERDESC_WRITE_FAIL
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

