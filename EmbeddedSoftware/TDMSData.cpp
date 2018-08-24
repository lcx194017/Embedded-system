#include "TDMSData.h"

Channel::Channel()
{
	//����Ĭ�����Գ�ʼֵ
	default_properties.insert(pair<string, string>("name", ""));
	default_properties.insert(pair<string, string>("description", ""));
	default_properties.insert(pair<string, string>("unit_string", ""));
	default_properties.insert(pair<string, string>("minimum", ""));
	default_properties.insert(pair<string, string>("maximum", ""));
}

Channel::Channel(string name, string description)
{
	//����Ĭ�����Գ�ʼֵ
	default_properties.insert(pair<string, string>("name", name));
	default_properties.insert(pair<string, string>("description", description));
	default_properties.insert(pair<string, string>("unit_string", ""));
	default_properties.insert(pair<string, string>("minimum", ""));
	default_properties.insert(pair<string, string>("maximum", ""));
}



Channel::~Channel()
{
	/*if (data_point)
		free(data_point);*/
}

//************************************
// Method:    setProperties
// FullName:  Channel::setProperties
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: string key
// Parameter: string value
// �������Ե�ʱ������Ĭ�����Լ����в��ң�������ҵ��޸�Ĭ�����Ե�ֵΪ�µ�value
// ������Բ���Ĭ�������У���key��Ϊ�գ�����Ϊ����������ӵ���������map��
//************************************
void Channel::setProperties(string key, string value)
{
	map<string, string>::iterator iter;
	iter = default_properties.find(key);
	if (iter != default_properties.end())        //���map�в�����Ҫ���õ�key���ǾͲ�������
		default_properties[key] = value;
	else
		if (key != "")
			extra_properties[key] = value;       //���������Ƕ�̬��չ�ģ�ֻҪkey��Ϊ�վͿ������
}

string Channel::findDefaultProperty(string key)
{
	map<string, string>::iterator iter;
	iter = default_properties.find(key);
	if (iter != default_properties.end())      //���map�в�����Ҫ���õ�key���ǾͲ�������
		return iter->second;
	else
		return "";                             //���ؿյ��ַ���
}

map<string, string> Channel::getExtraProperties()
{
	return extra_properties;
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
	group_description = "";
}

ChannelGroup::ChannelGroup(string name)
{
	group_name = name;
}

ChannelGroup::ChannelGroup(string name, string description)
{
	group_name = name;
	group_description = description;
}

ChannelGroup::~ChannelGroup()
{
}

void ChannelGroup::setGroupName(string name)
{
	group_name = name;
}

void ChannelGroup::setGroupDescription(string description)
{
	group_description = description;
}

void ChannelGroup::setGroupItems(list<Channel> items)
{
	group_items = items;
}

string ChannelGroup::getGroupName()
{
	return group_name;
}

string ChannelGroup::getGroupDescription()
{
	return group_description;
}

void ChannelGroup::setExtraProperties(string key, string value)
{
	if (key != "")
		extra_properties[key] = value;       //���������Ƕ�̬��չ�ģ�ֻҪkey��Ϊ�վͿ������
}

map<string, string> ChannelGroup::getExtraProperties()
{
	return extra_properties;
}

void ChannelGroup::addChannel(Channel channel)
{
	group_items.push_back(channel);
}

list<Channel> ChannelGroup::getGroupItems()
{
	return group_items;
}




TDMSData::TDMSData(string filepath, string filename)
{
	file_path = filepath;
	file_name = filename;

	//����Ĭ�����Գ�ʼֵ
	default_properties.insert(pair<string, string>("name", ""));
	default_properties.insert(pair<string, string>("description", ""));
	default_properties.insert(pair<string, string>("title", ""));
	default_properties.insert(pair<string, string>("author", ""));

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
// �������Ե�ʱ������Ĭ�����Լ����в��ң�������ҵ��޸�Ĭ�����Ե�ֵΪ�µ�value
// ������Բ���Ĭ�������У���key��Ϊ�գ�����Ϊ����������ӵ���������map��
//************************************
void TDMSData::setProperties(string key, string value)
{
	map<string, string>::iterator iter;
	iter = default_properties.find(key);
	if (iter != default_properties.end())        //���map�в�����Ҫ���õ�key���ǾͲ�������
		default_properties[key] = value;
	else
		if (key != "")
			extra_properties[key] = value;       //���������Ƕ�̬��չ�ģ�ֻҪkey��Ϊ�վͿ������
}

string TDMSData::findDefaultProperty(string key)
{
	map<string, string>::iterator iter;
	iter = default_properties.find(key);
	if (iter != default_properties.end())      //���map�в�����Ҫ���õ�key���ǾͲ�������
		return iter->second;
	else
		return "";                             //���ؿյ��ַ���
}

map<string, string> TDMSData::getExtraProperties()
{
	return extra_properties;
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
int TDMSData::read_tdms()
{
	int				ddcError = 0;
	unsigned int    length;
	DDCFileHandle	file = 0;
	char            *prop = 0;
	char			**properties = 0;
	unsigned int    numPropertyNames;

	unsigned int	numGroups;
	DDCChannelGroupHandle	*groups = 0;

	unsigned int	numChannels;
	unsigned __int64 numDataValues;
	DDCChannelHandle *channels = 0;
	double	*data = 0;

	map<string, string>::iterator iter;

	ddcChk(DDC_OpenFileEx((file_path + file_name).c_str(), DDC_FILE_TYPE_TDM_STREAMING, 1, &file));

	//��ȡ�ļ���������
	ddcChk(DDC_GetNumFileProperties(file, &numPropertyNames));
	//��ȡ�ļ���������������
	properties = (char**) malloc(numPropertyNames * sizeof(char*));
	ddcChk(DDC_GetFilePropertyNames(file, properties, numPropertyNames));

	//��ȡ�ļ����е�����ֵ
	//for (unsigned int k = 0; k < numPropertyNames; k++)
	for (unsigned int k = 0; k < 1; k++)
	{
		ddcChk(DDC_GetFileStringPropertyLength(file, properties[k], &length));
		nullChk(prop = (char *)malloc(sizeof(char) * (length + 1)));
		ddcChk(DDC_GetFileProperty(file, properties[k], prop, length + 1));
		string key(properties[k]);
		string value(prop);

		map<string, string>::iterator iter;
		iter = default_properties.find(key);
		if (iter != default_properties.end())        //���map�в�����Ҫ���õ�key���ǾͲ�������
			default_properties[key] = value;
		else
			if (key != "")
				extra_properties[key] = value;       //���������Ƕ�̬��չ�ģ�ֻҪkey��Ϊ�վͿ������

		free(prop);
		prop = 0;
	}
	free(properties);
	properties = 0;

	//��ȡͨ������Ϣ
	ddcChk(DDC_GetNumChannelGroups(file, &numGroups));
	nullChk(groups = (DDCChannelGroupHandle *)calloc(numGroups, sizeof(DDCChannelGroupHandle)));
	ddcChk(DDC_GetChannelGroups(file, groups, numGroups));

	for (unsigned int i = 0; i < numGroups; i++)
	{
		ChannelGroup channelGroup;

		//��ȡͨ�����������������
		ddcChk(DDC_GetNumChannelGroupProperties(groups[i], &numPropertyNames));
		properties = (char**)malloc(numPropertyNames * sizeof(char*));
		ddcChk(DDC_GetChannelGroupPropertyNames(groups[i], properties, numPropertyNames));

		//��ȡͨ�������е�����ֵ
		/*for (unsigned int k = 0; k < numPropertyNames; k++)*/
		for (unsigned int k = 0; k < 1; k++)
		{
			ddcChk(DDC_GetChannelGroupStringPropertyLength(groups[i], properties[k], &length));
			nullChk(prop = (char *)malloc(sizeof(char) * (length + 1)));

			ddcChk(DDC_GetChannelGroupProperty(groups[i], properties[k], prop, length + 1));
			string key(properties[k]);
			string value(prop);

			if (key == DDC_CHANNELGROUP_NAME)
				channelGroup.setGroupName(value);
			else if (key == DDC_CHANNELGROUP_DESCRIPTION)
				channelGroup.setGroupDescription(value);
			else
				if (key != "")
					channelGroup.setExtraProperties(key, value);

			free(prop);
			prop = 0;
		}
		free(properties);
		properties = 0;


		//��ȡͨ������ͨ��������
		ddcChk(DDC_GetNumChannels(groups[i], &numChannels));
		nullChk(channels = (DDCChannelHandle*)calloc(numChannels, sizeof(DDCChannelHandle)));
		ddcChk(DDC_GetChannels(groups[i], channels, numChannels));

		for (unsigned int j = 0; j < numChannels; j++)
		{
			Channel channel_item;   //���һ��ͨ�������Ժ����ݣ�Ȼ�����ͨ����

			//��ȡͨ����������������
			ddcChk(DDC_GetNumChannelProperties(channels[j], &numPropertyNames));
			properties = (char**)malloc(numPropertyNames * sizeof(char*));
			ddcChk(DDC_GetChannelPropertyNames(channels[j], properties, numPropertyNames));

			//for (unsigned int k = 0; k < numPropertyNames; k++)
			for (unsigned int k = 0; k < 1; k++)
			{
				ddcChk(DDC_GetChannelStringPropertyLength(channels[j], properties[k], &length));
				nullChk(prop = (char *)malloc(sizeof(char) * (length + 1)));
				ddcChk(DDC_GetChannelProperty(channels[j], properties[k], prop, length + 1));
				string key(properties[k]);
				string value(prop);
				channel_item.setProperties(key, value);

				free(prop);
				prop = 0;
			}
			free(properties);
			properties = 0;

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
	if (properties)
		free(properties);
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
int TDMSData::write_tdms()
{
	int						ddcError = 0;
	DDCFileHandle			file = 0;
	DDCChannelGroupHandle	group[GROUPS_MAX];
	DDCChannelHandle		channels[CHANNELS_MAX];
	int  groups_count = 0;
	int  channels_count = 0;

	map<string, string>::iterator iter;
	map<string, string> extra_properties;

	list<ChannelGroup>::iterator group_iter;   //ͨ���������

	list<Channel> channel_list;
	list<Channel>::iterator channel_iter;      //ͨ��������

	//����ļ����ڣ�ɾ��
	remove((file_path + file_name).c_str());

	//�����ļ������Ĭ������
	ddcChk(DDC_CreateFile((file_path + file_name).c_str(), DDC_FILE_TYPE_TDM_STREAMING,
		findDefaultProperty(DDC_FILE_NAME).c_str(),
		findDefaultProperty(DDC_FILE_DESCRIPTION).c_str(),
		findDefaultProperty(DDC_FILE_TITLE).c_str(),
		findDefaultProperty(DDC_FILE_AUTHOR).c_str(),
		&file));


	//�����ļ��Ķ�������
	extra_properties = getExtraProperties();
	for (iter = extra_properties.begin(); iter != extra_properties.end(); iter++)
	{
		ddcChk(DDC_CreateFileProperty(file, (iter->first).c_str(), DDC_String, (iter->second).c_str()));
	}

	//���ͨ����
	for (group_iter = groups.begin(); group_iter != groups.end(); group_iter++)
	{
		if (groups_count >= GROUPS_MAX)  return -1;             //����ֵ-1��ʾͨ���鲻����
		ddcChk(DDC_AddChannelGroup(file, (group_iter->getGroupName()).c_str(),
			(group_iter->getGroupDescription()).c_str(), &(group[groups_count])));


		//����ͨ����Ķ�������
		extra_properties = group_iter->getExtraProperties();
		for (iter = extra_properties.begin(); iter != extra_properties.end(); iter++)
		{
			ddcChk(DDC_CreateChannelGroupProperty(group[groups_count], (iter->first).c_str(),
				DDC_String, (iter->second).c_str()));
		}

		//���ͨ��
		channel_list = group_iter->getGroupItems();
		for (channel_iter = channel_list.begin(); channel_iter != channel_list.end(); channel_iter++)
		{
			if (channels_count >= CHANNELS_MAX)  return -2;     //����ֵ-2��ʾͨ��������

			//���ͨ��������Ĭ������
			ddcChk(DDC_AddChannel(group[groups_count], DDC_Double,
				(channel_iter->findDefaultProperty(DDC_CHANNEL_NAME)).c_str(),
				(channel_iter->findDefaultProperty(DDC_CHANNEL_DESCRIPTION)).c_str(),
				(channel_iter->findDefaultProperty(DDC_CHANNEL_UNIT_STRING)).c_str(),
				&channels[channels_count]));

			//����������������������û����
			/*ddcChk(DDC_SetChannelProperty(channels[channels_count], DDC_CHANNEL_MINIMUM,
			(channel_iter->findDefaultProperty(DDC_CHANNEL_MINIMUM)).c_str()
			));

			ddcChk(DDC_SetChannelProperty(channels[channels_count], DDC_CHANNEL_MAXIMUM,
			(channel_iter->findDefaultProperty(DDC_CHANNEL_MAXIMUM)).c_str()
			));*/

			//����ͨ���Ķ�������
			extra_properties = channel_iter->getExtraProperties();
			for (iter = extra_properties.begin(); iter != extra_properties.end(); iter++)
			{
				ddcChk(DDC_CreateChannelProperty(channels[channels_count],
					(iter->first).c_str(), DDC_String, (iter->second).c_str()));
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

