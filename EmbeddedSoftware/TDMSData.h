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

//TDMS�ļ��е�һ��ͨ��
class Channel
{
public:

	Channel();
	Channel(string name, string description);
	~Channel();

	void setProperties(string key, string value);  //����channel������ֵ
	string findDefaultProperty(string key);               //��ȡĬ�������е�item
	map<string, string> getExtraProperties();             //��ȡ���ж�������

	void setData(double* point, unsigned __int64 legth);
	double* getData();
	unsigned __int64 getDataLength();
	
private:
	map<string, string> default_properties;               //Channel��Ĭ������
	map<string, string> extra_properties;                 //Channel�Ķ�������
	double* data_point = 0;
	unsigned __int64 data_length = 0;     
};

//TDMS�ļ��е�һ��ͨ����
class ChannelGroup
{
public:
	ChannelGroup();
	ChannelGroup(string name);                   
	ChannelGroup(string name, string description);
	~ChannelGroup();
	 
	void setGroupName(string name);         //����ͨ������
	void setGroupDescription(string description);
	void setGroupItems(list<Channel> items);
	string getGroupName();
	string getGroupDescription();
	void setExtraProperties(string key, string value);    //����ͨ����Ķ�������ֵ
	map<string, string> getExtraProperties();             //��ȡ���ж�������
	void addChannel(Channel channel);       //��ͨ�������һ��Channel
	list<Channel> getGroupItems();          //��ȡͨ�����е�����ͨ��
	

private:
	string group_name;                      //ͨ������
	string group_description;               //ͨ��������
	map<string, string> extra_properties;   //ͨ����Ķ�������
	list<Channel> group_items;              //ͨ�����е�Channels
};

//��Ӧһ��TDMS�����ļ�
class TDMSData
{

public:
	TDMSData(string filepath, string filename);
	~TDMSData();

	void setGroups(list<ChannelGroup> data);
	void addGroup(ChannelGroup group);                    //��tdms�ļ������һ��ͨ����
	list<ChannelGroup> getGroups();                       //��ȡ���е�ͨ����

	void setProperties(string key, string value);         //�����ļ�������ֵ
	string findDefaultProperty(string key);               //��ȡĬ�������е�item

	map<string, string> getExtraProperties();             //��ȡ���ж�������
	int read_tdms();                                      //��TDMS�ļ�
	int write_tdms();                                     //дTDMS�ļ�

private:
	string file_path;                                     //TDMS�ļ���·��
	string file_name;                                     //TDMS�ļ�������

	map<string, string> default_properties;               //�ļ���Ĭ������
	map<string, string> extra_properties;                 //�ļ��Ķ�������
	list<ChannelGroup>  groups;                           //ͨ����
};

