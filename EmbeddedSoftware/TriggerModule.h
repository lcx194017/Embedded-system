#pragma once
#include <ctime>
#include "JSONModule.h"
#include "TDMSData.h"
#include <math.h>
#include <list>
using namespace std;
#pragma warning(disable : 4996)

//�������͵Ķ��壺
//ʱ�����������ض�ʱ�䴥������ֵ��������ֵ�仯�������ٶȴ������ٶȱ仯����
enum TriggerType
{
	TIME_INTERVAL, TIME_SPECIFIC, AMPLITUDE, AMPLITUDE_CHANGE, SPEED, SPEED_CHANGE
};



typedef struct
{
	string triggerEventName;
	string siteName;
	string equipmentName;
	string dataWatchName;
	string eventFileName;
	double triggeredValue;
	string triggeredtime;
	string triggerRules;

}TriggerEventInfo;


class TriggerModule
{
public:
	TriggerModule();
	~TriggerModule();

	static void init_trigger_rules(const TriggerSettings triggerSettings[] , const int length);

	static bool getTriggerFlag() { return trigger_flag; }
	static void setTriggerFlag(bool state) { trigger_flag = state; }

	static TriggerEventInfo rule_check(const ChannelGroup channelGroup[], const int length);

	void method(const TriggerSettings trigger_item, const double* p_date, const int len);

private:

	//����״̬��־,true��ʾĿǰ���ڴ�����¼״̬������ִ�д�����false��ʾ��ǰ���ڴ�����¼�ˣ������ٴ���
	static volatile bool trigger_flag;

	//��������������
	static list<TriggerSettings> trigger_rules_list;
	static list<double> trigger_last_vlues_list;            //�ʹ��������������Ӧ

	static time_t last_trigger_time;

};


