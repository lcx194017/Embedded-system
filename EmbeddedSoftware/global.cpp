#include "global.h"

//ϵͳJson��������
SystemInfo systemInfo;
ChannelSettings channelSettings;
TriggerSettings triggerSettings;
SystemSettings systemSettings;

//ϵͳ�����ʶ�ʹ������ȼ�����
PriorityQueue<CustomError> error_queue;
SystemError systemError;

//ϵͳ�߳����б�־
bool main_thread_flag = true;
bool working_thread_flag = true;
bool monitoring_thread_flag = true;
bool error_handling_thread_flag = true;
bool server_threads_flag = true;