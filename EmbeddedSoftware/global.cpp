#include "global.h"

//系统Json配置数据
SystemInfo systemInfo;
ChannelSettings channelSettings;
TriggerSettings triggerSettings;
SystemSettings systemSettings;

//系统错误标识和错误优先级队列
PriorityQueue<CustomError> error_queue;
SystemError systemError;

//系统线程运行标志
bool main_thread_flag = true;
bool working_thread_flag = true;
bool monitoring_thread_flag = true;
bool error_handling_thread_flag = true;
bool server_threads_flag = true;