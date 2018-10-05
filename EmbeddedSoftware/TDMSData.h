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

//�洢TDMS�е�ʱ���
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

//TDMS�ļ��е�һ��ͨ��
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

//TDMS�ļ��е�һ��ͨ����
class ChannelGroup
{
public:
	ChannelGroup();
	ChannelGroup(string name);
	ChannelGroup(string name, string group_channel_type);
	~ChannelGroup();

	void setGroupName(string name);           //����ͨ������
	void setGroupChannelType(string group_channel_type);
	void setGroupItems(list<Channel> items);
	string getGroupName();
	string getGroupChannelType();
	void addChannel(Channel channel);         //��ͨ�������һ��Channel
	list<Channel> getGroupItems();            //��ȡͨ�����е�����ͨ��


private:
	string group_name;                        //ͨ������
	string channel_type;                      //ͨ������[ע��:�����ͨ������ָ��������ͨ�������ͣ���TDMS�ļ��е�һ��ͨ�����Ӧ]
	list<Channel> group_items;                //ͨ�����е�Channels
};

//��Ӧһ��TDMS�����ļ�
class TDMSData
{

public:
	TDMSData();
	~TDMSData();

	void setGroups(list<ChannelGroup> data);
	void addGroup(ChannelGroup group);                    //��tdms�ļ������һ��ͨ����
	list<ChannelGroup> getGroups();                       //��ȡ���е�ͨ����

	void setProperties(string key, string value);         //�����ļ�������ֵ
	string getPropertyVaule(string key);                  //��ȡĬ�������е�item
	map<string, string> getProperties();                  //��ȡ�ļ�����

	void set_property_name(string name);
	string get_property_name();

	int read_tdms(string file_path, string file_name);                                      //��TDMS�ļ�
	int write_tdms(string file_path, string file_name);   //дTDMS�ļ�

private:
	string property_name;                                 //FILE��name�ֶ�
	map<string, string> properties;                       //�ļ�Ĭ������

	list<ChannelGroup>  groups;                           //ͨ����
};

