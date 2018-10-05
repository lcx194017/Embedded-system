#include "TDMSData.h"

Channel::Channel()
{
}

Channel::Channel(string name)
{
	channel_name = name;
}



Channel::~Channel()
{
	/*if (data_point)
	free(data_point);*/
}

void Channel::setChannelName(string name)
{
	channel_name = name;
}

void Channel::set_wf_start_time(Timestamp start_time)
{
	wf_start_time = start_time;
}

void Channel::set_wf_start_offset(double start_offset)
{
	wf_start_offset = start_offset;
}

void Channel::set_wf_samples(int samples)
{
	wf_samples = samples;
}

void Channel::set_wf_increment(double increment)
{
	wf_increment = increment;
}

void Channel::set_NI_DataType(int DataType)
{
	NI_DataType = DataType;
}

void Channel::set_NI_ChannelLength(unsigned __int64 ChannelLength)
{
	NI_ChannelLength = ChannelLength;
}

string Channel::getChannelName()
{
	return channel_name;
}

Timestamp Channel::get_wf_start_time()
{
	return wf_start_time;
}

double Channel::get_wf_start_offset()
{
	return wf_start_offset;
}

int Channel::get_wf_samples()
{
	return wf_samples;
}

double Channel::get_wf_increment()
{
	return wf_increment;
}

int Channel::get_NI_DataType()
{
	return NI_DataType;
}

unsigned __int64 Channel::get_NI_ChannelLength()
{
	return NI_ChannelLength;
}


void Channel::setData(double* point, unsigned __int64 legth)
{
	data_point = point;
	data_length = legth;
}

double* Channel::getData()
{
	return data_point;
}

unsigned __int64 Channel::getDataLength()
{
	return data_length;
}



ChannelGroup::ChannelGroup()
{
	group_name = "";
}

ChannelGroup::ChannelGroup(string name)
{
	group_name = name;
}

ChannelGroup::ChannelGroup(string name, string group_channel_type)
{
	group_name = name;
	channel_type = group_channel_type;
}

ChannelGroup::~ChannelGroup()
{
}

void ChannelGroup::setGroupName(string name)
{
	group_name = name;
}

void ChannelGroup::setGroupChannelType(string group_channel_type)
{
	channel_type = group_channel_type;
}

void ChannelGroup::setGroupItems(list<Channel> items)
{
	group_items = items;
}

string ChannelGroup::getGroupName()
{
	return group_name;
}

string ChannelGroup::getGroupChannelType()
{
	return channel_type;
}

void ChannelGroup::addChannel(Channel channel)
{
	group_items.push_back(channel);
}

list<Channel> ChannelGroup::getGroupItems()
{
	return group_items;
}




TDMSData::TDMSData()
{
	//�������Գ�ʼֵ
	properties.insert(pair<string, string>("SystemInfo", ""));
	properties.insert(pair<string, string>("SystemSettings", ""));
	properties.insert(pair<string, string>("ChannelSettings", ""));
	properties.insert(pair<string, string>("TriggerSettings", ""));
	properties.insert(pair<string, string>("Version", ""));
}


TDMSData::~TDMSData()
{
}

void TDMSData::setGroups(list<ChannelGroup> data)
{
	groups = data;
}

void TDMSData::addGroup(ChannelGroup group)    //��tdms�ļ������һ��ͨ����
{
	groups.push_back(group);
}

list<ChannelGroup> TDMSData::getGroups()
{
	return groups;
}

//************************************
// Method:    setProperties
// FullName:  TDMSData::setProperties
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: string key
// Parameter: string value
// ���Ҫ���õ����Բ������ļ������ԣ���������
//************************************
void TDMSData::setProperties(string key, string value)
{
	if (key != "SystemInfo" && key != "SystemSettings" && key != "ChannelSettings" &&
		key != "TriggerSettings" && key != "Version")
		return;
	properties[key] = value;
}

string TDMSData::getPropertyVaule(string key)
{
	map<string, string>::iterator iter;
	iter = properties.find(key);
	if (iter != properties.end())      //���map�в�����Ҫ���õ�key���ǾͲ�������
		return iter->second;
	else
		return "";                     //���ؿյ��ַ���
}

map<string, string> TDMSData::getProperties()
{
	return properties;
}

void TDMSData::set_property_name(string name)
{
	property_name = name;
}
string TDMSData::get_property_name()
{
	return property_name;
}

//************************************
// Method:    read_tdms
// FullName:  TDMSData::read_tdms
// Access:    public 
// Returns:   int
// Qualifier:
// �������DDC������г��ִ���ֱ�ӷ���DDC�Ĵ������ͣ����󷵻�ֵ�������nilibddc.h
// ��ȡ�������£��ȴ��ļ���Ȼ���ȡ�ļ������ԣ�����ȡ����ͨ����
// (1)����ÿһ��ͨ���飬���Ȼ�ȡͨ����ĸ������ֶΣ�Ȼ���ȡͨ�����µ�����ͨ��     ��Ϊ��һ�����
// (2)����ÿһ��ͨ�������Ȼ�ȡͨ���ĸ������ֶΣ�Ȼ���ȡͨ����洢������           ��Ϊ�ڶ������
//************************************
int TDMSData::read_tdms(string file_path, string file_name)
{
	int				ddcError = 0;
	unsigned int    length;
	DDCFileHandle	file = 0;
	char            *prop = 0;

	unsigned int	numGroups;
	DDCChannelGroupHandle	*groups = 0;

	unsigned int	numChannels;
	unsigned __int64 numDataValues;
	DDCChannelHandle *channels = 0;
	double	*data = 0;

	map<string, string>::iterator iter;

	ddcChk(DDC_OpenFileEx((file_path + file_name).c_str(), DDC_FILE_TYPE_TDM_STREAMING, 1, &file));

	//��ȡ�ļ�����������
	ddcChk(DDC_GetFileStringPropertyLength(file, "name", &length));
	nullChk(prop = (char *)malloc(sizeof(char) * (length + 1)));
	ddcChk(DDC_GetFileProperty(file, "name", prop, length + 1));
	set_property_name(prop);
	free(prop);
	prop = 0;

	//��ȡ�ļ���汾����
	ddcChk(DDC_GetFileStringPropertyLength(file, "Version", &length));
	nullChk(prop = (char *)malloc(sizeof(char) * (length + 1)));
	ddcChk(DDC_GetFileProperty(file, "Version", prop, length + 1));
	setProperties("Version", prop);
	free(prop);
	prop = 0;

	//��ȡ�ļ���Json�ļ�����
	ddcChk(DDC_GetFileStringPropertyLength(file, "SystemInfo", &length));
	nullChk(prop = (char *)malloc(sizeof(char) * (length + 1)));
	ddcChk(DDC_GetFileProperty(file, "SystemInfo", prop, length + 1));
	setProperties("SystemInfo", prop);
	free(prop);
	prop = 0;

	ddcChk(DDC_GetFileStringPropertyLength(file, "SystemSettings", &length));
	nullChk(prop = (char *)malloc(sizeof(char) * (length + 1)));
	ddcChk(DDC_GetFileProperty(file, "SystemSettings", prop, length + 1));
	setProperties("SystemSettings", prop);
	free(prop);
	prop = 0;

	ddcChk(DDC_GetFileStringPropertyLength(file, "ChannelSettings", &length));
	nullChk(prop = (char *)malloc(sizeof(char) * (length + 1)));
	ddcChk(DDC_GetFileProperty(file, "ChannelSettings", prop, length + 1));
	setProperties("ChannelSettings", prop);
	free(prop);
	prop = 0;

	ddcChk(DDC_GetFileStringPropertyLength(file, "TriggerSettings", &length));
	nullChk(prop = (char *)malloc(sizeof(char) * (length + 1)));
	ddcChk(DDC_GetFileProperty(file, "TriggerSettings", prop, length + 1));
	setProperties("TriggerSettings", prop);
	free(prop);
	prop = 0;


	//��ȡͨ������Ϣ
	ddcChk(DDC_GetNumChannelGroups(file, &numGroups));
	nullChk(groups = (DDCChannelGroupHandle *)calloc(numGroups, sizeof(DDCChannelGroupHandle)));
	ddcChk(DDC_GetChannelGroups(file, groups, numGroups));

	for (unsigned int i = 0; i < numGroups; i++)
	{
		ChannelGroup channelGroup;

		//��ȡͨ������
		ddcChk(DDC_GetChannelGroupStringPropertyLength(groups[i], "name", &length));
		nullChk(prop = (char *)malloc(sizeof(char) * (length + 1)));
		ddcChk(DDC_GetChannelGroupProperty(groups[i], "name", prop, length + 1));
		channelGroup.setGroupName(prop);
		free(prop);
		prop = 0;

		ddcChk(DDC_GetChannelGroupStringPropertyLength(groups[i], "ChannelType", &length));
		nullChk(prop = (char *)malloc(sizeof(char) * (length + 1)));
		ddcChk(DDC_GetChannelGroupProperty(groups[i], "ChannelType", prop, length + 1));
		channelGroup.setGroupChannelType(prop);
		free(prop);
		prop = 0;


		//��ȡͨ������ͨ��������
		ddcChk(DDC_GetNumChannels(groups[i], &numChannels));
		nullChk(channels = (DDCChannelHandle*)calloc(numChannels, sizeof(DDCChannelHandle)));
		ddcChk(DDC_GetChannels(groups[i], channels, numChannels));

		for (unsigned int j = 0; j < numChannels; j++)
		{
			Channel channel_item;   //���һ��ͨ�������Ժ����ݣ�Ȼ�����ͨ����

									//��ȡͨ��������
			ddcChk(DDC_GetChannelStringPropertyLength(channels[j], "name", &length));
			nullChk(prop = (char *)malloc(sizeof(char) * (length + 1)));
			ddcChk(DDC_GetChannelProperty(channels[j], "name", prop, length + 1));
			string channel_name(prop);
			channel_item.setChannelName(channel_name);
			free(prop);
			prop = 0;

			DDCDataType dataType;
			ddcChk(DDC_GetDataType(channels[j], &dataType));
			channel_item.set_NI_DataType(dataType);

			unsigned __int64 channel_length;
			ddcChk(DDC_GetNumDataValues(channels[j], &channel_length));
			channel_item.set_NI_ChannelLength(channel_length);

			if (channel_name == "TimeWaveform")
			{
				Timestamp start_time;
				ddcChk(DDC_GetChannelPropertyTimestampComponents(channels[j], "wf_start_time",
					&start_time.year,
					&start_time.month,
					&start_time.day,
					&start_time.hour,
					&start_time.minute,
					&start_time.second,
					&start_time.milliSecond,
					&start_time.weekDay
				));
				channel_item.set_wf_start_time(start_time);

				int samples;
				ddcChk(DDC_GetChannelProperty(channels[j], "wf_samples", &samples, 4));
				channel_item.set_wf_samples(samples);

				double start_offset;
				ddcChk(DDC_GetChannelProperty(channels[j], "wf_start_offset", &start_offset, 8));
				channel_item.set_wf_start_offset(start_offset);

				double increment;
				ddcChk(DDC_GetChannelProperty(channels[j], "wf_increment", &increment, 8));
				channel_item.set_wf_increment(increment);
			}

			ddcChk(DDC_GetNumDataValues(channels[j], &numDataValues));
			nullChk(data = (double*)malloc(sizeof(double) * (unsigned int)numDataValues));
			ddcChk(DDC_GetDataValues(channels[j], 0, (unsigned int)numDataValues, data));

			channel_item.setData(data, numDataValues);
			data = 0;

			channelGroup.addChannel(channel_item);       //����һ��ͨ���󣬰�ͨ������ͨ����
		}

		addGroup(channelGroup);      //ÿ��ͨ�����������groups
	}


	if (data)
		free(data);
	if (channels)
		free(channels);
	if (groups)
		free(groups);
	if (file)
		DDC_CloseFile(file);
	if (prop)
		free(prop);
	return 0;

Error:
	if (data)
		free(data);
	if (channels)
		free(channels);
	if (groups)
		free(groups);
	if (file)
		DDC_CloseFile(file);
	if (prop)
		free(prop);
	return ddcError;
}

//************************************
// Method:    write_tdms
// FullName:  TDMSData::write_tdms
// Access:    public 
// Returns:   int
// Qualifier:
// �������ִ������������ֵΪ0�� 
// ���Ҫд��ͨ������������Ԥ�ȶ����ͨ���飨20����������-1
// ���Ҫд��ͨ����������Ԥ�ȶ����ͨ������200����������-2
// �������DDC������г��ִ���ֱ�ӷ���DDC�Ĵ������ͣ����󷵻�ֵ�������nilibddc.h
//************************************
int TDMSData::write_tdms(string file_path, string file_name)
{
	int						ddcError = 0;
	DDCFileHandle			file = 0;
	DDCChannelGroupHandle	group[GROUPS_MAX];
	DDCChannelHandle		channels[CHANNELS_MAX];
	int  groups_count = 0;
	int  channels_count = 0;

	map<string, string>::iterator iter;
	map<string, string> properties;

	list<ChannelGroup>::iterator group_iter;   //ͨ���������

	list<Channel> channel_list;
	list<Channel>::iterator channel_iter;      //ͨ��������

											   //����ļ����ڣ�ɾ��
	remove((file_path + file_name).c_str());

	//�����ļ������Ĭ������
	/*ddcChk(DDC_CreateFile((file_path + file_name).c_str(), DDC_FILE_TYPE_TDM_STREAMING,
	findDefaultProperty(DDC_FILE_NAME).c_str(),
	findDefaultProperty(DDC_FILE_DESCRIPTION).c_str(),
	findDefaultProperty(DDC_FILE_TITLE).c_str(),
	findDefaultProperty(DDC_FILE_AUTHOR).c_str(),
	&file));*/

	ddcChk(DDC_CreateFile((file_path + file_name).c_str(), DDC_FILE_TYPE_TDM_STREAMING,
		get_property_name().c_str(),
		NULL,
		NULL,
		NULL,
		&file));


	//�����ļ��Ķ�������
	properties = getProperties();
	for (iter = properties.begin(); iter != properties.end(); iter++)
	{
		ddcChk(DDC_CreateFileProperty(file, (iter->first).c_str(), DDC_String, (iter->second).c_str()));
	}

	//���ͨ����
	for (group_iter = groups.begin(); group_iter != groups.end(); group_iter++)
	{
		if (groups_count >= GROUPS_MAX)  return -1;             //����ֵ-1��ʾͨ���鲻����
		ddcChk(DDC_AddChannelGroup(file, (group_iter->getGroupName()).c_str(), NULL, &(group[groups_count])));

		//����ͨ�����ͨ����������
		ddcChk(DDC_CreateChannelGroupProperty(group[groups_count], "ChannelType", DDC_String, (group_iter->getGroupChannelType()).c_str()));

		//���ͨ��
		channel_list = group_iter->getGroupItems();
		for (channel_iter = channel_list.begin(); channel_iter != channel_list.end(); channel_iter++)
		{
			if (channels_count >= CHANNELS_MAX)  return -2;     //����ֵ-2��ʾͨ��������

																//���ͨ��������Ĭ������
			ddcChk(DDC_AddChannel(group[groups_count], DDC_Double,
				(channel_iter->getChannelName()).c_str(),
				NULL,
				NULL,
				&channels[channels_count]));

			if (channel_iter->getChannelName() == "TimeWaveform")
			{
				ddcChk(DDC_CreateChannelPropertyTimestampComponents(channels[channels_count], "wf_start_time",
					channel_iter->get_wf_start_time().year,
					channel_iter->get_wf_start_time().month,
					channel_iter->get_wf_start_time().day,
					channel_iter->get_wf_start_time().hour,
					channel_iter->get_wf_start_time().minute,
					channel_iter->get_wf_start_time().second,
					channel_iter->get_wf_start_time().milliSecond));

				ddcChk(DDC_CreateChannelProperty(channels[channels_count],
					"wf_start_offset", DDC_Double, channel_iter->get_wf_start_offset()));
				ddcChk(DDC_CreateChannelProperty(channels[channels_count],
					"wf_samples", DDC_Int32, channel_iter->get_wf_samples()));
				ddcChk(DDC_CreateChannelProperty(channels[channels_count],
					"wf_increment", DDC_Double, channel_iter->get_wf_increment()));
			}
			//��ͨ�����������
			ddcChk(DDC_SetDataValues(channels[channels_count],
				channel_iter->getData(), channel_iter->getDataLength()));

			channels_count++;
		}

		groups_count++;
	}

	//�����ļ�
	ddcChk(DDC_SaveFile(file));

	if (file)
		DDC_CloseFile(file);
	return 0;

Error:
	if (file)
		DDC_CloseFile(file);
	return ddcError;
}