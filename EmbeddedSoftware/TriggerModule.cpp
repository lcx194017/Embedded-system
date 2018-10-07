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



//************************************
// Method:    rule_check
// FullName:  TriggerModule::rule_check
// Access:    public static 
// Returns:   void
// Qualifier:
// Parameter: const ChannelGroup channelGroup[]
// Parameter: const int length
// ��������Ǵ��������ɸ�ͨ�������ݣ���ÿ��ͨ������Ӧ�Ĺ�����м���Ƿ���ϴ�������
//************************************
TriggerEventInfo TriggerModule::rule_check(const ChannelGroup channelGroup[], const int length)
{
	TriggerEventInfo triggerEventInfo;
	
	if (!trigger_flag)       //����Ѿ��ڴ���״̬�ˣ�ֱ�ӷ���
		return;

	trigger_flag = false;    //���ô���״̬����ֹ���������߳̽���

	bool trigger_result = false;                 //ͨ��������Ľ����Ĭ��false���������ϴ�������

	//��ÿ��ͨ�������ݶ����й�����
	for (int i = 0; i < length; i++)
	{
		
		ChannelGroup ch_group = channelGroup[i];     //��ȡҪ����ͨ������(��������ϵ�ͨ������Ӧ����洢�е�ͨ����)

		list<TriggerSettings>::iterator trigger_rules_iterator;
		list<double>::iterator trigger_values_iterator;
		for (trigger_rules_iterator = trigger_rules_list.begin(), trigger_values_iterator = trigger_last_vlues_list.begin();
			trigger_rules_iterator != trigger_rules_list.end();
			trigger_rules_iterator++, trigger_values_iterator++)
		{

			//һ��ͨ�������ݿ����ɶ�����ϵĹ��������м�飬����һ������ֻ�ܼ��һ��ͨ��
			//ͨ�� �� ����֮��Ķ�Ӧ��ϵΪ��ͨ��������ͬ�������п���������ͬ�Ĳ�ֹһ������
			//�����ͬһ��ͨ���ļ�����Ͳ�ͬ
			if (ch_group.getGroupName() != trigger_rules_iterator->triggeredChannelName)
				continue;

			if (trigger_rules_iterator->triggerType == "LEVEL")
			{
				list<Channel> ch_list = ch_group.getGroupItems();
				list<Channel>::iterator ch_list_iterator;
				for (ch_list_iterator = ch_list.begin(); ch_list_iterator != ch_list.end(); ch_list_iterator++)
				{
					//�ҵ�ͨ�����������жϵ�ֵ
					//�ҵ���Ϳ��ǲ��Ǹ�ֵ���㴥��������Ȼ������������񶼲��ٲ�ѯͨ���е�����ͨ��
					if (ch_list_iterator->getChannelName() == "MaxValues")  
					{
						unsigned __int64 data_length = ch_list_iterator->getDataLength();
						double *p = ch_list_iterator->getData();
						for (int k = 0; k < data_length; k++)
						{
							if (*p >= trigger_rules_iterator->triggerValue)   //���㴥������
							{
								trigger_result = true;

								//��¼������Ϣ
								triggerEventInfo.triggerEventName = trigger_rules_iterator->triggerEventName;
								triggerEventInfo.siteName = trigger_rules_iterator->triggeredChannelId;
								triggerEventInfo.equipmentName = trigger_rules_iterator->triggeredChannelName;
								triggerEventInfo.dataWatchName = "MaxValues";
								triggerEventInfo.triggeredValue = *p;
								triggerEventInfo.triggerRules = trigger_rules_iterator->triggerType;
								break;
							}
							p++;
						}
						break;
					}	
				}	
			}

			//����trigger_result = true, ��ѭ���е���������Լ�����һ�������ͨ�������ڼ�飬ֱ�ӷ��أ�����ʼдTDMS�ļ�
			//����level��������
			if (trigger_result)
			{
				goto GenerateTriggerInformation;
			}

			if (trigger_rules_iterator->triggerType == "TIME_OF_DAY")
			{
				time_t current_time = time(NULL);
				tm * format_time = localtime(&current_time);
				int time_hour = format_time->tm_hour;                   //�õ���ǰʱ���Сʱ
				int time_minute = format_time->tm_min;                  //�õ���ǰʱ��ķ���

				if (time_hour == trigger_rules_iterator->triggerValue)             //�����ǰʱ����趨ʱ����ȣ���ʼ����
				{
					trigger_result = true;

					//��¼������Ϣ
					triggerEventInfo.triggerEventName = trigger_rules_iterator->triggerEventName;
					triggerEventInfo.siteName = trigger_rules_iterator->triggeredChannelId;
					triggerEventInfo.equipmentName = trigger_rules_iterator->triggeredChannelName;
					triggerEventInfo.dataWatchName = "TIME_OF_DAY";
					triggerEventInfo.triggeredValue = trigger_rules_iterator->triggerValue;
					triggerEventInfo.triggerRules = trigger_rules_iterator->triggerType;
				}
			}

			//����TIME_OF_DAY��������
			if (trigger_result)
			{
				goto GenerateTriggerInformation;
			}

			if (trigger_rules_iterator->triggerType == "TIME_INTERVAL")
			{
				time_t current_time = time(NULL);
				if (current_time - *trigger_values_iterator > trigger_rules_iterator->triggerValue)    //�趨��ʱ��������
				{
					trigger_result = true;
					last_trigger_time = current_time;      //�����ϴδ���ʱ��

					//��¼������Ϣ
					triggerEventInfo.triggerEventName = trigger_rules_iterator->triggerEventName;
					triggerEventInfo.siteName = trigger_rules_iterator->triggeredChannelId;
					triggerEventInfo.equipmentName = trigger_rules_iterator->triggeredChannelName;
					triggerEventInfo.dataWatchName = "TIME_INTERVAL";
					triggerEventInfo.triggeredValue = trigger_rules_iterator->triggerValue;
					triggerEventInfo.triggerRules = trigger_rules_iterator->triggerType;
				}
				
			}

			//����TIME_INTERVAL��������
			if (trigger_result)
			{
				goto GenerateTriggerInformation;
			}

			if (trigger_rules_iterator->triggerType == "DELTA_EU")
			{
				list<Channel> ch_list = ch_group.getGroupItems();
				list<Channel>::iterator ch_list_iterator;
				for (ch_list_iterator = ch_list.begin(); ch_list_iterator != ch_list.end(); ch_list_iterator++)
				{
					//�ҵ�ͨ�����������жϵ�ֵ
					//�ҵ���Ϳ��ǲ��Ǹ�ֵ���㴥��������Ȼ������������񶼲��ٲ�ѯͨ���е�����ͨ��
					if (ch_list_iterator->getChannelName() == "DCValues")
					{
						unsigned __int64 data_length = ch_list_iterator->getDataLength();
						double *p = ch_list_iterator->getData();
						for (int k = 0; k < data_length; k++)
						{
							//���������һ�εı仯ֵ�����㴥������
							if (abs(*p - *trigger_values_iterator) > trigger_rules_iterator->triggerValue)   
							{
								trigger_result = true;
								*trigger_values_iterator = *p;   //������һ�εı仯ֵ

								//��¼������Ϣ
								triggerEventInfo.triggerEventName = trigger_rules_iterator->triggerEventName;
								triggerEventInfo.siteName = trigger_rules_iterator->triggeredChannelId;
								triggerEventInfo.equipmentName = trigger_rules_iterator->triggeredChannelName;
								triggerEventInfo.dataWatchName = "DCValues";
								triggerEventInfo.triggeredValue = *p;
								triggerEventInfo.triggerRules = trigger_rules_iterator->triggerType;
								break;
							}
							p++;
						}
						break;
					}
				}
			}

			//����DELTA_EU��������
			if (trigger_result)
			{
				goto GenerateTriggerInformation;
			}

			if (trigger_rules_iterator->triggerType == "DELTA_SPEED")
			{
				list<Channel> ch_list = ch_group.getGroupItems();
				list<Channel>::iterator ch_list_iterator;
				for (ch_list_iterator = ch_list.begin(); ch_list_iterator != ch_list.end(); ch_list_iterator++)
				{
					//�ҵ�ͨ�����������жϵ�ֵ
					//�ҵ���Ϳ��ǲ��Ǹ�ֵ���㴥��������Ȼ������������񶼲��ٲ�ѯͨ���е�����ͨ��
					if (ch_list_iterator->getChannelName() == "DCValues")
					{
						unsigned __int64 data_length = ch_list_iterator->getDataLength();
						double *p = ch_list_iterator->getData();
						for (int k = 0; k < data_length; k++)
						{
							//���������һ�εı仯ֵ�����㴥������
							if (abs(*p - *trigger_values_iterator) > trigger_rules_iterator->triggerValue)   
							{
								trigger_result = true;
								*trigger_values_iterator = *p;   //������һ�εı仯ֵ
								
								//��¼������Ϣ
								triggerEventInfo.triggerEventName = trigger_rules_iterator->triggerEventName;
								triggerEventInfo.siteName = trigger_rules_iterator->triggeredChannelId;
								triggerEventInfo.equipmentName = trigger_rules_iterator->triggeredChannelName;
								triggerEventInfo.dataWatchName = "DCValues";
								triggerEventInfo.triggeredValue = *p;
								triggerEventInfo.triggerRules = trigger_rules_iterator->triggerType;
								break;
							}
							p++;
						}
						break;
					}
				}
			}

			//����DELTA_SPEED��������
			if (trigger_result)
			{
				goto GenerateTriggerInformation;
			}
		}
	}

GenerateTriggerInformation:
	if (trigger_result)
	{
		time_t nowtime = time(NULL);
		char tmp[64];
		strftime(tmp, sizeof(tmp), "%Y_%m_%d_%H_%M_%S", localtime(&nowtime));
		triggerEventInfo.triggeredtime = string(tmp);
		triggerEventInfo.eventFileName = triggerEventInfo.triggerEventName + "_" 
			+ triggerEventInfo.triggerRules + "_" 
			+ triggerEventInfo.equipmentName + "_" 
			+ triggerEventInfo.siteName + "_" 
			+ triggerEventInfo.triggeredtime;
	}
	else
	{
		//������������������Ļ����������������óɿɽ���״̬
		//������Ҫ�ȵ�120s��������Ϊ�ɽ���״̬
		trigger_flag = true;   
	}
	
	return triggerEventInfo;

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
