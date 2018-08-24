#include "SystemError.h"

/************************************************************************/
/*Json配置文件模块错误定义                                                */
/************************************************************************/
ConfigurationError::ConfigurationError()
{
}

ConfigurationError::~ConfigurationError()
{
}


/************************************************************************/
/* TDMS数据文件读写错误定义                                             */
/************************************************************************/
DataFileError::DataFileError()
{
}

DataFileError::~DataFileError()
{

}


SystemError::SystemError()
{
}


SystemError::~SystemError()
{
}



bool CustomError:: operator < (const CustomError &a) const
{
	return error_priority < a.error_priority;
}

ErrorSubmoduleType CustomError::getErrorSubmoduleType()
{
	return error_type;
}
ErrorDesc CustomError::getErrorDesc()
{
	return error_desc;
}
ErrorPriority CustomError::getErrorPriority()
{
	return error_priority;
}