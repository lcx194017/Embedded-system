#include <stdio.h>
#include <string.h>

/***************************************************************************
* Function Name: valiFoldername
* Description:  The ength of folder name should be less than 255.
*                      Illegal characters are \<>()[]&:,/|?* \0 ~ \31
* Return: 0 for success, otherwise 1.
****************************************************************************/
#define MAX_FOLDER_NAME_LEN 255

int validFoldername(const char *pName)
{
	int ret = 0;
	unsigned int u32Length = 0, u32Index = 0;
	const char u8SpecialChar[] = { '\\','<','>','(',')','[',']','&',':',',','/','|','?','*' };
	const unsigned char u8CtrlCharBegin = 0x0, u8CtrlCharEnd = 0x31;

	if (pName == NULL)
	{
		ret = 1;
	}
	else
	{
		u32Length = strlen(pName);
		if (u32Length >= MAX_FOLDER_NAME_LEN)
			ret = 1;
	}
	for (u32Index = 0; (u32Index < u32Length) && (ret == 0);
		u32Index++)
	{
		if (u8CtrlCharBegin <= pName[u32Index] <= u8CtrlCharEnd)
		{
			ret = 1;
		}
		else if (strchr(u8SpecialChar, pName[u32Index]) != NULL)
		{
			ret = 1;
		}
	}

	return ret;
}

