#include "TriggerModule.h"

volatile bool TriggerModule::trigger_flag = true;

list<TriggerSettings> TriggerModule::trigger_rules_list;

list<double> TriggerModule::trigger_last_vlues_list;

time_t TriggerModule::last_trigger_time = time(NULL);      //时间间隔模式下，上一次触发时间设置为系统启动的时间

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
// JSON文件中有若干条触发规则，对应内存中的一个TriggerSettings数组，但是无序
// Trigger模块定义了一个静态TriggerSettings链表，将触发规则加入链表，并排序
//************************************
void TriggerModule::init_trigger_rules(const TriggerSettings triggerSettings[], const int length)
{
	for (int i = 0; i < length; i++) 
	{
		trigger_rules_list.push_back(triggerSettings[i]);
		trigger_last_vlues_list.push_back(0);    //上次触发值默认0
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
// 函数入参是处理后的若干个通道的数据，对每个通道用响应的规则进行检查是否符合触发条件
//************************************
TriggerEventInfo TriggerModule::rule_check(const ChannelGroup channelGroup[], const int length)
{
	TriggerEventInfo triggerEventInfo;
	
	if (!trigger_flag)       //如果已经在触发状态了，直接返回
		return;

	trigger_flag = false;    //设置触发状态，防止其它触发线程进入

	bool trigger_result = false;                 //通道规则检查的结果，默认false，即不符合触发条件

	//对每个通道的数据都进行规则检查
	for (int i = 0; i < length; i++)
	{
		
		ChannelGroup ch_group = channelGroup[i];     //获取要检查的通道数据(物理概念上的通道，对应程序存储中的通道组)

		list<TriggerSettings>::iterator trigger_rules_iterator;
		list<double>::iterator trigger_values_iterator;
		for (trigger_rules_iterator = trigger_rules_list.begin(), trigger_values_iterator = trigger_last_vlues_list.begin();
			trigger_rules_iterator != trigger_rules_list.end();
			trigger_rules_iterator++, trigger_values_iterator++)
		{

			//一个通道的数据可能由多个符合的规则对其进行检查，但是一个规则只能检查一个通道
			//通道 和 规则之间的对应关系为：通道名称相同，规则中可能名称相同的不止一个，但
			//是其对同一个通道的检查类型不同
			if (ch_group.getGroupName() != trigger_rules_iterator->triggeredChannelName)
				continue;

			if (trigger_rules_iterator->triggerType == "LEVEL")
			{
				list<Channel> ch_list = ch_group.getGroupItems();
				list<Channel>::iterator ch_list_iterator;
				for (ch_list_iterator = ch_list.begin(); ch_list_iterator != ch_list.end(); ch_list_iterator++)
				{
					//找到通道中用于做判断的值
					//找到后就看是不是该值满足触发条件，然后无论满足与否都不再查询通道中的其它通道
					if (ch_list_iterator->getChannelName() == "MaxValues")  
					{
						unsigned __int64 data_length = ch_list_iterator->getDataLength();
						double *p = ch_list_iterator->getData();
						for (int k = 0; k < data_length; k++)
						{
							if (*p >= trigger_rules_iterator->triggerValue)   //满足触发条件
							{
								trigger_result = true;

								//记录触发信息
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

			//但凡trigger_result = true, 本循环中的其余规则以及再外一层的其它通道都不在检查，直接返回，并开始写TDMS文件
			//满足level触发条件
			if (trigger_result)
			{
				goto GenerateTriggerInformation;
			}

			if (trigger_rules_iterator->triggerType == "TIME_OF_DAY")
			{
				time_t current_time = time(NULL);
				tm * format_time = localtime(&current_time);
				int time_hour = format_time->tm_hour;                   //得到当前时间的小时
				int time_minute = format_time->tm_min;                  //得到当前时间的分钟

				if (time_hour == trigger_rules_iterator->triggerValue)             //如果当前时间和设定时间相等，开始触发
				{
					trigger_result = true;

					//记录触发信息
					triggerEventInfo.triggerEventName = trigger_rules_iterator->triggerEventName;
					triggerEventInfo.siteName = trigger_rules_iterator->triggeredChannelId;
					triggerEventInfo.equipmentName = trigger_rules_iterator->triggeredChannelName;
					triggerEventInfo.dataWatchName = "TIME_OF_DAY";
					triggerEventInfo.triggeredValue = trigger_rules_iterator->triggerValue;
					triggerEventInfo.triggerRules = trigger_rules_iterator->triggerType;
				}
			}

			//满足TIME_OF_DAY触发条件
			if (trigger_result)
			{
				goto GenerateTriggerInformation;
			}

			if (trigger_rules_iterator->triggerType == "TIME_INTERVAL")
			{
				time_t current_time = time(NULL);
				if (current_time - *trigger_values_iterator > trigger_rules_iterator->triggerValue)    //设定的时间间隔到了
				{
					trigger_result = true;
					last_trigger_time = current_time;      //更新上次触发时间

					//记录触发信息
					triggerEventInfo.triggerEventName = trigger_rules_iterator->triggerEventName;
					triggerEventInfo.siteName = trigger_rules_iterator->triggeredChannelId;
					triggerEventInfo.equipmentName = trigger_rules_iterator->triggeredChannelName;
					triggerEventInfo.dataWatchName = "TIME_INTERVAL";
					triggerEventInfo.triggeredValue = trigger_rules_iterator->triggerValue;
					triggerEventInfo.triggerRules = trigger_rules_iterator->triggerType;
				}
				
			}

			//满足TIME_INTERVAL触发条件
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
					//找到通道中用于做判断的值
					//找到后就看是不是该值满足触发条件，然后无论满足与否都不再查询通道中的其它通道
					if (ch_list_iterator->getChannelName() == "DCValues")
					{
						unsigned __int64 data_length = ch_list_iterator->getDataLength();
						double *p = ch_list_iterator->getData();
						for (int k = 0; k < data_length; k++)
						{
							//如果大于上一次的变化值，满足触发条件
							if (abs(*p - *trigger_values_iterator) > trigger_rules_iterator->triggerValue)   
							{
								trigger_result = true;
								*trigger_values_iterator = *p;   //更新上一次的变化值

								//记录触发信息
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

			//满足DELTA_EU触发条件
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
					//找到通道中用于做判断的值
					//找到后就看是不是该值满足触发条件，然后无论满足与否都不再查询通道中的其它通道
					if (ch_list_iterator->getChannelName() == "DCValues")
					{
						unsigned __int64 data_length = ch_list_iterator->getDataLength();
						double *p = ch_list_iterator->getData();
						for (int k = 0; k < data_length; k++)
						{
							//如果大于上一次的变化值，满足触发条件
							if (abs(*p - *trigger_values_iterator) > trigger_rules_iterator->triggerValue)   
							{
								trigger_result = true;
								*trigger_values_iterator = *p;   //更新上一次的变化值
								
								//记录触发信息
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

			//满足DELTA_SPEED触发条件
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
		//如果触发条件不成立的话，将触发调用设置成可进入状态
		//否则需要等到120s后再设置为可进入状态
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
		int time_hour = format_time->tm_hour;                   //得到当前时间的小时
		int time_minute = format_time->tm_min;                  //得到当前时间的分钟

		if (time_hour == trigger_item.triggerValue)             //如果当前时间和设定时间相等，开始触发
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
		if (current_time - last_trigger_time > trigger_item.triggerValue)    //设定的时间间隔到了
			flag = true;
		last_trigger_time = current_time;  //更新上次触发条件
	}

	if (flag)   //如果达到触发条件
	{
		time_t nowtime = time(NULL);    
		char tmp[64];
		strftime(tmp, sizeof(tmp), "%Y_%m_%d_%H_%M_%S", localtime(&nowtime));
		string time_stamp = string(tmp);

		string tdms_file_name = trigger_item.triggerEventName + "_" + trigger_item.triggerType + "_" + trigger_item.triggeredChannelName +
			"_" + "设备名称" + "_" + time_stamp;
	}
}
