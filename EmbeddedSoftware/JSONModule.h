#pragma once
#include <string>
#include <list>
#include "cJSON.h"
using namespace std;

/*****************************************************************************
Copyright: Chaos
File name: JSONModule.h
Description: 系统四个配置文件的数据类型结构体定义
Author: lcx
Version: V1.1
Date: 2018/08/20
History: 在C的版本上重写
*****************************************************************************/



//系统描述文件数据定义
typedef struct
{
	string siteID;				    //Unique ID for each site
	string siteName;   			    //Controller site name
	string siteCountry;			    //Controller location country
	string siteProvince;			//province
	string siteCity;				//city
	double siteLongitude;		    //longitude
	double siteLatitude;			//latitude
	string siteTimeZone;
	string plantName;				//Unique plant number
	string plantNo;
	string equipmentName;		    //Equipment Description in the plant
	string equipmentNo;
	string dataWatchName;    		//DNS Name for the DataWatch
	long dataWachAddedDate;		    //Date of settings’ creation (Time Stamp)
	string dataWatchAssetID;		//Unique equipment Asset ID
	string deviceType;
	string dataWachAddedBy;		    //User who edited settings

}SystemInfo;

//通道描述文件数据定义
typedef struct
{
	string equipmentNo;
	string channelId;
	int sensorModuleNo; 			//The slot of the channel in the compact RIO(Valid value : between 1 and 8)  	
	int	sensorNo; 			        //The port of the channel on the module(Valid value : between 1 and 8)	
	string sensorType;			    //Tachometer.High speed channels : Proximeter, Accelerometer, Fast voltage; Low speed channels : Temperature, Pressure, Valve Position, Slow current, Slow voltage	
	string channelName;  			//Name of the Channel – recommend using naming convention in historian	
	int samplingRate;
	double sensorSensitivity;		//Sensitivity of the channel(mV / EU or mA / EU)	
	string sensorEngineeringUnit;	//Engineering Unit
	bool sensorRangeCheck;     		//Send out alarm if out of range ? (True or False)
	double sensorRangeMin;			//Minimum input value for the channel	
	double sensorRangeMax;			//Maximum input value for the channel	
	double sensor1xAmplitudeRunout;	//1 time amplitude runout	
	double sensor1xPhaseRunout;   	//1 time phase runout	
	double sensorGapVoltage;      	//Gap Voltage of the probe	
	int sensorLocationInDegree;	    //The location of the probe(usually 0°, 45°, 90°, 135°)
	string sensorLeftOrRight;	    //The location of the probe, as seen by looking from the compressor	
	string shaftRotationDirection;  //Clockwise(CW) or Counterclockwise(CCW)	
	string speedRefChannelId;       //Speed reference channel, if any	
	double rpmMultiplier;	        //The multiple to applied to a pseudo key phasor 	
	string pairChannelId;	        //Paired x - y channel, if any	
	double bearingClearance;	    //Bearing initial clearance	
	string bearingStartPosition;	//Bearing Start Position(Valid Values : Bottom(default), Center, Top) 
	bool sensorICP;					//Turn on or off ICP to supply power
	bool couplingACDC;          	//Valid Values : AC / DC	
	double zeroScalePosition;	    //Voltage corresponding to valve’s 0 position	
	double fullScalePosition;     	//Voltage corresponding to valve’s full position	
	bool tachAutoTach;				//True or False, to use Sound and Vibration tool kit to auto - tach	
	string tachTriggerEdge;	        //Rising or falling edge	
	int tachTriggerPerRev;	        //Tachmeter triggers per revolution	
	double tachTriggerHysteresis; 	//Hysteresis setting	
	string tachTriggerVoltageLevel;	//Trigger level in voltage	
	string thermalCoupleType;  	    //J, K, T, E, N, B, R, and S thermocouple types supported
	string userDefineProperty1;	    //User defined parameter 1 to pass to Player and Viewer	string
	string userDefineProperty2;
	string userDefineProperty3;
	string userDefineProperty4;
	string userDefineProperty5;
	string userDefineProperty6;
	string comments;
	long sensorConfigureDate;	    //Last setting change date	(Time Stamp)
	string filter;
	list<double> startBrands;       //start brands array
	list<double> stopBrands;        //stop brands array
}ChannelSettings;

//触发条件描述文件数据定义
typedef struct
{
	string triggerEventName;	        //Name of the trigger event	
	string triggeredChannelId;
	string triggeredChannelName;	    //Channel to be evaluated for the trigger event	
	string triggerType;       	        //Indicates the type of analysis that will be performed to determine if an event has occurred[Time Interval, Time of Day, Delta EU, Delta Speed, Level]
	double triggerValue;	            //Specifies the time(in minutes) for Time Interval or Time of Day trigger types
	string triggerNotification;         //[Alarm, Danger]
	int preTriggerTime;    	            //Time(in seconds) of pre - trigger data to record to file
	int postTriggerTime;	            //Time(in seconds) of post - trigger data to record to file	
	bool triggerGatingOn;	            //是否满足条件才触发？	
	double triggerGateLow;	            //Gating condition, low	
	double triggerGateHigh;	            //Gating condition, high	
	string gateOperator;       	        //Gating condition, > , <, > < , greater, less, greater and less than	
	long  triggerConfigDate;	        //Last setting change date

}TriggerSettings;

//其它配置文件数据定义
typedef struct
{
	string equipmentNo;
	int	scanPeriodFpga;     	    //Scan period(seconds)
	int	preTriggerBuffer;	        //Pre - trigger buffer length(seconds)
	int	writingPeriodPlc;	        //PLC update period for spurious vibration(seconds)
	string plcIpAddress;
	bool plcWritingOnOff;
	int writtingPeriodCloud;        //Update period to send data to Cloud database
	string cloudIpAddress;
	bool cloudWritingOnOff;
	string secondaryDataPath;       //Valid values are : “”, “none”, “usb”, and “hard drive”
	int writingPeriodLocalServer;
	string localServerIpAddress;
	bool localServerWritingOnOff;
	string equipmentIpAddress;
	string alarmEmailServerIP;
	list<string> alarmEmailList;    //email list
	long lastConfigurationUpdated;	//Last setting change date

}SystemSettings;

enum JsonType
{
	SYSTEMINFO, CHANNELSETTINGS, TRIGGERSETTINGS, SYSTEMSETTINGS
};

class JSONModule
{
public:
	JSONModule();
	~JSONModule();

	//************************************
	// Method:    writeJsonDataToFile
	// FullName:  JSONModule::writeJsonDataToFile
	// Access:    public static 
	// Returns:   int
	// Qualifier:
	// Parameter: const char * filename
	// Parameter: void * data
	// Parameter: int data_type
	//************************************
	static int writeJsonDataToFile(const char* filename, void* data, JsonType type);

	//************************************
	// Method:    readJsonDataFromFile
	// FullName:  JSONModule::readJsonDataFromFile
	// Access:    public static 
	// Returns:   int
	// Qualifier:
	// Parameter: const char * filename
	// Parameter: void * data
	// Parameter: int data_type
	//************************************
	static int readJsonDataFromFile(const char* filename, void* data, JsonType type);

	static int systemInfoCheck(const SystemInfo &parameter);                             //数据的规则检查
	static int channelSettingsCheck(const ChannelSettings &parameter);
	static int triggerSettingsCheck(const TriggerSettings &parameter);
	static int systemSettingsCheck(const SystemSettings &parameter);

private:
	static char* makeSystemInfoJson(SystemInfo parameter);                                //将数据转换为Json字符串
	static bool parseSystemInfoJson(char * pMsg, SystemInfo *parameter);                  //将Json字符串转换成定义的struct格式

	static char* makeChannelSettingsJson(ChannelSettings parameter);
	static bool parseChannelSettingsJson(char * pMsg, ChannelSettings *parameter);        

	static char* makeTriggerSettingsJson(TriggerSettings parameter);
	static bool parseTriggerSettingsJson(char * pMsg, TriggerSettings *parameter);        

	static char* makeSystemSettingsJson(SystemSettings parameter);
	static bool parseSystemSettingsJson(char * pMsg, SystemSettings *parameter);

};


int validFoldername(const char *pName);

//系统配置文件数据解析故障代码
#define SYSTEM_VALIDNAME 101;          //设备名称不合法


//通道配置文件数据解析故障代码
#define CHANNEL_VALID_SENSORSENSITIVITY 201;

//触发配置文件数据解析故障代码


//其他配置文件数据解析故障代码

