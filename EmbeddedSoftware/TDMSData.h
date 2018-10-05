#pragma once
#include <map>
#include <string>
#include <list>
#include <iostream>
#include "nilibddc.h"
using namespace std;

#define GROUPS_MAX 20
#define CHANNELS_MAX 200

#define ddcChk(f) if (ddcError = (f), ddcError < 0) goto Error; else
#define nullChk(p) if (!(p)) { ddcError = DDC_OutOfMemory; goto Error; } else

//存储TDMS中的时间戳
struct Timestamp
{
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	double milliSecond;
	unsigned int weekDay;
};

//TDMS文件中的一个通道
class Channel
{
public:

	Channel();
	Channel(string name);
	~Channel();

	void setChannelName(string name);
	void set_wf_start_time(Timestamp start_time);
	void set_wf_start_offset(double start_offset);
	void set_wf_samples(int samples);
	void set_wf_increment(double increment);
	void set_NI_DataType(int DataType);
	void set_NI_ChannelLength(unsigned __int64 ChannelLength);

	string getChannelName();
	Timestamp get_wf_start_time();
	double get_wf_start_offset();
	int get_wf_samples();
	double get_wf_increment();
	int get_NI_DataType();
	unsigned __int64 get_NI_ChannelLength();

	void setData(double* point, unsigned __int64 legth);
	double* getData();
	unsigned __int64 getDataLength();

private:
	string channel_name;
	Timestamp wf_start_time;
	double wf_start_offset;
	int wf_samples;
	double wf_increment;
	int NI_DataType;
	unsigned __int64 NI_ChannelLength;

	double* data_point = 0;
	unsigned __int64 data_length = 0;
};

//TDMS文件中的一个通道组
class ChannelGroup
{
public:
	ChannelGroup();
	ChannelGroup(string name);
	ChannelGroup(string name, string group_channel_type);
	~ChannelGroup();

	void setGroupName(string name);           //设置通道组名
	void setGroupChannelType(string group_channel_type);
	void setGroupItems(list<Channel> items);
	string getGroupName();
	string getGroupChannelType();
	void addChannel(Channel channel);         //往通道组添加一个Channel
	list<Channel> getGroupItems();            //获取通道组中的所有通道


private:
	string group_name;                        //通道组名
	string channel_type;                      //通道类型[注意:这里的通道类型指的是物理通道的类型，和TDMS文件中的一个通道组对应]
	list<Channel> group_items;                //通道组中的Channels
};

//对应一个TDMS数据文件
class TDMSData
{

public:
	TDMSData();
	~TDMSData();

	void setGroups(list<ChannelGroup> data);
	void addGroup(ChannelGroup group);                    //往tdms文件中添加一个通道组
	list<ChannelGroup> getGroups();                       //获取所有的通道组

	void setProperties(string key, string value);         //设置文件的属性值
	string getPropertyVaule(string key);                  //获取默认属性中的item
	map<string, string> getProperties();                  //获取文件属性

	void set_property_name(string name);
	string get_property_name();

	int read_tdms(string file_path, string file_name);                                      //读TDMS文件
	int write_tdms(string file_path, string file_name);   //写TDMS文件

private:
	string property_name;                                 //FILE层name字段
	map<string, string> properties;                       //文件默认属性

	list<ChannelGroup>  groups;                           //通道组
};

