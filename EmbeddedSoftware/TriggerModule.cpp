#include "TriggerModule.h"

TriggerModule::TriggerModule()
{
}


TriggerModule::~TriggerModule()
{
}

void TriggerModule::setTriggerType(TriggerType type)
{
	triggerType = type;
}

void TriggerModule::setTriggerInterval(time_t interval)
{
	time_interval = interval;
}

void TriggerModule::setTriggerTime(int hour, int minute)
{
	hour_regular = hour;
	minute_regular = minute;
}
void TriggerModule::setAmplitudeThreshold(double threshold)
{
	amplitude_threshold = threshold;
}

void TriggerModule::setAmplitudeChangeThreshold(double threashold)
{
	amplitude_change_threshold = threashold;
}

void TriggerModule::setSpeedThreashold(double threashold)
{
	speed_threshold = threashold;
}

void TriggerModule::setSpeeedChangeThreashold(double threashold)
{
	speed_change_threshold = threashold;
}

int TriggerModule::triggerJudge()
{
	time_t now_time;
	time_t long_time;
	tm * newtime;
	int h;
	int m;

	switch (triggerType)
	{
	case TIME_INTERVAL:
		now_time = time(NULL);
		if (now_time - last_trigger_time >= time_interval)
		{
			//在新线程中进行触发操作
			last_trigger_time = time_interval;
		}
		break;
	case TIME_SPECIFIC:

		long_time = time(NULL);
		newtime = localtime(&long_time);
		h = newtime->tm_hour;  //得到当前时间的小时
		m = newtime->tm_min;   //得到当前时间的分钟
		if (h == hour_regular && m == minute_regular)
		{
			//在新线程中进行触发操作
		}
		break;
	case AMPLITUDE:
		if (0 > amplitude_threshold)
		{
			//在新线程中执行触发
		}
		break;
	case AMPLITUDE_CHANGE:
		if (0 > amplitude_change_threshold)
		{
			//在新线程中执行触发
		}
		break;
	case SPEED:
		if (0 > speed_threshold)
		{
			//在新线程中执行触发
		}
		break;
	case SPEED_CHANGE:
		if (0 > speed_change_threshold)
		{
			//在新线程中执行触发
		}
		break;
	default:
		break;
	}
	return 0;
}
