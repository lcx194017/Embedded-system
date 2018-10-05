#pragma once
#include <ctime>
#include "JSONModule.h"
#include <list>
using namespace std;
#pragma warning(disable : 4996)

//触发类型的定义：
//时间间隔触发、特定时间触发、幅值触发、幅值变化触发、速度触发、速度变化触发
enum TriggerType
{
	TIME_INTERVAL, TIME_SPECIFIC, AMPLITUDE, AMPLITUDE_CHANGE, SPEED, SPEED_CHANGE
};


class TriggerModule
{
public:
	TriggerModule();
	~TriggerModule();

	static void init_trigger_rules(const TriggerSettings triggerSettings[] , const int length);

	static bool getTriggerFlag() { return trigger_flag; }
	static void setTriggerFlag(bool state) { trigger_flag = state; }

	static void rule_check(const double *p_data, const int length);

	void method(const TriggerSettings trigger_item, const double* p_date, const int len);

private:

	//触发状态标志,true表示目前不在触发记录状态，可以执行触发；false表示当前已在触发记录了，不可再触发
	static volatile bool trigger_flag;

	//触发规则检查链表
	static list<TriggerSettings> trigger_rules_list;
	static list<double> trigger_last_vlues_list;            //和触发规则链表相对应

	static time_t last_trigger_time;

};


