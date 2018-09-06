#pragma once
#include <ctime>
using namespace std;
#pragma warning(disable : 4996)

//�������͵Ķ��壺
//ʱ�����������ض�ʱ�䴥������ֵ��������ֵ�仯�������ٶȴ������ٶȱ仯����
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

	int triggerJudge();     //��ʱ���ã��ɸ���ϵͳ�Դ�������ӦҪ�������Ե��á� Ĭ��1s����һ��
private:

	//������ʽ
	TriggerType triggerType;

	//�̶�ʱ��������
	time_t time_interval;			//�趨ʱ����
	time_t last_trigger_time;		//�ϴδ���ʱ���¼

									//�̶�ʱ�䴥��
	int hour_regular;				//����ʱ�䡪��Сʱ          
	int minute_regular;				//����ʱ�䡪������

									//��ֵ����
	double amplitude_threshold;		//��ֵ����

									//��ֵ�仯����
	double amplitude_change_threshold; //��ֵ�仯����

									   //�ٶȴ���
	double speed_threshold;			//�ٶȴ���

									//�ٶȱ仯����
	double speed_change_threshold;		//�ٶȱ仯����
};


