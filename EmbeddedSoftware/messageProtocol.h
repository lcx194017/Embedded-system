#pragma once

/************************************************************************/
/* 定义文件传输过程中的消息及协议                                          */
/************************************************************************/

#define MAX_PACK_SIZE  10240      //数据包的长度
#define MAX_FILE_NAME_LENGTH 256  //文件名的长度
#define INVALID_MSG -1            //无效的消息
#define MSG_FILE_LENGTH 1         //文件长度
#define MSG_FILE_NAME 2           //文件名
#define MSG_FILE   4              //文件内容
#define MSG_READY   3             //准备好消息
#define MSG_SEND_FILE 5           //发送文件
#define MSG_DOWNLOAD_FILE 6       //下载文件
#define MSG_COMPLETE 7            //完成信息