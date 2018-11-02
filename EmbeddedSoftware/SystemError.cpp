#include "SystemError.h"

/************************************************************************/
/*Json配置文件模块错误定义                                                */
/************************************************************************/
JsonConfigurationError::JsonConfigurationError()
{
}

JsonConfigurationError::~JsonConfigurationError()
{
}


/************************************************************************/
/* TDMS数据文件读写错误定义                                             */
/************************************************************************/
TDMSError::TDMSError()
{
}

TDMSError::~TDMSError()
{

}


/************************************************************************/
/* 文件传输模块错误定义                                                 */
/************************************************************************/
FileTransferError::FileTransferError()
{
}

FileTransferError::~FileTransferError()
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