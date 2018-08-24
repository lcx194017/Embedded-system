#pragma once
#include "PriorityQueue.h"
#include "SystemError.h"
/****************************************************************************************/
/*
文件名称: global.h
功    能: 全局变量的定义
作    者: lcx
小    组: 
联系方式: liu.changxin@qq.com
生成日期: 2018/08/17 15:09
版 本 号: V0.0.0.1
修改日志:
版权说明:
注    意:
*/
/****************************************************************************************/
extern PriorityQueue<CustomError> error_queue;            //错误队列
extern SystemError systemError;                           //系统错误标志位
