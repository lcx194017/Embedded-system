#pragma once
#include "JSONModule.h"
#include "PriorityQueue.h"
#include "SystemError.h"
/****************************************************************************************/
/*
�ļ�����: global.h
��    ��: ȫ�ֱ����Ķ���
��    ��: lcx
С    ��: 
��ϵ��ʽ: liu.changxin@qq.com
��������: 2018/08/17 15:09
�� �� ��: V0.0.0.1
�޸���־:
��Ȩ˵��:
ע    ��:
*/
/****************************************************************************************/

//ϵͳJson��������
extern SystemInfo systemInfo;
extern ChannelSettings channelSettings;
extern TriggerSettings triggerSettings;
extern SystemSettings systemSettings;

extern PriorityQueue<CustomError> error_queue;            //�������
extern SystemError systemError;                           //ϵͳ�����־λ

extern bool main_thread_flag;                             //ϵͳ�߳����б�־λ
extern bool working_thread_flag;
extern bool monitoring_thread_flag;
extern bool error_handling_thread_flag;
extern bool server_threads_flag;


