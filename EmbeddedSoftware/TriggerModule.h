#pragma once
#include <ctime>
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

	void setTriggerType(TriggerType type);

	void setTriggerInterval(time_t interval);

	void setTriggerTime(int hour, int minute);

	void setAmplitudeThreshold(double threshold);

	void setAmplitudeChangeThreshold(double threashold);

	void setSpeedThreashold(double threashold);

	void setSpeeedChangeThreashold(double threashold);

	int triggerJudge();     //定时调用，可根据系统对触发的响应要求，周期性调用。 默认1s调用一次
private:

	//触发方式
	TriggerType triggerType;

	//固定时间间隔触发
	time_t time_interval;			//设定时间间隔
	time_t last_trigger_time;		//上次触发时间记录

									//固定时间触发
	int hour_regular;				//触发时间——小时          
	int minute_regular;				//触发时间——分钟

									//幅值触发
	double amplitude_threshold;		//幅值界限

									//幅值变化触发
	double amplitude_change_threshold; //幅值变化界限

									   //速度触发
	double speed_threshold;			//速度触发

									//速度变化触发
	double speed_change_threshold;		//速度变化触发
};


