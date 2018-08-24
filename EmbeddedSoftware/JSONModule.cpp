#include "JSONModule.h"



JSONModule::JSONModule()
{
}


JSONModule::~JSONModule()
{
}

//************************************
// Method:    makeSystemInfoJson
// FullName:  makeSystemInfoJson
// Access:    public 
// Returns:   char*
// Qualifier:
// Parameter: SystemInfo parameter
// 将系统配置描述数据以Json格式写入文件
//************************************
char* JSONModule::makeSystemInfoJson(SystemInfo parameter)
{
	cJSON * pJsonRoot = NULL;

	pJsonRoot = cJSON_CreateObject();
	if (NULL == pJsonRoot)
		return NULL;

	cJSON_AddStringToObject(pJsonRoot, "siteID", parameter.siteID.c_str());
	cJSON_AddStringToObject(pJsonRoot, "siteName", parameter.siteName.c_str());
	cJSON_AddStringToObject(pJsonRoot, "siteCountry", parameter.siteCountry.c_str());
	cJSON_AddStringToObject(pJsonRoot, "siteProvince", parameter.siteProvince.c_str());
	cJSON_AddStringToObject(pJsonRoot, "siteCity", parameter.siteCity.c_str());
	cJSON_AddNumberToObject(pJsonRoot, "siteLongitude", parameter.siteLongitude);
	cJSON_AddNumberToObject(pJsonRoot, "siteLatitude", parameter.siteLatitude);
	cJSON_AddStringToObject(pJsonRoot, "siteTimeZone", parameter.siteTimeZone.c_str());
	cJSON_AddStringToObject(pJsonRoot, "plantName", parameter.plantName.c_str());
	cJSON_AddStringToObject(pJsonRoot, "plantNo", parameter.plantNo.c_str());
	cJSON_AddStringToObject(pJsonRoot, "equipmentName", parameter.equipmentName.c_str());
	cJSON_AddStringToObject(pJsonRoot, "equipmentNo", parameter.equipmentNo.c_str());
	cJSON_AddStringToObject(pJsonRoot, "dataWatchName", parameter.dataWatchName.c_str());
	cJSON_AddNumberToObject(pJsonRoot, "dataWachAddedDate", parameter.dataWachAddedDate);
	cJSON_AddStringToObject(pJsonRoot, "dataWatchAssetID", parameter.dataWatchAssetID.c_str());
	cJSON_AddStringToObject(pJsonRoot, "deviceType", parameter.deviceType.c_str());
	cJSON_AddStringToObject(pJsonRoot, "dataWachAddedBy", parameter.dataWachAddedBy.c_str());

	char * pJsonData = cJSON_Print(pJsonRoot);
	if (NULL == pJsonData)
	{
		cJSON_Delete(pJsonRoot);
		return NULL;
	}
	cJSON_Delete(pJsonRoot);
	return pJsonData;
}


//************************************
// Method:    makeChannelSettingsJson
// FullName:  makeChannelSettingsJson
// Access:    public 
// Returns:   char*
// Qualifier:
// Parameter: ChannelSettings parameter
//************************************
char* JSONModule::makeChannelSettingsJson(ChannelSettings parameter)
{
	cJSON * pJsonRoot = NULL;
	cJSON * startBrands_array = NULL;
	cJSON * stopBrands_array = NULL;

	pJsonRoot = cJSON_CreateObject();
	startBrands_array = cJSON_CreateArray();
	stopBrands_array = cJSON_CreateArray();

	if (NULL == pJsonRoot || NULL == startBrands_array || NULL == stopBrands_array)
		return NULL;

	cJSON_AddStringToObject(pJsonRoot, "equipmentNo", parameter.equipmentNo.c_str());
	cJSON_AddStringToObject(pJsonRoot, "channelId", parameter.channelId.c_str());
	cJSON_AddNumberToObject(pJsonRoot, "sensorModuleNo", parameter.sensorModuleNo);
	cJSON_AddNumberToObject(pJsonRoot, "sensorNo", parameter.sensorNo);
	cJSON_AddStringToObject(pJsonRoot, "sensorType", parameter.sensorType.c_str());
	cJSON_AddStringToObject(pJsonRoot, "channelName", parameter.channelName.c_str());
	cJSON_AddNumberToObject(pJsonRoot, "samplingRate", parameter.samplingRate);
	cJSON_AddNumberToObject(pJsonRoot, "sensorSensitivity", parameter.sensorSensitivity);
	cJSON_AddStringToObject(pJsonRoot, "sensorEngineeringUnit", parameter.sensorEngineeringUnit.c_str());
	cJSON_AddBoolToObject(pJsonRoot, "sensorRangeCheck", parameter.sensorRangeCheck);
	cJSON_AddNumberToObject(pJsonRoot, "sensorRangeMin", parameter.sensorRangeMin);
	cJSON_AddNumberToObject(pJsonRoot, "sensorRangeMax", parameter.sensorRangeMax);
	cJSON_AddNumberToObject(pJsonRoot, "sensor1xAmplitudeRunout", parameter.sensor1xAmplitudeRunout);
	cJSON_AddNumberToObject(pJsonRoot, "sensor1xPhaseRunout", parameter.sensor1xPhaseRunout);
	cJSON_AddNumberToObject(pJsonRoot, "sensorGapVoltage", parameter.sensorGapVoltage);
	cJSON_AddNumberToObject(pJsonRoot, "sensorLocationInDegree", parameter.sensorLocationInDegree);
	cJSON_AddStringToObject(pJsonRoot, "sensorLeftOrRight", parameter.sensorLeftOrRight.c_str());
	cJSON_AddStringToObject(pJsonRoot, "speedRefChannelId", parameter.speedRefChannelId.c_str());
	cJSON_AddNumberToObject(pJsonRoot, "rpmMultiplier", parameter.rpmMultiplier);
	cJSON_AddStringToObject(pJsonRoot, "pairChannelId", parameter.pairChannelId.c_str());
	cJSON_AddNumberToObject(pJsonRoot, "bearingClearance", parameter.bearingClearance);
	cJSON_AddStringToObject(pJsonRoot, "shaftRotationDirection", parameter.shaftRotationDirection.c_str());
	cJSON_AddStringToObject(pJsonRoot, "bearingStartPosition", parameter.bearingStartPosition.c_str());
	cJSON_AddBoolToObject(pJsonRoot, "sensorICP", parameter.sensorICP);
	cJSON_AddBoolToObject(pJsonRoot, "couplingACDC", parameter.couplingACDC);
	cJSON_AddNumberToObject(pJsonRoot, "zeroScalePosition", parameter.zeroScalePosition);
	cJSON_AddNumberToObject(pJsonRoot, "fullScalePosition", parameter.fullScalePosition);
	cJSON_AddBoolToObject(pJsonRoot, "tachAutoTach", parameter.tachAutoTach);
	cJSON_AddStringToObject(pJsonRoot, "tachTriggerEdge", parameter.tachTriggerEdge.c_str());
	cJSON_AddNumberToObject(pJsonRoot, "tachTriggerPerRev", parameter.tachTriggerPerRev);
	cJSON_AddNumberToObject(pJsonRoot, "tachTriggerHysteresis", parameter.tachTriggerHysteresis);
	cJSON_AddStringToObject(pJsonRoot, "tachTriggerVoltageLevel", parameter.tachTriggerVoltageLevel.c_str());
	cJSON_AddStringToObject(pJsonRoot, "thermalCoupleType", parameter.thermalCoupleType.c_str());
	cJSON_AddStringToObject(pJsonRoot, "userDefineProperty1", parameter.userDefineProperty1.c_str());
	cJSON_AddStringToObject(pJsonRoot, "userDefineProperty2", parameter.userDefineProperty2.c_str());
	cJSON_AddStringToObject(pJsonRoot, "userDefineProperty3", parameter.userDefineProperty3.c_str());
	cJSON_AddStringToObject(pJsonRoot, "userDefineProperty4", parameter.userDefineProperty4.c_str());
	cJSON_AddStringToObject(pJsonRoot, "userDefineProperty5", parameter.userDefineProperty5.c_str());
	cJSON_AddStringToObject(pJsonRoot, "userDefineProperty6", parameter.userDefineProperty6.c_str());
	cJSON_AddStringToObject(pJsonRoot, "comments", parameter.comments.c_str());
	cJSON_AddNumberToObject(pJsonRoot, "sensorConfigureDate", parameter.sensorConfigureDate);
	cJSON_AddStringToObject(pJsonRoot, "filter", parameter.filter.c_str());

	cJSON_AddItemToObject(pJsonRoot, "startBrands", startBrands_array);
	list<double>::iterator iter;
	for (iter = parameter.startBrands.begin(); iter != parameter.startBrands.end(); iter++)
	{
		cJSON_AddItemToArray(startBrands_array, cJSON_CreateNumber(*iter));
	}

	cJSON_AddItemToObject(pJsonRoot, "stopBrands", stopBrands_array);
	for (iter = parameter.stopBrands.begin(); iter != parameter.stopBrands.end(); iter++)
	{
		cJSON_AddItemToArray(stopBrands_array, cJSON_CreateNumber(*iter));
	}

	char * pJsonData = cJSON_Print(pJsonRoot);
	if (NULL == pJsonData)
	{
		//cJSON_Delete(startBrands_array);
		//cJSON_Delete(stopBrands_array);
		cJSON_Delete(pJsonRoot);
		return NULL;
	}
	//cJSON_Delete(startBrands_array);
	//cJSON_Delete(stopBrands_array);
	cJSON_Delete(pJsonRoot);
	return pJsonData;
}


//************************************
// Method:    makeTriggerSettingsJson
// FullName:  makeTriggerSettingsJson
// Access:    public 
// Returns:   char*
// Qualifier:
// Parameter: TriggerSettings parameter
//************************************
char* JSONModule::makeTriggerSettingsJson(TriggerSettings parameter)
{
	cJSON * pJsonRoot = NULL;

	pJsonRoot = cJSON_CreateObject();
	if (NULL == pJsonRoot)
		return NULL;

	cJSON_AddStringToObject(pJsonRoot, "triggerEventName", parameter.triggerEventName.c_str());
	cJSON_AddStringToObject(pJsonRoot, "triggeredChannelId", parameter.triggeredChannelId.c_str());
	cJSON_AddStringToObject(pJsonRoot, "triggeredChannelName", parameter.triggeredChannelName.c_str());
	cJSON_AddStringToObject(pJsonRoot, "triggerType", parameter.triggerType.c_str());
	cJSON_AddNumberToObject(pJsonRoot, "triggerValue", parameter.triggerValue);
	cJSON_AddStringToObject(pJsonRoot, "triggerNotification", parameter.triggerNotification.c_str());
	cJSON_AddNumberToObject(pJsonRoot, "preTriggerTime", parameter.preTriggerTime);
	cJSON_AddNumberToObject(pJsonRoot, "postTriggerTime", parameter.postTriggerTime);
	cJSON_AddBoolToObject(pJsonRoot, "triggerGatingOn", parameter.triggerGatingOn);
	cJSON_AddNumberToObject(pJsonRoot, "triggerGateLow", parameter.triggerGateLow);
	cJSON_AddNumberToObject(pJsonRoot, "triggerGateHigh", parameter.triggerGateHigh);
	cJSON_AddStringToObject(pJsonRoot, "gateOperator", parameter.gateOperator.c_str());
	cJSON_AddNumberToObject(pJsonRoot, "triggerConfigDate", parameter.triggerConfigDate);

	char * pJsonData = cJSON_Print(pJsonRoot);
	if (NULL == pJsonData)
	{
		cJSON_Delete(pJsonRoot);
		return NULL;
	}
	cJSON_Delete(pJsonRoot);
	return pJsonData;
}

/*************************************************
Function: makeparameterJson
Description: 将其它描述文件数据以Json格式写入文件
Input: parameter类型的数据
Return: Json数据指针
Others: 无
*************************************************/
char* JSONModule::makeSystemSettingsJson(SystemSettings parameter)
{
	cJSON * pJsonRoot = NULL;
	cJSON * alarmEmailList_array = NULL;

	pJsonRoot = cJSON_CreateObject();
	alarmEmailList_array = cJSON_CreateArray();

	if (NULL == pJsonRoot || NULL == alarmEmailList_array)
		return NULL;

	cJSON_AddStringToObject(pJsonRoot, "equipmentNo", parameter.equipmentNo.c_str());
	cJSON_AddNumberToObject(pJsonRoot, "scanPeriodFpga", parameter.scanPeriodFpga);
	cJSON_AddNumberToObject(pJsonRoot, "preTriggerBuffer", parameter.preTriggerBuffer);
	cJSON_AddNumberToObject(pJsonRoot, "writingPeriodPlc", parameter.writingPeriodPlc);

	cJSON_AddStringToObject(pJsonRoot, "plcIpAddress", parameter.plcIpAddress.c_str());
	cJSON_AddBoolToObject(pJsonRoot, "plcWritingOnOff", parameter.plcWritingOnOff);
	cJSON_AddNumberToObject(pJsonRoot, "writtingPeriodCloud", parameter.writtingPeriodCloud);
	cJSON_AddStringToObject(pJsonRoot, "cloudIpAddress", parameter.cloudIpAddress.c_str());
	cJSON_AddBoolToObject(pJsonRoot, "cloudWritingOnOff", parameter.cloudWritingOnOff);
	cJSON_AddStringToObject(pJsonRoot, "secondaryDataPath", parameter.secondaryDataPath.c_str());
	cJSON_AddNumberToObject(pJsonRoot, "writingPeriodLocalServer", parameter.writingPeriodLocalServer);
	cJSON_AddStringToObject(pJsonRoot, "localServerIpAddress", parameter.localServerIpAddress.c_str());
	cJSON_AddBoolToObject(pJsonRoot, "localServerWritingOnOff", parameter.localServerWritingOnOff);
	cJSON_AddStringToObject(pJsonRoot, "equipmentIpAddress", parameter.equipmentIpAddress.c_str());
	cJSON_AddStringToObject(pJsonRoot, "alarmEmailServerIP", parameter.alarmEmailServerIP.c_str());

	cJSON_AddItemToObject(pJsonRoot, "alarmEmailList", alarmEmailList_array);
	list<string>::iterator iter;
	for (iter = parameter.alarmEmailList.begin(); iter != parameter.alarmEmailList.end(); iter++)
	{
		cJSON_AddItemToArray(alarmEmailList_array, cJSON_CreateString((*iter).c_str()));
	}

	cJSON_AddNumberToObject(pJsonRoot, "lastConfigurationUpdated", parameter.lastConfigurationUpdated);


	char * pJsonData = cJSON_Print(pJsonRoot);
	if (NULL == pJsonData)
	{
		cJSON_Delete(pJsonRoot);
		//cJSON_Delete(alarmEmailList_array);
		return NULL;
	}
	cJSON_Delete(pJsonRoot);
	//cJSON_Delete(alarmEmailList_array);
	return pJsonData;
}


//************************************
// Method:    parseSystemInfoJson
// FullName:  parseSystemInfoJson
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: char * pMsg
// Parameter: SystemInfo * parameter
//************************************
bool JSONModule::parseSystemInfoJson(char * pMsg, SystemInfo *parameter)
{
	if (NULL == pMsg)
		return false;

	cJSON * pJson = cJSON_Parse(pMsg);
	if (NULL == pJson)
		return false;


	cJSON *item;
	bool readStatusFlag = false;

	item = cJSON_GetObjectItem(pJson, "siteID");
	if (item != NULL)
		parameter->siteID = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "siteName");
	if (item != NULL)
		parameter->siteName = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "siteCountry");
	if (item != NULL)
		parameter->siteCountry = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "siteProvince");
	if (item != NULL)
		parameter->siteProvince = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "siteCity");
	if (item != NULL)
		parameter->siteCity = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "siteLongitude");
	if (item != NULL)
		parameter->siteLongitude = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "siteLatitude");
	if (item != NULL)
		parameter->siteLatitude = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "siteTimeZone");
	if (item != NULL)
		parameter->siteTimeZone = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "plantName");
	if (item != NULL)
		parameter->plantName = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "plantNo");
	if (item != NULL)
		parameter->plantNo = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "equipmentName");
	if (item != NULL)
		parameter->equipmentName = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "equipmentNo");
	if (item != NULL)
		parameter->equipmentNo = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "dataWatchName");
	if (item != NULL)
		parameter->dataWatchName = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "dataWachAddedDate");
	if (item != NULL)
		parameter->dataWachAddedDate = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "dataWatchAssetID");
	if (item != NULL)
		parameter->dataWatchAssetID = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "deviceType");
	if (item != NULL)
		parameter->deviceType = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "dataWachAddedBy");
	if (item != NULL)
		parameter->dataWachAddedBy = item->valuestring;
	else
		goto Error;


	cJSON_Delete(pJson);
	readStatusFlag = true;
	return readStatusFlag;

Error:
	cJSON_Delete(pJson);
	return readStatusFlag;
}


//************************************
// Method:    parseChannelSettingsJson
// FullName:  parseChannelSettingsJson
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: char * pMsg
// Parameter: ChannelSettings * parameter
//************************************
bool JSONModule::parseChannelSettingsJson(char * pMsg, ChannelSettings *parameter)
{
	if (NULL == pMsg)
		return false;

	cJSON * pJson = cJSON_Parse(pMsg);
	if (NULL == pJson)
		return false;


	cJSON *item;
	cJSON *js_list;

	bool readStatusFlag = false;
	int array_size;

	item = cJSON_GetObjectItem(pJson, "equipmentNo");
	if (item != NULL)
		parameter->equipmentNo = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "channelId");
	if (item != NULL)
		parameter->channelId = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensorModuleNo");
	if (item != NULL)
		parameter->sensorModuleNo = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensorNo");
	if (item != NULL)
		parameter->sensorNo = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensorType");
	if (item != NULL)
		parameter->sensorType = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "channelName");
	if (item != NULL)
		parameter->channelName = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "samplingRate");
	if (item != NULL)
		parameter->samplingRate = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensorSensitivity");
	if (item != NULL)
		parameter->sensorSensitivity = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensorEngineeringUnit");
	if (item != NULL)
		parameter->sensorEngineeringUnit = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensorRangeCheck");
	if (item != NULL)
		parameter->sensorRangeCheck = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensorRangeMin");
	if (item != NULL)
		parameter->sensorRangeMin = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensorRangeMax");
	if (item != NULL)
		parameter->sensorRangeMax = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensor1xAmplitudeRunout");
	if (item != NULL)
		parameter->sensor1xAmplitudeRunout = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensor1xPhaseRunout");
	if (item != NULL)
		parameter->sensor1xPhaseRunout = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensorGapVoltage");
	if (item != NULL)
		parameter->sensorGapVoltage = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensorLocationInDegree");
	if (item != NULL)
		parameter->sensorLocationInDegree = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensorLeftOrRight");
	if (item != NULL)
		parameter->sensorLeftOrRight = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "shaftRotationDirection");
	if (item != NULL)
		parameter->shaftRotationDirection = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "speedRefChannelId");
	if (item != NULL)
		parameter->speedRefChannelId = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "rpmMultiplier");
	if (item != NULL)
		parameter->rpmMultiplier = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "pairChannelId");
	if (item != NULL)
		parameter->pairChannelId = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "bearingClearance");
	if (item != NULL)
		parameter->bearingClearance = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "bearingStartPosition");
	if (item != NULL)
		parameter->bearingStartPosition = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensorICP");
	if (item != NULL)
		parameter->sensorICP = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "couplingACDC");
	if (item != NULL)
		parameter->couplingACDC = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "zeroScalePosition");
	if (item != NULL)
		parameter->zeroScalePosition = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "fullScalePosition");
	if (item != NULL)
		parameter->fullScalePosition = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "tachAutoTach");
	if (item != NULL)
		parameter->tachAutoTach = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "tachTriggerEdge");
	if (item != NULL)
		parameter->tachTriggerEdge = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "tachTriggerPerRev");
	if (item != NULL)
		parameter->tachTriggerPerRev = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "tachTriggerHysteresis");
	if (item != NULL)
		parameter->tachTriggerHysteresis = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "tachTriggerVoltageLevel");
	if (item != NULL)
		parameter->tachTriggerVoltageLevel = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "thermalCoupleType");
	if (item != NULL)
		parameter->thermalCoupleType = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "userDefineProperty1");
	if (item != NULL)
		parameter->userDefineProperty1 = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "userDefineProperty2");
	if (item != NULL)
		parameter->userDefineProperty2 = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "userDefineProperty3");
	if (item != NULL)
		parameter->userDefineProperty3 = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "userDefineProperty4");
	if (item != NULL)
		parameter->userDefineProperty4 = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "userDefineProperty5");
	if (item != NULL)
		parameter->userDefineProperty5 = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "userDefineProperty6");
	if (item != NULL)
		parameter->userDefineProperty6 = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "comments");
	if (item != NULL)
		parameter->comments = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "sensorConfigureDate");
	if (item != NULL)
		parameter->sensorConfigureDate = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "filter");
	if (item != NULL)
		parameter->filter = item->valuestring;
	else
		goto Error;

	js_list = cJSON_GetObjectItem(pJson, "startBrands");
	if (js_list == NULL)
		goto Error;
	array_size = cJSON_GetArraySize(js_list);
	for (int i = 0; i < array_size; i++)
	{
		item = cJSON_GetArrayItem(js_list, i);
		if (item != NULL)
			parameter->startBrands.push_back(item->valuedouble);
		else
			goto Error;
	}

	js_list = cJSON_GetObjectItem(pJson, "stopBrands");
	if (js_list == NULL)
		goto Error;
	array_size = cJSON_GetArraySize(js_list);
	for (int i = 0; i < array_size; i++)
	{
		item = cJSON_GetArrayItem(js_list, i);
		if (item != NULL)
			parameter->stopBrands.push_back(item->valuedouble);
		else
			goto Error;
	}


	cJSON_Delete(pJson);
	readStatusFlag = true;
	return readStatusFlag;

Error:
	cJSON_Delete(pJson);
	return readStatusFlag;
}


//************************************
// Method:    parseTriggerSettingsJson
// FullName:  parseTriggerSettingsJson
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: char * pMsg
// Parameter: TriggerSettings * parameter
//************************************
bool JSONModule::parseTriggerSettingsJson(char * pMsg, TriggerSettings *parameter)
{
	if (NULL == pMsg)
		return false;

	cJSON * pJson = cJSON_Parse(pMsg);
	if (NULL == pJson)
		return false;


	cJSON *item;
	bool readStatusFlag = false;

	item = cJSON_GetObjectItem(pJson, "triggerEventName");
	if (item != NULL)
		parameter->triggerEventName = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "triggeredChannelId");
	if (item != NULL)
		parameter->triggeredChannelId = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "triggeredChannelName");
	if (item != NULL)
		parameter->triggeredChannelName = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "triggerType");
	if (item != NULL)
		parameter->triggerType = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "triggerValue");
	if (item != NULL)
		parameter->triggerValue = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "triggerNotification");
	if (item != NULL)
		parameter->triggerNotification = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "preTriggerTime");
	if (item != NULL)
		parameter->preTriggerTime = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "postTriggerTime");
	if (item != NULL)
		parameter->postTriggerTime = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "triggerGatingOn");
	if (item != NULL)
		parameter->triggerGatingOn = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "triggerGateLow");
	if (item != NULL)
		parameter->triggerGateLow = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "triggerGateHigh");
	if (item != NULL)
		parameter->triggerGateHigh = item->valuedouble;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "gateOperator");
	if (item != NULL)
		parameter->gateOperator = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "triggerConfigDate");
	if (item != NULL)
		parameter->triggerConfigDate = item->valueint;
	else
		goto Error;

	cJSON_Delete(pJson);
	readStatusFlag = true;
	return readStatusFlag;

Error:
	cJSON_Delete(pJson);
	return readStatusFlag;
}


//************************************
// Method:    parseSystemSettingsJson
// FullName:  parseSystemSettingsJson
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: char * pMsg
// Parameter: SystemSettings * parameter
//************************************
bool JSONModule::parseSystemSettingsJson(char * pMsg, SystemSettings *parameter)
{
	if (NULL == pMsg)
		return false;

	cJSON * pJson = cJSON_Parse(pMsg);
	if (NULL == pJson)
		return false;


	cJSON *item;
	cJSON *js_list;
	bool readStatusFlag = false;
	int array_size;

	item = cJSON_GetObjectItem(pJson, "equipmentNo");
	if (item != NULL)
		parameter->equipmentNo = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "scanPeriodFpga");
	if (item != NULL)
		parameter->scanPeriodFpga = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "preTriggerBuffer");
	if (item != NULL)
		parameter->preTriggerBuffer = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "writingPeriodPlc");
	if (item != NULL)
		parameter->writingPeriodPlc = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "plcIpAddress");
	if (item != NULL)
		parameter->plcIpAddress = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "plcWritingOnOff");
	if (item != NULL)
		parameter->plcWritingOnOff = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "writtingPeriodCloud");
	if (item != NULL)
		parameter->writtingPeriodCloud = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "cloudIpAddress");
	if (item != NULL)
		parameter->cloudIpAddress = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "cloudWritingOnOff");
	if (item != NULL)
		parameter->cloudWritingOnOff = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "secondaryDataPath");
	if (item != NULL)
		parameter->secondaryDataPath = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "writingPeriodLocalServer");
	if (item != NULL)
		parameter->writingPeriodLocalServer = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "localServerIpAddress");
	if (item != NULL)
		parameter->localServerIpAddress = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "localServerWritingOnOff");
	if (item != NULL)
		parameter->localServerWritingOnOff = item->valueint;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "equipmentIpAddress");
	if (item != NULL)
		parameter->equipmentIpAddress = item->valuestring;
	else
		goto Error;

	item = cJSON_GetObjectItem(pJson, "alarmEmailServerIP");
	if (item != NULL)
		parameter->alarmEmailServerIP = item->valuestring;
	else
		goto Error;

	js_list = cJSON_GetObjectItem(pJson, "alarmEmailList");
	if (js_list == NULL)
		goto Error;
	array_size = cJSON_GetArraySize(js_list);
	for (int i = 0; i < array_size; i++)
	{
		item = cJSON_GetArrayItem(js_list, i);
		if (item != NULL)
			parameter->alarmEmailList.push_back(item->valuestring);
		else
			goto Error;
	}

	item = cJSON_GetObjectItem(pJson, "lastConfigurationUpdated");
	if (item != NULL)
		parameter->lastConfigurationUpdated = item->valueint;
	else
		goto Error;

	cJSON_Delete(pJson);
	readStatusFlag = true;
	return readStatusFlag;

Error:
	cJSON_Delete(pJson);
	return readStatusFlag;
}

/*************************************************
Function: systemInfoCheck
Description: 检查数据的合法性，输入的数据或者从Json文件中读取的数据在使用前都需要进行合法性检查
Input: parameter类型的数据
Return: 1：数据符合规范  其他：数据不符合规范，并返回错误代码
Others: 无
*************************************************/
int JSONModule::systemInfoCheck(const SystemInfo & parameter)
{
	//if (0 == validFoldername(parameter.equipmentName.c_str()))
	if (0 == validFoldername("aaa"))
	{
		return SYSTEM_VALIDNAME;
	}
	return 1;
}

/*************************************************
Function: channelSettingsCheck
Description: 检查数据的合法性，输入的数据或者从Json文件中读取的数据在使用前都需要进行合法性检查
Input: parameter类型的数据
Return: 1：数据符合规范  其他：数据不符合规范，返回故障代码
Others: 无
*************************************************/
int JSONModule::channelSettingsCheck(const ChannelSettings & parameter)
{

	if (parameter.sensorSensitivity <= 0)
	{
		return CHANNEL_VALID_SENSORSENSITIVITY;
	}
	return 1;
}

/*************************************************
Function: triggerSettingsCheck
Description: 检查数据的合法性，输入的数据或者从Json文件中读取的数据在使用前都需要进行合法性检查
Input: parameter类型的数据
Return: 1：数据符合规范  0：数据不符合规范
Others: 无
*************************************************/
int JSONModule::triggerSettingsCheck(const TriggerSettings & parameter)
{
	return 1;
}

/*************************************************
Function: systemSettingsCheck
Description: 检查数据的合法性，输入的数据或者从Json文件中读取的数据在使用前都需要进行合法性检查
Input: parameter类型的数据
Return: 1：数据符合规范  0：数据不符合规范
Others: 无
*************************************************/
int JSONModule::systemSettingsCheck(const SystemSettings & parameter)
{
	return 1;
}


//************************************
// Method:    writeJsonDataToFile
// FullName:  JSONModule::writeJsonDataToFile
// Access:    public static 
// Returns:   int
// Qualifier:
// Parameter: const char * filename
// Parameter: void * data
// Parameter: JsonType type
// 返回值为0表示数据正常到Json文件，返回值-1表示打开文件失败，返回值为-2表示数据转化为json格式过程失败
// 返回值为其它值，表示数据校规则检查不通过，详细参考JSONModule.h宏定义
//************************************
int JSONModule::writeJsonDataToFile(const char* filename, void* data, JsonType type)
{

	FILE *file = NULL;   //文件资源定义
	SystemInfo *systemInfo = NULL;
	ChannelSettings *channelSettings = NULL;
	TriggerSettings *triggerSettings = NULL;
	SystemSettings *systemSettings = NULL;
	int rule_check_result;
	char *p = NULL;      //Json格式的字符串

	//打开文件
	fopen_s(&file, filename, "w");
	if (file == NULL)
		return -1;

	//根据传入参数的数据类型进行类型转换，并变换成Json字符串
	switch (type)
	{
	case SYSTEMINFO:
		systemInfo = (SystemInfo*)data;
		rule_check_result = systemInfoCheck(*systemInfo);
		if (1 != rule_check_result)
			return rule_check_result;             //规则检查不通过，直接退出
		p = makeSystemInfoJson(*systemInfo);
		if (NULL == p)                            //如果数据转成Json失败，直接退出
			return -2;
		break;
	case CHANNELSETTINGS:
		channelSettings = (ChannelSettings*)data;
		rule_check_result = channelSettingsCheck(*channelSettings);
		if (1 != rule_check_result)
			return rule_check_result;             //规则检查不通过，直接退出
		p = makeChannelSettingsJson(*channelSettings);
		if (NULL == p)                            //如果数据转成Json失败，直接退出
			return -2;
		break;
	case TRIGGERSETTINGS:
		triggerSettings = (TriggerSettings*)data;
		rule_check_result = triggerSettingsCheck(*triggerSettings);
		if (1 != rule_check_result)
			return rule_check_result;
		p = makeTriggerSettingsJson(*triggerSettings);
		if (NULL == p)
			return -2;
		break;
	case SYSTEMSETTINGS:
		systemSettings = (SystemSettings*)data;
		rule_check_result = systemSettingsCheck(*systemSettings);
		if (1 != rule_check_result)
			return rule_check_result;
		p = makeSystemSettingsJson(*systemSettings);
		if (NULL == p)
			return -2;
		break;
	default:
		break;
	}

	if (NULL != p)
	{
		fprintf_s(file, "%s", p);
		free(p);
	}

	fclose(file);
	
	return 0;

}

//************************************
// Method:    readJsonDataFromFile
// FullName:  JSONModule::readJsonDataFromFile
// Access:    public static 
// Returns:   int
// Qualifier:
// Parameter: const char * filename
// Parameter: void * data
// Parameter: JsonType type
// 返回值为0表示解析数据成功， -1表示读取文件失败， -2表示解析过程失败
//************************************
int JSONModule::readJsonDataFromFile(const char* filename, void* data, JsonType type)
{
	FILE *file = NULL;    //文件资源定义
	long len;             //从文件读取数据的长度
	char *content = NULL;
	bool parseFlag;       //数据解析结果
	SystemInfo *systemInfo = NULL;
	ChannelSettings * channelSettings = NULL;
	TriggerSettings * triggerSettings = NULL;
	SystemSettings * systemSettings = NULL;


	fopen_s(&file, filename, "r");
	if (NULL == file)
		return -1;
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	fseek(file, 0, SEEK_SET);
	content = (char*)malloc(len + 1);
	fread(content, 1, len, file);
	fclose(file);

	switch (type)
	{
	case SYSTEMINFO:
		systemInfo = (SystemInfo *) data;
		parseFlag = parseSystemInfoJson(content, systemInfo);
		if (!parseFlag)    //数据解析失败
			return -2;   
		break;
	case CHANNELSETTINGS:
		channelSettings = (ChannelSettings *)data;
		parseFlag = parseChannelSettingsJson(content, channelSettings);
		if (!parseFlag)    //数据解析失败
			return -2;
		break;
	case TRIGGERSETTINGS:
		triggerSettings = (TriggerSettings *)data;
		parseFlag = parseTriggerSettingsJson(content, triggerSettings);
		if (!parseFlag)    //数据解析失败
			return -2;
		break;
	case SYSTEMSETTINGS:
		systemSettings = (SystemSettings *)data;
		parseFlag = parseSystemSettingsJson(content, systemSettings);
		if (!parseFlag)    //数据解析失败
			return -2;
		break;
	default:
		break;
	}

	if (NULL != content)
		free(content);

	return 0;

}

