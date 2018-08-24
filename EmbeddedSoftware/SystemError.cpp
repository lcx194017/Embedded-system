#include "SystemError.h"

/************************************************************************/
/*Json�����ļ�ģ�������                                                */
/************************************************************************/
ConfigurationError::ConfigurationError()
{
}

ConfigurationError::~ConfigurationError()
{
}


/************************************************************************/
/* TDMS�����ļ���д������                                             */
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