#include "TriggerModule.h"

volatile bool TriggerModule::trigger_flag = true;

list<TriggerSettings> TriggerModule::trigger_rules_list;

list<double> TriggerModule::trigger_last_vlues_list;

time_t TriggerModule::last_trigger_time = time(NULL);      //ʱ����ģʽ�£���һ�δ���ʱ������Ϊϵͳ������ʱ��

TriggerModule::TriggerModule()
{
}


TriggerModule::~TriggerModule()
{
}

//************************************
// Method:    init_trigger_rules
// FullName:  TriggerModule::init_trigger_rules
// Access:    public static 
// Returns:   void
// Qualifier:
// Parameter: const TriggerSettings triggerSettings[]
// Parameter: const int length
// JSON�ļ������������������򣬶�Ӧ�ڴ��е�һ��TriggerSettings���飬��������
// Triggerģ�鶨����һ����̬TriggerSettings���������������������������
//************************************
void TriggerModule::init_trigger_rules(const TriggerSettings triggerSettings[], const int length)
{
	for (int i = 0; i < length; i++) 
	{
		trigger_rules_list.push_back(triggerSettings[i]);
		trigger_last_vlues_list.push_back(0);    //�ϴδ���ֵĬ��0
	}

	trigger_rules_list.sort();
}

void TriggerModule::rule_check(const double *p_data, const int length)
{
	
	if (!trigger_flag)       //����Ѿ��ڴ���״̬�ˣ�ֱ�ӷ���
		return;

	trigger_flag = false;    //���ô���״̬����ֹ���������߳̽���
	
	//������Buffer�е�����Copy�����ؽ��д���
	double *data = new double[length];
	memset(data, 0, length * sizeof(double));
	memcpy(data, p_data, length * sizeof(double));

	list<TriggerSettings>::iterator trigger_rules_iterator;
	list<double>::iterator trigger_values_iterator;

	for (trigger_rules_iterator = trigger_rules_list.begin(), trigger_values_iterator = trigger_last_vlues_list.begin(); 
		trigger_rules_iterator != trigger_rules_list.end(); 
		trigger_rules_iterator++, trigger_values_iterator++)
	{
		
	}
	delete[] data;

	trigger_flag = true;   //���ô���Ϊ����״̬
}

void TriggerModule::method(const TriggerSettings trigger_item, const double* p_date, const int len)
{
	bool flag = false;
	/*string triggerEventName":"Time interval_Alarm",
		"triggeredChannelId" : "911",
		"triggeredChannelName" : "315 TURB KEY PHASOR_KA371",*/
	if (trigger_item.triggerType == "LEVEL")
	{
		for (int i = 0; i < len; i++)
			if (p_date[i] > trigger_item.triggerValue)
				flag = true;
	}
	else if (trigger_item.triggerType == "TIME_OF_DAY")
	{
		time_t current_time = time(NULL);
		tm * format_time = localtime(&current_time);
		int time_hour = format_time->tm_hour;                   //�õ���ǰʱ���Сʱ
		int time_minute = format_time->tm_min;                  //�õ���ǰʱ��ķ���

		if (time_hour == trigger_item.triggerValue)             //�����ǰʱ����趨ʱ����ȣ���ʼ����
			flag = true;
	}
	else if (trigger_item.triggerType == "DELTA_EU")
	{

	}
	else if (trigger_item.triggerType == "DELTA_SPEED")
	{

	}
	else if (trigger_item.triggerType == "TIME_INTERVAL")
	{
		time_t current_time = time(NULL);
		if (current_time - last_trigger_time > trigger_item.triggerValue)    //�趨��ʱ��������
			flag = true;
		last_trigger_time = current_time;  //�����ϴδ�������
	}

	if (flag)   //����ﵽ��������
	{
		time_t nowtime = time(NULL);    
		char tmp[64];
		strftime(tmp, sizeof(tmp), "%Y_%m_%d_%H_%M_%S", localtime(&nowtime));
		string time_stamp = string(tmp);

		string tdms_file_name = trigger_item.triggerEventName + "_" + trigger_item.triggerType + "_" + trigger_item.triggeredChannelName +
			"_" + "�豸����" + "_" + time_stamp;
	}
}
