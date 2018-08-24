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

//TDMS文件中的一个通道
class Channel
{
public:

	Channel();
	Channel(string name, string description);
	~Channel();

	void setProperties(string key, string value);  //设置channel的属性值
	string findDefaultProperty(string key);               //获取默认属性中的item
	map<string, string> getExtraProperties();             //获取所有额外属性

	void setData(double* point, unsigned __int64 legth);
	double* getData();
	unsigned __int64 getDataLength();
	
private:
	map<string, string> default_properties;               //Channel的默认属性
	map<string, string> extra_properties;                 //Channel的额外属性
	double* data_point = 0;
	unsigned __int64 data_length = 0;     
};

//TDMS文件中的一个通道组
class ChannelGroup
{
public:
	ChannelGroup();
	ChannelGroup(string name);                   
	ChannelGroup(string name, string description);
	~ChannelGroup();
	 
	void setGroupName(string name);         //设置通道组名
	void setGroupDescription(string description);
	void setGroupItems(list<Channel> items);
	string getGroupName();
	string getGroupDescription();
	void setExtraProperties(string key, string value);    //设置通道组的额外属性值
	map<string, string> getExtraProperties();             //获取所有额外属性
	void addChannel(Channel channel);       //往通道组添加一个Channel
	list<Channel> getGroupItems();          //获取通道组中的所有通道
	

private:
	string group_name;                      //通道组名
	string group_description;               //通道组描述
	map<string, string> extra_properties;   //通道组的额外属性
	list<Channel> group_items;              //通道组中的Channels
};

//对应一个TDMS数据文件
class TDMSData
{

public:
	TDMSData(string filepath, string filename);
	~TDMSData();

	void setGroups(list<ChannelGroup> data);
	void addGroup(ChannelGroup group);                    //往tdms文件中添加一个通道组
	list<ChannelGroup> getGroups();                       //获取所有的通道组

	void setProperties(string key, string value);         //设置文件的属性值
	string findDefaultProperty(string key);               //获取默认属性中的item

	map<string, string> getExtraProperties();             //获取所有额外属性
	int read_tdms();                                      //读TDMS文件
	int write_tdms();                                     //写TDMS文件

private:
	string file_path;                                     //TDMS文件的路径
	string file_name;                                     //TDMS文件的名称

	map<string, string> default_properties;               //文件的默认属性
	map<string, string> extra_properties;                 //文件的额外属性
	list<ChannelGroup>  groups;                           //通道组
};

