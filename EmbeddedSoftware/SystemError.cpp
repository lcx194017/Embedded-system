#include "SystemError.h"

/************************************************************************/
/*Json�����ļ�ģ�������                                                */
/************************************************************************/
JsonConfigurationError::JsonConfigurationError()
{
}

JsonConfigurationError::~JsonConfigurationError()
{
}


/************************************************************************/
/* TDMS�����ļ���д������                                             */
/************************************************************************/
TDMSError::TDMSError()
{
}

TDMSError::~TDMSError()
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