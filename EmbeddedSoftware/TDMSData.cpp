#include "TDMSData.h"

Channel::Channel()
{
	//设置默认属性初始值
	default_properties.insert(pair<string, string>("name", ""));
	default_properties.insert(pair<string, string>("description", ""));
	default_properties.insert(pair<string, string>("unit_string", ""));
	default_properties.insert(pair<string, string>("minimum", ""));
	default_properties.insert(pair<string, string>("maximum", ""));
}

Channel::Channel(string name, string description)
{
	//设置默认属性初始值
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
// 设置属性的时候，现在默认属性集合中查找，如果能找到修改默认属性的值为新的value
// 如果属性不在默认属性中，且key不为空，就作为额外属性添加到额外属性map中
//************************************
void Channel::setProperties(string key, string value)
{
	map<string, string>::iterator iter;
	iter = default_properties.find(key);
	if (iter != default_properties.end())        //如果map中不存在要设置的key，那就不做处理
		default_properties[key] = value;
	else
		if (key != "")
			extra_properties[key] = value;       //额外属性是动态拓展的，只要key不为空就可以添加
}

string Channel::findDefaultProperty(string key)
{
	map<string, string>::iterator iter;
	iter = default_properties.find(key);
	if (iter != default_properties.end())      //如果map中不存在要设置的key，那就不做处理
		return iter->second;
	else
		return "";                             //返回空的字符串
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
		extra_properties[key] = value;       //额外属性是动态拓展的，只要key不为空就可以添加
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

	//设置默认属性初始值
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

void TDMSData::addGroup(ChannelGroup group)    //往tdms文件中添加一个通道组
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
// 设置属性的时候，现在默认属性集合中查找，如果能找到修改默认属性的值为新的value
// 如果属性不在默认属性中，且key不为空，就作为额外属性添加到额外属性map中
//************************************
void TDMSData::setProperties(string key, string value)
{
	map<string, string>::iterator iter;
	iter = default_properties.find(key);
	if (iter != default_properties.end())        //如果map中不存在要设置的key，那就不做处理
		default_properties[key] = value;
	else
		if (key != "")
			extra_properties[key] = value;       //额外属性是动态拓展的，只要key不为空就可以添加
}

string TDMSData::findDefaultProperty(string key)
{
	map<string, string>::iterator iter;
	iter = default_properties.find(key);
	if (iter != default_properties.end())      //如果map中不存在要设置的key，那就不做处理
		return iter->second;
	else
		return "";                             //返回空的字符串
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
// 如果调用DDC库过程中出现错误，直接返回DDC的错误类型，错误返回值定义详见nilibddc.h
// 读取流程如下：先打开文件，然后读取文件的属性，并获取所有通道组
// (1)对于每一个通道组，首先获取通道组的各属性字段，然后获取通达组下的所有通道     此为第一层遍历
// (2)对于每一个通道，首先获取通道的各属性字段，然后获取通道里存储的数据           此为第二层遍历
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

	//获取文件属性数量
	ddcChk(DDC_GetNumFileProperties(file, &numPropertyNames));
	//获取文件的所有属性名称
	properties = (char**) malloc(numPropertyNames * sizeof(char*));
	ddcChk(DDC_GetFilePropertyNames(file, properties, numPropertyNames));

	//读取文件所有的属性值
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
		if (iter != default_properties.end())        //如果map中不存在要设置的key，那就不做处理
			default_properties[key] = value;
		else
			if (key != "")
				extra_properties[key] = value;       //额外属性是动态拓展的，只要key不为空就可以添加

		free(prop);
		prop = 0;
	}
	free(properties);
	properties = 0;

	//读取通道组信息
	ddcChk(DDC_GetNumChannelGroups(file, &numGroups));
	nullChk(groups = (DDCChannelGroupHandle *)calloc(numGroups, sizeof(DDCChannelGroupHandle)));
	ddcChk(DDC_GetChannelGroups(file, groups, numGroups));

	for (unsigned int i = 0; i < numGroups; i++)
	{
		ChannelGroup channelGroup;

		//获取通道组的所有属性名称
		ddcChk(DDC_GetNumChannelGroupProperties(groups[i], &numPropertyNames));
		properties = (char**)malloc(numPropertyNames * sizeof(char*));
		ddcChk(DDC_GetChannelGroupPropertyNames(groups[i], properties, numPropertyNames));

		//读取通道组所有的属性值
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


		//获取通道组中通道的数量
		ddcChk(DDC_GetNumChannels(groups[i], &numChannels));
		nullChk(channels = (DDCChannelHandle*)calloc(numChannels, sizeof(DDCChannelHandle)));
		ddcChk(DDC_GetChannels(groups[i], channels, numChannels));

		for (unsigned int j = 0; j < numChannels; j++)
		{
			Channel channel_item;   //存放一条通道的属性和数据，然后加入通道组

			//获取通道的所有属性名称
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

			channelGroup.addChannel(channel_item);       //读完一个通道后，把通道加入通道组
		}

		addGroup(channelGroup);      //每个通道组读完后加入groups
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
// 如果函数执行正常，返回值为0。 
// 如果要写的通道组数超过了预先定义的通道组（20个），返回-1
// 如果要写的通道数超过了预先定义的通道数（200个），返回-2
// 如果调用DDC库过程中出现错误，直接返回DDC的错误类型，错误返回值定义详见nilibddc.h
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

	list<ChannelGroup>::iterator group_iter;   //通道组迭代器

	list<Channel> channel_list;
	list<Channel>::iterator channel_iter;      //通道迭代器

	//如果文件存在，删除
	remove((file_path + file_name).c_str());

	//创建文件并添加默认属性
	ddcChk(DDC_CreateFile((file_path + file_name).c_str(), DDC_FILE_TYPE_TDM_STREAMING,
		findDefaultProperty(DDC_FILE_NAME).c_str(),
		findDefaultProperty(DDC_FILE_DESCRIPTION).c_str(),
		findDefaultProperty(DDC_FILE_TITLE).c_str(),
		findDefaultProperty(DDC_FILE_AUTHOR).c_str(),
		&file));


	//创建文件的额外属性
	extra_properties = getExtraProperties();
	for (iter = extra_properties.begin(); iter != extra_properties.end(); iter++)
	{
		ddcChk(DDC_CreateFileProperty(file, (iter->first).c_str(), DDC_String, (iter->second).c_str()));
	}

	//添加通道组
	for (group_iter = groups.begin(); group_iter != groups.end(); group_iter++)
	{
		if (groups_count >= GROUPS_MAX)  return -1;             //返回值-1表示通道组不够用
		ddcChk(DDC_AddChannelGroup(file, (group_iter->getGroupName()).c_str(),
			(group_iter->getGroupDescription()).c_str(), &(group[groups_count])));


		//创建通道组的额外属性
		extra_properties = group_iter->getExtraProperties();
		for (iter = extra_properties.begin(); iter != extra_properties.end(); iter++)
		{
			ddcChk(DDC_CreateChannelGroupProperty(group[groups_count], (iter->first).c_str(),
				DDC_String, (iter->second).c_str()));
		}

		//添加通道
		channel_list = group_iter->getGroupItems();
		for (channel_iter = channel_list.begin(); channel_iter != channel_list.end(); channel_iter++)
		{
			if (channels_count >= CHANNELS_MAX)  return -2;     //返回值-2表示通道不够用

			//添加通道并设置默认属性
			ddcChk(DDC_AddChannel(group[groups_count], DDC_Double,
				(channel_iter->findDefaultProperty(DDC_CHANNEL_NAME)).c_str(),
				(channel_iter->findDefaultProperty(DDC_CHANNEL_DESCRIPTION)).c_str(),
				(channel_iter->findDefaultProperty(DDC_CHANNEL_UNIT_STRING)).c_str(),
				&channels[channels_count]));

			//下面这两个属性设置现在没有用
			/*ddcChk(DDC_SetChannelProperty(channels[channels_count], DDC_CHANNEL_MINIMUM,
			(channel_iter->findDefaultProperty(DDC_CHANNEL_MINIMUM)).c_str()
			));

			ddcChk(DDC_SetChannelProperty(channels[channels_count], DDC_CHANNEL_MAXIMUM,
			(channel_iter->findDefaultProperty(DDC_CHANNEL_MAXIMUM)).c_str()
			));*/

			//创建通道的额外属性
			extra_properties = channel_iter->getExtraProperties();
			for (iter = extra_properties.begin(); iter != extra_properties.end(); iter++)
			{
				ddcChk(DDC_CreateChannelProperty(channels[channels_count],
					(iter->first).c_str(), DDC_String, (iter->second).c_str()));
			}

			//往通道中添加数据
			ddcChk(DDC_SetDataValues(channels[channels_count],
				channel_iter->getData(), channel_iter->getDataLength()));

			channels_count++;
		}

		groups_count++;
	}

	//保存文件
	ddcChk(DDC_SaveFile(file));

	if (file)
		DDC_CloseFile(file);
	return 0;

Error:
	if (file)
		DDC_CloseFile(file);
	return ddcError;
}

