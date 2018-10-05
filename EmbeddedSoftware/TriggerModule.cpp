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

void TriggerModule::rule_check(const double *p_data, const int length)
{
	
	if (!trigger_flag)       //如果已经在触发状态了，直接返回
		return;

	trigger_flag = false;    //设置触发状态，防止其它触发线程进入
	
	//将数据Buffer中的数据Copy到本地进行处理
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

	trigger_flag = true;   //设置触发为可入状态
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
